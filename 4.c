/*************************************************************************
	> File Name: signal.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Fri 26 Apr 2019 01:22:21 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handler (int sig) {
    if(sig == SIGTSTP) {
        printf("i have got SIGTSTP\n");
    }
}

int main () {
    sigset_t sigset;
    sigemptyset(&sigset);

    sigaddset(&sigset,SIGTSTP);
    
    sigprocmask(SIG_SETMASK,&sigset,NULL);
    pause();

    return 0;
}
