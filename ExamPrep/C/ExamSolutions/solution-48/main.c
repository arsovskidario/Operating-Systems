#include <sys/types.h>
#include<string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include<unistd.h>
#include<errno.h>
#include<err.h>
#include<time.h>

int toInteger(char* set){
	for(size_t i=0;i<strlen(set);i++) {
		if( set[i] >= '0' && set[i] <='9') {
			return set[i] -'0';
		}
	}

	return -1;
}

int main(int argc, char* argv[] )
{
	if( argc < 3 ) {
		err(1,"Invalid commands");
	}

	int fd = open("run.log",O_CREAT | O_TRUNC | O_RDWR,0660);
	if( fd == -1 ) {
		err(-1,"coudn't open run.log");
	}

	struct timer{
		time_t start;
		time_t end;
		int status;
	};

	int counter=1;
	while(1) {
		
		int f1=fork();
		if(f1 == -1 ) {
			int old=errno;
			close(fd);
			errno=old;
			err(-2,"Coudn't fork()");
		}

		struct timer t;

		if( f1 == 0 ) {
			// Child
			
			t.start=time(NULL);

			if( argc > 3 ) {
				if( execlp(argv[2],argv[2],argv[3],(char*)NULL) == -1) {
					int old=errno;	
					close(fd);
					errno=old;
					err(3,"Coudnt execute command Q");
				}
			}
			else {
				if( execlp(argv[2],argv[2],(char*)NULL) == -1 ) {
					int old=errno;
					close(fd);
					errno=old;
					err(3,"Coudnt execute command Q");
				}
			}
		}
		// Parent
		int status;

		if( wait(&status) == -1 ){
                    int old=errno;
                    close(fd);
                    errno=old;
		    err(4,"Failed to wait for processes");
		}

                t.end=time(NULL);
                t.status=status;

		if(counter == 2 && WEXITSTATUS(status) != 0  && (t.end-t.start) < toInteger(argv[1])){
			break;
		}
		else if( WEXITSTATUS(status) == 0 && counter==1 && (t.end-t.start) < toInteger(argv[1])){
			if(write(fd,&t,sizeof(t)) != sizeof(t)) {
				int old=errno;
				close(fd);
				errno=old;
				err(-4,"Failed to write to log file");
			}	

			break;
		}

		counter++;

	}


	exit(0);
}

