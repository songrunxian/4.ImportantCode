/*************************************************************************
	> File Name: home1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Mon 26 Aug 2019 01:20:43 AM PDT
 ************************************************************************/

#include <stdio.h> 
long long quickpower(long long aa,long long bb, long long pp) {
    long long ans = 1;
    if (bb == 0) {
        return 1;
    }
    while (bb) {
        if (bb & 1) {
            ans *= aa;
            ans %= pp;
        }
        aa *= aa;
        aa %= pp;
        bb >>= 1;
        //printf("hello\n");
    }
    return ans;
}
int main () {
    long long a , b , p;
    long long ans = 0;
    scanf ("%lld%lld%lld",&a,&b,&p);
    ans = quickpower(a , b, p);
    printf("%lld\n",ans % p);
    return 0;
}
