/*************************************************************************
	> File Name: testformat.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Fri 17 May 2019 07:18:14 PM PDT
 ************************************************************************/

#include <stdio.h> 

int main () {
    printf("%2$d %2$#x; %1$d %1$#x\n", 16, 17);
    printf("%2d\n", 3);
    printf("%02d\n", 3);
    printf("%-2d\n", 3);
    printf("%0-d\n", 3);
    char str[100];
    char str1[100];
    scanf("%[^\n]",str);
    printf("%d\n",sprintf(str1,"%s",str));
    return 0;
}
