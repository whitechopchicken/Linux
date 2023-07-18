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

    pid_t pid = fork();
    if(pid == -1){
        perror("fork error\n");
        exit(1);
    }else if(pid ==0){
        printf("----child is created\n");
    }else if(pid > 0){
        printf("---parent process: my child is %d\n", pid);
    }
    
    pid_t mypid = getpid();
    pid_t ppid = getppid();
    printf("parent pid == %d\n", mypid);    //这两行后增加的
    printf("====parent ppid==%d\n", ppid);
    printf("====end of file\n");
    

    return 0; 
}

/*执行结果：
            before fork -1
            before fork -2
            before fork -3
            before fork -4
            ---parent process: my child is 4401
            ====end of file
            ----child is created
            ====end of file
    分析：fork() 之前，一切正常；
        fork() 之后，分支由1变成了2==>
        fork()成功，pid > 0 ==>父进程打印
        ==>子进程打印

        与视频教程有点区别就是：两次end of file 打印的顺序不同
        原因：printf() 是两个不同的进程，虽然在同一个终端，
        但是cpu调度进程是随机的。
        "因为异步，两个进程‘同时’ 执行，执行的先后顺序并不知道" 

*/
