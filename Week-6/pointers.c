#include <stdlib.h>
#include<stdio.h>
int main(int argc, char* argv[]) 
{	
	int a=25;
	int* ptr =&a;
	

	printf ("Value :%d, Address: %p \n",a,ptr);
	
	char* name;
	name =(char*) malloc(6); 
	for(int i=0;i<sizeof(name);i++) 
	{
		name[i]=i+ '0';
	}	
	
	name[5]='\0';
	printf("%s ",name);
	
	free(name);
	name=NULL;

	return(0);
}
