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

int main(int argc, char* argv[]){

	if( argc != 3 ) {
		err(-4,"Invalid arguments");
	}

	int fid1 = fork();

	if (fid1 == -1 ) {
		err(-5,"Failed to fork fist process");
	}

	if ( fid1 == 0 ) {
		//child
		if( execlp(argv[1],argv[1],(char*)NULL) == -1 ){
			err(1,"Failed to execute %s",argv[1]);
		}
	}


	int fid2=fork();
	
	if(fid2 == -1 ) {
		err(-2,"failed to fork second process");
	}


	if ( fid2 == 0 ) {
		//child 2
		if( execlp(argv[2],argv[2],(char*)NULL) == -1 ) {
			err(2,"Failed to execute command %s",argv[2]);
		}
	}


	int status;
	
	pid_t cpid=waitpid(-1,&status,0);

	if( WIFEXITED(status) && WEXITSTATUS(status) == 0 ) {
		printf("PID: %d\n",cpid);
	}
	else {
		err(-1,"Error");
	}
}
