#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "wrap.h"

#define MAXLINE 100
#define SERV_PORT 1249

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr;
    char buf[MAXLINE];
    int sockfd, n;      //客户端的cfd 改叫 sockfd，因为自己就是客户端
    char *str;

    if(argc != 2){
        fputs("usage: ./client message\n", stderr);
        exit(1);
    }
    str = argv[1];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));       //作用：
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "172.31.229.77", &serv_addr.sin_addr);   //作用：

    Connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));//把自己的fd 与服务器ip 端口连接

    Write(sockfd, str, strlen(str));        //作用：把客户端的内容写到服务器屏幕上？

    n = Read(sockfd, buf, MAXLINE);         //作用：读取来自服务器的内容
    printf("Response from server:\n");

    Write(STDOUT_FILENO, buf, n);           //写到自己的屏幕上；

    close(sockfd);
    return 0;
}
