#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int fd = open("f1",O_RDWR);

	int pid= fork();

	if ( pid == 0 ){
		// Child
		
		write(fd,"dario",5);
		close(fd);
		exit(0);
	}


	char* dar = (char*) malloc(sizeof(char)*5);

	read(fd,dar,5);

	printf("%s",dar);
	close(fd);
	exit(0);
}
