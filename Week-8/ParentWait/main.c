#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<err.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){ 
	int status;
	if(fork() > 0){
		//wait(&status);
		for(int i=0;i<25;i++) {
                        printf("Parent\n");
                }

	}
	else {
		for(int i=0;i<25;i++) {
			int ppid=getppid();
                        printf("Child ppid:%d\n",ppid);
			execl("bin/ps","ps","-p",ppid,"-o","comm",(char*)NULL);

                }

	}

	// wait(&status);

	exit(0);
}
