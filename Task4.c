#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void ChildTerminated(int);
int childIsTerminated = 0;

int main(void)
{
	int pid = fork();
	
	if(pid == 0)
	{
		//child
		printf("[CHILD] My Pid is: %d\n", getpid());
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0)
	{
		//parent
		signal(SIGCHLD, ChildTerminated);
		int wstatus;
		waitpid(pid, &wstatus, 0);
		while(!childIsTerminated)
			sleep(1);
		
		printf("[PARENT] I'm sure my child is dead.\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		perror("fork failed\n");
		exit(EXIT_FAILURE);
	}
}

void ChildTerminated(int sig)
{
	signal(SIGCHLD, SIG_IGN);
	printf("[PARENT] Child died.\n");
	childIsTerminated = 1;
	signal(SIGCHLD, ChildTerminated);
	if(sig == -1) return; //cuz waaah "unused parameter" blabla
}