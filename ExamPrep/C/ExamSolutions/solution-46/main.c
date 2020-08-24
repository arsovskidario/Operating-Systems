#include<unistd.h>
#include<string.h>
#include<err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<errno.h>
#include<stdlib.h>
#include<stdint.h>

int main ( int argc, char* argv[] )
{

	int echo_flag=1; //true 

	if( argc == 2 ) {
		echo_flag=0;
		if(strlen(argv[1]) > 4 ) {
			errx(1,"Invalid command length");
		}
	}

	char* buf = malloc(sizeof(char) * 8);

	uint8_t rd = read(0,buf,sizeof(char)*8);
	if( (rd  > sizeof(char) * 8) )  {
		int old=errno;
		free(buf);
		errno=old;
		err(-1,"Failed to read from STDIN");

	}


	int j=0;
	int len=strlen(buf);
	while(1){

	 // Create max two params
    	char* first= malloc(sizeof(char)*5);
    	char* second=malloc(sizeof(char)*5);
		first[0]='\0';
		second[0]='\0';
		for(int i=0;i<len;i++) {
			if( buf[i] =='\n' || buf[i] ==0x20){
				j++;
				first[i]='\0';
				break;
			}
	
				first[i]=buf[j++];
			}
	
			for(int i=0;i<len;i++){
				if(buf[i] == '\n' || buf[i] == 0x20) {
					j++;
					second[i]='\0';
					break;
				}
	
				second[i]=buf[j++];
			}
	
			if( first[0] == '\0'){
				break;
			}
	
			int fd=fork();
			if( fd == -1 ) {
				int old=errno;
				free(buf);
				errno=old;
				err(-2,"Failed to fork() process");
			}
	
	
			if( fd == 0 ){
			
				if(echo_flag == 1) {
	
				    if( second[0] != '\0'){
						if( execlp("echo","echo",first,second,(char*)NULL) == -1 ){
							int old=errno;
							free(buf);
							errno=old;
							err(-3,"Failed to execute echo");
						}
			        }
				    else{
					      if( execlp("echo","echo",first,(char*)NULL) == -1 ){
	    	                            int old=errno;
	    	                            free(buf);
	    	                            errno=old;
	    	                            err(-3,"Failed to execute echo");
	    	                }
	
					}
	
				}
				else{
				    if( second[0] != '\0'){
						if( execlp(argv[1],argv[1],first,second,(char*)NULL) == -1 ) {
							int old=errno;
							free(buf);
							free(first);
							free(second);
							errno=old;
							err(-4,"Failed to execute cmd from param");
						}
					}
				    else {
					    if( execlp(argv[1],argv[1],first,(char*)NULL) == -1 ) {
	    	                            int old=errno;
	    	                            free(buf);
	    	                            free(first);
	    	                            free(second);
	    	                            errno=old;
	    	                            err(-4,"Failed to execute cmd from param");
	    	            }
	
					}
			      }
			}
	
			//Parent
			int status;
	
			if ( wait(&status) == -1 ) {
				int old=errno;
				free(buf);
				errno=old;
				err(-4,"Failed to wait fro child execution");
			}
	
	
			if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ){
				int old=errno;
				free(buf);
				errno=old;
				err(-5,"Exectuion of child failed to terminate");
			}
	
			if( j == len-1) {
				break;
			}

    }

	exit(0);
}
