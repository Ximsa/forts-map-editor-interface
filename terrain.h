#ifndef TERRAINPARSER_H
#define TERRAINPARSER_H
#include "polygon.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct Terrain
{
	struct Terrain* next;
	struct Polygon* pol;
	const char* filename;
	int owner;
	bool foundations;
	bool mines;
	bool windfloor;
	bool viewfloor;
	bool nodraw;
}Terrain;

const uint16_t Terrain_Header_1 = 0x0000;
const uint64_t Terrain_Header_2 = 0x00000000 ;

void 
Terrain_add(
	Terrain* ter, 
	Polygon* pol, 
	const char* filename,
	int owner,
	bool foundations,
	bool mines,
	bool windfloor,
	bool viewfloor,
	bool nodraw);

Terrain*
Terrain_create(
	Terrain* ter);

void
Terrain_free(
	Terrain* ter);

Terrain*
Terrain_getElement(
	Terrain* ter, 
	int i);

int
Terrain_getSize(
	Terrain* ter);

Terrain*
Terrain_removeLast(
	Terrain* ter);

void* 
Terrain_toMemory(
	Terrain* ter);

#endif 
