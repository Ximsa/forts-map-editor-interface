#include "customString.h"

int
CharList_length(
	CharList* list)
{
	if(list)
	{
		return CharList_length(list->next) + 1;
	}
	else
	{
		return 0;
	}
}

// creates a new CharList 
CharList*
CharList_create(
	char c)
{
	if(c == 0)
	{
		return 0;
	}

	CharList* list = (CharList*)malloc(sizeof(CharList));
	if(list)
	{
		list->c = c;
		list->next = 0;
	}
	return list;
}
// appends a char and returns a new list if empty
CharList*
CharList_appendC(
	CharList* list, 
	char c)
{
	if (c == 0)
	{
		// do nothing and return list
	}
	else if(!list)
	{
		return CharList_create(c);
	}
	else if(list->next)
	{
		CharList_appendC(list->next, c);
	}
	else
	{
		list->next = (CharList*)malloc(sizeof(CharList));
		list->next->c = c;
		list->next->next = 0;
	}
	return list;
}

// appends a char array
void
CharList_appendCA(
	CharList* list, 
	char *c)
{
	//safety checks
	if(!c || !list)
	{
		return;
	}
	else
	{
		int i = 0;
		while(c[i] != 0)
		{
			// performance optimisation
			// spool to the last element
			// lets just hope its not a ring buffer ;)
			while(list->next)
			{
				list = list->next;
			}


			CharList_appendC(list, c[i]);
			i++;
		}
	}
}
// appends a char list
void
CharList_appendCL(
	CharList *dest, 
	CharList *src)
{
	// safety checks
	if(dest && src)
	{
		while(src)
		{
			// performance optimisation
			// spool to the last element
			// lets just hope its not a ring buffer ;)
			while(dest->next)
			{
				dest = dest->next;
			}
			CharList_appendC(
				dest, 
				src->c);
			src = src->next;
		}
	}
	return;
}

// gets the i'th element, 0 on error
char
CharList_getC(
	CharList *list, 
	int i)
{
	if(!list)
	{
		return 0;
	}
	else if(i == 0)
	{
		return list->c;
	}
	else
	{
		return CharList_getC(list->next, i-1);
	}
}

// creates a string
char*
CharList_toString(
	CharList *list)
{
	char* str = 0;
	//safety
	if(list)
	{
		// get length
		int length  = CharList_length(list);
		int i = 0;
		str = (char*)malloc(sizeof(char) * (length + 1));
		while(list && str && i < length)
		{
			str[i] = list->c;
			i++;
			list = list->next;
			
		}
		str[length] = 0;
	}
	return str;
}

// remove an element and returns the new list (if neccesary)
CharList*
CharList_remove(
	CharList *list, 
	int elem)
{

	if(!list || !list->next)
	{
		// nothing to remove..
	}
	else if(elem <= 0)
	{
		CharList* tmp = list->next;
		free(
			list);		
		return tmp;
	}
	else if(elem == 1)
	{
		// remove next element
		CharList *tmp = list->next;
		list->next = list->next->next;
		free(
			tmp);
	}
	else
	{
		CharList_remove(
			list->next, 
			elem - 1);
	}
	return list;
}

void
CharList_free(
	CharList *list)
{
	CharList *tmp;
	while(list)
	{
		tmp = list;
		list = list->next;
		free(
			tmp);
	}
}
























