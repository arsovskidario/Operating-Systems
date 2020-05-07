#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	int fd1;
	int fd2;
	int fd3;

	if( (fd1=open(argv[1],O_RDWR) ) == -1)
	{
		close(fd1);
		fprintf(stderr,"Bad file one input\n");
		return -1;

	}
	
	if( (fd2=open(argv[2],O_RDWR) ) == -1)
        {
                close(fd1);
		close(fd2);
                fprintf(stderr,"Bad file two input\n");
                return -1;
        }

	fd3=open("helper",O_CREAT | O_RDWR);

	char ch;
	while( read(fd1,&ch,1) ){
	     write(fd3,&ch,1);
	}

	
	lseek(fd1,0,SEEK_SET);
	lseek(fd3,0,SEEK_SET);

	//Copy f2 to f1 
	while( read(fd2,&ch,1) ){
		write(fd1,&ch,1);
	}
	
	lseek(fd2,0,SEEK_SET);

	while( read(fd3,&ch,1)) {
		write(fd2,&ch,1);
	}
	

	close(fd1);
	close(fd2);
	close(fd3);
	remove("helper");	
	exit(0);
}
