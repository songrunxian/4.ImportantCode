/*************************************************************************
	> File Name: 1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Mon 15 Jul 2019 11:28:48 PM PDT
 ************************************************************************/

#include <stdio.h> 
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/types.h>

#define ASK "DO you want to another try"

void set_crmode();
void tty_mode(int);
void set_nonblock_mode();

int get_response(char *);

int main () {
    int response;
    tty_mode(0);
    set_crmode();
    set_nonblock_mode();
    response = get_response(ASK);
    tty_mode(1);
    printf("\n response = %d\n",response);
    return 0;
}

void set_nonblock_mode () {
   int termflags;
    termflags = fcntl(0,F_GETFL);
    termflags |= O_NONBLOCK;     
    fcntl(0,F_SETFL,termflags);
}

void set_crmode() {
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&ttystate);
}

void tty_mode(int how) {
    static struct termios orignal_mode;
    if(how == 0) {
        tcgetattr(0,&orignal_mode);
    }else {
        tcsetattr(0,TCSANOW, &orignal_mode);
    }
}

int get_response(char *ask) {
    printf("%s (y/n)",ask);
    fflush(stdout);//這樣就可以把stdout文件內容輸出
    int get_ok_char();
    int input;
    fd_set set;
    FD_ZERO(&set);
    FD_SET(0,&set);
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    int ret = select(1,&set,NULL,NULL,&tv);//第一個參數是最大文件描述符+1
    if(ret == 1) {
        if(FD_ISSET(0,&set)) {
            while(1) {
                input = get_ok_char();
                switch(input) {
                    case 'Y' :
                    case 'y' : return 1;
                    case 'N' :
                    case 'n' : return 0;
                    default : {
                        sleep(3);
                        printf("\n");
                        tty_mode(1);
                        exit(1);
                    }
                }
            }
        }
    }
    return 2;
}


            


int get_ok_char() {
    int c;
    while((c = getchar()) != EOF);
    return c;
}
//這樣也有缺點，如果輸入錯誤也是不會超時退出請改進

