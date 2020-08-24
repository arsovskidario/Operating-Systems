#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int findNumber(char* set) {
	int len=strlen(set);
	for(int i=0;i<len;i++)
		if(set[i] >='0' && set[i] <='9') 
			return set[i] -'0';

	return -1;
}

void take_characters(int argc, char* argv[]) {
	if( argc == 5 ) {
		if ( strcmp(argv[3],"-")  == 0 ) {
			int until = findNumber(argv[2]);
			if(until == -1 ) {
				errx(3,"no number given");
			}

			int maxnum=findNumber(argv[4]);

			if(maxnum == -1 ) {
				errx(4,"No number given");
			}


			int length= maxnum - until;

			char* buf = (char*) malloc( sizeof(char) * until);

			read(0,buf,sizeof(char)*until);

			for(int i=0;i<length;i++) {
				char c;
				read(0,&c,sizeof(c));
				write(1,&c,sizeof(c));	
			}

			
		}
		else {
			errx(2,"Inavlid arguments");
		}
	}
	else {
		 int until = findNumber(argv[2]);
                 if(until == -1 ) {
                    errx(3,"no number given");

                 }

		 char* buf = (char*) malloc( sizeof(char) * until);

                 read(0,buf,sizeof(char)*until);

		 char c;
		 while( read(0,&c,sizeof(c)) > 0 ){
			 write(1,&c,sizeof(c));
		 }


	}
}

void delimiter_print(char* set1, char* set2,char delimiter) {
       int until = findNumber(set1);
       if(until == -1 ) {
          errx(3,"no number given");
       }

       int maxnum=findNumber(set2);

       if(maxnum == -1 ) {
          errx(4,"No number given");
       }


       int counter=0;
       char c;

       while ( read(0,&c,sizeof(c)) > 0 ) {
	      if(c == delimiter) {
                       counter++;
               }


	       if( counter >= until && counter<= maxnum) 
		  {
			  write(1,&c,1);
	          }

      }

}

void delimiter_normal(char* set, char delimiter) {
	int number = findNumber(set);
	if(number == -1 ) {
		errx(6,"invalid number param");
	}

	int counter=1;
	char c;
	while ( read(0,&c,sizeof(c)) > 0 ) {
		if( c == delimiter) {
			counter++;
		}

		if( counter == number ) {
			if( c != delimiter) {
				write(1,&c,sizeof(c));
			}
		}
	}
}

int main( int argc, char* argv[]) 
{
	if( argc == 1 ) {
		errx(1,"Invalid params");
	}

	if( strcmp(argv[1],"-c") == 0 ) {
		take_characters(argc,argv);
	}
	else if ( strcmp(argv[1],"-d") == 0 ) {
		char delimiter=argv[2][0];
		if( strcmp(argv[3],"-f") == 0 ) {
			if( argc == 7  && (strcmp(argv[5],"-") == 0)) {
				delimiter_print(argv[4],argv[6],delimiter);	
			}
			else {
				delimiter_normal(argv[4],delimiter);
			}
		}
		else {
			errx(5,"Invalid arguments");
		}
	}
}
