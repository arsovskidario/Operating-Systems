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

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(-2,"Invalid arguments");
	}

	int fd=open(argv[1],O_RDWR | O_TRUNC | O_CREAT,0700);

	if(fd == -1 ){
		err(1,"Coudn't open file %d",fd);
	}


	int fid = fork();
	if (fid == 0 ){
		char* text="foobar";	
		// 6 is len of text hardcoded
		if( write(fd,text,6) != 6 ) {
			int olderrno=errno;
			close(fd);
			free(text);
			errno=olderrno;
			err(-4,"Coudn't write text to file");
	
		}

		exit(0);

	}
	else if( fid > 0 ) {
		wait(NULL); // wait for child
		lseek(fd,0,SEEK_SET);

		char c;
		int i=0;
		while ( read(fd,&c,sizeof(c)) > 0) {
			if( i%2 == 0 ){
		  		printf("%c ",c);
			}
			else{
				printf("%c",c);
			}

			i++;
		}

		printf("\n");
	}
	else {
		int olderrno =errno;
		close(fd);
		errno = olderrno;
		err(-1,"fork has failed");
	}
}
