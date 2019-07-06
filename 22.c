/*************************************************************************
	> File Name: fork.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Thu 04 Jul 2019 03:19:47 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX 10000
#define INS 10

char sum_file[] = {"./sum.txt"};
char now_file[] = "./now.txt";

void  get_num(char *file, int *num) {
    FILE *f = fopen (file, "r");
    if (f == NULL) {
        perror ("fopen not success");
    }
    flock(f->_fileno,LOCK_EX);
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len,f);
    *num = atoi(line);
    free(line);
    fclose(f);
    usleep(200000);
}

void  set_num(char *file, int num) {
    FILE *f = fopen (file, "w");
    if(f == NULL) {
        perror("fopen");
    }
    flock(f->_fileno,LOCK_EX);
    fprintf(f,"%d",num);
    fclose(f);
    usleep(200000);
}

int main () {
    set_num(sum_file, 0);
    set_num(now_file, 0);
    pid_t pid;
    int tmp_n = 0;
    int tmp_s = 0;
    for(int i = 0; i < INS;i++) {
        pid = fork();
        if(pid == 0) break;
    }

    if(pid == 0) {
        while(1) {
            get_num(now_file,&tmp_n);
            get_num(sum_file,&tmp_s);
            if (tmp_n > MAX) break;
            tmp_s += tmp_n;
            set_num(now_file,tmp_n + 1);
            set_num(sum_file,tmp_s);
        }
        exit(0);

    }
    
    return 0;
}
