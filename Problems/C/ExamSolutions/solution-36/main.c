#include <sys/types.h>                    
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	int NUMBER_FLAG=0; // false

	if( strcmp(argv[1],"-n") == 0 ) {
		NUMBER_FLAG=1;
	}

 	int NEW_LINE_FLAG=1;
	uint8_t number=1;	

	if( (argc == 1 && NUMBER_FLAG==0) || (argc == 2 && NUMBER_FLAG==1)) {
		// Read from STDIN and print text 
		
		char c;

		while ( read(0,&c,sizeof(c)) > 0 ) {
			if( NEW_LINE_FLAG == 1 ) {
				//Can be tested 
				//write(1,&number,sizeof(number));
				//write(1," ",sizeof(char));
				setbuf(stdout,NULL);
				fprintf(stdout,"%d ",number);
				NEW_LINE_FLAG=0;
			}

			write(1,&c,sizeof(c));

			if(c == '\n') {
				NEW_LINE_FLAG=1;
				number++;
			}
			
			number++;

		}

	}
	else{
		for(int i=1;i<argc;i++) {
			if( strcmp(argv[i],"-") == 0 ) {

				char c;
				while (read(0,&c,sizeof(c)) > 0 ){

					if( NEW_LINE_FLAG == 1 && NUMBER_FLAG==1 ) {
		                                //Can be tested 
                		               	//write(1,&number,sizeof(number));
                                		//write(1," ",sizeof(char));
                                		setbuf(stdout,NULL);
									    fprintf(stdout,"%d ",number);
                                		NEW_LINE_FLAG=0;
                        		}

                        		write(1,&c,sizeof(c));

                      		       if(c == '\n') {
                               	        NEW_LINE_FLAG=1;
                               	        number++;
                       		       }

				}
			}
			else {


				int fd=open(argv[i],O_RDONLY);
			        char c;
                                while (read(fd,&c,sizeof(c)) > 0 ){

                                        if( NEW_LINE_FLAG == 1 && NUMBER_FLAG==1 ) {
                                                //Can be tested 
                                                //write(1,&number,sizeof(number)); 
                                                //write(1," ",sizeof(char));
                                        		setbuf(stdout,NULL);
                                        		fprintf(stdout,"%d ",number);
                                                NEW_LINE_FLAG=0;
                                        }

                                        write(1,&c,sizeof(c));

                                       if(c == '\n') {
                                        NEW_LINE_FLAG=1;
                                        number++;
                                       }

                                }

				close(fd);


			}


			
		}

	}
}
