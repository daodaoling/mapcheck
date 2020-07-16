
#ifndef UTIL_H
#define UTIL_H
#include<time.h>
#include<stdio.h>
#include<sys/time.h> 
#include<sys/types.h>
#include<mapconfig.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include<writelog.h>

using namespace std;
class Util{
    public :
        static int64_t get_current_time();
        static int check_map_generate(string s,long start_time);
        static void delete_last_enter(string &strs);

};

int64_t Util::get_current_time()      //直接调用这个函数就行了，返回值最好是int64_t，long long应该也可以
{    
    struct timeval tv;    
    gettimeofday(&tv,NULL);    //该函数在sys/time.h头文件中
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}  
void Util::delete_last_enter(string &strs)
{
      if( !strs.empty() )
      {
          strs.erase(strs.find_last_not_of("\n") + 1);
      }
  
}
int Util::check_map_generate(string s,long start_time)
{

    //std::cout<<"nowTime: "<<Util::get_current_time()/1000<<"\n"; 
    
    //string s = "/var/www/html/maptoolapi/uploads/file_material/20200711/7441622555f0989cca412c5076875898/set_arg_and_run_159446066371283457cd441ec1.launch";
    vector<string> vStr;
    boost::split( vStr, s, boost::is_any_of( "/" ), boost::token_compress_on );
    string strs;
    string str_last;

    for( vector<string>::iterator it = vStr.begin(); it != vStr.end(); ++ it ){
        str_last = *it;
    }
    //std::cout<<"last:"<<str_last<<endl;

    string base = s.substr(0,s.length()-str_last.length());
    //std::cout<<"base:"<<s.substr(0,s.length()-str_last.length())<<endl;

    vector<string> vStr2;
    boost::split( vStr2, str_last, boost::is_any_of( "." ), boost::token_compress_on );
    //string strs2;
    vector<string>::iterator it0 = vStr2.begin();
    //cout<<"it0:"<<*it0<<endl;

    string last_folder = *it0;
    vector<string> vStr_last;
    boost::split( vStr_last, last_folder, boost::is_any_of( "_" ), boost::token_compress_on );
    string str_launch;

    for( vector<string>::iterator it = vStr_last.begin(); it != vStr_last.end(); ++ it ){
        last_folder = *it;
    }    

    //std::cout<<"last_folder:"<<last_folder<<endl;
    base = base + last_folder + "/";
    //std::cout<<"base:"<<base<<endl;
    string path_svg = base + "path.svg";
    string map_info_yaml = base + "map_info.yaml";
    string syntheticMap_png = base + "syntheticMap.png";
    string syntheticMap_yaml = base + "syntheticMap.yaml";
    //std::cout<<"path_svg:"<<path_svg<<endl;


    //std::cout<<"nowTime: "<<Util::get_current_time()/1000<<"\n"; 
    struct stat buf1;
    struct stat buf2;
    struct stat buf3;
    struct stat buf4;
    //int result;
    //获得文件状态信息
    //path_svg = "/home/pengzhao/Desktop/for_peng_zhao.txt";
    int result1 =stat(path_svg.c_str(), &buf1 );
    int result2 =stat(map_info_yaml.c_str(), &buf2 );
    int result3 =stat(syntheticMap_png.c_str(), &buf3 );
    int result4 =stat(syntheticMap_yaml.c_str(), &buf4 );
    if(result1||result2||result3||result4){
        WriteLog::write_log_map("Some file are not found !");
        return 1;
    }

    //cout<<"文件创建时间:"<<ctime(&buf.st_ctime);
    //cout<<"访问日期:"<<ctime(&buf.st_atime);//注意这里访问时间为00:00:00为正常
    //cout<<"最后修改日期:"<<ctime(&buf.st_mtime);
    //cout<<buf.st_mtime<<endl;
    long last_modify_time1 = buf1.st_mtime;
    long last_modify_time2 = buf2.st_mtime;
    long last_modify_time3 = buf3.st_mtime;
    long last_modify_time4 = buf4.st_mtime;
    int time1 = (start_time < last_modify_time1); //
    int time2 = (start_time < last_modify_time2);
    int time3 = (start_time < last_modify_time3);
    int time4 = (start_time < last_modify_time4);
    //all the 
    if(time1==0||time2==0||time3==0||time4==0){
        WriteLog::write_log_map("Some file are not the new generated !");
        return 0;
    }
    //std::cout<<"last_modify_time:"<<last_modify_time1<<endl;
    //std::cout<<"nowTime: "<<Util::get_current_time()/1000<<"\n"; 
    WriteLog::write_log_map("New file generated correctly !");
    return 2;
}
#endif
