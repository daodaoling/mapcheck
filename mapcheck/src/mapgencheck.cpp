#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <ros/ros.h>
#include <list>
#include <rosbag/view.h>
#include </usr/include/jsoncpp/json/json.h>
#include <gtest/gtest.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <boost/foreach.hpp>
#include "GPFPD.h"
#include "rslidar_msgs/rslidarPacket.h"
#include "rslidarScan.h"
#include "sensor_msgs/Imu.h";
#include  "tf2_msgs/TFMessage.h";
#include <assert.h>
#include <cstdlib>
#include <fstream>  
#include <ctime>
#include <cstdio>
#include </usr/include/mysql/mysql.h>
#pragma comment(lib,"libmySQL.lib")  //要加不然会编译出错
#include "stdio.h"
#include "string.h"
#include<iostream>
#include<typeinfo>
#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h> 
#include<mapconfig.h>
#include<httprequest.h>
#include<util.h>
#include<writelog.h>

using namespace std;

struct conn_info {
	char *host;
	char *user;
	char *password;
	char *db;
};

class Mysql
{
public:
/********************************连接数据库*****************************************************/
	MYSQL* mysql_connect(conn_info con){
		MYSQL* mysql=mysql_init(NULL);//mysql初始化函数，实例化一个新的对象（NULL为新的对象，否则为初始化以创建的对象)
		if(!mysql_real_connect(mysql,con.host,con.user,con.password,con.db,3306,NULL,0)){//mysql_real_connect(MYSQL *mysql,const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
			//上面的函数为，与mysql进行连接
			cout<<"connection error";
			WriteLog::write_log_map("mysql connection error !");
			exit(1);
		}else{
			cout<<"connection success !";
			WriteLog::write_log_map("mysql connection success !");
		}
		return mysql;//返回实例化的对象
	}
 
/****************************************数据库操作函数*******************************************************/
	void mysql_operation(MYSQL* mysql,char *sql_op)
	{
		if(mysql_query(mysql,sql_op))//mysql_query()函数为对mysql进行操作，第一个参数为刚才实例化的对象，第二个位需要进行的操作
		{ 
			printf("MySQL query error : %s/n", mysql_error(mysql));  //需要加上这个，因为这个是操作失败时返回显示
			getchar();
		 	exit(1);
		}	
	}
 
/*******************************查询函数***********************************************************/
	MYSQL_RES* mysql_find(MYSQL* mysql,const char *table,MYSQL_RES* res){
		char cmd[100];
		strcpy(cmd,"select * from ");
		strcat(cmd,table);		//拼接函数
 
		cout<<cmd<<endl;
 
		mysql_free_result(res);
		mysql_operation(mysql,cmd);
		return mysql_store_result(mysql);//查询的结果,用mysql_store_result函数后接mysql_affected_rows()可以返回查询次数，而用mysql_use_result()则不行
	}
/*******************************查询函数***********************************************************/
	MYSQL_RES* mysql_update(MYSQL* mysql,MYSQL_RES* res,const char *id){
		char cmd[100];
		strcpy(cmd,"update queue set queue_status=0 where id= ");
		strcat(cmd,id);		//拼接函数
 
		cout<<cmd<<endl;
 
		//mysql_free_result(res);
		mysql_operation(mysql,cmd);
		return mysql_store_result(mysql);//查询的结果,用mysql_store_result函数后接mysql_affected_rows()可以返回查询次数，而用mysql_use_result()则不行
	}

/*******************************************************************************************************************/
	void mysql_get_run(MYSQL* conn ,MYSQL_RES* res,Mysql mysql)//用于存储查询返回的数据，但这个数据还不能显示，需要进行转换
	{
		MYSQL_ROW row;
		
		string url = MapConfig::mapgencheck_url;

		while (( row = mysql_fetch_row(res) ) != NULL)//	row = mysql_fetch_row(res);进行数据的转换,需要循环转换，具体看程序最后的解释
		{
			//cout<<row[4]<<endl;
			WriteLog::write_log_map("Get the queue_status from db "+std::string(row[4]));
			if( strcmp(row[4],"1") == 0){
				
				char *cmd_base = "roslaunch ";

				std::string const& cmd_str = std::string(cmd_base) + std::string(row[3]);
				char const *cmd = cmd_str.c_str();
				
				WriteLog::write_log_map(boost::lexical_cast<string>(cmd));
				long start_time = Util::get_current_time()/1000;
				int re=system(cmd);
				int sys_result = Util::check_map_generate(row[3],start_time);

				string file_id = row[1];
				string task_id = row[2];

				string param = "&file_id="+file_id+"&task_id="+task_id;
				std::cout<<param<<endl;

				mysql_update(conn,res,row[0]);

				if(re!=0||sys_result!=2){
					param = param + "&checked=0";
					std::cout<<"re!=0||sys_result!=2"<<endl;
					WriteLog::write_log_map("map generate failed !re:"+boost::lexical_cast<string>(re)+"sys_result:"+boost::lexical_cast<string>(sys_result));
					HttpRequest::send_post(url,param);
				}else{
					param = param + "&checked=1";
					std::cout<<"else"<<endl;
					HttpRequest::send_post(url,param);	
				}
				//std::cout<<"sys_result:"<<sys_result<<endl;
				//std::cout<<"re:"<<re<<endl;
				res = mysql.mysql_find(conn,"queue",res);//进行操作，此处为查询数据库名为mysql中的test表格数据
				
				row = mysql_fetch_row(res);
			}
		 	
		}
		WriteLog::write_log_map("step out of loop !");
				
	}

};


int main(){
	
	MapConfig *mc;
	
	int re = system("killall -9 rosmaster");//kill all the node first 
	WriteLog::write_log_map("system kill all the rosnode result :"+boost::lexical_cast<string>(re));
	
	MYSQL* conn;//用于实例化的新的对象
	MYSQL_RES* res;//用于存储查询返回的数据，但这个数据还不能显示，需要进行转换
	//MYSQL_ROW row;//这个是转换完的数据，可以进行显示
	
	struct conn_info info;
	Mysql mysql;
	
	res = NULL;//要先初始化，否则会报错
 
	info.host = mc->host;
	info.user = mc->user;
	info.password = mc->password;
	info.db = mc->db;//我的数据库名字
	
	WriteLog::write_log_map(info.host);
	WriteLog::write_log_map(info.user);
	WriteLog::write_log_map(info.password);
	WriteLog::write_log_map(info.db);
	conn = mysql.mysql_connect(info); //初始化，包括创建对象和连接mysql

	res = mysql.mysql_find(conn,"queue",res);//进行操作，此处为查询数据库名为mysql中的test表格数据

	mysql.mysql_get_run(conn,res,mysql);

	mysql_free_result(res);
	mysql_close(conn);

	return 0;
}
