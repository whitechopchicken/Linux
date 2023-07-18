#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//fork() 成功的话，父进程返回PID，子进程返回0 ； 失败 返回-1
int main(int argc, char **argv)
{

    pid_t pid;
    int i;

    for(i=0;i<10;i++){
        if(fork()==0) break;
    }
    if(i==10) printf("I'am parent\n");
    else  printf("I'm %d th child\n", i+1);
    
    return 0; 
}
/*
yyshinidaye@DESKTOP-TFE5J52:~/linux/hw/hw1$ ./loop_fork_std
I'm 1 th child
I'm 2 th child
I'm 4 th child
I'm 3 th child
I'm 5 th child
I'm 6 th child
I'm 7 th child
I'm 8 th child
I'm 9 th child
I'am parent
I'm 10 th child
yyshinidaye@DESKTOP-TFE5J52:~/linux/hw/hw1$ 
*/

/*
子进程多的话，其中某些子进程占用cpu的顺序有可能比父进程还晚一些，
甚至比父进程的父进程
也就是bash(打印终端的)还晚。
加sleep(int seconds)可以让进程等待
*/

