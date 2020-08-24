#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char * argv[])
{
	if ( argc != 3 ){
		errx(-1,"Invalid arguments");
	}


	int fd1 = open(argv[1],O_RDONLY);
	struct stat st;

	if ( fstat(fd1,&st) == -1 ){
		close(fd1);
		err(-2,"Failed to stat file!");
	}

	char* buff = (char*) malloc( sizeof(char) * st.st_size);
	

	if ( read(fd1,buff,st.st_size) != st.st_size)
	{
		err(-3,"Unable to read from first file!");
		close(fd1);
		free(buff);
	}

	close(fd1); // close already existing fd
	fd1=open(argv[1],O_TRUNC | O_WRONLY); // Reopen file and truncate it
	
	char c;
	int fd2=open(argv[2],O_RDWR);
	
	int read_size;	
	while( (read_size=read(fd2,&c,sizeof(c))) > 0 )
	{
		if( write(fd1,&c,sizeof(c)) != read_size)
		{
			close(fd1);
			close(fd2);
			free(buff);

			err(-4,"unable to write to first file");
		}
	}


	close(fd2);

	fd2=open(argv[2],O_TRUNC | O_WRONLY);
	
	if( write(fd2,buff,st.st_size) != st.st_size )
	{
		close(fd1);
		close(fd2);
		free(buff);
		errx(-5,"unable to write to second file");
	}


	close(fd1);
	close(fd2);
	free(buff);
	exit(0);
}
