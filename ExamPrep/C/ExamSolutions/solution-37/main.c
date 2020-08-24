#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
	if( argc != 4 ) {
		err(1,"Invalid arguments");
	}

	struct reader{
		uint16_t offset;
		uint8_t original;
		uint8_t fake;
	};

	struct reader rd;

	struct stat st;

	if( stat(argv[1],&st) == -1 ) {
		err(2,"Patch.bin coudn't stat");
	}


	if( st.st_size == 0 ) {
		err(3,"patch bin is empty");
	}


	if( (st.st_size % (sizeof(rd))) != 0 ){
		err(4,"Patch.bin has invalid size");
	}


	int patch=open(argv[1],O_RDONLY);

	if ( patch == -1 ) {
		err(-1,"failed to open patch.bin");
	}

	int fd1=open(argv[2],O_RDONLY);

	if ( fd1 == -1 ) {
		int old=errno;
		close(patch);
		errno=old;
		err(-2,"Coudn't open f1.bin");
	}


	int fd2=open(argv[3],O_CREAT | O_TRUNC | O_RDWR,0660);

	if( fd2 == -1 ) {
		int old=errno;
		close(patch);
		close(fd1);
		errno=old;
		err(-3,"Coudn't open f2.bin");
	}

	// Copy fd1 to fd2
	
	uint8_t n;

	while( read(fd1,&n,sizeof(n)) == sizeof(n)) {
		if( write(fd2,&n,sizeof(n)) != sizeof(n)) {
			int old=errno;
			close(patch);
			close(fd1);
			close(fd2);
			errno=old;
		}
	}



	close(fd1);

	//Test lseek
	lseek(fd2,0,SEEK_SET);

	while ( read(patch,&rd,sizeof(rd)) == sizeof(rd)) {

		if( lseek(fd2,rd.offset,SEEK_SET) == -1 ) {
			int old=errno;
			close(patch);
			close(fd2);
			errno=old;
			err(-4,"Coudn't lseek f1.bin");
		}

		uint8_t c;

		if( read(fd2,&c,sizeof(c)) != sizeof(c)) {
			int old=errno;
			close(patch);
			close(fd2);
			errno=old;
			err(-5,"Coudnt read from f1.bin");

		}


		if( c == rd.original) {

			// Test lseek and write 
			lseek(fd2,-1,SEEK_CUR);

			write(fd2,&rd.fake,sizeof(rd.fake));
		}	
		else {
			int old=errno;
			close(patch);
			close(fd2);
			errno=old;
			errx(-6,"Original byte doesn't exist");
		}
	}


	close(fd2);
	close(patch);
}
