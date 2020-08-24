#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<err.h>
#include <sys/wait.h>
#include<errno.h>
#include <unistd.h>

// cat file | sort 
int main(int argc, char* argv[])
{

	if( argc !=2 ) {
		err(1,"Invalid arguments");
	}

	int fd=open(argv[1],O_RDONLY);

	if( fd == -1 ) {
		err(-2,"Failed to open file for read");
	}

	int a[2];

	if( pipe(a) == -1 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(-9,"Failed to create pipe");
	}

	int f1=fork();
	if ( f1 == -1 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(-1,"Failed to fork()");
	}


	if( f1 == 0 ) {
		//Child 
		close(a[0]);
		if( dup2(a[1],1) == -1 ) {
			int old =errno;
			close(fd);
			errno=old;
			err(-2,"Failed to dup2 first process");
		}

		if( execlp("cat","cat",argv[1],(char*)NULL) == -1 ){
			int old=errno;
			close(fd);
			errno=old;
			err(-3,"Failed to execute cat on file");
		}
	
	}
	

	// Connect one more pipe
	close(a[1]);
	int f2=fork();
	if(f2 == -1 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(-4,"Failed to fork for second pipe");
	}


	if( f2 == 0 ){
		// Second child 
		// sort
		if( dup2(a[0],0) == -1 ) {
			int old=errno;
			close(fd);
			errno=old;
			err(-6,"Failed to dup2 a[0]");
		}
		
		if( execlp("sort","sort","-n",(char*) NULL) == -1 ){
			int old=errno;
			close(fd);
			errno=old;
			err(-7,"Failed to execute sort ");
		}

	}


	int status;

	if( wait(&status) == -1 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(-8,"Failed to wait for processes");
	}

	if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
		int old=errno;
		close(fd);
		errno=old;
		err(-9,"Execution of process failed in some stage");
	}


	close(fd);
	exit(0);

}
