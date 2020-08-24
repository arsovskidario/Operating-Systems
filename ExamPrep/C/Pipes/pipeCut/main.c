#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<sys/wait.h>

int main() 
{

	int a[2];

	if ( pipe(a) == -1 ) {
		err(-2,"Coudn't pipe first process");
	}


	pid_t f1=fork();

	if ( f1 == -1 ) {
		err(-3,"Failed to fork ()");
	}


	if( f1 == 0 ) {
		// Child
		// Cut here
		close(a[0]);
		dup2(a[1],1);
		close(a[1]);

		int b[2];

		if ( pipe(b) == -1 ) {
			int old =errno;
			close(b[0]);
			close(b[1]);
			errno=old;
			err(-4,"Failed to pipe second process");
		}

		pid_t f2 = fork();

		if( f2 == -1 ) {
			int old = errno;
			close(b[0]);
			close(b[1]);
			errno=old;
			err(-5,"Failed to fork second process");
		}


		if( f2 == 0 ) {
			// Child sort
			close(b[0]);
			dup2(b[1],1);
			close(b[1]);

			int c[2];

			if ( pipe(c) == -1 ) {
				int old=errno;
				close(c[0]);
				close(c[1]);
				errno=old;
				err(-7,"Failed to pipe third process");
			}

			pid_t f3= fork();

			if( f3 == -1 ) {
				int old=errno;
				close(c[0]);
				close(c[1]);
				errno=old;
				err(-8,"Failed to fork third process");
			}


			if( f3 == 0 ) {
				//Child uniq
				close(c[0]);
				dup2(c[1],1);
				close(c[1]);

				if( execlp("cat","catko","/etc/passwd",(char*)NULL) == -1 ) 
				{
					err(-10,"Failed to cat");
				}


			}

			close(c[1]);
			dup2(c[0],0);
			close(c[0]);

			if( execlp("cut","cutko","-d",":","-f6",(char*)NULL) == -1 ) {
				err(-9,"Failed to cut input");
			}
		}


		close(b[1]);
		dup2(b[0],0);
		close(b[0]);

		if ( execlp("sort","sortko",(char*)NULL) == -1 )
		{
			err(-6,"Failed to sort");
		}
	}

	// Parent cat
	close(a[1]);
	dup2(a[0],0);
	close(a[0]);
	
	if( execlp("uniq","uniqko",(char*)NULL) == -1 ) {
		err(-1,"Failed to execute cat cmd");
	}
		
}
