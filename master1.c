/***********************************************************************
	> File Name: master1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Tue 23 Jul 2019 11:27:25 PM PDT
 ************************************************************************/

#include <stdio.h> 
#include "master1.h"


int main () {
    char *config= "./pihealthd.conf" ;
    int server_listen;
    int Port,Ins,CHPort;
    char FromIp[20] = {0};
    char ToIp[20] = {0};
    char tmp[20] = {0};
    unsigned int begin, end;
   
    
    //常用的處理配置文件的方法
    //設計函數，從config抓過來取“INS”的值，放在tmp裏面。
    get_conf_value(config, "INS", tmp);
    Ins=atoi(tmp);
    get_conf_value(config,"From",tmp);
    strcpy(FromIp, tmp);
    get_conf_value(config, "To",tmp);
    strcpy(ToIp, tmp);
    get_conf_value(config, "ClientHeart", tmp);
    CHPort = atoi(tmp);
    get_conf_value(config, "MasterPort", tmp);
    Port=atoi(tmp);
    
    begin = ntohl(inet_addr(FromIp));
    end = ntohl(inet_addr(ToIp));


    LinkedList *linkedlist = (LinkedList *)malloc(Ins * sizeof(LinkedList));//創建ins個連續的鏈表頭==鏈表頭數組
    //爲了設置負載平衡，我們要記錄每一個鏈表的長度
    int *sum = (int *)malloc(Ins *sizeof(int));
    memset(sum, 0, Ins*sizeof(int));//最常用的初始化函數

    struct sockaddr_in initaddr;
    initaddr.sin_family = AF_INET;
    initaddr.sin_port = htons(CHPort);
    initaddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    //初始化鏈表
    for(int i = 0; i < Ins; i++) {
        Node *p = (Node *)malloc(sizeof(Node));
        p->client_addr = initaddr;
        p->node_sock = -1;
        p->next = NULL;
        linkedlist[i] = p;
    }



    for(unsigned int i = begin; i <= end; i++) {
        struct sockaddr_in tmpaddr;
        if(i % 256 == 0 || (i+1)%256 == 0) {
            //把字符串IP變成int，IP，判斷合法IP
            //如果末尾後八位全是0，那麼相當於左移動8位 = 2^8 = 256
            continue;
        }
        initaddr.sin_addr.s_addr = htonl(i);
        //合法IP 生成相應合法節點
        Node *p = (Node *)malloc(sizeof(Node));
        p->client_addr=initaddr;
        p->next = NULL;
        p->node_sock = -1;

        //找最短序列
        int sub = find_min(sum,Ins);//數組作爲參數會退化成爲指針，所以要傳遞長度信息
        insert(linkedlist[sub], p);
        sum[sub]++;
    }

    for (int i = 0; i < Ins;i++) {
        printf("Ins <%d>:\n",i);
        print_list(linkedlist[i]);
    }

    //創建線程，測量心跳

    pthread_t HeartTid;
    long TimeOut;
    get_conf_value(config,"TimeOut",tmp);
    TimeOut = atol(tmp);
    struct HEART heartarg;
    heartarg.sum = sum;
    heartarg.head = linkedlist;
    heartarg.ins = Ins;
    heartarg.timeout = TimeOut;
    if (pthread_create(&HeartTid, NULL, heartbeat_all,(void *)
                       &heartarg)< 0) {
                           perror("pthread_create");
                           exit(1);
                       }
    
    pthread_t t[Ins];
    struct WORK workarg[Ins];

    for(int i = 0; i < Ins;i++) {
        workarg[i].head = linkedlist[i];
        workarg[i].index = i;
        if(pthread_create(&t[i],NULL,work,(void *)&workarg) == -1) {
            perror("pthread_create");
            exit(1);
        }
    }

    //創建監聽套接字
    if((server_listen = socket_create(Port)) < 0) {
        perror("server_listen");
        exit(1);
    }

    do_epoll(server_listen,linkedlist,sum,Ins);


    for (int i = 0; i < Ins; i++) {
        pthread_join(t[i], NULL);//主線程等待子線程結束再次結束
    }
    pthread_join(HeartTid,NULL);

    //sleep(1000);
    return 0;

}
