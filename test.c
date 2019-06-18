/*************************************************************************
	> File Name: test.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Tue 18 Jun 2019 04:15:33 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <sys/types.h>
#include <pthread.h>
struct Mess {
    char name[20];
    int high;
};

void *out (void *arg) {
    struct Mess *p;
    p = (struct Mess*) arg;
    printf("%d\n", p->high);
    printf("%s\n", p->name);
}

int main () {
    struct Mess m = {"srx",181};
    pthread_t id;
    pthread_create(&id,NULL, out,(void *)(&m));
    pthread_join(id,NULL);
    pthread_detach(id);
    return 0;
}
