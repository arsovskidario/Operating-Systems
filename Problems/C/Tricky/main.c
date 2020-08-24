#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( )
{

        int fd = open("f1",O_RDWR);

        int pid=fork();

        if ( pid == -1 )
        {
                err(1,"error");
        }

        if( pid == 0 ) {
                //Child
                write(fd,"dariosrce",9);
                close(fd);
                exit(0);
        }

	wait(NULL);

	lseek(fd,0,SEEK_SET);
	char c;
	while( read(fd,&c,sizeof(c)) >0 )
	{
		write(1,&c,sizeof(c));
	}
        close(fd);
        exit(0);
}
