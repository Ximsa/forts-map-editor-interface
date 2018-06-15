#ifndef CUSTOMSTRING_H
#define CUSTOMSTRING_H


#include <stdlib.h>

typedef struct CharList
{
	char c;
	struct CharList* next;
}CharList;

int
CharList_length(
	CharList* list);

CharList*
CharList_create(
	char c);

CharList*
CharList_appendC(
	CharList* list, 
	char c);

void
CharList_appendCA(
	CharList* list, 
	char *c);

void
CharList_appendCL(
	CharList *dest, 
	CharList *src);

char
CharList_getC(
	CharList *list, 
	int i);

char*
CharList_toString(
	CharList *list);

CharList*
CharList_remove(
	CharList *list, 
	int elem);

void
CharList_free(
	CharList *list);

#endif
