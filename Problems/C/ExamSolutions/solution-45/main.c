#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

// cat /etc/passwd | cut -d ":" -f 7 | sort | uniq | sort -nk 1

int main() 
{
	int pid=fork();
	if( pid == -1 ) {
		err(1,"Failed to fork main process");
	}


	if( pid == 0 ) {
		// child
		// sort -nrk1
		int a[2];

		if( pipe(a) == -1 ) {
			err(4,"Failed to pipe first process");
		}

		int p1 = fork();
		if( p1 == -1 ) {
			err(5,"Failed to fork()");
		}

		if( p1 == 0 ){
			//Child 
			// uniq
			close(a[0]);
			dup2(a[1],1);
			close(a[1]);

			int b[2];

			if( pipe(b) == -1 ) {
				int old=errno;
				close(b[0]);
				close(b[1]);
				errno=old;
				err(8,"Failed to pipe second process");
			}

			int p2 =fork();
			if(p2 == -1){
                               int old=errno;
                                close(b[0]);
                                close(b[1]);
                                errno=old;
				err(9,"Failed to second fork()");
			}

			if( p2 == 0) {
				// Child
				// sort
				close(b[0]);
				dup2(b[1],1);
				close(b[1]);

				int c[2];

				if ( pipe(c) == -1 ) {
                                int old=errno;
                                close(c[0]);
                                close(c[1]);
                                errno=old;
				err(11,"Failed to pipe second process");
				}

				int p3 = fork();
				if(p3 == -1) {
					int old=errno;
					close(c[0]);
					close(c[1]);
					errno=old;
					err(15,"Failed to fork sort()");
				}

				if( p3 == 0 ){
					//cihld 
					//cut -d ":" -f 7
					close(c[0]);
					dup2(c[1],1);
					close(c[1]);

					int d[2];

					if( pipe(d) == -1 ) {
						int old=errno;
						close(d[0]);
						close(d[1]);
						errno=old;
						err(13,"Failed to pipe cut proecs");
					}
					
					int p4 = fork();

					if( p4 == -1) {
                                                int old=errno;
                                                close(d[0]);
                                                close(d[1]);
                                                errno=old;
                                                err(14,"Failed to fork cut proecs");

					}

					if( p4 == 0 ) {
						// Child 
						// cat /etc/passwd
						close(d[0]);
						dup2(d[1],1);
						close(d[1]);


						if( execlp("cat","cat","/etc/passwd",(char*)NULL) == -1 ) {
							err(16,"Failed to cat etc passswd");
						}
					}

				
					// cut -d ":" "-f7"

					close(d[1]);
					dup2(d[0],0);
					close(d[0]);

					wait(NULL);

					if( execlp("cut","cut","-d",":","-f7",(char*)NULL) == -1 ){
						err(15,"failed to execute cut command");
					}

				}

				// sort

				close(c[1]);
				dup2(c[0],0);
				close(c[0]);
				wait(NULL);
				if( execlp("sort","sort",(char*)NULL) == -1 ) {
					err(12,"Failed to execute sort");
				}
			}
			// uniq
			close(b[1]);
			dup2(b[0],0);
			close(b[0]);

			wait(NULL);

			if( execlp("uniq","uniq","-c",(char*)NULL) == -1 ) {
				err(10,"Failed to execute uniq");
			}
		}

		close(a[1]);
		dup2(a[0],0);
		close(a[0]);
		wait(NULL);
		if( execlp("sort","sort","-n","-k1",(char*)NULL) == -1 ) {
			int old=errno;
			close(a[0]);
			close(a[1]);
			errno=old;
			err(6,"failed to execute cmd");
		}
	}

	// Main parent
	
	int status;

	if( wait(&status) == -1 )
	{
		err(2,"Failed to wait for processes");
	}
	
	if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
		err(3,"Processes failed to execute");
	}
	
	exit(0);
}
