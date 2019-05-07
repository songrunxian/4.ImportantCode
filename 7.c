/*************************************************************************
	> File Name: my_ll.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Mon 06 May 2019 05:01:40 PM PDT
 ************************************************************************/

#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#define max 10000
int main (int argc, char *argv[]) {

    struct stat *st = malloc(sizeof(struct stat));
    if(stat(argv[1], st) < 0) {
        perror("stat");
    } 

    char type; 
    if(S_ISLNK(st->st_mode)) type = 'l';
    else if(S_ISREG(st->st_mode)) type = '-';
    else if(S_ISDIR(st->st_mode)) type = 'd';
    else if(S_ISCHR(st->st_mode)) type = 'c';
    else if(S_ISBLK(st->st_mode)) type = 'b';
    else if(S_ISFIFO(st->st_mode)) type = 'p';
    else if(S_ISSOCK(st->st_mode)) type = 's';

    char permission[9];
    memset(permission,'-',9*sizeof(char));
    if(st->st_mode & S_IRUSR) permission[0] = 'r';
    if(st->st_mode & S_IWUSR) permission[1] = 'w';
    if(st->st_mode & S_IXUSR) permission[2] = 'x';
    if(st->st_mode & S_IRGRP) permission[3] = 'r';
    if(st->st_mode & S_IWGRP) permission[4] = 'w';
    if(st->st_mode & S_IXGRP) permission[5] = 'x';
    if(st->st_mode & S_IROTH) permission[6] = 'r';
    if(st->st_mode & S_IWOTH) permission[7] = 'w';
    if(st->st_mode & S_IXOTH) permission[8] = 'x';

    int i;
    printf("%c" ,type);
    while(i < 9) {
        printf("%c", permission[i]);
        i++;
    }
    printf("\t%d",st->st_nlink);

    struct passwd *pwd;
    struct group *grp;
    pwd = getpwuid(st->st_uid);
    grp = getgrgid(st->st_gid);
    printf("\t%s",pwd->pw_name);
    printf("\t%s",grp->gr_name);

    printf("\t%d",st->st_size);
    printf("\t%s",ctime(&(st->st_mtim)));
    printf("\t%s",argv[1]);
    return 0;
}
