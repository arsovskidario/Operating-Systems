#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

int cmp(const void* a, const void*b )
{
	return *((uint16_t*)a) - *((uint16_t*)b);
}

int main(int argc,char* argv[]) {
	if(argc != 3 ) {
		errx(1,"Invalid arguments");
	}

	struct stat st; 
	
	if( stat(argv[1],&st) == -1 ) {
		errx(2,"Coudn't stat file");
	}

	if( st.st_size == 0 ) {
		errx(3,"Emptyi file");
	}

	if( (st.st_size % sizeof(uint16_t)) != 0 ) {
		errx(4,"File has invalid size");
	}

	uint16_t elements= st.st_size / sizeof(uint16_t);
	uint16_t* buf = malloc(elements * sizeof(uint16_t));

	int fd = open(argv[1],O_RDONLY);

	if( fd == -1 ) {
		int old=errno;
		free(buf);
		errno=old;
		err(-1,"Codunt open file input.bin");
	}

	uint16_t rd;
	if( (rd=read(fd,buf,sizeof(uint16_t) * elements)) != (elements * sizeof(uint16_t)) ) 
	{
		int old=errno;
		close(fd);
		free(buf);
		errno=old;
		err(-2,"Coudn't read from input.bin");
	}


	qsort(buf,elements,sizeof(uint16_t),cmp);


	close(fd);
	
	int result = open(argv[2],O_CREAT | O_TRUNC | O_RDWR,0660);

	if( result == -1 ) {
		int old=errno;
		free(buf);
		errno=old;
		err(-3,"Coudnt open output file");
	}


	if( (rd=write(result,buf,sizeof(uint16_t)* elements) ) != (elements * sizeof(uint16_t)) )
	{
		int old=errno;
		close(result);
		free(buf);
		errno=old;
		err(-4,"Coudnt write to output file");
	}

	close(result);
	free(buf);
	exit(0);
}
