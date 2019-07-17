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

void set_crmode();//設置屬性
void tty_mode(int);//獲得屬性     0->get  1->set  0獲得mode，1設定mode


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
    struct termios ttystate;//ttystate表示虛擬終端狀態
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANON;//
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
    char input;
    while (1) {
        switch(getchar()){  
            case 'Y':
            case 'y':    return true;
            case 'N':
            case 'n':
            case EOF :return  false;
            default:
            printf("\n can't understand %c, please input (y/n)\n",input);
        }
    }
}

//改進只接受YyNn其他字符輸入時候不會有反應
