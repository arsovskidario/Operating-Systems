#include<stdio.h>
#include<stdlib.h>
#include<err.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
	if(argc ==1){
		errx(1,"Nothing to read");
	}
	
	char line[4096];
	for(int i=1;i<argc;i++) {
		int fd;
		fd=open(argv[i],O_RDONLY);

		if( fd ==-1 ){
			errx(1,"%s: can't be read\nExiting...",argv[i]);
		}	
		
		while(read(fd,&line,sizeof(line)) ){
			fprintf(stdout,"%s",line);	
		} 
		
		close(fd);	
	}

	exit(0);
}
