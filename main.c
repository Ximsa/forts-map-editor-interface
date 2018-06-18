#include "customString.h"
#include "terrain.h"
#include "error.h"
#include "fweHeader.h"
#include "util.h"
#include <math.h>

int main()
{
	Polygon* pol = 0;
	pol = Polygon_create(pol);

	Polygon_add(pol, 150 , 100);
	Polygon_add(pol, 150 , 50);
	Polygon_add(pol, 200 , 100);

	Polygon_removeLast(pol);
	
	Terrain* ter = 0;
	ter = Terrain_create(ter);

	Terrain_add(ter, pol, "environment/alpine/ground/ground1.dds", 1, true, true, true, true, true);
	Memory* header = 0;
	header = FweHeader_create(header, "environment/alpine");
	Memory* mem = Terrain_toMemory(ter);
	Util_writeVoidArrayFile(0,"result.fwe", header->data, header->size);
	Util_writeVoidArrayFile(1,"result.fwe", mem->data, mem->size);
	return 0;
}
