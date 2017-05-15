#include<unistd.h> //for fork and getpid
#include<sys/wait.h> //for wait
#include<sys/types.h> //manpages suggests to include for wait
#include<stdlib.h>
#include<stdio.h> //because I got used to include them anywhere

#define MAXCHILDS 16

int main(void)
{
	for(int kid = 0; kid < MAXCHILDS; kid++)
	{
		int pid = fork(); //we create a new child
		
		//From here, we have to distinguish between the child and the parent
		if(pid < 0)
		{
			//in which case something terrible happened and we aint gonna
			//do error handling here :^}
			exit(EXIT_FAILURE);
		}
		else if(pid == 0)
		{
			//Here comes the code for the child-process
			printf("Hello, I'm Process #%ld\n", (long)getpid()); //because I have no clue how big this pid_t type actually is, but it may always have enough space in a long :)
			exit(EXIT_SUCCESS);
		}
		else
		{
			//And here we go with the parent
			continue; //since we "instantly" want the next child to be created
		}
	}

	printf("%d child processes have been created.\n", MAXCHILDS);
	exit(EXIT_SUCCESS);
}
