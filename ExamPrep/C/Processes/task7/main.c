#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	
	if( argc != 4 ) 
	{
		err(-1,"Invalid arguments");
	}


	int fid=fork();

	if( fid == 0 ) 
	{
		// First child 
		int fid1=fork();
		if (fid1 == 0 )
		{
			//Second child
			int fid2=fork();

			if (fid2 == 0) {
				 // Third child 
       			         if ( execlp(argv[1],argv[1],(char*)NULL)  == -1 )
               			 {
                        		err(-2,"Coudn't execute first command");
               			 }
			}
			else if(fid2 >0 ) {
				int status;
				wait(&status);

				if( WIFEXITED(status) ) {
					printf("PID:%d, EXIT_STATUS:%d\n",fid2,WEXITSTATUS(status));
				}

				 if ( execlp(argv[2],argv[2],(char*)NULL)  == -1 )
                                 {
                                        err(-4,"Coudn't execute second command");
                                 }

			}
			else {
				err(-3,"Process failed to fork");
			}
		}
		else if ( fid1 >0 )
		{
			int status;
                        wait(&status);

                        if( WIFEXITED(status) ) {
                                 printf("PID:%d, EXIT_STATUS:%d\n",fid1,WEXITSTATUS(status));
                         }

			 if ( execlp(argv[3],argv[3],(char*)NULL)  == -1 )
                                 {
                                        err(-5,"Coudn't execute third command");
                                 }



		}
		else {
			err(-6,"Failed to fork second commmand");
		}
	}
	else if ( fid > 0 )
	{
		 int status;
                 wait(&status);

                 if( WIFEXITED(status) ) {
                              printf("PID:%d, EXIT_STATUS:%d\n",fid,WEXITSTATUS(status));
                }

	}

	else {
		err(-10,"Failed to fork first command");
	}

	
}
