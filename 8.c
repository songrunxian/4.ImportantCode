/*************************************************************************
	> File Name: width.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Wed 08 May 2019 05:44:49 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
int main () {
    struct winsize size;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    printf("%d\n",size.ws_col);
    printf("%d\n",size.ws_row);
    return 0;
}
