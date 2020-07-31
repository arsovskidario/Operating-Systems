#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[]) {
	
	if( argc != 4 ) {
		errx(1,"Invalid arguments !");
	}
	
	int N=3; //number of commands
	
	int forkId;
	for(int i=1;i<=N;i++){

		forkId = fork();
		
		if(forkId >0 ){
			wait(NULL);
		}

		else{
		 
			//Child execute command 
			// If command is successfull the child ends by default ( man 3 execl)

			printf("Process currently executing command %d\n",getpid());

			if ( execlp(argv[i],argv[i],(char*)NULL)  == -1 ) {
				err(2,"Couldn't execute command ");

			}
			
		}

		// Child has finished 
		// If unsuccessfull it has been err exited

	printf("Command %s has been completed!\n",argv[i]);
			
	}


	exit(0);
}
