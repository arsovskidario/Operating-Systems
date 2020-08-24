#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 4 ) {
		errx(1,"Invalid arguments");
	}

	int fd=open(argv[3],O_RDWR | O_TRUNC | O_CREAT,0600);

	if( fd == -1 ) {
		err(-1,"Failed to open file");
	}

	int fid=fork();
	if (fid < 0 ) {
		int olderrno = errno;
		close(fd);
		errno=olderrno;
		err(-2,"Coudn't fork process");
	}


	if ( fid == 0 ) {

		if( execlp(argv[1],argv[1],(char*)NULL) == -1 ) {
			int olderrno =errno;
			close(fd);
			errno = olderrno;
			err(-3,"coudn't execute first command");
		}
	}

	int status;
	if(wait(&status) == -1){
		int olderrno = errno;
		close(fd);
		errno=olderrno;
		err(-10,"Coudn't wait for process to finish");
	}

	if ( WIFEXITED(status) && WEXITSTATUS(status) == 0) {

		for(size_t i=0;i<strlen(argv[1]);i++)
		{
			if ( write(fd,&argv[1][i],sizeof(argv[1][i])) != 1)
			{
				int old=errno;
				close(fd);
				errno=old;
				err(-23,"Coudn't write to file");
			}
		}

		char new_line='\n';

		if ( write(fd,&new_line,sizeof(char)) != sizeof(char)) {
			int old=errno;
			close(fd);
			errno=old;
			err(-23,"Coudn't write to file");
		}
		
	}
	else {
		err(69,"Command has failed it's execution");
	}


	close(fd);

	if( execlp(argv[2],argv[2],(char*)NULL) == -1 )
	{
		int old=errno;
		close(fd);
		errno=old;
		err(-123,"Coudn't execute second command!");
	}
}
