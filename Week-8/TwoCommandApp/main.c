#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(int argc, char* argv[]){

	//if (argc !=3){
	//	errx(-11,"Invalid arguments!");
//	}

	int forkId = fork();

	if( forkId == -1 ) {
		err(2,"Wanst able to fork process");
	}
	
	if (forkId == 0 ){
		if( execlp(argv[0],argv[0],NULL) == -1 ){

			err(42,"Excel didn't work");
		}

		exit(0);

	}

	int status;

	wait(&status);

	if( !WIFEXITED(status)){
		errx(42,"Child did not terminate correctyl");
	}

	if( WEXITSTATUS(status) !=0 ){
		errx(42,"Command didnt return 0");
	}

	forkId = fork();

	if( forkId == -1 ) {
                err(2,"Wasnt able to fork process");
        }

	printf("%s",argv[1]);
	if( forkId ==0){

		if ( execlp(argv[1],argv[1],NULL) == -1 ){
			err(42,"Parent wasnt able to execute execl");
		}

		exit(0);

	}


	wait(&status);

	if( status == -1){
		err(-2,"Parent didnt wait for second command ");
	}

	exit(0);
}
