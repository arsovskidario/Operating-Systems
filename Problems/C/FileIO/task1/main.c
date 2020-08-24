#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#include <err.h>
#include <unistd.h>

int main()
{
	int fd1 = open("./f1",O_RDONLY);

	if ( fd1 == -1 ){
		err(-1,"Couldn't open file!");
	}


	int fd2 = open("./f2",O_WRONLY | O_CREAT | O_TRUNC);

	if ( fd2 == -1 ){
		close(fd1);
		err(-2,"Couldn't open second file!");
	}

	
	char c;
	while ( read(fd1,&c,sizeof(c))) {
		if( errno == -1) {
			close(fd1);
			close(fd2);
			err(-3,"Couldn't read from file!");
		}	


		if(write(fd2,&c,sizeof(c)) == -1) {
			close(fd1);
			close(fd2);
			err(-4,"Couldn't write to second file!");
		}


	}


	close(fd1);
	close(fd2);

	exit(0);

}
