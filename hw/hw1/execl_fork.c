#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//fork() 成功的话，父进程返回PID，子进程返回0 ； 失败 返回-1
//用exec函数，让子进程执行 自定义程序
int main(int argc, char **argv)
{

    pid_t pid;
    pid = fork();
    if(pid==-1){
        perror("fork error\n");
        exit(1);
    }
    else if(pid==0){
        execlp("./test","./test", NULL);       //第一个参数和第二个参数一样，就是自定义程序的相对路径
        perror("exec error");
        exit(1);
    }
    else if(pid>0){
        printf("son pid:%d \n", pid);
        printf("parent pid: %d\n", getpid());
    }
    
    return 0; 
}


