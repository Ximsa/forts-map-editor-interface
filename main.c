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
	float ly = 0;
	for(float x = -999; x < 1000; x++)
	{

		float y = (sin(0.006*x*cos(0.005*x+cos(0.004*x))) + sin(0.05*x)) * 5;
		Polygon *pol = 0;
		pol = Polygon_create(pol);
		Polygon_add(pol, 0 , 100000);
		Polygon_add(pol, (x-1)*10, ly * 1000);
		Polygon_add(pol, x*10, y*1000);

		Terrain_add(ter, pol, "environment/alpine/ground/ground1.dds", 1, true, true, true, true, false);
		ly = y;
	}

	Memory* header = 0;
	header = FweHeader_create(header, "environment/alpine");
	Memory* mem = Terrain_toMemory(ter);
	Util_writeVoidArrayFile(0,"test_2.fwe", header->data, header->size);
	Util_writeVoidArrayFile(1,"test_2.fwe", mem->data, mem->size);
	return 0;
}
