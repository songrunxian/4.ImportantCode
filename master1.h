/*************************************************************************
	> File Name: master1.h
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Tue 23 Jul 2019 11:18:07 PM PDT
 ************************************************************************/

#ifndef _MASTER1_H
#define _MASTER1_H
#include "common.h"
#include <sys/ioctl.h>
#include <pthread.h>
#define CTLPORT 8732
#define BUFFSIZE 1024


typedef struct Node {
    struct sockaddr_in client_addr;//用這個結構體存儲地址
    int node_sock;
    struct Node *next;
}Node, *LinkedList;

struct HEART {
    LinkedList *head;
    int ins;
    int *sum;
    long timeout;
};

struct WORK{
    LinkedList head;
    int index;
};

int insert(LinkedList head, Node *node);
int find_min(int *sum,int ins);
void print_list(LinkedList head);
void *heartbeat_all(void *arg);
void *work(void *arg);
int check_connect(struct sockaddr_in,long timeout);
int do_event(struct sockaddr_in );
int socket_connet1(struct sockaddr_in addr);

int insert(LinkedList head,Node *node) {
    Node *p = head;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = node;
    return 0;
}

int find_min(int *sum, int ins) {
    int sub = 0;
    for(int i = 0; i < ins;i++) {
        if (*(sum + i) < *(sum + sub)) {
            sub = i;
        }
    }
    return sub;
}

void print_list(LinkedList head) {
    Node *p = head;
    int cnt = 0;
    while(p->next != NULL) {
        printf("<%d> %s\n ",cnt++,inet_ntoa(p->client_addr.sin_addr));
        p = p->next;
    }
}

int check_connect(struct sockaddr_in addr,long timeout) {
    int sockfd;
    if (( sockfd = socket(AF_INET ,SOCK_STREAM, 0)) < 0)  {
        perror("socket");
        return 0;
    }
    int error = -1;
    int len = sizeof(int);
    int ret = -1;
    struct timeval tv;
    unsigned long ul = 1;
    tv.tv_sec = 0;
    tv.tv_usec = timeout;

    ioctl(sockfd,FIONBIO,&ul);//設置非阻塞IO
    
    fd_set set;
    FD_ZERO(&set);
    FD_SET(sockfd, &set);

    if(connect(sockfd,(struct sockaddr*) &addr, sizeof(addr) ) < 0) {
        if (select(sockfd + 1,NULL,&set, NULL,&tv) > 0) {
            getsockopt(sockfd,SOL_SOCKET,SO_ERROR, &error, (socklen_t *)&len);
            if(error == 0) {
                ret = 1;
            } else {
                ret = 0;
            }
        }
    }
    close(sockfd);
    return ret;//表示聯通，0表示不通
}


void *heartbeat_all(void *arg) {
    struct HEART *heart;
    heart = (struct HEART *) arg;

    //心跳
    while(1) {
        for(int i = 0; i < heart->ins;i++ ) {
            Node *p = heart->head[i];
            while(p->next != NULL) {
                if (!check_connect(p->next->client_addr,heart->timeout)) {
                    printf("%s:%d \033[31mdeleting\033[0m..\n",inet_ntoa(p->next->client_addr.sin_addr),ntohs(p->next->client_addr.sin_port));
                    Node *q;
                    q = p->next;
                    p->next = p->next->next;
                    free(q);
                    heart->sum[i]--;
                } else {
                    printf("%s:%d\033[32m online\033[0m...\n",inet_ntoa(p->next->client_addr.sin_addr),ntohs(p->next->client_addr.sin_port));
                    p = p->next;
                    
                }
            }
        }
        sleep(5);
    }
    return NULL;
}


void *work(void *arg) {
    struct WORK *inarg = (struct WORK *)arg;
    char log[50] = {0};
    sprintf(log,"./%d.log",inarg->index );
    while(1) {
        FILE *file = fopen(log,"w");
        Node *p = inarg->head;

        while(p->next != NULL) {
            fprintf(file, "%s:%d\n", inet_ntoa(p->next->client_addr.sin_addr),ntohs(p->next->client_addr.sin_port));
            do_event(p->next->client_addr);//鏈接對方，發個信息，再收個信息
            p = p->next;
        }
        fclose(file);
    }
    return NULL;  
}

int socket_connet1(struct sockaddr_in addr) {
    int sockfd;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket");
        return -1;
    }
    if (connect(sockfd,(struct sockaddr*) &addr,sizeof(addr)) < 0) {
        perror("connect");
        return -1;
    }
}

int do_event(struct sockaddr_in addr) {
    int sockfd;
    char buff[BUFFSIZE] = {0};
    addr.sin_port = htons(CTLPORT);
    if(sockfd = socket_connet1(addr) < 0) {
        perror("socket_connet1");
        return -1;
    }
    send(sockfd,"Hello",strlen("Hello"),0);

    if(recv(sockfd,buff,BUFFSIZE, 0) <= 0) {
        close(sockfd);
        return 0;
    }else {
        close(sockfd);
        printf("%s\n",buff);
        return 0;
    }

}


#endif
