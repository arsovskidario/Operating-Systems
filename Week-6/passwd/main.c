#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char* argv[]) 
{
	int fd1;
	fd1 = open("/etc/passwd",O_RDONLY);
	int fd2;
	fd2 = open("passwd.txt",O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);

	if (fd1 == -1){
		close(fd1);
		errx(-1,"Couldn't open /etc/passwd");
	}
	
	if( fd2 == -1) {
		close(fd1);
		close(fd2);
		errx(-2,"Error while creating new file");
	}

	char c;
	while ( read(fd1,&c,sizeof(c)) ) {
		if ( c == ':') {
			c='?';
		}
		
		if( write(fd2,&c,1) != 1) {
			close(fd1);
			close(fd2);
			errx(-3,"Error while writing to new file!");
		}
		
	}
	
	close(fd1);
	close(fd2);
	
	exit(0);
}

