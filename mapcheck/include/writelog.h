#ifndef WRITE_LOG
#define WRITE_LOG
#include<iostream>
#include<fstream>
#include<mapconfig.h>
using namespace std;
class WriteLog{
    private:
    public :
        static int write_log_rosbag(string content);
        static int write_log_map(string content);


};

int WriteLog::write_log_map(string content){
    MapConfig *mc;
    time_t tt = time(NULL);
    tm* t=localtime(&tt);
    ofstream fout;

    fout.open(mc->mapgencheck_logpath.c_str(),ios::app);//open the log file
    fout <<t->tm_year + 1900<<"-" <<t->tm_mon + 1<<"-"<<t->tm_mday<<"  "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec<<" : "<<content << " ";
    fout << endl;
}

int WriteLog::write_log_rosbag(string content){
    MapConfig *mc;
    time_t tt = time(NULL);
    tm* t=localtime(&tt);
    ofstream fout;

    fout.open(mc->rosbagcheck_logpath.c_str(),ios::app);//open the log file
    fout <<t->tm_year + 1900<<"-" <<t->tm_mon + 1<<"-"<<t->tm_mday<<"  "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec<<" : "<<content << " ";
    fout << endl;
}
#endif