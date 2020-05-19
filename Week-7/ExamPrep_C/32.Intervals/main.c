#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>

int main(int argc,char* argv[]) {
	//Stat file
	struct stat st; 
	if(stat("f1",&st) == -1) {
		err(1,"Failed to stat f1");
	}

	if(st.st_size % sizeof(u_int32_t) != 0) {
		errx(2,"Wrong size of f1");
	}

	if(stat("f2",&st) == -1) {
		err(1,"Failed to stat f2");
	}

	if(st.st_size % sizeof(u_int32_t) != 0) {
		errx(2,"Wrong size of f2");
	}

	int fd1;
	fd1=open("f1",O_RDONLY);

	if( fd1 == -1 ) {
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(-1,"Failed to open the first %d",fd1);
	}
	
	int fd2;
	fd2= open("f2",O_RDONLY);

	if( fd2 == -1){
		int olderrno = errno;
		close(fd1);
		close(fd2);
		errno = olderrno;
		err(-1,"Failed to open the second file %d",fd2);
	}

	int fd3;
	fd3 = open("f3",O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);

	if( fd3 == -1){
		int olderrno = errno;
		close(fd1);
		close(fd2);
		close(fd3);
		errno = olderrno;
		err(-2,"Failed to open the read file %d",fd3);
		
	}

	// Read from fd1 into 64bit pair 
	struct pair {
		u_int32_t start;
		u_int32_t end;
	};

	struct pair pr;

	while ( read(fd1,&pr,sizeof(pr)) ) {
		
		// Lseek to the location of the number position 
		// -1 in order not to skip the n-th number
		if (lseek(fd2,(pr.start-1) * sizeof(u_int32_t),SEEK_SET) == -1) {
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fd3);
			errno = olderrno;
			err(-2,"Invalid lseek for f2 %d",fd2);
		}

		for(int i=0;i<pr.end;i++){
			// Read integer from f2 and write to f3
			u_int32_t ch;
			if( read(fd2,&ch,sizeof(ch)) == -1 ) {
				int olderrno = errno;
				close(fd1);
				close(fd2);
				close(fd3);
				errno =olderrno;
				err(-2,"Couldn't read from f2 %d",fd2);
			}	
			
			if( write(fd3,&ch,sizeof(ch)) == -1 ){
				int olderrno = errno;
                                close(fd1);
                                close(fd2);
                                close(fd3);
                                errno =olderrno;
                                err(-2,"Couldn't write to f3 %d",fd3);
			}

		}
	}

	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}

