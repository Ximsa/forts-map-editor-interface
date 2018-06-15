#include "terrain.h"

void 
Terrain_add(
	Terrain* ter, 
	Polygon* pol,
	const char* filename,
	int owner, 
	bool foundations,
	bool mines,
	bool windfloor,
	bool viewfloor,
	bool nodraw
	)
{
	if(ter)
	{
		if(ter->next)
		{
			Terrain_add(
				ter->next,
				pol,
				filename,
				owner,
				foundations,
				mines,
				windfloor,
				viewfloor,
				nodraw);
		}
		else
		{
			ter->pol = pol;
			ter->filename = filename;
			ter->owner = owner;
			ter->foundations = foundations;
			ter->mines = mines;
			ter->windfloor = windfloor;
			ter->viewfloor = viewfloor;
			ter->nodraw = nodraw;
			ter->next = Terrain_create(
				ter->next);
		}
	}
	else
	{
		return;
	}
}

Terrain*
Terrain_create(
	Terrain* ter)
{
	ter = (Terrain*)calloc(
		sizeof(Terrain),1);
	return ter;
}

void
Terrain_free(
	Terrain* ter)
{
	do
	{
		ter = Terrain_removeLast(
			ter);
		
	} while(ter);
}

Terrain*
Terrain_getElement(
	Terrain* ter, 
	int i)
{
	if(ter)
	{
		if(i)
		{
			return Terrain_getElement(
				ter->next,
				i-1);
		}
		else
		{
			return ter;
		}
	}
	else
	{
		return 0;
	}
}

int
Terrain_getSize(
	Terrain* ter)
{
	if(ter)
	{
		if(ter->next)
		{
			return 1 + Terrain_getSize(
				ter->next);
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

Terrain*
Terrain_removeLast(
	Terrain* ter)
{
	if(ter)
	{
		if(ter->next)
		{
			if(ter->next->next)
			{
				Terrain_removeLast(
					ter->next);
			}
			else
			{
				free(
					ter->next);
				ter->next = 0;
			}
		}
		else
		{
			free(
				ter);
			return 0;
		}
	}
	else
	{
		return 0;
	}
	return ter;
}

Memory*
Terrain_toMemory(
	Terrain* ter)
{
	Memory* mem = (Memory*)malloc(sizeof(Memory));
	mem->data = 0;
	mem->size = 0;
	int offset = 0;


	// first element is filesting length + NULL-byte
	offset = mem->size;
	mem->size += sizeof(uint32_t); 
	mem->data = realloc(
		mem->data, 
		mem->size);
	if(!mem->data)
	{
		Error_fatal("Reallocation Failed");
	}
	uint32_t filenameLen = strlen(ter->filename) + 1; // NULL-byte
	memcpy(
		mem->data + offset, 
		&filenameLen, 
		sizeof(uint32_t));

	//second element is the string
	offset = mem->size;
	mem->size += filenameLen;
		mem->data = realloc(
		mem->data, 
		mem->size);
	if(!mem->data)
	{
		Error_fatal("Reallocation Failed");
	}

	memcpy(
		mem->data + offset,
		ter->filename,
		filenameLen);


	//third element are Flags
	

	//debug
	printVoidArray(
		mem->data, 
		mem->size);
	
	return mem;
}


