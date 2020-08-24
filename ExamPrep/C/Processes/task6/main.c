#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if(argc !=2 )
	{
		errx(-2,"Not valid arguments");
	}

	int fid=fork();

	if (fid == 0 )
	{
		if(execlp(argv[1],argv[1],(char*)NULL) == -1){
			err(-3,"Coudn't execute command");
		}
	}
	else if (fid > 0 ) 
	{
		// Parent

		int status;
		wait(&status);

		if (WIFEXITED(status) )
		{
			printf("Command %s executed correctly\n",argv[1]);
		}
	}
	else if ( fid < 0 )
	{
		err(-1,"Failed to fork() process");
	}

	
}
