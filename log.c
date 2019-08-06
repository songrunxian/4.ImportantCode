/*************************************************************************
	> File Name: log.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Tue 06 Aug 2019 01:38:38 AM PDT
 ************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#define size 2048
enum LogLevel {
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    DEBUG = 4,
};
char *s_loginfo[] = {
    [ERROR] = "ERROR",
    [WARN] = "WARN",
    [INFO] = "INFO",
    [DEBUG] = "DEBUG",
};
#define LOGLEVEL DEBUG
void WriteLog(char *filename, int line,enum LogLevel level,const char *fmt,...);
void get_timestamp(char *buffer); 

int main () {
    FILE *fp = fopen("./aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","r");
    int i = 1;
    if(fp == NULL) {
        WriteLog("./log.c",32,WARN,"can not open the file");
        i++;
    }
    return 0;
}

void WriteLog(char *filename, int line,enum LogLevel level,const char *fmt,...) {
    if (level > DEBUG) return;
    char buf[size];
    memset((void *)buf,0,size);
    va_list ap;
    va_start(ap,fmt);
    vsnprintf(buf,size,fmt,ap);
    char time[32] = {0};

    const char *tmp = strrchr(filename,'/');
    if(!tmp) tmp = filename;
    else tmp++;
    get_timestamp(time);
    printf("%s[%s][%s:%d]%s\n",time,s_loginfo[level],tmp,line,buf);
    FILE *fp = fopen("./runxianlog","w");
    fprintf(fp,"%s[%s][%s:%d]%s\n",time,s_loginfo[level],tmp,line,buf);
    va_end(ap);
}

void get_timestamp(char *buffer) {
    time_t t;
    struct tm *p;
    struct timeval tv;
    int millsec;
    t = time(NULL);
    p = localtime(&t);
    gettimeofday(&tv,NULL);
    millsec = (int)(tv.tv_usec / 1000);
    int len = snprintf(buffer,32,"[%04d-%02d-%02d %02d:%02d:%02d:%03d]",p->tm_year + 1900,p->tm_mon + 1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec,millsec);
    buffer[len] = '\0';
}
