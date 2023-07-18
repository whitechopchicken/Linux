#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

#define SERV_PORT 1244
#define IP_SIZE 100

void sys_err(const char * str){
    perror(str);
    exit(1);
}
int main(int argc, char** argv)
{
    int lfd, cfd, ret;
    char buf[BUFSIZ],client_ip[IP_SIZE];
    struct sockaddr_in serv_addr, clit_addr;
    socklen_t clit_addr_len;

    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);

    lfd = socket(AF_INET, SOCK_STREAM, 0); //没有判断 lfd == -1
    bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(lfd, 100);
    cfd = accept(lfd, (struct sockaddr*)&clit_addr, &clit_addr_len);
    printf("client ip:%s, port:%d\n", 
    inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, client_ip, sizeof(client_ip)), 
    ntohs(clit_addr.sin_port));

    while(1){
        ret = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret); //写到服务器屏幕   原始的内容 
        for(int i=0; i<ret; i++){
            buf[i] = toupper(buf[i]);
        }
        write(cfd, buf, ret);           //写回客户端屏幕    处理后的内容，大写
    }
    close(lfd);
    close(cfd);
}