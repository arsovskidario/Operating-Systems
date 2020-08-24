#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
	if (argc != 3 ){
		err(1,"Invalid parametars");
	}

	int fid=fork();
	if (fid <0) {
		err(-1,"fork has failed");
	}

	if (fid == 0 ) {
		// child 

		if( execlp(argv[1],argv[1],(char*)NULL) == -1 ){
			err(-2,"failed to execute first command");
		}
	}

	int status;
	if (wait(&status) == -1 )
	{
		err(-3,"Failed to wait for child process");
	}

	
	// Should you use the execlp command in the parent process
	// Or should you always create a fork() if you want to execute some command 
	// =>12 zadacha 
	if( WIFEXITED(status) ) {
	    if( WEXITSTATUS(status) == 0 ) {
		if (execlp(argv[2],argv[2],(char*)NULL)  == -1 ) {
			err(-4,"Coudn't execute second command");
		}
	    }
	    else {
		    err(-10,"Previous command didn't work");
	   }
	}


	err(42,"First command wasn't exited");
	
}
