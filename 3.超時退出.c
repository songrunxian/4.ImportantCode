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

#define ASK "DO you want to another try"

void set_crmode();
void tty_mode(int);
void set_nonblock_mode();
#define TRY 3
#define SLEEPTIME 2

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

void set_nonblock_mode () {//設定非阻塞模式
   int termflags;
    termflags = fcntl(0,F_GETFL);
    termflags |= O_NONBLOCK;     //通過|=添加狀態  &= 屏蔽狀態
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
    int get_ok_char();
    int input;
    int maxtry = TRY;
    while (1) {
            printf("\n Time left <%d>",maxtry);
            input = tolower(get_ok_char());
               if(input == 'y') {
                   return 1;
               }
               if(input == 'n') {
                   return 0;
               }
        if(maxtry-- == 0) {
            return 2;
        }
        sleep(SLEEPTIME);
    }
}


int get_ok_char() {
    int c;
    while((c = getchar()) != EOF && strchr("yYnN",c) == NULL);
    return c;
}
//但是這個程序再輸入內容以後要等一會才會有顯示。不會立刻反應
//why？
//阻塞就會等到輸入才會繼續，非阻塞是直接跳過
//0是非阻塞，所以get_ok_char()不卡，直接跳過就會睡了
//改進通過select
