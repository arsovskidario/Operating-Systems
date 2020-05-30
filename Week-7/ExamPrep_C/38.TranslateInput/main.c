#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

void deleteInput(char* set_match) {
	char input [4096];
	if ( read(0,&input,sizeof(input)) == -1  ) {

		err(-1,"Couldn't read from STDIN");
	}

	int len = strlen(set_match);
	int leftover_str = (strlen(input)-1 ) % strlen(set_match);

	int i=0;
	for(;i< (strlen(input)-1) - leftover_str;i++){
		char sub_str[len+1];
		for(int j=0;j<len;j++){
			sub_str[j] = input[i+j];
		}
		sub_str[len+1] = '\0';

		// Compare strings 
		
		if( strcmp(sub_str,set_match) != 0 ){
			// Print the sub_str
			write(1,&sub_str,sizeof(sub_str));
		}
	}	


	// size of STDIN % len = leftOver by default 
	// Print leftover by default 
	
	while(i<(strlen(input)-1)) {
		char c;
		c=input[i];
		write(1,&c,sizeof(c));
		i++;
	}
       	

}

int main(int argc, char* argv[]){

	// 1. Check if first parametar is an option
	//  1.1 If it is -s squeze SET 1 
	//  1.2 if it is -d delete set 1 
	// 2. No parametars  = exchange SET1 WITH set2 in stdin and print out to STDOUt
	

	// Traverse logic get set2 length and traverse by length ammount to find substring 
	// If not one found don't do anything 
	

	// Logic for deletion when substring foud
	// Have another buffer 
	// 1. If substring is not in SET2 
	// 	Add the substring to the helper buffer
	//    else dont add the substring to helper buffer 
	
	if ( strcmp(argv[1],"-s") == 0 ) {
		exit(0);
	}
	else if (strcmp(argv[1],"-d") == 0 ) {
		deleteInput(argv[2]);
		exit(0);
	}


	// Change SET1 with SET2 

	exit(0);
}

