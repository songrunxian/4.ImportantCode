/*************************************************************************
	> File Name: 1.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Thu 18 Jul 2019 04:28:55 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int get_conf_val(char *file,char *key) {
    int len = 0;
    char mystring [100];
    char test[100];
    len = strlen(key);
    FILE *pfile = fopen(file,"r");
    if (pfile == NULL) {
        printf ("error opening\n");
        exit(1);
    }
    while (fgets(mystring,100,pfile) != NULL) {
        strncpy(test,mystring,len);
        if (!strcmp(test,key)) {
            int len2 = strlen(mystring);
            strncpy(test,mystring+len+1,len2 - len);
            printf("%s\n",test);
        }
        puts(mystring);
    }
    fclose(pfile);
    return 0;
}

int main () {
    get_conf_val("test.c","a");
    return 0;
}
