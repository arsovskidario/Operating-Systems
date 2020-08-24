#include<stdlib.h>
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main() {

	int fd = open("../dest/darko",O_RDONLY);

	dup2(fd,0);

	execlp("sort","sort",(char*)NULL);
}
