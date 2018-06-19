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
	Polygon_add(pol, 0 , 10000);
	for(float i = -999; i < 10000; i++)
	{
		float y = i/2 + sin(0.005*i)*255;
		Polygon_add(pol, i , y);
	}

	Memory* header = 0;
	header = FweHeader_create(header, "environment/alpine");
	Memory* mem = Terrain_toMemory(ter);
	Util_writeVoidArrayFile(0,"test_2.fwe", header->data, header->size);
	Util_writeVoidArrayFile(1,"test_2.fwe", mem->data, mem->size);
	return 0;
}
