#ifndef MAP_CONFIG_H
#define MAP_CONFIG_H
#include<iostream>

using namespace std;

class MapConfig{

   public:
               //log path
       static std::string mapgencheck_logpath;
       static std::string rosbagcheck_logpath;
       static std::string mapgencheck_url;
       static std::string rosbagcheck_url;
       //mysql log information
       static char* host;
       static char* user;
       static char* password;
       static char* db;
       //MapConfig();


};

std::string MapConfig::mapgencheck_logpath = "/home/mapping_ws_auto/src/mapcheck/logs/mapgencheck.log";
std::string MapConfig::rosbagcheck_logpath = "/home/mapping_ws_auto/src/mapcheck/logs/rosbagcheck.log";
std::string MapConfig::mapgencheck_url = "http://127.0.0.1:81/api/task/createMap";
std::string MapConfig::rosbagcheck_url = "http://127.0.0.1:81/api/task/checkFile";
char* MapConfig::host = "localhost";
char* MapConfig::user = "root";
char* MapConfig::password = "ventimysql";
char* MapConfig::db = "maptool";

#endif




