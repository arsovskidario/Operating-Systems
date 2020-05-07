#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char* argv[])
{
	int fd1;

	fd1=open(argv[1],O_RDONLY);

	char c[4];
	int counter=0;
	while( (read(fd1,&c,sizeof(c))) > 0)
	{
		fprintf(stdout," ^%d^ ",counter);
		counter++;
		fprintf(stdout,"%s",c);
	}

	return 0; 
}
