#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>

int main(int argc, char* argv[]){ 

	if ( argc !=2 ) {
		err(1,"No arguments !");
	}

	if( execl("/bin/ls","ls",argv[1],(char*)NULL) == -1 ) {
		err(2,"Could execute command!");
	}
	

	exit(0);
}
