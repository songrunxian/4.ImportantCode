/*************************************************************************
	> File Name: homework1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Sun 16 Jun 2019 11:41:33 PM PDT
 ************************************************************************/

#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>

void * thread_run(void *arg) {
    char buf[1024];
    int fd = (int)arg;
    printf("creat a new thread...\n");
    while(1) {
        ssize_t _s = read(fd,buf,sizeof(buf));
        if (_s > 0) {
            buf[_s-1] = '\0';
        }else if (_s == 0) {
            printf("client close....\n");
            break;
        }else {
            break;
        }
        printf("client :%s\n",buf);
        write(fd,buf,strlen(buf));
    }
    close(fd);
    pthread_exit(0);
}

int main () {
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0) {
        perror("socket error\n");
        return -1;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(8888);
    local.sin_addr.s_addr = inet_addr("192.168.2.124");
    if(bind(sockfd,(struct sockaddr*)&local, sizeof(local)) < 0) {
        perror("bind error\n");
        close(sockfd);
        return -1;
    }
    if(listen(sockfd,5) < 0) {
        perror("listen error\n");
        close(sockfd);
        return -1;
    }
    printf("bind and listen success ,wait accept..\n");

    struct sockaddr_in client_sock;
    socklen_t len = sizeof(client_sock);
    while(1) {
        int new_fd = accept(sockfd,(struct sockaddr*)&client_sock, &len);
        if(new_fd < 0) {
            perror("accept\n");
            close(sockfd);
            return -1;
        }
        pthread_t id;
        if (pthread_create(&id,NULL,thread_run,(void*)new_fd) < 0){
            perror("phthread_create false\n");
            close(sockfd);
            return -1;
        }
        pthread_detach(id);
    }
    close(sockfd);
    return 0;
}
