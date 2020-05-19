#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int cmp(const void *a, const void* b){
	u_int32_t x = *((u_int32_t*)a);
	u_int32_t y = *((u_int32_t*)b);

	if(x>y)
		return 1;
	else if (x<y)
		return -1;

	return 0;
}

int main(int argc, char* argv[]){
	
	int fd1=open("f1",O_RDWR);
	
	if(fd1 == -1){
		err(-1,"Failed to open file %d",fd1);
	}

	struct stat st;

	if( fstat(fd1,&st) == -1){
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(-2,"Failed to stat file %d",fd1);
	}

	if( st.st_size % sizeof(u_int32_t) != 0){
		close(fd1);
		errx(1,"Incorrect memory of file %d",fd1);
	}

	// Half the file into two new files because the files will be in the HDD memory
	// If you half the file into buffers it will exceed the RAM LIMIT
	
	int t1 = open("t1",O_CREAT | O_TRUNC | O_RDWR, 00700);

	if (t1 == -1 ){
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(-3,"Couldn't split file %d",t1);
	}

	int halfSize = (st.st_size/sizeof(u_int32_t)) /2;
	void* x = malloc(halfSize * sizeof(u_int32_t));
	if( read(fd1,x,halfSize * sizeof(u_int32_t)) != halfSize*sizeof(u_int32_t)) {
		int olderrno = errno;
		close(fd1);
		close(t1);
		errno = olderrno;
		free(x);
		err(-3,"Couldn't read file %d",fd1);
	}	

	qsort(x,halfSize,sizeof(u_int32_t),cmp);

	if ( write(t1,x,halfSize * sizeof(u_int32_t)) !=  halfSize*sizeof(u_int32_t) ){
		int olderrno = errno;
                close(fd1);
                close(t1);
		free(x);
                errno = olderrno;
                err(-3,"Couldn't write file %d",fd1);
	}

	// Read rest of file 
	
	int t2 = open("t2",O_CREAT | O_TRUNC | O_RDWR, 00700);

        if (t2 == -1 ){
                int olderrno = errno;
                close(fd1);
		close(t1);
		close(t2);
                errno = olderrno;
                err(-3,"Couldn't split file %d",t2);
        }
	

	if( read(fd1,x,halfSize * sizeof(u_int32_t)) == -1) {
                int olderrno = errno;
                close(fd1);
		close(t1);
                close(t2);
		free(x);
                errno = olderrno;
                err(-3,"Couldn't read file %d",fd1);
        }

        qsort(x,halfSize,sizeof(u_int32_t),cmp);

        if ( write(t2,x,halfSize * sizeof(u_int32_t)) == -1 ){
                int olderrno = errno;
                close(fd1);
		close(t1);
                close(t2);
		free(x);
                errno = olderrno;
                err(-3,"Couldn't write file %d",fd1);
        }

	// Read from t1 and t2 and compare the elements and write them to original file
	lseek(fd1,0,SEEK_SET); // return to beginning oringal file 
	lseek(t1,0,SEEK_SET);
	lseek(t2,0,SEEK_SET);

	int i=0;
	int j=0;
	u_int32_t a;
	u_int32_t b;

	if( read(t1,&a,sizeof(a)) == -1){
		int olderrno = errno;
		close(fd1);
		close(t1);
		close(t2);
		free(x);
		errno = olderrno;
		err(-4,"Couldn't read file %d",t1);
	}
	
	if( read(t2,&b,sizeof(b)) == -1){
                int olderrno = errno;
                close(fd1);
                close(t1);
                close(t2);
                free(x);
                errno = olderrno;
                err(-4,"Couldn't read file %d",t2);
        }




	while( i<halfSize && j<halfSize){
		if(a<b){
			if( write(fd1,&a,sizeof(a) ) ==-1){
				int olderrno = errno;
	               		close(fd1);
        	       		close(t1);
               			close(t2);
                		free(x);
               			errno = olderrno;
                		err(-4,"Couldn't write file %d",fd1);
		        	}

			if( read(t1,&a,sizeof(a)) == -1){
		                int olderrno = errno;
                		close(fd1);
                		close(t1);
                		close(t2);
                		free(x);
                		errno = olderrno;
               			err(-4,"Couldn't read file %d",t1);
       				 }

			i++;
		}
		else{ 
			
			if( write(fd1,&b,sizeof(b) ) != sizeof(b)){
                                int olderrno = errno;
                                close(fd1);
                                close(t1);
                                close(t2);
                                free(x);
                                errno = olderrno;
                                err(-4,"Couldn't write file %d",fd1);
                                }

                        if( read(t2,&b,sizeof(b)) == -1){
                                int olderrno = errno;
                                close(fd1);
                                close(t1);
                                close(t2);
                                free(x);
                                errno = olderrno;
                                err(-4,"Couldn't read file %d",t2);
                                 }

			j++;

		}

	}

	while(i<halfSize){
		  if( write(fd1,&a,sizeof(a) ) ==-1){
                                int olderrno = errno;
                                close(fd1);
                                close(t1);
                                close(t2);
                                free(x);
                                errno = olderrno;
                                err(-4,"Couldn't read file %d",fd1);
                                }

                        if( read(t1,&a,sizeof(a)) == -1){
                                int olderrno = errno;
                                close(fd1);
                                close(t1);
                                close(t2);
                                free(x);
                                errno = olderrno;
                                err(-4,"Couldn't read file %d",t1);
                                 }

                        i++;

	}

	while(j<halfSize){
		 if( write(fd1,&b,sizeof(b) ) ==-1){
                                int olderrno = errno;
                                close(fd1);
                                close(t1);
                                close(t2);
                                free(x);
                                errno = olderrno;
                                err(-4,"Couldn't read file %d",fd1);
                                }

                        if( read(t2,&b,sizeof(b)) == -1){
                                int olderrno = errno;
                                close(fd1);
                                close(t1);
                                close(t2);
                                free(x);
                                errno = olderrno;
                                err(-4,"Couldn't read file %d",t2);
                                 }


                        j++;
	}

	close(fd1);
	close(t1);
	close(t2);
	free(x);
	exit(0);
}


