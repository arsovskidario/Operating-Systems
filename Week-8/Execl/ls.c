#include<stdio.h>
#include<stdlib.h>
#include<err.h>
#include<unistd.h>


int main(int argc, char* argv[] ){
	
	if(execl("/bin/ls","ls","-la",(char*)NULL) == -1){
		err(1,"eror");
	}

	printf("Finished with command ");
	
	exit(0);
}
