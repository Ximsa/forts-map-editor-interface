#ifndef POLYGON_H
#define POLYGON_H
#include <stdlib.h>

typedef struct Polygon
{
	float x;
	float y;
	struct Polygon* next;
}Polygon;

void 
Polygon_add(Polygon* pol, 
	float x, 
	float y);

Polygon*
Polygon_create(
	Polygon* pol);

void
Polygon_free(
	Polygon* pol);

Polygon*
Polygon_getElement(
	Polygon* pol, 
	int i);

int
Polygon_getSize(
	Polygon* pol);

Polygon*
Polygon_removeLast(
	Polygon* pol);
#endif 
