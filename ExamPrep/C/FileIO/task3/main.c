#include<stdlib.h>
#include <stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

	if( argc !=2 ){
		errx(-1,"Invalid arguments");
	}

	int fd;

	if ( (fd=open(argv[1],O_RDONLY) ) == -1 ){
		err(-2,"Can't open file");
	}


	int wordCounter=0;
	int charCounter=0;
	int lineCounter=0;

	char c;
	while ( read(fd,&c,sizeof(c)) ){

		if ( errno == -1 ){
			close(fd);
			err(-3,"Couldn't read from file");
		}

		if ( c == '\n' ){
			wordCounter++;
			lineCounter++;
		}

		if ( c  == ' ') {
			wordCounter++;
		}

		charCounter++;
	}


	printf("%d %d %d %s\n",lineCounter,wordCounter,charCounter,argv[0]);

	close(fd);

	exit(0);
}
