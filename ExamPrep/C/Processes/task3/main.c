#include<unistd.h>
#include<err.h>
#include<stdlib.h>

int main ()
{
	if( fork() == 0)
	{
		execlp("sleep","daki100","60",(char*)NULL);
	}
}

