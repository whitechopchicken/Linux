#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>

#define SERV_PORT 1249

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}
int main(int argc, char** argv)
{
    int lfd=0, cfd=0;
    int ret=0;
    struct sockaddr_in serv_addr, clit_addr;
    char buf[BUFSIZ], clit_IP[1000];
    socklen_t clit_addr_len;

    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd==-1){
        sys_err("socket error");
    }
    bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(lfd, 127);
    cfd = accept(lfd, (struct sockaddr *)&clit_addr, &clit_addr_len);
    if(cfd==-1){
        sys_err("accept error");
    }
    while(1){
        ret = read(cfd, buf, sizeof(buf));  //server读取来自cfd的buf
        write(STDOUT_FILENO, buf, ret);     //先在server的屏幕上写这串buf
        //  如果用lfd，那么只执行一次就会结束。

        for(int i=0; i<ret; i++){
            buf[i] = toupper(buf[i]);       //server对这些buf进行处理，并保存
        }
        write(cfd, buf, ret);               //写到cfd的屏幕上,注意返回的大小不再是sizeof
    }
    close(lfd);
    close(cfd);

}