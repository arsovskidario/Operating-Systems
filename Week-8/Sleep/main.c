#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>

int main() {

	if( execl("/bin/sleep","sleep","60s",(char*)NULL) == -1) {
		err(1,"Couldn't execute command");
	}

	exit(0);
}
