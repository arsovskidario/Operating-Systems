#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{

	if ( argc != 2 ) {
		err(5,"Invalid arguments");
	}

	int fd = open(argv[1],O_RDWR);

	if( fd == -1 ) {
		err(1,"Coudn't open file");
	}

	if ( write(fd,"fo",2) != 2 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(3,"Coudn't write fo to file %d",fd);
	}

	int fid=fork();

	if ( fid == -1 ) {
		int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(2,"Failed to fork()");
	}

	if ( fid == 0 ) {
		// Child 
		char* text ="bar\n";

		if ( write(fd,text,3) != 3 ) {
			int olderrno = errno;
			close(fd);
			errno = olderrno;
			err(3,"Child failed to write to file");
		}

		close(fd);
		exit(0);
	}
	
	if ( wait(NULL) == -1 ) {
		int old = errno;
		close(fd);
		errno = old;
		err(-1,"failed to wait for process");
	}

	if ( write(fd,"o\n",2) != 2 ){
		int old = errno;
		close(fd);
		errno = old;
		err(-2,"Parent failed to write to text file");
	}

	close(fd);
}
