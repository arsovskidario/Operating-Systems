#include <unistd.h>
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
#include<string.h>
// parent <text> 1 > 0 <read_text>  child 
int main(int argc, char* argv[] )
{
	if ( argc != 2 ) {
		errx(2,"Insufficient arguments");
	}

	int pfd[2];

	if ( pipe(pfd) == -1 ) {
		err(1,"failed to create a pipe");
	}

	pid_t pid = fork();
	if ( pid == -1 ) {
		err(2,"Fork failed!");
	}

	if ( pid == 0 ) {
		// child
		close(pfd[1]);

		char c;
		while ( read(pfd[0],&c,sizeof(c)) > 0 ) {

			if( write(1,&c,sizeof(c)) != sizeof(c) ) {
				int old =errno;
				close(pfd[0]);
				errno = old;
				err(-3,"Failed to write to STDOUT");
			}
		}

		close(pfd[0]);
	}
	else {
		// Parent
		close(pfd[0]);
		
		int len =strlen(argv[1]);
		if( write(pfd[1],argv[1],len)  != len ) {
			int old = errno;
			close(pfd[1]);
			errno = old;
			err(-1,"Failed to write to pipe");
		}

		close(pfd[1]);
		wait(NULL); // Wait for child to write to STDOUT
	}

}
