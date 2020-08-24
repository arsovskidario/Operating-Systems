#include<unistd.h>
#include<err.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char* argv[]) {

	if( argc !=2 ) {
		errx(1,"Invalid args");
	}

	//find argv[1] -type -printf "%f %T@\n" | sort -nrk2 | head -n 1 | cut -d " " -f 1
	

	int a[2];

	if( pipe(a) == -1 ){
		err(1,"failed to pipe first process");
	}

	int pid=fork();
	if(pid == -1 ) {
		err(2,"Failed to fork");
	}


	if( pid == 0 ) {
		// Child  find
		close(a[0]);

		if( dup2(a[1],1) == -1 ){
			int old=errno;
			close(a[1]);
			errno=old;
			err(3,"Failed to dup");
		}

		close(a[1]);

		if ( execlp("find","find",argv[1],"-type","f","-printf","%f %T@\n",(char*)NULL) == -1 ){
			err(4,"failed to execlp");
		}
	}

	int status;
        if(wait(&status) == -1 ) {
                err(18,"Failed to wait for process to finish");
        }


        if( !WIFEXITED(status) || WEXITSTATUS(status) !=0 ) {
                err(19,"Executions weren't good");
        }


	// Parent again
	
	close(a[1]);

	int b[2];

	if( pipe(b) == -1 ){
		err(6,"Failed to pipe");
	}

	int f2=fork();
	if( f2 == -1) {
		err(7,"Failed to fork");
	}

	if( f2 == 0 ) {
		if( dup2(a[0],0) == -1 ){
			err(8,"Failed to take input from find");
		}

		close(b[0]);

		if( dup2(b[1],1) == -1 ) {
			err(9,"Failed to dup b");
		}


		if ( execlp("sort","sort","-n","-r","-k2",(char*)NULL) == -1 ) {
			err(10,"Failed to sort");
		}
	}
        if(wait(&status) == -1 ) {
                err(18,"Failed to wait for process to finish");
        }


        if( !WIFEXITED(status) || WEXITSTATUS(status) !=0 ) {
                err(19,"Executions weren't good");
        }

	
	// Parent for head -n 1 
	
	close(b[1]);
	
	int c[2];

	if ( pipe(c) == -1 ) {
		err(11,"Failed to pipe c");
	}

	int f3=fork();
	if(f3 == -1 ){
		err(12,"Failed to fork() f2");
	}


	if( f3 == 0 ) {
		// child head -n 1 

		if( dup2(b[0],0) == -1 ){
			err(12,"Failed to connect b pipe");
		}


		if( dup2(c[1],1) == -1) {
			err(13,"failed t o connect c pipe for head");
		}


		if( execlp("head","head","-n1",(char*) NULL) == -1 ) {
			err(14,"Coudn't execute head");
		}
	}

        if(wait(&status) == -1 ) {
                err(18,"Failed to wait for process to finish");
        }


        if( !WIFEXITED(status) || WEXITSTATUS(status) !=0 ) {
                err(19,"Executions weren't good");
        }

	

	// Parent for cut
	close(c[1]);

	int f4=fork();
	if( f4 == -1 ) {
		err(15,"Failed to fork()");
	}

	if( f4 == 0 ) {
		// child cut 
		if( dup2(c[0],0) == -1 ) {
			err(16,"Failed to connect c to cut");
		}

		if( execlp("cut","cut","-d"," ","-f1",(char*)NULL) == -1 ) {
			err(17,"Failed to executec cut");
		}	
	}

	if(wait(&status) == -1 ) {
		err(18,"Failed to wait for process to finish");
	}


	if( !WIFEXITED(status) || WEXITSTATUS(status) !=0 ) {
		err(19,"Executions weren't good");
	}

	exit(0);
}

