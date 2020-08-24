#include<stdlib.h>
#include<stdint.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
	if ( argc != 5 ) {
		err(1,"Invalid arguments");
	}

	struct reader{ 
		uint16_t pos;
		uint8_t len;
		uint8_t no;
	};


	struct stat st;

	if( stat(argv[2],&st) == -1 ) {
		err(2,"Failed to stat");
	}


	if( st.st_size == 0 ) {
		err(3,"Empty file");
	}


	if( (st.st_size%sizeof(uint32_t)) !=0 ) {
		err(3,"File is not of valid type");
	}

	int fd1=open(argv[1],O_RDWR);

	if( fd1 == -1 ) {
		err(-1,"Failed to open the file");
	}

	int fd2=open(argv[2],O_RDWR);

	if( fd2 == -1 ) {
		err(-2,"Failed to open first idx file");
	}

	int ff1=open(argv[3],O_CREAT | O_TRUNC | O_RDWR,0660);

	if ( ff1 == -1 ) {
		int old=errno;
		close(fd1);
		close(fd2);
		errno=old;
		err(-6,"Fialed to open temp file dat");
	}

	int ff2 = open(argv[4],O_CREAT | O_TRUNC | O_RDWR, 0660);

	if( ff2 == -1 ) {
		int old =errno;
		close(fd1);
		close(fd2);
		close(ff1);
		errno=old;
		err(-7,"Failed to open temp file idx");
	}

	struct reader rd;
	struct reader result;
	result.pos=0;
	result.no=0;
	while( read(fd2,&rd,sizeof(rd)) > 0) {
		
		if ( lseek(fd1,rd.pos,SEEK_SET) == -1 ) {
			int old=errno;
			close(fd1);
			close(fd2);
			errno=old;
			err(4,"Failed to set lseek");
		}

		uint8_t counter=1;
		uint8_t c;
		
		
		if( (read(fd1,&c,sizeof(c)) <= 0) || (c<0x41 ||  c>0x5A)){
			continue;
		}

		if( write(ff1,&c,sizeof(c)) <= 0 ){
			int old=errno;
			close(fd1);
			close(fd2);
			errno=old;
			err(5,"Codunt write to file");
		}

		while( read(fd1,&c,sizeof(c)) > 0 ) {

			if(counter>=rd.len) {
				break;
			}

		        if( write(ff1,&c,sizeof(c)) <= 0 ){
                        int old=errno;
                        close(fd1);
                        close(fd2);
                        errno=old;
                        err(5,"Codunt write to file");
                	}

			counter++;
		}

		//write(ff2,&pos,sizeof(pos));
                //write(ff2,&rd.len,sizeof(rd.len));

		result.len=rd.len;

		write(ff2,&result,sizeof(result));

		result.pos=result.pos+rd.len;

	}

	close(fd1);
	close(fd2);
	close(ff1);
	close(ff2);
}
