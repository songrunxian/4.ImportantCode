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

#define ASK "DO you want to another try"

void set_crmode();
void tty_mode(int);


bool get_response(char *);

int main () {
    bool response;
    tty_mode(0);
    set_crmode();
    response = get_response(ASK);
    tty_mode(1);
    printf("\n response = %d\n",response);
    return 0;
}

void set_crmode() {
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;//屏蔽回顯
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

bool get_response(char *ask) {
    printf("%s (y/n)",ask);
    int input;
    while (1) {
        switch(getchar()){  
            case 'Y':
            case 'y':    return true;
            case 'N':
            case 'n':
            case EOF :return  false;
            //default:
            //printf("\n can't understand %c, please input (y/n)\n",input);
        }
    }
}
//缺少超時退出
//把0(標準輸入)設置成非阻塞模式  用fcntl()函數NONBLOCK
//等兩秒鍾判斷一下，嘗試三次
