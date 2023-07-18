
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	printf("程序开始运行");
	//首先创建子进程
	pid_t pid = fork();
	if(pid == -1){
		perror("fork error");
		exit(1);
	}
	if(pid == 0){
		printf("----child process----\n");
	}else if(pid>0){
		printf("----parent process---\n");
	}
	pid_t mypid = getpid();
	pid_t parentppid = getppid();

	printf("parent id == %d \n", mypid);
	printf("ppid = %d \n", parentppid);

	return 0;





}


