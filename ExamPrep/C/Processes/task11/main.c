#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int succ_counter=0;
	int fail_counter=0;

	for(int i=1;i<=argc;i++) {
		int fid = fork();
		if (fid == -1 ) {
			err(-3,"Failed to fork command");
		}

		if( fid == 0 ) {
		    if(execlp(argv[i],argv[i],(char*)NULL) == -1 )
		    {
			    err(-4,"Failed to execute command");
	            }	    
		}

		// Parent here
		int status;
		wait(&status);

		if( WIFEXITED(status) ) {
			if ( WEXITSTATUS(status) == 0 ) {
				succ_counter++;
			}
			else {
				fail_counter++;
			}
		}
	}


	printf("Failed: %d \nSuccessful: %d \n",fail_counter,succ_counter);


}
