/*************************************************************************
	> File Name: homework.c
	> Author: songrunxian 
	> Mail: 13359850710@163.com 
	> Created Time: Sun 16 Jun 2019 10:15:56 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pwd.h>
int socket_connect (int port, char *user) {
    int sockfd;
    struct sockaddr_in dest_addr;
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("socket() error");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sinport = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(user);

    if(connect(sockfd, (struct sockaddr *)&dest_addr,sizeof(dest_addr)) < 0){
        perror("connect() error");
        return -1;
    }
    return sockfd;

}

int main() {
    int socket_fd;
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char ip_addr[20] = "192.168.1.40";
    int port = 8888;
    char username[20] = {0};
    strcpy(username, pwd->pw_name);
    socket_fd = socket_connect(port,ip_addr);
    if (socket_fd < 0) {
        exit(1);
    }
    if (send(socket_fd,username,strlen(username),0) > 0) {
        printf("Check Success\n");
    }
    close(socket_fd);
    return 0;
}
