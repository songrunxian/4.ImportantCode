/*************************************************************************
	> File Name: 1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Sun 28 Jul 2019 03:36:00 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define size 4096
int main () {
    //先申請共享內存，然後產生進程。親緣關系的共享進程很典型
    char *share_memory = NULL;
    int shmid = shmget(0,size,0666|IPC_CREAT);
    
    if  (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    if((share_memory = shmat(shmid,NULL,0)) == NULL){
        perror("shmat");
        exit(1);
    }

    int pid = fork();
    if (pid == 0) {
        char buff[1024] = "nihao";
        strcpy(share_memory,buff);
    }
    printf("%s\n",share_memory);
    return 0;
}
