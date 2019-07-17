/*************************************************************************
	> File Name: 1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Mon 15 Jul 2019 11:09:24 PM PDT
 ************************************************************************/

#include <stdio.h> 
#include <stdbool.h>

#define ASK "DO you want to another try"

bool get_response(char *);

int main () {
    bool response;
    response = get_response(ASK);
    printf("\n response = %d\n",response);
    return 0;
}

bool get_response(char *ask) {
    printf("%s (y/n)",ask);
    while (1) {
        switch(getchar()){  //getchar獲取字符，返回值就是輸入字符
            case 'Y':
            case 'y':    return true;
            case 'N':
            case 'n':
            case EOF :return false;
        }
    }
}
//缺點這裏需要按下回車才有值；
//按下回車證明我在輸入字母的時候，bash沒有收到內容
//接下來要學會關閉緩衝
