#include<stdlib.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char * argv[]){
	
	if (argc != 2 ) {
		errx(-1,"Invalid arguments");
	}
	

	int fd1;


	if ( (fd1=open(argv[1],O_RDONLY)) == -1){
		err(-2,"Couldn't open file");
	}


	char c;
	int lineCounter=0;	
	while ( read(fd1,&c,sizeof(c)) ) {
		if (errno == -1 ){
			close(fd1);
			err(-3,"Couldn't read from file");
		}

		if( (write(1,&c,sizeof(c)) ) == -1 ) {
			close(fd1);
			err(-4,"Couldn't write to STDOUT");
		}

		if ( c == '\n'){
			lineCounter++;
		}

		if ( lineCounter == 10 ){
			break;
		}

	}

	close(fd1);
	exit(0);
}
