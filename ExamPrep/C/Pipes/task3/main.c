#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//   1 | 0 wc -l

int main(int argc, char* argv[] ) 
{
	if ( argc != 2 ) {
		err(-1,"Invalid arguments");
	}

	int fd[2];

	if ( pipe(fd) == -1 ) 
	{
		err(-2,"Failed to pipe ");
	}

	pid_t pid=fork();

	if ( pid == -1 ) {
		err(-3,"Failed to fork()");
	}

	if(  pid==0 ) {
		//Child
		close(fd[1]);

		dup2(fd[0],0);
		if ( execlp("wc","wc","-c",(char*)NULL) == -1 ) {
			int old = errno;
			close(fd[0]);
			errno = old;
			err(-5,"Coudn't execute wc -c ");
		}
		
	}

	close(fd[0]);

	int len = strlen(argv[1]);

	if ( write(fd[1],argv[1],len) != len ) 
	{
		int old = errno;
		close(fd[1]);
		errno = old;
		err(-7,"Failed to write to pipe %d",fd[1]);
	}

	// Should I test close here 
	close(fd[1]);

	int status;
        if( wait(&status) == -1 ) {
                int old = errno;
                close(fd[1]);
                errno=old;
                err(-6,"Failed to wait for child");
        }


	if( !WIFEXITED(status) ||  WEXITSTATUS(status) != 0 ) 
	{
		err(-7,"Child process failed to execute command");
	}


	exit(0);
}
