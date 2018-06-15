#include "customString.h"
#include "terrain.h"
#include "error.h"
#include <math.h>
int main()
{
	Polygon* pol;
	pol = Polygon_create(pol);

	Polygon_add(pol, 150 , 100);
	Polygon_add(pol, 150 , 50);
	Polygon_add(pol, 200 , 100);

	Polygon_removeLast(pol);
	
	Terrain* ter;
	ter = Terrain_create(ter);

	Terrain_add(ter, pol, "  environment/alpine/ground/ground1.dds", 1, true, true, true, true, true);
	Terrain_toMemory(ter);
	return 0;
}
