#include <sys/wait.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include<string.h>

int main()
{
	while(1) {
		char buf[1024];
		ssize_t count;

		count = read(0,buf,sizeof(buf));

		if( count < 0) {
			err(1,"Failed to read from STDIN");
		}

		buf[count-1]='\0';

		if( strcmp(buf,"exit") == 0 ){
			break;
		}


		pid_t pid=fork();
		
		if( pid == -1) {
			err(2,"failed to fork()");
		}

		if( pid == 0 ) {
			// Child
			
			if( execlp(buf,"cmd",(char*)NULL) == -1 ) {
				err(3,"Failed to execute %s",buf);
			}
		}

		int status;

		if( wait(&status) == -1 ) {
			err(4,"Failed to wait for child");
		}

		if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ){
			err(5,"failed to execute cmd");
		}
	}

	exit(0);

}
