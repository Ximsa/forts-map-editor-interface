#include "customString.h"
#include "terrain.h"
#include "error.h"
#include "fweHeader.h"
#include "util.h"
#include <math.h>

int main()
{
	Terrain *ter = 0;
	ter = Terrain_create(ter);
	Polygon *pol = 0;
	pol = Polygon_create(pol);
	Polygon_add(pol, 0 , 100000);
	for(float x = -9999; x < 10000; x+=50)
	{

		float y = x/2 + sin(0.005*x)*255;
		Polygon_add(pol, x, y);


	}
	Terrain_add(ter, pol, "environment/alpine/ground/ground1.dds","rocks01", 1, true ,true, true, true, false, false);
	Memory* header = 0;
	header = FweHeader_create(header, "environment/alpine");
	Memory* mem = Terrain_toMemory(ter);
	Util_writeVoidArrayFile(0,"surface_test_01.fwe", header->data, header->size);
	Util_writeVoidArrayFile(1,"surface_test_01.fwe", mem->data, mem->size);
	return 0;
}
