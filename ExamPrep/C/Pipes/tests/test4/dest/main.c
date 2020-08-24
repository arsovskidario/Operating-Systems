#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<err.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>


int main() {

        int fd = open("../src/myfifo",O_RDONLY);

        dup2(fd,0);

        execlp("sort","sort","-r",(char*)NULL);

}

