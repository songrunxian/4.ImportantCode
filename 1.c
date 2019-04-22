/*************************************************************************
	> File Name: linuxhomework.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Mon 22 Apr 2019 02:50:09 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define PRINT_FONT_RED  printf("\033[31m"); //红色
#define PRINT_FONT_YEL  printf("\033[33m"); //黄色

int main () {
    
    char buf[80];
    getcwd(buf , sizeof(buf));
    
    char hostname[60];
    int res = gethostname(hostname ,sizeof(hostname));
    
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    PRINT_FONT_RED
    printf("%s@%s:" ,pwd->pw_name , hostname );
    PRINT_FONT_YEL
    printf("%s \n",buf);

    return 0;
 
}
