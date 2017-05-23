#define _POSIX_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void SigHandler(int);
int childFinish = 0;

int main(void)
{
	//we create a second process
	int pid = fork();
	
	if(pid < 0)
	{
		perror("error on fork\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("[CHILD] Hello\n");
		printf("[CHILD] Registering SigHandler for SIGUSR1\n");
		signal(SIGUSR1, SigHandler);
		printf("[CHILD] Ignoring SIGUSR2\n");
		signal(SIGUSR2, SIG_IGN);
		int passedSeconds = 0;
		
		while(!childFinish)
		{
			printf("[CHILD] Waiting for a signal\n");
			fflush(stdout);
			sleep(1);
			//install it after 15 seconds
			if((++passedSeconds) == 15)
				signal(SIGUSR2, SigHandler);
		}
		printf("[CHILD] finish\n");
		fflush(stdout);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("[PARENT] Hello\n");
		//install handler for sigalarm
		printf("[PARENT] Registering SigHandler for SIGALARM\n");
		signal(SIGALRM, SigHandler);
		for(int i = 2; i >= 0; i--)
		{
			//setting alarm-clock
			printf("[PARENT] Setting Alarm Clock\n");
			alarm(5); //this sends signal every 5 seconds to parent
			printf("[PARENT] Waiting for alarm...\n");
			fflush(stdout);
			pause();
			printf("[PARENT] Sending SIGUSR1\n");
			fflush(stdout);
			kill(pid, SIGUSR1);
		}
		sleep(2); //because otherwise the SIGUSR2 might not be listening
		
		printf("[PARENT] Sending SIGUSR2\n");
		fflush(stdout);
		kill(pid, SIGUSR2);
		
		int wstatus;
		waitpid(pid, &wstatus,  0);
		printf("[PARENT] finish\n");
		exit(EXIT_SUCCESS);
	}
}

void SigHandler(int sig)
{
	printf("handler called\n");
	
	//we ignore the signal while the function executes
	signal(sig, SIG_IGN);
	
	switch(sig)
	{
		default:
		case SIGUSR1:
			printf("[CHILD] SIGUSR1 received\n");
			break;
		case SIGUSR2:
			printf("[CHILD] SIGUSR2 received\n");
			childFinish = 1;
			break;
		case SIGALRM:
			printf("[PARENT] SIGALRM received\n");
			break;
	}
	
	//reinstall it
	signal(sig, SigHandler);
}