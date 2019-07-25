/*************************************************************************
	> File Name: client.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Wed 24 Jul 2019 04:28:13 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include "client.h"
#define PORT 8732
int main () {
    int sockfd,listen;
    if ((listen = socket_create(PORT)) < 0) {
        perror("socket_create");
        exit(1);
    }

    while(1) {
        if((sockfd = accept(listen,NULL,NULL)) < 0) {
            perror("accept");
            continue;
        }
        char buff[BUFFSIZE] = {0};
        if (recv(sockfd,buff,BUFFSIZE,0) > 0) {
            printf("%s\n",buff);
            sprintf(buff,"client : %s",buff);
            send(sockfd, buff,strlen(buff),0);
            close(sockfd);
        } else {
            close(sockfd);
        }
    }

    return 0;
}
