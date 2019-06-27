/*************************************************************************
	> File Name: 24_56oj.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Wed 26 Jun 2019 07:20:06 PM PDT
 ************************************************************************/

#include <stdio.h>
#define max 10

int jnum[max] = {0};
int dnum[max] = {0};

void init() {
    jnum[0] = 1;
    for (int i = 1; i < max; i++) {
        dnum[i] = 1;
        jnum[i] = i * jnum[i-1];
    }
    return ;
}

int get_num(int n,int k) {
    int ind = k /jnum[n] + 1;
    int i = -1;
    while (ind > 0) {
        i++;
        ind -= dnum[i];
    }
    dnum[i] = 0;
    return i;
}

int main () {
    init();
    int n,k;
    scanf("%d%d",&n,&k);
    k -= 1;
    for(int i= n-1; i >= 0;i--) {
        int num = get_num(i,k);
        printf("%d",num);
        k %= jnum[i];
    }
    printf("\n");
    return 0;
}
