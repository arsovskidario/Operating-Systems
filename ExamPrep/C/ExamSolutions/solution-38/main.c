#include <sys/types.h>
#include<string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdint.h>

int contains(char c, char* set) {
	int len=strlen(set);
	for(int i=0;i<len;i++) {
		if( c==set[i]) {
			return 1;
		}
	}
	
	return 0;
}

void squeeze(char* set) {
     int flag=0; // if flag=1 then will delete chars
              // 0 = don't deletm 1 =delete

     char c;

     while( read(0,&c,sizeof(c)) > 0 ) {

     if( contains(c,set)) {
         if( flag == 0 ) {
             write(1,&c,sizeof(c));
          }

             flag=1;
          }
          else{
              write(1,&c,sizeof(c));
              flag=0;
          }

    }
}


void delete(char c, char* set) {
	char* p = strchr(set,c);
	if(!p){
		write(1,&c,sizeof(c));
	}
}

void change(char c, char* set1, char* set2){

	char* p = strchr(set1,c); 

	if(p) {
		
	    int pos=p-set1;
	    char a=set2[pos];
	    write(1,&a,sizeof(set2[pos]));
	}
	else {
		write(1,&c,sizeof(c));
	}
}

int main( int argc, char* argv[])
{
	if( argc == 1 )
	{
		err(1,"No arguments");
	}

	if( strcmp(argv[1],"-d") == 0 ) {
		
		char c;
		while( read(0,&c,sizeof(c)) == sizeof(c)) {
			delete(c,argv[2]);
		}


	}
	else if ( strcmp(argv[1],"-s") == 0 ) {
		squeeze(argv[2]);
	}
	else {
		char c;
		while(read(0,&c,sizeof(c)) == sizeof(c)) {
			change(c,argv[1],argv[2]);
		}
	}

	exit(0);
}
