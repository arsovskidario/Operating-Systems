#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdint.h>

int cmp(const void* a, const void* b){
	return *((uint32_t*)a) - *((uint32_t*)b);
}


int main()
{
	struct stat st;

	if( stat("./f2",&st) == -1 ) {
		err(1,"Failed to stat");
	}


	if( st.st_size == 0 ) {
		errx(2,"File empty");
	}


	if( (st.st_size% sizeof(uint32_t)) != 0){
		errx(3,"Invalid memory for file!");
	}

	int fd = open("f2",O_RDWR);

	if ( fd == -1 ) {
		err(-1,"failed to open file %d",fd);
	}

	uint32_t half= (st.st_size / sizeof(uint32_t)/2);

	uint32_t* half1=(uint32_t*) malloc(half* sizeof(uint32_t));


	uint32_t rd = read(fd,half1,half*sizeof(uint32_t));
	if( rd != sizeof(uint32_t) * half) {
		int old=errno;
		close(fd);
		free(half1);
		errno=old;
		err(-2,"failed to read from f1");
	}

	qsort(half1,half,sizeof(uint32_t),cmp);


	int t1=open("tmp1",O_CREAT | O_TRUNC | O_RDWR,0660);

	if (t1 == -1) {
		int old=errno;
		close(fd);
		free(half1);
		errno=old;
		err(-3,"Failed to open tmp1 file");
	}


	uint32_t r1=write(t1,half1,half*sizeof(uint32_t));
	if( r1 != sizeof(uint32_t) * half) {
		int old=errno;
		close(fd);
		free(half1);
		errno=old;
		err(-4,"Failed to write to tmp1");
	}

	free(half1); //free from RAM
	//lseek can be checked
	lseek(t1,0,SEEK_SET); // Return pointer to first char of file

	uint32_t* half2=(uint32_t*) malloc(half*sizeof(uint32_t));

	rd=read(fd,half2,sizeof(uint32_t)*half);

	if( rd != half*sizeof(uint32_t)) {
		int old=errno;
		close(fd);
		close(t1);
		free(half2);
		errno=old;
		err(-5,"Failed to read to second buffer");
	}


	qsort(half2,half,sizeof(uint32_t),cmp);

	int t2=open("tmp2",O_CREAT | O_TRUNC | O_RDWR,0660);

	if( t2 == -1 ) {
		int old=errno;
		close(fd);
		close(t1);
		close(t2);
		free(half2);
		errno=old;
		err(-6,"Failed to open tmp2");
	}


	r1 = write(t2,half2,sizeof(uint32_t)*half);
	if( r1 != half * sizeof(uint32_t) ) {
		int old=errno;
                close(fd);
                close(t1);
                close(t2);
                free(half2);
                errno=old;
                err(-7,"Failed to write to tmp2");

	}

	// check lseek if you have time 
	lseek(t2,0,SEEK_SET);
	free(half2); // Free second buffer

	int res=open("result",O_CREAT | O_TRUNC | O_RDWR,0660);

	if( res == -1 ) {
		int old=errno;
		close(fd);
		close(t1);
		close(t2);
		errno=old;
		err(-8,"Failed to create result file");
	}

    uint32_t i=0;
	uint32_t j=0;
	uint32_t c1;
	uint32_t c2;

	while (read(t1,&c1,sizeof(c1)) >0 && read(t2,&c2,sizeof(c2)) > 0 ){
		if( c1 <= c2 ) {
			write(res,&c1,sizeof(c1));
			lseek(t2,-1*sizeof(c2),SEEK_CUR);
			i++;
		}
		else {
			write(res,&c2,sizeof(c2));
			lseek(t1,-1*sizeof(c1),SEEK_CUR);
			j++;
		}
	}


	while( i<half && read(t1,&c1,sizeof(c1)) > 0 ) {
		write(res,&c1,sizeof(c1));
		i++;
	}

	while( j<half && read(t2,&c2,sizeof(c2)) > 0 ) {
                write(res,&c2,sizeof(c2));
                j++;
        }

	close(fd);
	close(t1);
	close(t2);
}

