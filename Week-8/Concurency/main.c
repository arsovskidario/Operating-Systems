#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include <sys/types.h>

int main(){


	if ( fork()> 0 ) {
		// Parent

		for(int i=0;i<25;i++) {
			printf("Parent\n");
		}
	}
	else {
		// Child
		 for(int i=0;i<25;i++) {
                        printf("Child\n");
                }

	}

	exit(0);
}

