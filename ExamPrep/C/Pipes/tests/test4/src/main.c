#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {

	mkfifo("myfifo",0770);

        int fd = open("myfifo",O_WRONLY);

	dup2(fd,1);
	
	execlp("cat","cat","f1",(char*)NULL);

}

