#include<unistd.h>
#include<errno.h>
#include<err.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{

if ( argc != 2 )
{
	errx(1,"Invalid arggs!");
}


	execlp("ls","dakishamki",argv[1],(char*)NULL);
}
