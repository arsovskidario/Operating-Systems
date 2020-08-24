#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main( int argc, char* argv[] )
{
	if ( argc != 4 ) {
		err(1,"Invalid arguments");
	}

	struct stat st1;
	struct stat st2;

	if( stat(argv[1],&st1) == -1 ){
		err(4,"Coudn't stat f1");
	}

	if( stat(argv[2],&st2) == -1 )
	{
		err(5,"Coudn't stat f2");
	}


	if( st1.st_size != st2.st_size) {
		errx(6,"f1 and f2 don't have same size");
		
	}	


	int f1 = open(argv[1],O_RDONLY);

	if( f1 == -1 ) {
		err(2,"Coudn't open file f1 ");
	}

	int f2 = open(argv[2],O_RDONLY);

	if( f2 == -1 ) {
		err(3,"Coudn't open file f2");
	}


	int patch=open(argv[3],O_RDWR);

	if( patch == -1 ) {
		err(4,"Coudn't open patch file");
	}


	struct put{
		uint16_t offset;
		uint8_t f1char;
		uint8_t f2char;
	};

	uint8_t c1;
	uint8_t c2;

	int test1;
	int test2;

	struct put p;
	while ( (test1=read(f1,&c1,sizeof(c1))) && (test2=read(f2,&c2,sizeof(c2))) ) {

		if( c1 != c2 ) {
			p.offset=lseek(f1,0,SEEK_CUR)-1;

			if(p.offset  == (uint16_t)-1 ) {
				int old=errno;
				close(f1);
				close(f2);
				close(patch);
				errno=old;
				err(-4,"Coudn't lseek() file");
			}

			p.f1char=c1;
			p.f2char=c2;

			if( write(patch,&p,sizeof(p)) != sizeof(p)) {
				int old=errno;
                                close(f1);
                                close(f2);
                                close(patch);
                                errno=old;
                                err(-4,"Coudn't lseek() file");
			}

		}
	}

	if( test1 < 0 || test2<0) {
		int old=errno;
		close(f1);
		close(f2);
		close(patch);
		errno=old;
		err(-2,"Coudn't read from file f1 and f2");
	}

}
/*
 *
 * if( size of files doesn't match then end program);
 * */

