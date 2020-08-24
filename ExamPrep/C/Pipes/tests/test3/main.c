#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<err.h>
#include <sys/wait.h>
#include<errno.h>
#include <unistd.h>
// cat argv | sort | head -n 10 
int main(int argc, char* argv[]) {

	if( argc != 2 ) {
		errx(1,"Invalid arguments");
	}

	int a[2];
	if( pipe(a) == -1 ) {
		err(-1,"Failed to pipe");
	}

	int f1=fork();
	if( f1 == -1 ) {
		err(-2,"failed to fork");
	}

	if( f1 == 0 ) {
		//child write to pipe
		close(a[0]);
		if( dup2(a[1],1) == -1 ) {
			err(-3,"Failed to dup2 first process");
		}

		if( execlp("cat","cat",argv[1],(char*)NULL) == -1 ) {
			err(-4,"Failed to cat file");
		}
	}

	close(a[1]);

	// Child read form pipe;
	int b[2];

	if ( pipe(b) == -1) {
		err(-5,"Failed to pipe second proc");
	}

	int f2=fork();
	if(f2 == -1) {
		err(-6,"Failed to fork()");
	}

	if( f2 == 0 ){
		// Child for sort
		if( dup2(a[0],0) == -1 ) {
			err(-7,"Failed create read pipe");
		}

		close(b[0]);

		if( dup2(b[1],1) == -1 ) {
			err(-8,"Failed to implenet write channe");
		}

		execlp("sort","sort",(char*)NULL);
	}

	// final process;
	close(b[1]);

	int f3=fork();
	if(f3==-1){
		err(-9,"Failed to fork final proc");
	}

	if( f3 == 0 ){
		if(dup2(b[0],0) == -1 ) {
			err(-10,"Failed to create read channel");
		}

		if (execlp("head","head","-n10",(char*) NULL) == -1 ){
			err(-11,"Failed to head input");
		}
	}

	int status;
	if( wait(&status) == -1 ){
		err(-12,"Failed to wait for proce");
	}

	if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
		err(-13,"Failed to execute command final");
	}


	exit(0);
}
