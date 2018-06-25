#include "polygon.h"

void 
Polygon_add(
	Polygon* pol, 
	float x, 
	float y,
	int8_t hasSurfacename,
	char* surfacename)
{
	if(pol)
	{
		Polygon* toWrite = 0;
		if(pol->last)
		{
			// new last element
			toWrite = pol->last;
			pol->last->next = Polygon_create();
			pol->last = pol->last->next;
			
		}
		else
		{
			// first element
			toWrite = pol;
			pol->next = Polygon_create();
			pol->last = pol->next;
			
		}
		toWrite->x = x;
		toWrite->y = y;
		toWrite->hasSurfacename = hasSurfacename;
		toWrite->surfacename = surfacename;
	}
	else
	{
		return;
	}
}

Polygon*
Polygon_create()
{
	Polygon* pol = (Polygon*)calloc(
		sizeof(Polygon),1);
	return pol;
}

void
Polygon_free(
	Polygon* pol)
{
	do
	{
		pol = Polygon_removeLast(
			pol);
		
	} while(pol);
}

Polygon*
Polygon_getElement(
	Polygon* pol, 
	int i)
{
	if(pol)
	{
		if(i)
		{
			return Polygon_getElement(
				pol,
				i-1);
		}
		else
		{
			return pol;
		}
	}
	else
	{
		return 0;
	}
}

int
Polygon_getSize(
	Polygon* pol)
{
	if(pol)
	{
		if(pol->next)
		{
			return 1 + Polygon_getSize(
				pol->next);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

Polygon*
Polygon_removeLast(
	Polygon* pol)
{
	if(pol)
	{
		if(pol->next)
		{
			if(pol->next->next)
			{
				Polygon_removeLast(
					pol->next);
			}
			else
			{
				free(
					pol->next);
				pol->next = 0;
			}
		}
		else
		{
			free(
				pol);
			return 0;
		}
	}
	else
	{
		return 0;
	}
	return pol;
}
