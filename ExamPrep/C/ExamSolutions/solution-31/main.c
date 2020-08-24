#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<errno.h>
#include<err.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int cmp (const void* a, const void* b )
{
	uint8_t x = *((uint8_t*)a);
	uint8_t y = *((uint8_t*)b);
	if ( x  > y) {
		return -1;
	}	
	else if ( x <y )
	{
		return 1;
	}
	return 0;
	//return *((uint8_t*)a) - *((uint8_t*)b);
}

int main( int argc, char* argv[])
{
	if (argc !=2) {
		errx(2,"Invalid arguments");
	}

	struct stat st;

	if ( stat(argv[1],&st) == -1 ) 
	{
		err(3,"Stat failed");
	}


	if( st.st_size == 0 ) 
	{
		errx(3,"Nothing to read from file ");
	}

	int fd;

	if ((fd=open(argv[1],O_RDWR)) == -1)
	{
		err(4,"Coudn't open the file!");
	}


	uint8_t* buff = (uint8_t*) malloc(st.st_size);

	if( read(fd,buff,st.st_size) != st.st_size)
	{
		int olderrno = errno;
		close(fd);
		free(buff);
		errno=olderrno;
		err(5,"Failed to read from file");

	}


	qsort(buff,st.st_size,sizeof(uint8_t),cmp);
	
	close(fd);

	fd= open(argv[1],O_TRUNC | O_WRONLY);
	
	if (fd == -1)
	{
		free(buff);
		err(7,"Failed to clean file");
	}

	if ( write(fd,buff,st.st_size) != st.st_size)
	{
		int olderrno = errno;
		close(fd);
		free(buff);
		errno = olderrno;
		err(6,"failed to write result ot same file");
	}

	close(fd);
	free(buff);
	exit(0);
}
