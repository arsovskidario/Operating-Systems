#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>

// 
int main()
{
	int pd[2];

	if( pipe(pd) == -1 ){
		err(-1,"Coudn't pipe first process");
	}

	pid_t fd1=fork();

	if( fd1 == -1 ) {
		int old=errno;
		close(pd[0]);
		close(pd[1]);
		errno=old;
		err(-2,"Fork was unsuccesful");
	}


	if ( fd1 == 0 ) {
		// Child  Sort
		close(pd[1]);
		dup2(pd[0],0);
		close(pd[0]);

		int pd1[2];

		if( pipe(pd1) == -1 ) {
			int old=errno;
	                close(pd[0]);
        	        close(pd[1]);
			errno=old;
			err(-3,"Failed to create second pipe");

		}

		pid_t fd2=fork();

		if( fd2 == -1 ) {
			int old=errno;
			close(pd1[0]);
			close(pd1[1]);
			errno=old;
		}

		if( fd2 == 0 ) {
			//Second child Uniq
			close(pd1[1]);
			// Read
			dup2(pd1[0],0);
			close(pd1[0]);

			if ( execlp("uniq","uniq",(char*)NULL) == -1 )
			{
				int old = errno;
				close(pd1[1]);
				errno=old;
				err(-4,"Uniq command failed");
			}
		}
		
		// First child sort
		close(pd1[0]);
		dup2(pd1[1],1);
		close(pd1[1]);

		if( execlp("sort","sort","-n",(char*)NULL) == -1 ) {
			int old=errno;
			close(pd1[0]);
			close(pd1[1]);
			errno=old;
			err(-5,"Sort cmd failed");
		}


	}

	close(pd[0]);
	dup2(pd[1],1);
	close(pd[1]);

	if( execlp("cat","cat","f1",(char*)NULL) == -1 ) {
		err(-10,"Cat failed !!");
	}

	exit(0); // Nothing has failed :)

}
