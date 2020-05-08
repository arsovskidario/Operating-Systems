#include<stdio.h>
#include<stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if(argc != 3){
		err(1,"Illegal arguments!");
	}

	int fd1;
	int fd2;

	fd1=open(argv[1],O_RDONLY);
	if(fd1 == -1){
		close(fd1);
		err(2,"%s",argv[1]);
	}
	
	fd2=open(argv[2],O_WRONLY | O_CREAT);
	if(fd2 == -1){
		close(fd2);
		err(3,"%s",argv[2]);
	}
	
	char line[4096];
	size_t readBytes;	
	while( (readBytes=read(fd1,&line,sizeof(line)) ) >0 ){
		if( write(fd2,&line,readBytes) != readBytes ){
			close(fd1);
			close(fd2);
			err(4,"Error while writing to file 2 !");
		}	
	}
	
	close(fd1);
	close(fd2);
	exit(0);
}
