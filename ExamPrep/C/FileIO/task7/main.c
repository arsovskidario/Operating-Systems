#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if( argc < 3) 
	{
		errx(2,"not enough arguments");
	}

	int i=1;
	int dest_fd=open(argv[argc-1],O_WRONLY);
	if (dest_fd == -1){
		err(-1,"Coudn't open destination");
	}


	for(;i<argc-1;i++)
	{
		int fd=open(argv[i],O_RDONLY);
		if(fd == -1)
		{
			close(dest_fd);
			err(-2,"Coudn't open first file");
		}


		struct stat st;

		if ( fstat(fd,&st) == -1 )
		{
			close(dest_fd);
			close(fd);
			err(-3,"Coudn't stat file");
		}

		char* buff = (char*) malloc(st.st_size *sizeof(char));

		if ( read(fd,buff,st.st_size) != st.st_size)
		{
			int olderrno=errno;
			close(dest_fd);
			close(fd);
			free(buff);
			errno=olderrno;
			err(-4,"Coudn't read from file argument");
		}


		if( write(dest_fd,buff,st.st_size) != st.st_size)
		{
			int olderrno = errno;
			close(dest_fd);
			close(fd);
			free(buff);
			errno =olderrno;
			err(-5,"Coudn't write to destination");
		}


		close(fd);
		free(buff);

	}


	close(dest_fd);
}
