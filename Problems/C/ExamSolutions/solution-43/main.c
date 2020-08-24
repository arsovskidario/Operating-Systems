#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

int main()
{
	
     pid_t fid= fork();

     if( fid == -1 ){
	     err(-1,"Failed to fork()");
      }

     if ( fid == 0 ) {
	     //Child
	     //sort
	     int a[2];
	     if( pipe(a) == -1 ) {
		     err(-2,"Failed to pipe first process");
	     }

	     pid_t f1 = fork();
	     if( f1 == -1 ) {
		     err(-3,"Failed to fork in child()");
	     }

	     if( f1 == 0 ) {
		     // Child 
		     // cat
		     close(a[0]);
		     dup2(a[1],1);
		     close(a[1]);

		     if ( execlp("cat","catko",(char*)NULL) == -1 ) {
			     err(-4,"Failed to execute cat");
	  	     }

             } 

	     // Parent will sort 
	     int status;
	     if( wait(&status) == -1 ) {
		     err(-5,"Failed to wait for child(cat)");
             }

	     close(a[1]);
             dup2(a[0],0);
             close(a[0]);

	     if( !WIFEXITED(status) ||  WEXITSTATUS(status) != 0 ) {
		     err(-6,"Cat failed to execute");
             }

	     if( execlp("sort","sortko",(char*)NULL) == -1 ) {
		     err(-7,"Failed to execute sort");
 	     }

     }

     int status;

     if ( wait(&status) == -1 ) {
	     err(-8,"failed to wait for processes to complete");
     }

     if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
	     err(-9,"Executing of processes failed");
     }



     exit(0);
}
