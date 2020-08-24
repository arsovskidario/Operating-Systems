#include<stdlib.h>
#include<unistd.h>

int main()
{

	execlp("date","da","+%F-%r", (char*)NULL);
}
