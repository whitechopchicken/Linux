#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//fork() 成功的话，父进程返回PID，子进程返回0 ； 失败 返回-1
int main(int argc, char **argv)
{
    printf("before fork -1\n");
    printf("before fork -2\n");
    printf("before fork -3\n");
    printf("before fork -4\n");

    for(int i=0;i<5;i++){
        pid_t pid = fork();
        pid_t mypid = getpid();
        printf("this is %d th fork \t", i+1);
        printf("it'pid = %d \t", mypid);
        printf("fork() pid = %d\n", pid);
    }
    
    
    return 0; 
}


