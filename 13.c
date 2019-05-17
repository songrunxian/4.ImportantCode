/*************************************************************************
	> File Name: 1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Fri 17 May 2019 03:31:15 AM PDT
 ************************************************************************/

#include <stdio.h>
int main () {
    char a[1000];
    FILE *f = fopen("/dev/null","w");
    scanf ("%[^\n]" , a);
    printf("%d\n",fprintf(f, "%s", a));
    return 0;
}

