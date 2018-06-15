#ifndef ERROR_H
#define ERROR_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void
Error_fatal(
	char* zMessage);

void
Error_message(
	char* zMessage);

void
Error_warning(
	char* zMessage);

#endif
