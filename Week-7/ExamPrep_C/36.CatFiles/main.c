#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int main(int argc, char* argv[]){

	//1. Read from parameters and cat them to stdout 
	//	1.2. If -n count the lines when \n appears
	//2. If no parameters passed print from STDIN
	//3. if - as parametar print from STDIN  o
	
	int isNumbered = 0; // false 

	if ( argc == 1 ) {
		// Print from STDIN	

		u_int8_t c;

		while( read(0,&c,sizeof(c)) ) {
			if ( write(1,&c,sizeof(c)) !=sizeof(c) ){ 
				err(-2,"Couldn't write to stdout");
			}
		}

		exit(0);
	}
	
	int i=1;
	int lineCounter = 1;
	if ( strcmp(argv[1],"-n") == 0 ) {

		isNumbered = 1;
		i=2; // Start from second parameter 
	}


	while ( i<argc ) {

		u_int8_t ch;
		int isNewLine = 1;
		if ( strcmp(argv[i],"-") == 0 ){
		 while( read(0,&ch,sizeof(ch)) ) {

			if ( isNumbered  && isNewLine ) {
                                setbuf(stdout,NULL);
                                printf("%03d  ",lineCounter);
                                fflush(stdout);
                                lineCounter++;
                                isNewLine = 0;

                        }

                        if ( ch == 0x0a ) {
                                isNewLine = 1;
                        }

                        if ( write(1,&ch,sizeof(ch)) !=sizeof(ch) ){
                                err(-2,"Couldn't write to stdout");
                        }
                }



		}
		else {
			int fd = open (argv[i],O_RDWR);

			if( fd == -1) {
				err(-1,"Couldn't open file");
			}

			while( read(fd,&ch,sizeof(ch)) ) {

			if ( isNumbered  && isNewLine ) { 
				setbuf(stdout,NULL);
				printf("%03d  ",lineCounter);
				fflush(stdout);
				lineCounter++;
				isNewLine = 0;

			}

			if ( ch == 0x0a ) {
				isNewLine = 1;
			}
			
				write(1,&ch,sizeof(ch));
			}

			 close(fd);

		}

		i++;
		lineCounter = 1;
	}

	exit(0);
}
