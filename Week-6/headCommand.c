#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd1;

	if( (fd1 = open(argv[1],O_RDONLY)) == -1 )
	{
		fprintf(stdout,"Bad input\n");
	}
	
	int counter=0;
	char ch;
	while(read(fd1,&ch,1))
	{
		if(counter == 9)
		{
			break;
		}	
		
		fprintf(stdout,"%c",ch);
		
		if(ch == '\n'){
		   counter++;
		}
	}

	close(fd1);
	return 0;
}
