/*************************************************************************
	> File Name: 123.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Thu 13 Jun 2019 06:22:53 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <math.h>


void getXY(int n,int s,int &x,int &y) {
    if(n == 0) {
        x = 0, y = 0;
        return ;
    }
    int  xx, yy;
    int  len_n_1=(int) pow(2,n-1);
    int  total_n = len_n_1 * len_n_1;
    int ind1 = s / total_n, ind2 = s % total_n;
    getXY(n-1, ind2, xx, yy);
    switch(ind1) {
        case 0: {
            x = yy, y = yy + len_n_1;
        }break;
        case 1: {
            x = xx, y = yy + len_n_1;
        }break;
        case 2: {
            x = xx + len_n_1, y == yy + len_n_1;
        }break;
        case 3: {
            x = 2*len_n_1 - yy -1,y = len_n_1 -xx-1;
        }break;
    }
    return;
}

void solve() {
    int n,s,d;
    scanf("%d %d %d",&n,&s,&d);
    int x1,x2,y1,y2;
    getXY(n,s,&x1,&y1);
    getXY(n,d,&x2,&y2);
    printf("%f0.1", sqrt ((x1-x2)*(x1-x2)*10 + (y1 - y2) *(y1 - y2)*10));
    return ;
}

int main () {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
    
}
