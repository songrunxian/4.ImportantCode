/*************************************************************************
	> File Name: 10.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Sat 11 May 2019 02:13:05 AM PDT
 ************************************************************************/

#include <stdio.h> 

int main () {
    int year;
    scanf("%d", &year);
    if ((year % 4) && !(year % 100)) { 
        printf("leap\n");
    }else if (!(year % 400)) {
        printf("leap\n");
    }else {
        printf("not leap\n");
    }

    return 0;
}
