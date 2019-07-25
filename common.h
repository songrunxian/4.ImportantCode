/*************************************************************************
	> File Name: common.h
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Thu 18 Jul 2019 05:19:36 AM PDT
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>


#define MAXEVENTS 64



int get_conf_value(char *file,char *key,char *value) {
    FILE *fp=NULL;
    char *line=NULL;
    size_t n = 0, len = 0;
    ssize_t read;
    char *substr = NULL;

    if(key == NULL || value == NULL) {
        printf("error\n");
        return -1;
    }

    fp = fopen(file,"r");

    if(fp == NULL) {
        printf("open error \n");
        return -1;
    }

    while((read = getline(&line,&n,fp)) >= 0) {
        substr = strstr(line,key);
        if(substr== NULL) {
            continue;
        } else {
            len = strlen(key);
            if (line[len] == '=') {
                strncpy(value,line+len+1, (int)read - len -2);
                break;
            }else {
                continue;
            }
        }
    }

    if (substr == NULL) {
        printf("%s Not find\n",key);
        fclose(fp);
        free(line);
        return -1;
    }

    fclose(fp);
    free(line);

    return 0;
}



/*
int socket_connect(char *host,int port,struct timeval time) {
    int sockfd;
    struct sockaddr_in server;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);

    fd_set rfds;
    int retval;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    retval = select(1, NULL, &rfds, NULL,&time);

    while (!retval) {
        retval = select(1, NULL, &rfds, NULL, &time);
    }

}
*/


int socket_create(int port) {
    int sockfd;
    struct sockaddr_in addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        return -1;

    }

    if (listen(sockfd, 20) < 0) {
        return -1;
    }
    return sockfd;
}


int socket_connect(char *host, int port) {
    int sockfd;
    struct sockaddr_in server;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }

    return sockfd;
}


#endif
