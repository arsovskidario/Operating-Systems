#include<stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<err.h>

int main(){
	int fd1 = open("./f2",O_WRONLY);

	if (fd1 == -1){
		err(-1,"Couldn't open file 1");
	}


	int fd2 = open("./f1",O_RDONLY);

	if (fd2 == -1){
		close(fd1);
		err(-2,"Couldn't open second file");
	}

	char c;

	while( read(fd2,&c,sizeof(c)) ) {
		if( errno == -1){
			close(fd1);
			close(fd1);
			err(-3,"Couldn't read from file 2 ");
		}

		if( (write(fd1,&c,sizeof(c)) ) == -1 ){
			close(fd1);
			close(fd2);
			err(-4,"Couldn't write to file 1");

		}
	}
	

	close(fd1);
	close(fd2);
}
