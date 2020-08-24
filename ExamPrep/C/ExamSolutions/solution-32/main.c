#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main () 
{

	struct  prop{
		uint32_t x;
		uint32_t y;
	};


	int fd1 = open("f1",O_RDONLY);


	if ( fd1 == -1 ) {
		err(-1,"Failed to open file");
	}


	struct stat st;

	if( fstat(fd1,&st) == -1 ) {
		int old =errno;
		close(fd1);
		errno=old;
		err(1,"Failed to stat file");
	}


	if( st.st_size % sizeof(uint64_t) != 0 ) {
		int old=errno;
		close(fd1);
		errno=old;
		err(2,"File size doesnt match read context");
	}

	
	int fd2 = open("f2",O_RDONLY);

	if( fd2 == -1 ) {
		int old=errno;
		close(fd1);
		errno=old;
		err(-2,"Failed to open file : %d",fd2);

	}


	if ( fstat(fd2,&st) == -1 ) {
		int old=errno;
		close(fd1);
		close(fd2);
		errno=old;
		err(3,"Failed to stat file f2");
	}


	if( (st.st_size % sizeof(uint32_t)) !=0 ) {
		int old=errno;
		close(fd1);
		close(fd2);
		errno=old;
		err(4,"F2 doesn't match file size");
	}

	int fd3=open("f3",O_RDWR | O_CREAT | O_TRUNC,0600);

	if ( fd3 == -1 ) {
		int old=errno;
		close(fd1);
		close(fd2);
		errno=old;
		err(5,"F3 can't open");
	}

	struct prop pr;
	while ( read(fd1,&pr,sizeof(pr)) > 0 ) {

		lseek(fd2,pr.x,SEEK_SET);
		
		uint32_t r;
		uint32_t i=0;
		while( read(fd2,&r,sizeof(r)) > 0 ) {

			if( i == pr.y) {
				break;
			}


			if( write(fd3,&r,sizeof(r)) != sizeof(r)) {
				int old=errno;
				close(fd1);
				close(fd2);
				close(fd3);
				errno=old;
				err(-4,"Failed to write to file 3");
			}

			i++;
		}	

	}


	close(fd1);
	close(fd2);
	close(fd3);

	exit(0);
	

}
