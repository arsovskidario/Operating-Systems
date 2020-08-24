#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) 
{
	if( argc != 3 ) {
		errx(1,"Invalid args");
	}


	char c[16]; // One line read :D
	int counter=0;

	int even= open("tmp1",O_CREAT | O_TRUNC | O_RDWR,0700);

	if( even == -1 ) {
		err(-1,"Failed to find even");
	}

	int noteven = open("tmp2",O_CREAT | O_TRUNC | O_RDWR,0700);

	if(noteven == -1 ) {
		int old=errno;
		close(even);
		errno=old;
		err(-2,"failed to find uneven");
	}

	while ( read(0,c,16) > 0 ) 
	{
		if( (counter % 2) == 0 ) {
			if ( write(even,c,16) == -1 ) {
				int old = errno;
				close(even);
				close(noteven);
				errno = old;
				err(-3,"Coudnt write to tmp file");
			}
		}
		else { 
			if ( write(noteven,c,16) == -1 ) {
                                int old = errno;
                                close(even);
                                close(noteven);
                                errno = old;
                                err(-4,"Coudnt write to tmp file");
                        }

		}
		// Read a line and place into file or string with 
		counter++;
	}


	pid_t fd1 = fork();

	if (fd1 == -1 ) {
		int old = errno;
                close(even);
                close(noteven);
                errno = old;
		err(-5,"Coudn't fork process");
	}

	if( fd1 == 0 ) {
		// Child
		char buf[4096];

		if ( read(even,buf,4096) < 0 ) {
			int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
			err(-6,"Unable to read from tmp file 1");
		}


		if ( execlp(argv[1],argv[1],buf,(char*)NULL) == -1 ) 
		{
                        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
			err(-7,"Unable to execute first command");

		}
	}



	pid_t fd2 = fork();
	        if (fd2 == -1 ) {
                int old = errno;
                close(even);
                close(noteven);
                errno = old;
                err(-5,"Coudn't fork process");
        }

        if( fd2 == 0 ) {
                // Child
                char buf[4096];

                if ( read(even,buf,4096) < 0 ) {
                        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
                        err(-6,"Unable to read from tmp file 1");
                }


                if ( execlp(argv[2],argv[2],buf,(char*)NULL) == -1 )
                {
                        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
                        err(-7,"Unable to execute first command");

                }
        }


	int status;
	if ( wait(&status) == -1 ) {
		        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
			err(-8,"Failed to wait for processes");
	}


	if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
                        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
			err(-9,"Command failed to execute");

	}
	

	// Wait for second process
	  if ( wait(&status) == -1 ) {
                        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
                        err(-8,"Failed to wait for processes");
        }


        if( !WIFEXITED(status) || WEXITSTATUS(status) != 0 ) {
                        int old = errno;
                        close(even);
                        close(noteven);
                        errno = old;
                        err(-9,"Command failed to execute");

        }


	exit(0);

}

