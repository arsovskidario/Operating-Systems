#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<err.h>
#include <sys/wait.h>
#include<errno.h>
#include <unistd.h>

//cut -d : -f7 | sort | uniq -c | sort -nrk1
//	      1 0    1 0       1 0
int main() {

	int a[2];

	if( pipe(a) == -1 ){
		err(3,"Failed to pipe");
	}

	int f1 = fork();
	if (f1 == -1 ) {
		err(-1,"Failed to fork");
	}

	if ( f1 == 0 ) {
		//child cut 
		close(a[0]);
		if( dup2(a[1],1) == -1 ) {
			err(-2,"Failed to dup cut process");
		}

		if( execlp("cut","cut","-d",":","-f7","/etc/passwd",(char*)NULL) == -1 )
			err(-3,"Failed to execute cut command");
	}

	// Parent
	
	close(a[1]);

	int b[2];

        if( pipe(b) == -1 ){
                err(3,"Failed to pipe");
        }


	int f2=fork();
	if( f2 == -1 ){
		err(-4,"failed to fork for sort");
	}

	if( f2 == 0 ) {
		// sort
		if( dup2(a[0],0) == -1 ) {
			err(-5,"failed to dup input for sort");
		}

		close(b[0]);
		if( dup2(b[1],1) == -1 ) {
			err(-6,"Failed to dup output for sort");
		}


		if( execlp("sort","sort",(char*)NULL) == -1 ) {
			err(-7,"Failed to execute sort");
		}
	}

	close(b[1]);
	
	int c[2];
        if( pipe(c) == -1 ){
                err(3,"Failed to pipe");
        }

	int f3=fork();
	if(f3 == -1 ) {
		err(-8,"Failed to fork uniq");
	}

	if( f3 == 0 ){
		if( dup2(b[0],0) == -1 ) {
			err(-9,"Failed to dup reading pipe uniq");
		}

		close(c[0]);

		if( dup2(c[1],1) == -1 ) {
			err(-10,"Failed to dup input for pipe uniq");
		}

		if( execlp("uniq","uniq","-c",(char*)NULL) == -1 ){
			err(-11,"Failed to execute uniq");
		}
	}

	// Parent for sort -nrk1
	
	close(c[1]);

	int f4=fork();
	if(f4==-1){
		err(-12,"failed to execute fork for sort-n");
	}

	if( f4 == 0 ) {
	      if( dup2(c[0],0) == -1 ) {
		      err(-13,"Failed to dup2 for final pipe");
	      }

	      if ( execlp("sort","sort","-nk1",(char*)NULL) == -1 ){
		      err(-14,"Failed to execute final sort");
	      }
	}

	int status;

	if( wait(&status) == -1 ) {
		err(-15,"Failed to wait for processes");
	}

	if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
		err(-16,"The execution failed at some point");
	}

	exit(0);

}
