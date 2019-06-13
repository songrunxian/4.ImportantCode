/*************************************************************************
	> File Name: 235.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Thu 13 Jun 2019 04:24:31 AM PDT
 ************************************************************************/

#include <stdio.h> 
int arr[25];
int vis[25];

void output (int k, int n) {
    if(k == n) {
        printf("%d", arr[0]);
        for(int i = 1;i < n;i++) {
            printf(" %d", arr[i]);
        }
        printf("\n");
        return ;
    }
    for(int i = 1;i <= n;i ++) {
        if (vis[i]) continue;
        arr[k] = i;
        vis[i] = 1;
        output(k+1,n);
        vis[i] = 0;
    }
    return ;
}

int main() {
    int n;
    scanf("%d", &n);
    output(0,n);
    return 0;
}
