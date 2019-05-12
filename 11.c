/*************************************************************************
	> File Name: 11.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Sat 11 May 2019 02:27:11 AM PDT
 ************************************************************************/

#include <stdio.h> 

int main () {
    int n;
    int result = 1;
    scanf ("%d", &n);
    if (n == 1) {
        printf("%d\n" ,1);
    }else if (n == 0) {
        printf(" %d\n",1);
    } else {
        for(int i = n;i >=  1;i--){
            result *= i;
        }
        printf( "%d\n",result );
    }
    return 0;
}

