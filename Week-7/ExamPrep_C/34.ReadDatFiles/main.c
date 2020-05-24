#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){

	if( argc != 5){
		errx(-4,"Invalid arguments");
	}

	// Read from .dat with help of idx and place int f2.dat and modify f2.idx
	
	// .dat % u_int16_t  == 0 ? 
	
	struct idx{
		u_int16_t pos;
		u_int8_t len;
		u_int8_t reserved;
	};

	struct stat st;

	if( stat(argv[1],&st) ){
		err(-1,"couldn't stat file");
	}
	
	if( st.st_size % sizeof(u_int16_t) ){
		errx(-1,"File has inavlid size");
	}

	// Open all files
	// Create struct to take in f1.idx
	// Write to f2
	
	int fd1 = open(argv[1],O_RDONLY);
	if( fd1 == -1){
		err(-2,"Unable to open file f1.dat");
	}

	int fx1= open(argv[2],O_RDONLY);
	if( fx1 == -1){
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(-2,"Unable to open f1.idx");
	}


	int fd2 = open(argv[3],O_RDWR);
	if ( fd2 == -1 ){
		int olderrno= errno;
		close(fd1);
		close(fx1);
		errno = olderrno;
		err(-3,"Unable to open f2.dat");
	}

	int fx2 = open(argv[4],O_RDWR);
	if( fx2 == -1 ){
		int olderrno = errno;
		close(fd1);
		close(fd2);
		close(fx1);
		errno = olderrno;
		err(-3,"Unable to open f2.idx");
	}


	struct idx x;

	u_int16_t current_pos=0x0;
	struct idx y;
	while ( read(fx1,&x,sizeof(x)) ) {

		//set for f2.idx

		y.pos = current_pos;
		y.len = x.len;
		y.reserved = x.reserved;
		
		u_int8_t* buf;

		buf = malloc(sizeof(u_int8_t) *x.len);

		if ( lseek(fd1,x.pos,SEEK_SET) == -1 ) {
			 int olderrno = errno;
	                 close(fd1);
        	         close(fd2);
               		 close(fx1);
			 close(fx2);
               		 errno = olderrno;
               		 err(-5,"Unable to lseek f1.dat");

		}

		if( read(fd1,buf,sizeof(u_int8_t) *x.len) != sizeof(u_int8_t) *x.len){
			int olderrno = errno;
                         close(fd1);
                         close(fd2);
                         close(fx1);
                         close(fx2);
                         errno = olderrno;
                         err(-6,"Unable to read f1.dat");

		}
	
		// Check if string starts with upper letter	
		if( buf[0] <0x41 || buf[0] >0x5A){
			continue;	
		}
		

		// Add the buffer to f2.dat
		// Modify f2.idx to fit the file 
		// Variable that stores previous lseek position of f2.dat 
		// Increase by buffer size lseek position size (x.len) 		
		
		if( write(fd2,buf,sizeof(u_int8_t)*x.len) != sizeof(u_int8_t) *x.len){
			int olderrno = errno;
                         close(fd1);
                         close(fd2);
                         close(fx1);
                         close(fx2);
                         errno = olderrno;
                         err(-6,"Unable to write f2.dat");
		}


		if( write(fx2,&y,sizeof(y)) != sizeof(y) ) {
			int olderrno = errno;
                         close(fd1);
                         close(fd2);
                         close(fx1);
                         close(fx2);
                         errno = olderrno;
                         err(-6,"Unable to write f2.idx");

		}

		current_pos += x.len;

	}

	exit(0);
}
