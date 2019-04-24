/*************************************************************************
	> File Name: main.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Wed 24 Apr 2019 04:20:08 AM PDT
 ************************************************************************/

#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#define BUF_SIZE 64
#define PATH_SIZE 64
#define PRINT_FONT_RED  printf("\033[31m"); //红色
#define PRINT_FONT_YEL  printf("\033[33m"); //黄色
#define MAX_CMD 1000

typedef struct _input_type{
    char *str; //the value of input
    int size; //the length of size
}input_type;

input_type input[] = {
    {"exit" ,4},
    {"cd" , 2},
    {"ls" , 2}
};

int cds(const char *p){
    char path[PATH_SIZE];
    char *start;
    char *end;
    int res;
    int n = 0;

    memset(path,'\0',PATH_SIZE);

    start = strchr(p,' ');
    end = strchr(p,'\n');

    if(!start || !end){
        printf("can't support this format \n");
        return 1;
    }

    strncpy(path , p+3 ,end - start -1);

    res = chdir(path);

    if(res != 0){
        printf("%s is not a path,check please\n", path);
    }

    return res;
    
}
void lss(const char *p){
    printf("ls\n");
}

int main(int argc , char *argv[]){
    char cmdstring[MAX_CMD];
    char buff[MAX_CMD];
    char hostname[MAX_CMD];
    char buf[BUF_SIZE];
    int res = 1;
    int flag = 1;
    int index = 0;

    while(flag){
        getcwd(buf , sizeof(buff));
        gethostname(hostname,sizeof(hostname));
        struct passwd *pwd;
        pwd = getpwuid(getuid());
        PRINT_FONT_RED
        printf("%s@%s:" ,pwd->pw_name,hostname);
        PRINT_FONT_YEL
        printf("%s ",buf);
        
        if(NULL == fgets(buf,BUF_SIZE,stdin))
        return 0;

        index = sizeof(input)/sizeof(input_type);
        while(--index > 0){
            res = strncmp(buf,input[index].str,input[index].size);
            if(res == 0){
                switch(index){
                    case 0:
                    flag = 0;
                    break;
                    case 1:
                    cds(buf);
                    break;
                    case 2:
                    lss(buf);
                    break;
                    default:
                    printf("can not \n");
                    break;
                }
                index = -1;
            }
        }
        if(index == -1){
            printf("can not find commond: %s",buf);
        }
    }
    //printf("%d",sizeof(input_type));
    return 0;
}
