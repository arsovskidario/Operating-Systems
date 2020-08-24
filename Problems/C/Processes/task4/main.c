#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<unistd.h>


int main()
{
	if ( fork() == 0 ) 
	{
	 	printf("In child will wait 10sec");
		printf("WAITED");	
		exit(0);
	}

	printf("Parent done");
}
