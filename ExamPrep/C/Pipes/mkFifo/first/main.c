#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main()
{

	if( mkfifo("fifo1",0700) == -1 ) {
		err(1,"Failed to create a fifo pipe");
	}


	int fd = open("fifo1",O_WRONLY);

	if( fd == -1 ) {
		err(-2,"Failed to open the fifo pipe");
	}


	// Read from STDIN
	char c;
	while(read(0,&c,sizeof(c)) > 0 ) 
	{
		if ( write(fd,&c,sizeof(c)) == -1 ) {
			int old=errno;
			close(fd);
			errno=old;
			err(-3,"Failed to write to fifo pipe");
		}
	}


	exit(0);
}
