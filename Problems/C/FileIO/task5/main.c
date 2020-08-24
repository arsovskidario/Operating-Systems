#include<stdlib.h>
#include<err.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if ( argc !=3 ) {
		errx(-1,"invalid arguments");
	}


	int fd1 = open(argv[1],O_RDONLY);

	if (fd1 == -1)
	{
		err(-2,"Couldn't open first file");
	}

	struct stat st;

	if( fstat(fd1,&st) == -1 )
	{
		close(fd1);
		err(-3,"Coudn't stat file");
	}


	char* buff = (char*) malloc(sizeof(char) * st.st_size);

	if( read(fd1,buff,st.st_size) != st.st_size ) {
		int olderrno=errno;
		close(fd1);
		free(buff);
		errno=olderrno;
		err(-4,"Couldn't read from first file");
	}




	if ( write(1,buff,st.st_size) != st.st_size){
		int olderrno=errno;
		close(fd1);
		free(buff);
		errno=olderrno;
		err(-6,"Couldnt write to new file");
	}

	close(fd1);
	free(buff);
	exit(0);
}	
