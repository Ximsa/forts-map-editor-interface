#include "customString.h"
#include "terrain.h"
#include "error.h"
#include <math.h>
int main()
{
	Polygon* pol;
	pol = Polygon_create(pol);
	for(int i = 1; i < 5; i++)
	{
		Polygon_add(pol, i , i*sin(i));
	}
	Polygon_removeLast(pol);
	
	Terrain* ter;
	ter = Terrain_create(ter);

	Terrain_add(ter, pol, "environment/alpine/ground/ground1.dds", 1, true, true, false, false, false);
	Terrain_toMemory(ter);
	return 0;
}
