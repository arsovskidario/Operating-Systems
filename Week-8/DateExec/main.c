#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

int main () {

	if( execl("/bin/date","date",(char*)NULL) == -1 ) { 
		printf("Could'nt execute commnad!");
	}

	return 0;
}
