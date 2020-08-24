#include<stdlib.h>
#include<unistd.h>
#include<err.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){

	if ( mkfifo("darko",0660) == -1 ){
		err(-3,"Fail");
	}

	int fd = open("darko",O_WRONLY);

	dup2(fd,1);

	execlp("cat","cat","f1",(char*)NULL);


}
