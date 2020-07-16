#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curl.h>
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
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#define foreach BOOST_FOREACH
#include <iostream>
#include<string>
#include<vector>
#include<httprequest.h>
#include<writelog.h>
#include<util.h>
using namespace std;

int main (int argc, char** argv)
{   
    string url = MapConfig::rosbagcheck_url;
    std::string reason="The file path is not right !";
    std::string rosbag_path;
    std::string rosbag_num;

    ros::init(argc, argv, "param_test");

    if(argc > 1)
    {
        for(int i = 0; i<argc; i++)
        {
            if(i == 1){
                rosbag_path = argv[i];
            }
            if(i == 2){
                rosbag_num = argv[i];
            }
            if(i == 3){
                rosbag_num = argv[i];                
            }

        }
    }
    string file_id = rosbag_num;
    std::fstream _file;
    _file.open(rosbag_path.c_str(),ios::in);
    if(!_file){
        std::cout<<"file not exists !"<<std::endl;
        WriteLog::write_log_rosbag("file not exists !The file path is not right !");
        std::string reason="The file path is not right !";
        string param = "&file_id="+file_id+"&checked=0&reason="+reason;
        HttpRequest::send_post(url,param);
        system("killall -9 rosmaster");
        WriteLog::write_log_rosbag("kill all the ros topic !");
        _file.close();
        return 0;
    }

    //to see the result of geting data
    std::cout<< "rosbag_path :"<< rosbag_path << endl;
    std::cout<< "rosbag_num :"<< rosbag_num << endl;
    WriteLog::write_log_rosbag("rosbag_path :"+ rosbag_path);
    WriteLog::write_log_rosbag("rosbag_num :"+ rosbag_num);
    //check the suffix of the file
    //get the suffix first
    std::string suffixStr = rosbag_path.substr(rosbag_path.find_last_of('.')+1);
    std::cout << suffixStr <<endl;
    
    //check the suffix is the same as bag or not . if the same the compare should be 0 ,else it will be no-zero;
    if(suffixStr.compare("bag")){
        std::cout << " file format is wrong !!!" <<endl;
        //send result to Amry 
        std::string reason="file format is  wrong !";
        string param = "file_id="+file_id+"&checked=0&reason="+reason;
        HttpRequest::send_post(url,param);
        system("killall -9 rosmaster");
        WriteLog::write_log_rosbag(" file format is wrong !!!");
        return 0;
    }
    if(!suffixStr.compare("bag")){
        std::cout << " file format is right !!!" <<endl;
        WriteLog::write_log_rosbag(" file format is right !!!");
    }
    
    boost::shared_ptr<rosbag::Bag> m_file;
    m_file=boost::shared_ptr<rosbag::Bag>(new rosbag::Bag());
    try{
	    
        m_file->open(rosbag_path,rosbag::bagmode::Read);
        WriteLog::write_log_rosbag("open file is right !!!");
    
	}catch(exception e){
        std::cout<< "hello rosbag::BagIOException " <<endl;
        std::string reason = "The rosbag crashed  !";
        string param = "file_id="+file_id+"&checked=0&reason="+reason;
        WriteLog::write_log_rosbag("rosbag::BagIOException!!!file format is right !!!"+param);
        HttpRequest::send_post(url,param);
        system("killall -9 rosmaster");
        return 0;
    }
	
    bool gps_starneto_GPFPD=true;
    bool sensor_msgs_Imu=false;
    bool rslidar_msgs_rslidarScan=false;
    bool rslidar_msgs_rslidarPacket=false;
    bool tf2_msgs_TFMessage=false;

    rosbag::View viewer(*m_file);
    int n = viewer.getConnections().size();
    std::set<string> gpsTopicSet;
    std::set<string> imuTopicSet;
    std::set<string> rslidarPacketsTopicSet;
    std::set<string> rslidarPacketsDifopTopicSet;
    std::set<string> tfTopicSet;
    for(int i = 0; i < n;i++){
            
            if(!viewer.getConnections().at(i)->datatype.compare("gps_starneto/GPFPD")){
                gpsTopicSet.insert(viewer.getConnections().at(i)->topic);
                gps_starneto_GPFPD = true;
            }else if(!viewer.getConnections().at(i)->datatype.compare("sensor_msgs/Imu")){
                imuTopicSet.insert(viewer.getConnections().at(i)->topic);
                sensor_msgs_Imu = true;
            }else if((!viewer.getConnections().at(i)->datatype.compare("rslidar_msgs/rslidarScan")) || 
			(!viewer.getConnections().at(i)->datatype.compare("rslidar_msgs_v3/rslidarScan"))){
                rslidarPacketsTopicSet.insert(viewer.getConnections().at(i)->topic);
                rslidar_msgs_rslidarScan = true;
            }else if((!viewer.getConnections().at(i)->datatype.compare("rslidar_msgs/rslidarPacket")) || 
			(!viewer.getConnections().at(i)->datatype.compare("rslidar_msgs_v3/rslidarPacket"))){
                rslidarPacketsDifopTopicSet.insert(viewer.getConnections().at(i)->topic);
                rslidar_msgs_rslidarPacket = true;
            }else if(!viewer.getConnections().at(i)->datatype.compare("tf2_msgs/TFMessage")){
                tfTopicSet.insert(viewer.getConnections().at(i)->topic);
                tf2_msgs_TFMessage = true;
            }
		    WriteLog::write_log_rosbag("View the connetion !");  
    }
    set<string>::iterator it;
    
    list<string> lst;
    if(
    gps_starneto_GPFPD&&
    sensor_msgs_Imu&&
    rslidar_msgs_rslidarScan&&
    rslidar_msgs_rslidarPacket&&
    tf2_msgs_TFMessage
    ){
        std::string reason="All the info in the bag are OK !";
        Json::Value topic_info;
        WriteLog::write_log_rosbag("All the info in the bag are OK !");  
       
        for(it=gpsTopicSet.begin();it!=gpsTopicSet.end();it++){
        
            std::cout<<"hello"<<*it<<endl;
            topic_info["gpsList"].append(*it); 
        }
    

       
        for(it=imuTopicSet.begin();it!=imuTopicSet.end();it++){
            
            std::cout<<"hello"<<*it<<endl;
            topic_info["imuList"].append(*it);
        }
        
        for(it=rslidarPacketsTopicSet.begin();it!=rslidarPacketsTopicSet.end();it++){
            
            std::cout<<"hello"<<*it<<endl;
            topic_info["rslidarPacketsList"].append(*it);
        }
        
        for(it=rslidarPacketsDifopTopicSet.begin();it!=rslidarPacketsDifopTopicSet.end();it++){
            
            std::cout<<"hello"<<*it<<endl;
            topic_info["rslidarPacketsDifopList"].append(*it);
        }
        
        for(it=tfTopicSet.begin();it!=tfTopicSet.end();it++){
            
            std::cout<<"hello"<<*it<<endl;
            topic_info["tfList"].append(*it);
        }

        Json::FastWriter fw;
	    string strs = fw.write(topic_info);
	    Util::delete_last_enter(strs);
        string param = "&file_id="+file_id+"&checked=1&reason="+reason+"&topic_info="+strs;
        HttpRequest::send_post(url,param);
        return 0;
    }else{
        // send the message list and the lack of message to Army
        bool checked = true;
        
        std::string reason="Some topics missed !lacks of :";
        std::cout<<"file_id"<<file_id<<endl;
        std::string param = "&file_id="+file_id+"&checked=0&reason="+reason;
        Json::Value missed_message;
        Json::Value missed_topics;
        Json::Value missed_topic_class;
        WriteLog::write_log_rosbag("Some topics missed ! failed !");
        std::cout<<
        gps_starneto_GPFPD<< 
        sensor_msgs_Imu<<
        rslidar_msgs_rslidarScan<<
        rslidar_msgs_rslidarPacket<<
        tf2_msgs_TFMessage<<endl;
        if(gps_starneto_GPFPD==0){
            missed_message["missed_message"].append(" gps_starneto/GPFPD");
            missed_topics["missed_topics"].append(" gps");
            param = param + " gps";
        }
        if(sensor_msgs_Imu==0){
            missed_message["missed_message"].append(" sensor_msgs/Imu");
            missed_topics["missed_topics"].append(" imu");
            param = param + " imu";
        }
        if(rslidar_msgs_rslidarScan==0){
            missed_message["missed_message"].append(" rslidar_msgs/rslidarScan");
            missed_topics["missed_topics"].append(" rslidarPackets");
            param = param + " rslidarPackets";
        }
        if(rslidar_msgs_rslidarPacket==0){
            missed_message["missed_message"].append(" rslidar_msgs/rslidarPacket");
            missed_topics["missed_topics"].append(" rslidarPacketsDifop");
            param = param + " rslidarPacketsDifop";
        }
        if(tf2_msgs_TFMessage==0){
            missed_message["missed_message"].append(" tf2_msgs/TFMessage");
            missed_topics["missed_topics"].append(" tf");
            param = param + " tf";
        }

        param = param + ".";

        HttpRequest::send_post(url,param);
        system("killall -9 rosmaster");
        return 0;
    }

}

