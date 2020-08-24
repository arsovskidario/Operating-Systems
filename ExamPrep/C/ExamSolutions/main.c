#include<stdlib.h>
#include<stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>

int main () {
	struct trick{
		uint32_t x;
		uint32_t y;
		uint32_t z;
		uint32_t a;
		uint32_t b;
	};


	int fd=open("test",O_RDWR| O_CREAT|O_TRUNC,0700);

	struct trick f1;
	f1.x=23;
	f1.y=1;
	f1.z=425;
	f1.a=50;
	f1.b=0;
	write(fd,&f1,sizeof(f1));

	close(fd);
}

