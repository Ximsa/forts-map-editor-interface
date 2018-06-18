#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdint.h>
void 
Util_printVoidArray(
	void* data, 
	int length);

void
Util_writeVoidArrayFile(
	int8_t append,
	const char* filename,
	void* data,
	int length);

#endif 
