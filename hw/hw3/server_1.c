#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "wrap.h"
#include <ctype.h>

#define SERV_PORT 1249
#define IP_SIZE 100
#define MAXLINE 80

void do_sigchild(int num)   //函数名作为值传递给 sigaction.sa_handler   
{                           //作用： 处理子进程的退出信号。  在子进程退出时，通过调用waitpid() 来回收子进程资源，防止子进程变成 僵尸进程
    while(waitpid(0, NULL, WNOHANG) > 0)// waitpid() 用来等待子进程退出，并回收子进程资源。 
    ;                                   //0 表示等待任意子进程退出 ； NULL 表示不关心子进程的退出状态 ； 
                                        //WNOHANG 使waitpid（）以非阻塞方式运行， 如果没有子进程退出， waitpid()立即返回，而不会阻塞父进程
    //该循环意义： 如果存在已经退出的子进程，则进入循环体继续等待并回收子进程的资源。
}

int main(void)
{
    struct sockaddr_in serv_addr, clit_addr ;
    socklen_t clit_addr_len ;
    int listenfd, connfd ;
    char buf[MAXLINE];          //作用：
    char str[INET_ADDRSTRLEN];  //作用：
    int i, n;           //i：计数变量，n 接收客户端发送的buf大小
    pid_t pid;          //记录进程id

    struct sigaction newact;    //作用
    newact.sa_handler = do_sigchild;
    sigemptyset(&newact.sa_mask) ;      //作用：
    newact.sa_flags = 0 ;
    sigaction(SIGCHLD, &newact, NULL);      //作用：
    
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET ;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    Listen(listenfd, 120);
    printf("Accepting connections ....\n");
    
    while(1){
        clit_addr_len = sizeof(clit_addr);
        connfd = Accept(listenfd, (struct sockaddr*)&clit_addr, &clit_addr_len);
        pid = fork();
        if(pid == 0){       //子进程
            Close(listenfd);
            while(1){
                n = Read(connfd, buf, MAXLINE);
                if(n == 0){
                    printf("the other side has been closed.\n");
                    break;
                }
                printf("recieved from %s at PORT %d\n",     //打印客户端ip
                        inet_ntop(AF_INET, &clit_addr.sin_addr, str, sizeof(str)), 
                        ntohs(clit_addr.sin_port));
                for(i=0; i<n; i++){
                    buf[i] = toupper(buf[i]);
                }
                Write(connfd, buf, n);//写回客户端
            }
            Close(connfd);
            return 0;
        }
    }


}