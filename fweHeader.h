#ifndef FWEHEADER_H
#define FWEHEADER_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "error.h"

static uint8_t fweHeader_data[] = 
{
	0x14, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0x75, 0x44,
	0x00, 0x00, 0x00, 0x00,

	0x00, 0xe0, 0x2b, 0x46,
	0x00, 0xe0, 0x2b, 0xc6,
	0x00, 0xe0, 0x2b, 0x46,
	0x00, 0xe0, 0x2b, 0xc6
};

Memory*
FweHeader_create(
	Memory* head, 
	const char* filename);

#endif