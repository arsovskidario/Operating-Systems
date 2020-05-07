#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd1;

	fd1=open(argv[1],O_RDONLY);
	
	if(fd1 == -1)
	{ 
		printf("Can't open file!\n");
		return 1;
	}
	
	int fd2;

        if ( (fd2=open(argv[2],O_WRONLY)) == -1 )
	{
		printf("Can't open source destination!\n");
		return 1;
	}

	char ch;		
	while(read(fd1,&ch,1) )
	{
		printf ("%c\n",ch);
		write(fd2,&ch,1);
	}
	
	close(fd1);
	close(fd2);
	return 0;
}
