#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdint.h>
void 
printVoidArray(
	void* data, 
	int length);

void
writeVoidArrayFile(
	int8_t append,
	const char* filename,
	void* data,
	int length);

#endif 
