/*************************************************************************
	> File Name: binary.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Sat 04 May 2019 01:08:04 AM PDT
 ************************************************************************/

#include <stdio.h> 

int binary_search(int *arr, int n, int x){
    int head = 0, tail = n - 1, mid;
    while(head <= tail) {
        mid = (head + tail) >> 1;
        if(arr[mid] == x) return mid;
        if(arr[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

int arr[100];

int main() {
    int n,a;
    scanf("%d" ,&n);
    for(int i = 0; i < n; i++){
        scanf("%d" , arr + i);
    }
    while (~scanf("%d", &a)) {
        printf("binary_search result = %d\n", binary_search(arr, n, a));
    }
    return 0;
}
