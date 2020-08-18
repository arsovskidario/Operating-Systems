#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if( argc !=2 )
	{
		errx(2,"Invalid arguments");
	}


	int fd1 = open(argv[1],O_RDONLY);

	if(fd1 == -1)
	{
		err(-1,"Coudn't open file dump");
	}

	struct stat st;

	if( fstat(fd1,&st) == -1 )
	{
		close(fd1);
		err(-2,"Coudn't stat file");
	}

	if( st.st_size == 0 )
	{
		close(fd1);
		errx(3,"file is empty");
	}


	u_int8_t c;
	u_int8_t max_number=0;
	while( read(fd1,&c,sizeof(c)) > 0)
	{
		if( c > max_number)
		{
			max_number=c;
		}

	}

	if( errno == -1)
	{
		close(fd1);
		errx(-10,"Read wasn't able to read from file");
	}

	printf("The maximum number found is: %d\n",max_number);

	close(fd1);
	exit(0);
}
