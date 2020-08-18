#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<err.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc !=3){
		errx(-1,"Invalid arguments");
	}

	int fd1 = open(argv[1],O_RDWR);

	if (fd1 == -1){
		err(-2,"Couldn't open first file!");
	}


	int fd2 = open(argv[2],O_RDWR);

	if (fd2 == -1){
		close(fd1);
		err(-3,"Couldn't open second file!");
	}


	int fd3 = open("temp",O_CREAT | O_RDWR | O_TRUNC);
	
	if (fd3 == -1){
		close(fd1);
		close(fd2);
		err(-4,"Couldn't create temp file");
	}


	char c;
	
	int read_size;
	while( (read_size=read(fd1,&c,sizeof(c))) > 0 )
	{
	      if ( (write(fd3,&c,sizeof(c))) != read_size )
		{
			close(fd1);
			close(fd2);
			close(fd3);
			err(-5,"Coudlnt write to temp file");
		}
	}

	lseek(fd1,0,SEEK_SET);

	while( (read_size=read(fd2,&c,sizeof(c)) ) >0 )
	{

		if ( write(fd1,&c,sizeof(c)) != read_size)
		{
			close(fd1);
			close(fd2);
			close(fd3);
			err(-6,"couldnt transfer data to f1");
		}
	}
	
	lseek(fd2,0,SEEK_SET);
	lseek(fd3,0,SEEK_SET);


	while ( (read_size=read(fd3,&c,sizeof(c)) ) > 0 ) 
	{
		if ( write(fd2,&c,sizeof(c)) != read_size)
		{
			close(fd1);
			close(fd2);
			close(fd3);
			err(-7,"Couldnt transfer data to f2");
		}	
	}


	close(fd1);
	close(fd2);
	close(fd3);

}
