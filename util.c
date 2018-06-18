 #include "util.h"

void 
Util_printVoidArray(
	void* data, 
	int length)
{
	const int bpl = 16; 
	int lines = length / bpl;
	int offset = 0;
	for(int i = 0; i <= lines; i++)
	{
		for(int j = 0; j < 4; ++j)
		{
			for(int k = 0; k < 4; k++)
			{
				if(offset < length)
				{
					printf("%02x ", ((uint8_t*) data)[offset]);
					offset++;
				}
			}
			printf("%s", "  ");
		}
		printf("%s","\n");
  			
	}	
}
void
Util_writeVoidArrayFile(
	int8_t append,
	const char* filename,
	void* data,
	int length)
{
	FILE* pFile = fopen(
		filename,
		append? "ab": "wb");
	fwrite(data,1 , length, pFile);
	fclose(pFile);	
}
