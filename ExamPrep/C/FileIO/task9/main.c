#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
	if ( argc != 3) 
	{
		err(-1,"Bad arguments");
	}
		

	int fd = open(argv[2],O_RDONLY);

	if( fd == -1)
	{
		err(-2,"Coudn't open file");
	}

	// File check for size
	struct stat st;

	if(fstat(fd,&st) == -1)
	{
		close(fd);
		err(-4,"FAILED TO STAT");
	}

	if( st.st_size == 0 )
	{
		close(fd);
		errx(-7,"File is empty");
	}

	if( (st.st_size % sizeof(u_int16_t) ) !=0 )
	{
		close(fd);
		errx(-6,"Does not contain only u_int16_t numbers");
	}


	u_int16_t max_number=0; // cant be minus
	u_int16_t min_number=65535; // because we are working with u_int16t


	int canPrint=0;

	if( strcmp(argv[1],"--print") ==0 )
	{
		canPrint=1;
	}

	u_int16_t c;
	while( read(fd,&c,sizeof(c)) > 0) 
	{
		if( c > max_number)
		{
			max_number=c;
			
		}

		if( c<min_number)
		{
			min_number=c;
		}


		if(canPrint){
			printf("%d\n",c);
		}

		
	}


	if( strcmp(argv[1],"--min") == 0)
	{
		printf("The minimum is : %d\n",min_number);
	}
	else if(!canPrint) {
		printf("The maximum is : %d\n",max_number);
	}

	close(fd);
	exit(0);


}
