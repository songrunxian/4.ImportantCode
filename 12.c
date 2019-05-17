/*************************************************************************
	> File Name: 1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Fri 17 May 2019 01:34:29 AM PDT
 ************************************************************************/

#include <stdio.h> 

int main () {
    int n;
    char ch[100];
    FILE *f = fopen("/dev/null", "w");
    printf("%d\n",EOF);
    while (~scanf ("%d", &n)) {
        printf("%d\n" ,fprintf(f,"%d", n ));
        printf ("%d\n", sprintf(ch, "%d", n));
    }
    return 0;
}
