#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int comparator(const void* a, const void*b){
	return *((unsigned char*)a) - *((unsigned char*)b);
}

int main (int argc, char* argv[]) 
{
	if ( argc != 2) {
		errx(1,"Invalid arguments!");
	}
	
	int fd;
	fd = open(argv[1],O_RDONLY);

	if ( fd == -1){
		close(fd);
		err(2,"Couldn't open file");
	}
	
	struct stat st;
        if( fstat(fd,&st) == -1){
                err(2,"Failed to stat file");
        }

	void* buff;
	buff =  malloc(st.st_size);	
	
	if( read(fd,buff,st.st_size) != st.st_size) {
		err(3,"Error while writing to file");
	}	

	qsort(buff,st.st_size,1,comparator);
	
	int fd1;
	fd1=open("tmp",O_CREAT | O_WRONLY,S_IRUSR);	
	if( write(fd1,buff,st.st_size) != st.st_size){
		err(4,"Error whiel writing to new file");
	}	

	free(buff);
	close(fd);

	exit(0);
}
