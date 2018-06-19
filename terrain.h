#ifndef TERRAINPARSER_H
#define TERRAINPARSER_H
#include "polygon.h"
#include "memory.h"
#include "error.h"
#include "util.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <byteswap.h>

typedef struct Terrain
{
	struct Terrain* next;
	struct Polygon* pol;
	const char* filename;
	const char* surfacename;
	int owner;
	int8_t hasSurfacename;
	int8_t foundation;
	int8_t mine;
	int8_t windfloor;
	int8_t viewfloor;
	int8_t nodraw;
}Terrain;

void 
Terrain_add(
	Terrain* ter, 
	Polygon* pol, 
	const char* filename,
	const char* surfacename,
	int32_t owner,
	int8_t hasSurfacename,
	int8_t foundation,
	int8_t mine,
	int8_t windfloor,
	int8_t viewfloor,
	int8_t nodraw);

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
