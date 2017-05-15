#include<unistd.h> //for fork
#include<sys/wait.h> //for wait
#include<sys/types.h> //manpages suggests to include for wait
#include<stdlib.h>
#include<stdio.h> //because I got used to include them anywhere

#define MAXCHILDS 9

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
			exit(EXIT_SUCCESS); //but it's a boring child, it kills itself

			//i think there might be an issue, if we dont use exit or at least break
			//because then the child process would continue to create child process,
			//wouldn't it?
		}
		else
		{
			//And here we go with the parent
			continue; //since we "instantly" want the next child to be created
		}
	}

	//now, the above code does nothing else but create 9 childs and let the exit immediatly
	//none of the childs get to this code, but the parent does
	
	for(int kid = 0; kid < MAXCHILDS; kid++)
	{
		//The idea is to wait for ANY child to finish, because we can't know which of the childs would finish next - beside the fact that they ain't doin anything at all...
		int wstatus;
		pid_t pid = waitpid(-1, &wstatus, 0); //-1 = wait for any child, status
							//wstatus = yeah, read manpage
							//0, read manpage again
		printf("%d\n", pid); //because "blabla, unused pid variable error"
			//and it's nice to see how many processes this parent actually waits for
	}
	
	exit(EXIT_SUCCESS);
}
