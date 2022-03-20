#include	<sys/wait.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<stdlib.h>
#include	<stdio.h>
int main(void)
{

	char command[] = "ls";
	char arg1[] = "-la";

	pid_t	pid;

	if ( (pid = fork()) < 0)
		perror("fork error");
	else if (pid == 0) {
		printf("Ez a gyerek processz. pid: %d\n",pid);
		execlp(command, arg1, 0,0);
	} else {
		printf("Ez a szulo processz. pid: %d\n",pid);
		wait(NULL);
	}
	exit(0);
}
