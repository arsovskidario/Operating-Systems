#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd=open("./passwd",O_RDWR);

	if( fd == -1)
	{
		err(-1,"Coudn't open file");
	}


	struct stat st;

	if( fstat(fd,&st) == -1)
	{
		close(fd);
		err(-2,"Coudn't stat file");
	}


	char* buff = (char*) malloc(sizeof(char) * st.st_size);


	if( read(fd,buff,st.st_size) != st.st_size) 
	{
		close(fd);
		err(-3,"Unable to read from file");
	}

	for(int i=0;i<st.st_size;i++)
	{
		if( buff[i] == ':'){
			buff[i]='?';
		}
	}

	close(fd);

	fd = open("./passwd",O_TRUNC | O_WRONLY);

	if ( fd == -1 ) {
		free(buff);
		err(-4,"failed to reopen file");
	}


	if ( write(fd,buff,st.st_size) != st.st_size) 
	{
		close(fd);
		free(buff);
		err(-5,"Failed to write to file");
	}

	printf( "Successfuly transformed file!");

	close(fd);
	free(buff);
	exit(0);

}
