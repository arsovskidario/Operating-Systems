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
	for(int i=1;i<argc;i++){
		int fd=open(argv[i],O_RDONLY);

		if (fd == -1)
		{
			err(-1,"Coudn't open from file");
		}


		struct stat st;

		if( fstat(fd,&st) == -1) 
		{
			close(fd);
			err(-2,"Coudn't stat file");

		}


		char* buff = (char*) malloc( sizeof(char) * st.st_size);

		if( read(fd,buff,st.st_size) != st.st_size) 
		{
			int olderrn=errno;
			close(fd);
			free(buff);
			errno=olderrn;
			err(-3,"Coudn't read from file");
		}


		if( write(1,buff,st.st_size) != st.st_size)
		{
			int olderrno=errno;
			close(fd);
			free(buff);
			errno=olderrno;
			err(-4,"Coudn't write to STDOUT");
		}

		close(fd);
		free(buff);
	}
}
