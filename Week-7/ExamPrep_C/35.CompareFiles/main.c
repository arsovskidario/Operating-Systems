#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if( argc != 4){
		errx(-1,"Invalid arguments!");
	}

	struct stat st1;
	struct stat st2;

	if( stat(argv[1],&st1) == -1){
		err(-1,"Failed stat on file 1 ");
	}

	if( stat(argv[2],&st2) == -1){
                err(-1,"Failed stat on file 2 ");
        }

	if( st1.st_size % sizeof(u_int8_t) != 0 ) {
		err(-1,"Invalid size of file 1 ");
	}

	if( st2.st_size % sizeof(u_int8_t) != 0 ) {
                err(-1,"Invalid size of file 2 ");
        }

	int fd1 = open(argv[1],O_RDONLY);	
	if (fd1 == -1 ){
		err(-2,"failed to open file 1");
	}

	int fd2 = open(argv[2],O_RDONLY);
	if ( fd2 == -1){
		int olerrno = errno;
		close(fd1);
		errno = olerrno;
		err(-2,"failed to open file 2");
	}

	int fd3 = open(argv[3],O_RDWR);
	if( fd3 == -1 ){
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(-2,"failed to open file 3");
	}

	struct reader { 
		u_int16_t position;
		u_int8_t originalByte;
		u_int8_t newByte;
	};

	struct reader rd;


	// Read from f2.bin and lseek the f1.bin file 
	// Current position of file is in hex u_int16_t = lseek(fd2,0,SEEK_CUR);
	
	struct Dim2d{
		u_int8_t x;
		u_int8_t y;
	};



	struct Dim2d c1; // f1.bin
	struct Dim2d c2; // f2bin
	u_int16_t cur_pos=0x0; // position to move f1.bin
	// If c1 and c2 dont match than take u_int16_t position
	while( read(fd2,&c2,sizeof(c2))) {

		lseek(fd1,cur_pos,SEEK_SET);

		if( read(fd1,&c1,sizeof(c1)) == -1 ){
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fd3);
			errno = olderrno;
			err(-3,"File 1 can't be read!");

		}

		if( c1.x != c2.x ) {

			rd.position = cur_pos;
			rd.originalByte = c1.x;
			rd.newByte = c2.x;

			// Write changes to patch.bin

			if( write(fd3,&rd,sizeof(rd)) != sizeof(rd)){

				int olderrno = errno;
				close(fd1);
				close(fd2);
				close(fd3);
				errno = olderrno;
				err(-4,"Couldn't write to patch.bin");
			}
		}

		if( c1.y != c2.y ) {

                        rd.position = cur_pos;
                        rd.originalByte = c1.y;
                        rd.newByte = c2.y;

                        // Write changes to patch.bin
                        if( write(fd3,&rd,sizeof(rd)) != sizeof(rd)){

                                int olderrno = errno;
                                close(fd1);
                                close(fd2);
                                close(fd3);
                                errno = olderrno;
                                err(-4,"Couldn't write to patch.bin");
                        }
                }


		
	cur_pos = lseek(fd2,0,SEEK_CUR);


	}

	exit(0);
}
