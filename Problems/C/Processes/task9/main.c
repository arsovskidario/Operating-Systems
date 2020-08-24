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

int main()
{
	int fd = open("file1",O_CREAT | O_TRUNC | O_RDWR,0600);

	if ( fd == -1 )
	{	
		err(-1,"Failed to open file!");
	}

	int fid=fork();

	if( fid == 0 ) {
		char* f="foo";
	
		if ( write(fd,f,3) !=3 ) {
			int olderrno = errno;
			close(fd);
			errno=olderrno;
			err(-2,"Failed to write to file %d!",fd);
		}

		exit(0);
	}

	int status;

	if( wait(&status) == -1) {
		int olderrno=errno;
		close(fd);
		errno=olderrno;
		err(-5,"Coudn't wait for process to finish");
	}

	if ( ! WIFEXITED(status) )
	{
		int olderrno =errno;
		close(fd);
		errno=olderrno;
		err(-4,"Process foo didn't terminate %d ",WEXITSTATUS(status));
	}

	fid=fork();

	if (fid == 0) {
		char* b ="bar";

		 if ( write(fd,b,3) !=3 ) {
                        int olderrno = errno;
                        close(fd);
                        errno=olderrno;
                        err(-2,"Failed to write to file %d!",fd);
                }

		
		exit(0);

	}


}
