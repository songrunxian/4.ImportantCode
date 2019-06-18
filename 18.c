/*************************************************************************
	> File Name: 235.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Fri 14 Jun 2019 07:04:18 PM PDT
 ************************************************************************/

#include <stdio.h>
int a[25];
void out (int ind,int n,int k,int *a) {
    if(ind == n) {
        return ;
    }
    for (int i = ind +1; i <= n;i++) {
        a[k] = i;
        for(int j = 0;j <= k;j++) {
            printf("%d",a[j]);
        }
        printf("\n");
        out (i, n, k+1, a);
    }
    return ;
}
int main () {
    int n;
    scanf ("%d", &n);
    out(0,n,0,a);
    return 0;
}
