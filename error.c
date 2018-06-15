#include "error.h"

void
Error_fatal(
	char* zMessage)
{
	time_t rawtime;
	time(&rawtime);
	char* time = asctime(
			localtime(
				&rawtime));
	time[strlen(time) - 1] = 0;
	printf(
		"%s\t[FATAL]:\t%s\n", 
		time,
		zMessage);
	exit(-1);
}

void
Error_message(
	char* zMessage)
{
	time_t rawtime;
	time(&rawtime);
	char* time = asctime(
			localtime(
				&rawtime));
	time[strlen(time) - 1] = 0;
	printf(
		"%s\t[MESSAGE]:\t%s\n", 
		time,
		zMessage);
}

void
Error_warning(
	char* zMessage)
{
	time_t rawtime;
	time(&rawtime);
	char* time = asctime(
			localtime(
				&rawtime));
	time[strlen(time) - 1] = 0;
	printf(
		"%s\t[WARNING]:\t%s\n", 
		time,
		zMessage);

	printf("Press enter to continue\n");
	char enter = 0;
	while (enter != '\r' && enter != '\n') 
	{ 
		enter = getchar(); 
	}
}


