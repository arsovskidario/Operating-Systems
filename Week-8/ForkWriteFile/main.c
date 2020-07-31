#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <err.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main ( int argc, char* argv[]){
	
	if(argc != 2){
		errx(1,"Invalid arguments");
	}

	int forkResult = fork();
	
	int fd;
	if( forkResult == 0 ){
		// Child 

		fd = open(argv[1],O_CREAT | O_RDWR,00700);

		if ( fd == -1 ){
			err(1,"Couldn't open file ");
		}

		if( write(fd,"foobar",6) == -1 ){
			int olderrno = errno;
			close(fd);
			errno = olderrno;
			err(2,"Couldn't write to file !");

		}

		close(fd);
		exit(0);
	}

	wait(NULL);

	fd = open(argv[1],O_RDONLY);

	if( fd == -1 ){
		err(2,"Couldn't open file for read!");
	}
	
	char* buff = malloc(sizeof(char)*6);
	if ( read(fd,buff,sizeof(char)*6) == -1 ) {
		int olderrno = errno;
		close(fd);
		errno = olderrno;
		err(3,"Couldn't read from file !");

	}


	printf("%s\n",(char*)buff);


	exit(0);
}
