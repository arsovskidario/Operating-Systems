#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <err.h>

int main(int argc, char* argv[]) {

	if( argc != 2 ){
		err(1,"Invalid arguments!");
	}

	if( execlp(argv[1],argv[1],(char*)NULL) == -1 ){
		err(2,"Failed to execute command! ");
	}
	else {
		printf("Successfully executed %s ",argv[1]);
	}

	exit(0);
}
