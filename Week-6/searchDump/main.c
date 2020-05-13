#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

u_int16_t maxNumber(int fd) {
	u_int16_t c;
	int max=0;
	while( read(fd,&c,1)){
		if( c > max){
			max = c;
		}		
	}
	
	lseek(fd,0,SEEK_SET);
	return max;
}

u_int16_t minNumber(int fd){
	u_int16_t c;
	u_int16_t min= 65535;
	while( read(fd,&c,1)){
		if( c < min) {
			min=c;
		}
	}
	
	lseek(fd,0,SEEK_SET);
	return min;
}

void print(int fd){
	u_int16_t c;
	while( read(fd,&c,1)) {
		printf("%d\n",c);
	}
}

int main(int argc, char* argv[])
{
	if( argc !=2 ) {
                errx(-2,"Invalid arguments!");
        }
	
	int fd1;
	fd1 = open("dump",O_RDONLY);
	
	if( fd1 == -1){
		errx(-1,"Couldn't find the binary dump!");
	}
	
	char* option=argv[1];
	u_int16_t result;	
	if(strcmp(option,"--max") ==0 ){	
		result = maxNumber(fd1);	
		printf("The max number is : %d\n",result);
	}	
	
	else if( strcmp(option,"--min") ==0 ){
		result = minNumber(fd1);
		printf("Min number is  %d \n ",result);	
	}
	else if ( strcmp(option,"--print") ==0 ){
		print(fd1);
	}
	
	close(fd1);
	exit(0);
}
