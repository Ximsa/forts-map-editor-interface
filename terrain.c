#include "terrain.h"


const uint32_t Terrain_Init = 0x00000003;
const uint32_t Terrain_Seperator = 0x3F800000;
const uint32_t Terrain_Header_0 = 0x003EC00;
const uint64_t Terrain_Empty_64 = 0x0000000000000000;
const uint32_t Terrain_Empty_32 = 0x00000000;
const uint8_t Terrain_Empty_8 = 0x00;
const uint8_t Terrain_Reserved_Flag = 0x00;
const uint16_t Terrain_Header_1 = 0x0101;
void 
Terrain_add(
	Terrain* ter, 
	Polygon* pol,
	const char* filename,
	const char* surfacename,
	int32_t owner,
	int8_t hasSurfacename,
	int8_t foundation,
	int8_t mine,
	int8_t windfloor,
	int8_t viewfloor,
	int8_t nodraw
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
				surfacename,
				owner,
				hasSurfacename,
				foundation,
				mine,
				windfloor,
				viewfloor,
				nodraw);
		}
		else
		{
			ter->pol = pol;
			ter->filename = filename;
			ter->surfacename = surfacename;
			ter->owner = owner;
			ter->hasSurfacename = hasSurfacename;
			ter->foundation = foundation;
			ter->mine = mine;
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
			return 0;
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
	// inititialize memory
	Memory* mem = (Memory*)malloc(
		sizeof(Memory));
	mem->data = 0;
	mem->size = 0;
	int offset = 0;
	
	// header
	// polygon count
	offset = mem->size;
	mem->size += sizeof(uint64_t); 
	mem->data = realloc(
		mem->data, 
		mem->size);
	if(!mem->data)
	{
		Error_fatal("Reallocation Failed");
	}
	uint64_t polygonLen = (Terrain_getSize(ter));
	memcpy(
		mem->data + offset, 
		&polygonLen,
		sizeof(uint64_t));


	// end header

	while(ter && ter->pol)	
	{
		// number of points in this polygon
		offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		uint32_t polygonCount = Polygon_getSize(ter->pol);
		memcpy(
			mem->data + offset, 
			&polygonCount,
			sizeof(uint32_t));

		// seperate 
		for(int i = 0; i < 4; i++)
		{
			offset = mem->size;
			mem->size += sizeof(uint32_t); 
			mem->data = realloc(
				mem->data, 
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}
			memcpy(
				mem->data + offset, 
				&Terrain_Seperator, 
				sizeof(uint32_t));

		}

		// first element is filesting length
		offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data,
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		uint32_t filenameLen = strlen(ter->filename);
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

		// 2.5th element is the surfacenameLength + surfacename
		if(ter->hasSurfacename)
		{
			//length
			offset = mem->size;
			mem->size += sizeof(uint32_t); 
			mem->data = realloc(
				mem->data,
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}
			uint32_t surfacenameLen = strlen(ter->surfacename);
			memcpy(
				mem->data + offset, 
				&surfacenameLen, 
				sizeof(uint32_t));			

			// name
			offset = mem->size;
			mem->size += surfacenameLen;
			mem->data = realloc(
				mem->data, 
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}

			memcpy(
				mem->data + offset,
				ter->surfacename,
				surfacenameLen);
		}
		else
		{
			//NULL-int32
			offset = mem->size;
			mem->size += sizeof(uint32_t); 
			mem->data = realloc(
				mem->data, 
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}
			memcpy(
				mem->data + offset, 
				&Terrain_Empty_32, 
				sizeof(uint32_t));
		}
		// NULL - byte
		offset = mem->size;
		mem->size += sizeof(uint8_t);
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}

		memcpy(
			mem->data + offset,
			&Terrain_Empty_8,
			sizeof(uint8_t));

		//third element is constant (Header #0 - #2)
		offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&Terrain_Header_0, 
			sizeof(uint32_t));
	
		offset = mem->size;
		mem->size += sizeof(uint64_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&Terrain_Empty_64, 
			sizeof(uint64_t));

		offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&Terrain_Empty_32, 
			sizeof(uint32_t));

		// fourth element ist the team
		offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		uint32_t endianSwapedOwner = __bswap_32(ter->owner);
		memcpy(
			mem->data + offset, 
			&endianSwapedOwner, 
			sizeof(uint32_t));

		// fitht elements are flags
	
		// reserved1-3
		for(int i = 0; i < 3; i++)
		{
			offset = mem->size;
			mem->size += sizeof(uint8_t); 
			mem->data = realloc(
				mem->data, 
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}
			memcpy(
				mem->data + offset,
				&Terrain_Reserved_Flag,
				sizeof(uint8_t));
		}

		// Wind Floor Flag
	
		offset = mem->size;
		mem->size += sizeof(uint8_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&ter->windfloor, 
			sizeof(uint8_t));

		// View Floor Flag
		offset = mem->size;
		mem->size += sizeof(uint8_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&ter->viewfloor, 
			sizeof(uint8_t));

		// No Draw Flag
	
		offset = mem->size;
		mem->size += sizeof(uint8_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&ter->nodraw, 
			sizeof(uint8_t));

		// Foundation Flag
		offset = mem->size;
		mem->size += sizeof(uint8_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&ter->foundation, 
			sizeof(uint8_t));

		// Mine Flag	
		offset = mem->size;
		mem->size += sizeof(uint8_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&ter->mine, 
			sizeof(uint8_t));
	
		// constant
		offset = mem->size;
		mem->size += sizeof(uint16_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset, 
			&Terrain_Header_1, 
			sizeof(uint16_t));

		// polygon //TODO: see what mystery parameters do (seems to be pointles)
		Polygon* polCur = ter->pol;
		
		while(polCur->next)
		{
			// add x
			offset = mem->size;
			mem->size += sizeof(float); 
			mem->data = realloc(
				mem->data, 
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}
			memcpy(
				mem->data + offset, 
				&polCur->x, 
			sizeof(float));

			// add y
			offset = mem->size;
			mem->size += sizeof(float); 
			mem->data = realloc(
				mem->data, 
				mem->size);
			if(!mem->data)
			{
				Error_fatal("Reallocation Failed");
			}
			memcpy(
				mem->data + offset, 
				&polCur->y, 
			sizeof(float));

			// add trailing 2 empty integers
			for(int i = 0; i < 2; i++)
			{
				offset = mem->size;
				mem->size += sizeof(uint32_t); 
				mem->data = realloc(
					mem->data, 
					mem->size);
				if(!mem->data)
				{
					Error_fatal("Reallocation Failed");
				}
				memcpy(
					mem->data + offset,
					&Terrain_Empty_32,
					sizeof(uint32_t));
			}
			// write surface info
			if(polCur->hasSurfacename)
			{
				//length
				uint32_t surfacenameLen = strlen(
					polCur->surfacename);
				offset = mem->size;
				mem->size += sizeof(uint32_t); 
				mem->data = realloc(
					mem->data, 
					mem->size);
				if(!mem->data)
				{
					Error_fatal("Reallocation Failed");
				}
				memcpy(
					mem->data + offset,
					&surfacenameLen,
					sizeof(uint32_t));
				
				//name
				offset = mem->size;
				mem->size += surfacenameLen;
				mem->data = realloc(
					mem->data, 
					mem->size);
				if(!mem->data)
				{
					Error_fatal("Reallocation Failed");
				}

				memcpy(
					mem->data + offset,
					polCur->surfacename,
					surfacenameLen);
			}
			else
			{
				//write zero
				offset = mem->size;
				mem->size += sizeof(uint32_t); 
				mem->data = realloc(
					mem->data, 
					mem->size);
				if(!mem->data)
				{
					Error_fatal("Reallocation Failed");
				}
				memcpy(
					mem->data + offset,
					&Terrain_Empty_32,
					sizeof(uint32_t));
			}
			// next point
			polCur = polCur->next;
		}
		// and tell number of points + 1
		/*offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		uint32_t polPoints = Polygon_getSize(
			ter->pol) + 1;
		memcpy(
			mem->data + offset,
			&polPoints,
			sizeof(uint32_t));*/

		//1 more empty byte
		offset = mem->size;
		mem->size += sizeof(uint32_t); 
		mem->data = realloc(
			mem->data, 
			mem->size);
		if(!mem->data)
		{
			Error_fatal("Reallocation Failed");
		}
		memcpy(
			mem->data + offset,
			&Terrain_Empty_32,
			sizeof(uint32_t));
		ter = ter->next;

	}
	//Footer
	offset = mem->size;
	mem->size += sizeof(uint64_t); 
	mem->data = realloc(
		mem->data, 
		mem->size);
	if(!mem->data)
	{
		Error_fatal("Reallocation Failed");
	}
	memcpy(
		mem->data + offset,
		&Terrain_Empty_64,
		sizeof(uint64_t));

	return mem;
}


