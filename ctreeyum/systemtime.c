/*This file should return raw UNIX epoch seconds. The way it's coded right now, it returns the full date. Removing this conversion will speed processing for block synchronization.*/
#include <stdio.h>
#include <time.h>

int main(){;
	
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf("UNIX seconds: %s", asctime (timeinfo));


	return 0;


}
