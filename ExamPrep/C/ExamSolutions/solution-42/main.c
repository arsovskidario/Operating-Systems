#include<stdlib.h>
#include<err.h>
#include<errno.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>

uint32_t power ( uint32_t num , uint32_t expo){
	for(uint32_t i=0;i<expo;i++){
		num*=num;	
	}

	return num;
}

int main(int argc, char* argv[])
{
	if( argc != 2 ) {
		errx(1,"Invalid arguments");
	}

	struct reader {
		uint32_t id;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t start;
		uint32_t end;
	};
	
	struct reader rd;

	struct stat st;

	if( stat(argv[1],&st) == -1 ) {
		err(2,"Failed to stat file");
	}


	if( st.st_size == 0 ) {
		errx(3,"Empty file");
	}

	if( (st.st_size % sizeof(rd)) != 0 ) {
		errx(4,"Invalid file size");
	}

	int fd= open(argv[1],O_RDWR);

	if( fd == -1 ) {
		err(-1,"Failed to open file");
	}

	uint32_t num_members= st.st_size / sizeof(rd);

	uint32_t sum_time=0;
	while( read(fd,&rd,sizeof(rd)) == sizeof(rd)) {

		sum_time= sum_time + ( rd.end - rd.start);
	}

	if( lseek(fd,0,SEEK_SET) == -1 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(-2,"Failed to lseek file");
	}

	uint32_t avg=sum_time / num_members;
	uint32_t disp=0;

	while( read(fd,&rd,sizeof(rd)) == sizeof(rd)) {
		disp= disp + ( power((rd.end-rd.start)-avg,2));
	}

	disp= disp / num_members;

	 if( lseek(fd,0,SEEK_SET) == -1 ) {
                int old=errno;
                close(fd);
                errno=old;
                err(-2,"Failed to lseek file");
        }


	while( read(fd,&rd,sizeof(rd)) == sizeof(rd)) {
		uint32_t result = power(rd.end-rd.start,2);

		if( result > disp) {
			uint32_t id=rd.id;
			if( write(1,&id,sizeof(id)) != sizeof(id)) {
				int old=errno;
				close(fd);
				errno=old;
				err(-3,"Failed to write user id to STDOUT");
			}
		}
	}

	close(fd);


}
