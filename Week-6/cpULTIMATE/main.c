#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int tmp;
        tmp=open("helper",O_CREAT|O_TRUNC|O_RDWR);
	for(int i=1;i<argc-1;i++){
		int fd;
		fd=open(argv[i],O_RDONLY);
		
		char line[4096];
		ssize_t line_size;
		while( (line_size=read(fd,&line,sizeof(line))) >0){
			if( (write(tmp,&line,line_size)) != line_size){
				close(fd);
				close(tmp);
				errx(1,"Can't write to file!\n");
			}
		}
			
		close(fd);
	}
	
	lseek(tmp,0,SEEK_SET);
	int dst;
	dst = open(argv[argc-1],O_WRONLY | O_CREAT | O_TRUNC,0644);
	
	char line[4096];
	ssize_t reader_count;
	
	while( (reader_count=read(tmp,&line,sizeof(line)))>0 ){
		if( (write(dst,&line,reader_count)) != reader_count){
			close(tmp);
			close(dst);
			errx(-1,"Cant write to destination!\n");
		}
	}
	
	close(dst);
	close(tmp);
	remove("helper");
	exit(0);
}

