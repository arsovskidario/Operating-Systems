#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<err.h>
#include<stdlib.h>
#include<stdio.h>

int main ()
{
	int fd = fork();

	if (fd < 0 )
	{
		err(-2,"fork failed");
	}

	if ( fd == 0 )
	{
		for(int i=0;i<15;i++){
			printf("%d",i);
		}
	}
	else if( fd >0 )
	{
		wait(NULL);
		printf("Parent waited 10 cycles");

	}
}
