/*************************************************************************
	> File Name: sleep.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Wed 10 Jul 2019 06:40:55 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void wake()
{
    printf("it is time to wake!!\n");
}
int main(void)
{
    int n;
    scanf("%d",&n);
    printf("you have %d s sleep!\n",n);
    signal(SIGALRM,wake);
    alarm(n);
    pause();
    return 0;
}
