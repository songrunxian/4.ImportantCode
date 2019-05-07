/*************************************************************************
	> File Name: sushushai.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Fri 03 May 2019 11:34:23 PM PDT
 ************************************************************************/
#include <stdio.h>
#define MAX_N 10000

int prime[MAX_N + 5] = {0};

int main () {
    for (int i = 2; i * i <= MAX_N; i++){
        if (prime[i]) continue;
        for (int j = i * i; j <= MAX_N; j += i) {
            prime[j] = 1;
        }
    }
    for (int i = 2; i <= MAX_N ;i++) {
        if (prime[i]) continue;
        prime[++prime[0]] = i;
    }
    int n;
    while (~scanf("%d" ,&n)) {
        printf("%d \n",prime[n]);
    }
    return 0;
}
