#ifndef TERRAINPARSER_H
#define TERRAINPARSER_H
#include "polygon.h"
#include "memory.h"
#include "error.h"
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

Memory*
Terrain_toMemory(
	Terrain* ter);

#endif 
