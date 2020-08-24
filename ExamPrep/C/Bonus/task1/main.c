#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>

int main(int argc, char* argv[])
{
	if ( argc != 2 ) {
		err(-1,"Invalid arguments");
	}

       char c[16]; // one line= 10 bytes probs idk :D
       int status;

       pid_t pid;
       while ( read(1,c,16) > 0 ) {
	       pid=fork();
	       if ( pid == -1 ) {
		       err(-2,"Fork failed");
	       }

	       if ( pid == 0 ) {
		       // Child
		       if ( execlp(argv[1],argv[1],c,(char*)NULL) == -1 )
		       {
			       err(-1,"Coudn't execute command");
		       }
	       }
	       
	       // Parent
	       if ( wait(&status) == -1 ) {
		       err(-3,"Failed to wait for child");
	       }

	       if( !WIFEXITED(status) && WEXITSTATUS(status) != 0 ) {
		       err(-5,"Command failed to execute!");
	       }

	       memset(c,0,16);
       }
}
