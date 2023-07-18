1.信号处理函数：

void do_sigchild(int num)
{
    while(waitpid(0, NULL, WNOHANG) > 0)
        ;
}
这是一个信号处理函数，用于处理子进程退出的信号(SIGCHLD)。在子进程退出时，通过调用waitpid()来回收子进程资源，防止子进程变成僵尸进程。

main函数：

int main(void)
{
    //...

    struct sigaction newact;
    newact.sa_handler = do_sigchild;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGCHLD, &newact, NULL);

    //...
}
在main函数中，设置了SIGCHLD信号的处理方式，即在子进程退出时调用do_sigchild函数进行处理。

创建监听套接字：

listenfd = Socket(AF_INET, SOCK_STREAM, 0);
使用Socket()函数创建一个IPv4的TCP套接字，并将返回的文件描述符存储在listenfd中。

初始化服务器地址结构：

bzero(&serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(SERV_PORT);
通过使用bzero()函数将serv_addr结构体清零，然后设置地址族为IPv4（AF_INET），IP地址为任意地址（INADDR_ANY），端口号为预定义的SERV_PORT。

绑定套接字到服务器地址：

Bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
将套接字绑定到服务器地址，以便接收来自客户端的连接请求。

监听套接字：

Listen(listenfd, 120);
开始监听指定端口上的连接请求，第二个参数表示允许同时排队等待连接的最大数量。

进入主循环，接受连接并创建子进程处理请求：

while(1){
    clit_addr_len = sizeof(clit_addr);
    connfd = Accept(listenfd, (struct sockaddr*)&clit_addr, &clit_addr_len);
    pid = fork();
    if(pid == 0){       //子进程
        //...
    }
}
在主循环中，使用Accept()函数接受客户端的连接请求，返回一个新的连接套接字connfd。然后使用fork()创建一个子进程，子进程处理客户端的请求，父进程继续监听新的连接请求。

子进程处理客户端请求：

if(pid == 0){       //子进程
    Close(listenfd);
    while(1){
        n = Read(connfd, buf, MAXLINE);
        if(n == 0){
            printf("the other side has been closed.\n");
            break;
        }
        printf("recieved from %s at PORT %d\n",
                inet_ntop(AF_INET, &clit_addr.sin_addr, str, sizeof(str)),
                ntohs(clit_addr.sin_port));
        for(i=0; i<n; i++){
            buf[i] = toupper(buf[i]);
        }
        Write(connfd, buf, n);
    }
    Close(connfd);
    return 0;
}
子进程首先关闭监听套接字listenfd，然后进入一个循环来接收客户端发送的数据。使用Read()函数从套接字中读取数据到缓冲区buf，如果读取的数据大小为0，表示客户端已经关闭连接，退出循环。然后打印客户端的IP地址和端口号，将接收到的数据转换为大写字母，并使用Write()函数将转换后的数据发送回客户端。最后关闭连接套接字connfd，并返回0。

以上就是这段代码的分析。它实现了一个简单的并发服务器，可以接收多个客户端的连接请求，并对每个连接进行处理。