#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <err.h>
#include<errno.h>

int main(){

	int fd = open("test",O_CREAT | O_TRUNC | O_RDWR,0700);

	if (fd == -1 ){
		err(1,"Couldn't open file");
		close(fd);
	}

	int forkId = fork();

	if ( forkId == -1 ){
                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(2,"Wasn't able to fork process");
        }


	if( forkId == 0 ) {
		if ( write(fd,"foo",3) ==-1 ){
			int olderrno =errno;
			close(fd);
			err(1,"Couldn't write foo ");
		}
		
		exit(0);
	}
	
	// wait(NULL) // Will wait for foo to be written first 
	
	forkId = fork();

	if ( forkId == -1 ){
		int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(2,"Wasn't able to fork process");
	}

        if( forkId == 0 ) {

	 if ( write(fd,"bar",3) ==-1 ){
                        int olderrno =errno;
                        close(fd);
                        err(1,"Couldn't write foo ");
         }

	   exit(0);
	   
	}

	wait(NULL); // will have to wait for procceses before it closes the fd
	close(fd);
	exit(0);
}
