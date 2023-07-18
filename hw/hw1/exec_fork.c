#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//fork() 成功的话，父进程返回PID，子进程返回0 ； 失败 返回-1
//用exec函数，让子进程执行 ls命令 
int main(int argc, char **argv)
{

    pid_t pid;
    pid = fork();
    if(pid==-1){
        perror("fork error\n");
        exit(1);
    }
    else if(pid==0){
        printf("son pid--getpid == %d \n", getpid());
        printf("pid == %d \n", pid);    //子进程的ID并不是这个pid，这个只是返回值
        execlp("ls","ls", "-l","-h", NULL);
        perror("exec error");
        exit(1);
    }
    else if(pid>0){
        printf("son pid:%d \n", pid);
        printf("parent pid: %d\n", getpid());
    }
    
    return 0; 
}


