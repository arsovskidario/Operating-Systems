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
	int fd=open("../first/fifo1",O_RDONLY);

	if( fd == -1 ) {
		err(-2,"Failed to open fifo pipe");
	}

	char c;
	while ( read(fd,&c,sizeof(c)) > 0 )
	{
		if( write(1,&c,sizeof(c)) == -1 )
		{
			int old=errno;
			close(fd);
			errno=old;
			err(-3,"Failed to write to STDOU");
		}
	}

	exit(0);
}
