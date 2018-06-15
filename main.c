#include "customString.h"
#include "terrain.h"
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

	Terrain_add(ter, pol, 1, true, true, false, false, false);
	return 0;
}
