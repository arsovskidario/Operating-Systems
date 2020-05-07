#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int fd1;

	if( (fd1=open(argv[1],O_RDONLY)) == -1 ) {
		fprintf(stderr,"No input file!\n");
	}

	int wordCounter=0;
	char ch;
	while( read(fd1,&ch,1) ) {
		wordCounter++;
	}	
	
	fprintf(stdout,"Total words found : %d \n",wordCounter);	
	
	return 0;
}
