#include<unistd.h>
#include<stdio.h>
#include <fcntl.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdlib.h>
#include<err.h>
#include<errno.h>

int main( int argc, char* argv[])
{

	if( argc != 4 ) {
		errx(2,"invalid arguments");
	}

	   struct header{
                uint32_t magic;
                uint8_t hversion;
                uint8_t dversion;
                uint16_t count;
                uint32_t reserved1;
                uint32_t reserved2;
        };


	struct stat st;

        struct header hd;

	if( stat(argv[1],&st) == -1 ){
		err(1,"Failed to stat patch.bin");
	}

	struct data0{
		uint16_t offset;
		uint8_t original;
		uint8_t new;
	};

	struct data1{
		uint32_t offset;
		uint16_t original;
		uint16_t new;
	};

	// Copy files f1.bin to f2.bin
	int f1=open(argv[2],O_RDONLY);
	if( f1 == -1 ) {
		err(-3,"Failed to open f1");
        }	

	int f2=open(argv[3],O_CREAT | O_TRUNC | O_RDWR,0660);

	if( f2 == -1 ) {
		int old=errno;
		close(f1);
		errno=old;
		err(-4,"Failed to open f2");
	}

	uint8_t c;

	while( read(f1,&c,sizeof(c)) > 0 ) {
		if( write(f2,&c,sizeof(c)) != sizeof(c)) {
			int old=errno;
			close(f1);
			close(f2);
			errno=old;
			err(-5,"Failed to write to f2.bin");
		}
	}

	if( lseek(f1,0,SEEK_SET) == -1 ) {
		int old=errno;
		close(f1);
		close(f2);
		errno=old;
		err(-6,"Failed to lseek f1");
	}
	
	 if( lseek(f2,0,SEEK_SET) == -1 ) {
                int old=errno;
                close(f1);
                close(f2);
                errno=old;
                err(-6,"Failed to lseek f2");
        }





	int patch=open(argv[1],O_RDONLY);

	if( patch == -1 ) {
		int old=errno;
		close(f1);
		close(f2);
		errno=old;
		err(-3,"failed to open patch");
	}

	if( read(patch,&hd,sizeof(hd)) != sizeof(hd)) {
		int old=errno;
		close(f1);
		close(f2);
		errno=old;
		err(-4,"Failed to read header");
	}

	if( hd.dversion == 0x00) {
		struct data0 d; 
		while(  read(patch,&d,sizeof(d)) > 0 ) {
				if( lseek(f2,d.offset,SEEK_SET) == -1 ){
	    		            int old=errno;
        		                close(f1);
        		                close(f2);
        		                close(patch);
        		                errno=old;
					err(-5,"Failed to lseek() f2");
			}
	
						uint8_t b;
						int rd=read(f2,&b,sizeof(b));
						if( rd == -1 ){
		        		                int old=errno;
		        		                close(f1);
		        		                close(f2);
		        		                close(patch);
		        		                errno=old;
							err(-6,"failed to read from f2");
						}

						if(b != d.original) {
		       		                int old=errno;
		       		                close(f1);
		       		                close(f2);
		       		                close(patch);
		       		                errno=old;
						errx(-7,"Bytes dont match");
						}
					
								if( lseek(f2,-1*sizeof(uint8_t),SEEK_CUR) == -1 )
								{
		    		    		                int old=errno;
		    		    		                close(f1);
		    		    		                close(f2);
		    		    		                close(patch);
		    		    		                errno=old;
									err(-9,"coudn't lseek back f2");
		
						}
	
					if( write(f2,&d.new,sizeof(d.new)) < 0 ) {
	        		                int old=errno;
	        		                close(f1);
	        		                close(f2);
	        		                close(patch);
	        		                errno=old;
							err(-8,"Coudn't write new byte");
				}

	       }


	}
	else{
		struct data1 d;
		while(read(f1,&d,sizeof(d)) > 0 ){
			if( lseek(f2,d.offset,SEEK_SET) == -1 ){
	    		            int old=errno;
        		                close(f1);
        		                close(f2);
        		                close(patch);
        		                errno=old;
					err(-5,"Failed to lseek() f2");
			}
			uint16_t b;
			int rd=read(f2,&b,sizeof(b));
						if( rd == -1 ){
		        		                int old=errno;
		        		                close(f1);
		        		                close(f2);
		        		                close(patch);
		        		                errno=old;
							err(-6,"failed to read from f2");
	
					}
	
					if(b != d.original) {
	        		                int old=errno;
	        		                close(f1);
	        		                close(f2);
	        		                close(patch);
	        		                errno=old;
						errx(-7,"Bytes dont match");
	
						}
					
								if( lseek(f2,-1*sizeof(uint8_t),SEEK_CUR) == -1 )
								{
		    		    		                int old=errno;
		    		    		                close(f1);
		    		    		                close(f2);
		    		    		                close(patch);
		    		    		                errno=old;
									err(-9,"coudn't lseek back f2");
		
						}
	
					if( write(f2,&d.new,sizeof(d.new)) < 0 ) {
	        		                int old=errno;
	        		                close(f1);
	        		                close(f2);
	        		                close(patch);
	        		                errno=old;
							err(-8,"Coudn't write new byte");
				}

		}

	}

	close(patch);
	close(f1);
	close(f2);
	exit(0);

	

}
