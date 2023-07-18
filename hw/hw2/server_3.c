#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

#define SERV_PORT 1998
#define IP_SIZE 100

void sys_err(const char *str){
    perror(str);
    exit(1);
}

int main(int argc, char** argv)
{
    int lfd, cfd, ret;
    char buf[BUFSIZ], clit_ip[IP_SIZE];
    struct sockaddr_in serv_addr, clit_addr;
    socklen_t clit_addr_len;
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd==-1){
        sys_err("socket error");
    }
    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(lfd, 120);
    cfd = accept(lfd, (struct sockaddr *)&clit_addr, &clit_addr_len);
    if(cfd==-1){
        sys_err("accept error");
    }
    //printf("client ip: %s , ")
    printf("client ip:%s port:%d\n", 
            inet_ntop(AF_INET, &clit_addr.sin_addr.s_addr, clit_ip, sizeof(clit_ip)), 
            ntohs(clit_addr.sin_port));			// 根据accept传出参数，获取客户端 ip 和 port
    while(1){
        ret = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);

        for(int i=0; i<ret; i++){
            buf[i] = toupper(buf[i]);
        }
        write(cfd, buf, ret);
        write(STDOUT_FILENO, buf, ret);
    }
    close(lfd);
    close(cfd);
}