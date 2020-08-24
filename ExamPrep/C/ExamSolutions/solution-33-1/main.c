#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <stdio.h>
#include <errno.h>

int cmp(const void* a, const void* b) {
	return *((uint32_t*)a) - *((uint32_t*)b);
}


int main(int argc, char* argv[])
{
	if(argc != 2 ) {
		errx(1,"invalid args");
	}


	struct stat st;

	stat(argv[1],&st);

	if( (st.st_size %sizeof(uint32_t)) != 0 ) {
		err(-1,"Bad size");
	}

	uint32_t half= ( st.st_size/sizeof(uint32_t)) /2;
	uint32_t* fhalf= malloc( half* sizeof(uint32_t));

	int fd=open(argv[1],O_RDONLY);

	int tmp1=open("tmp1",O_CREAT | O_TRUNC | O_RDWR,0660);

	uint32_t rd;
 	if( (rd=read(fd,fhalf,sizeof(uint32_t) * half)) != sizeof(uint32_t) * half) {
		err(-2,"Error reading");
	}
	
	qsort(fhalf,half,sizeof(uint32_t),cmp);

	write(tmp1,fhalf,sizeof(uint32_t)*half);
	free(fhalf);
	
	uint32_t* rhalf=malloc(half*sizeof(uint32_t));
	int tmp2=open("tmp2",O_CREAT | O_TRUNC | O_RDWR,0660);

	if( (rd=read(fd,rhalf,sizeof(uint32_t) * half)) != sizeof(uint32_t) * half) {
                err(-2,"Error reading");
        }


	qsort(rhalf,half,sizeof(uint32_t),cmp);
	write(tmp2,rhalf,sizeof(uint32_t)*half);


	free(rhalf);

	lseek(tmp1,0,SEEK_SET);
	lseek(tmp2,0,SEEK_SET);

	int result=open("result", O_CREAT | O_TRUNC | O_RDWR,0660);

  uint32_t i=0;
        uint32_t j=0;
        uint32_t c1;
        uint32_t c2;

        while (read(tmp1,&c1,sizeof(c1)) >0 && read(tmp2,&c2,sizeof(c2)) > 0 ){
                if( c1 <= c2 ) {
                        write(result,&c1,sizeof(c1));
                        lseek(tmp2,-1*sizeof(c2),SEEK_CUR);
                        i++;
                }
                else {
                        write(result,&c2,sizeof(c2));
                        lseek(tmp1,-1*sizeof(c1),SEEK_CUR);
                        j++;
                }
        }


        while( i<half && read(tmp1,&c1,sizeof(c1)) > 0 ) {
                write(result,&c1,sizeof(c1));
                i++;
        }

        while( j<half && read(tmp2,&c2,sizeof(c2)) > 0 ) {
                write(result,&c2,sizeof(c2));
                j++;
        }


	close(tmp1);
	close(tmp2);
}
