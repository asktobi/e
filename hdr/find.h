#ifndef FIND_C
#define FIND_C


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash.c"

#define SUM_H 1



struct entry 
{
	char *name;
	struct entry *next;
	void *ptr;
};


struct db 
{

	struct entry *list[256];

};

struct db *c_db()
{
	return (struct db *) malloc(sizeof(struct db)); 
}
struct entry *c_entry()
{
	return (struct entry *) malloc(sizeof(struct entry));
}

struct entry *find_entry(struct db *searchspace, char *name)
{
	struct entry *found;
	uint8_t index = (uint8_t) *(int * ) (hashstring(SUM_H,name));
	
	if ( !searchspace->list[index])
	{
		printf("(find) : No entry found");
		return NULL;
	}

	//printf("%p == %p = %d", searchspace->list[index]->name, name, strcmp(searchspace->list[index]->name, name));

	if ((strcmp(searchspace->list[index]->name,name))== 0)
	{
		//printf("Found a match (%p)",searchspace->list[index]);
		return searchspace->list[index];
	}
	return NULL;
	
}
void *find(struct db *searchspace, char *name)
{
	struct entry *found;
	uint8_t index = (uint8_t) *(int * ) (hashstring(SUM_HASH,name));
	
	if ( !searchspace->list[index])
	{
		printf("(find) : No entry found\n");
		return NULL;
	}

	//printf("%p == %p = %d", searchspace->list[index]->name, name, strcmp(searchspace->list[index]->name, name));
	found = searchspace->list[index];
	do {
		if ((strcmp(found->name,name))== 0)
		{
			//printf("Found a match (%p)",searchspace->list[index]);
			return found->ptr;
		}

		if (found->next == NULL)
		{
			return NULL;
		}

		found = found->next;
	}while (1);
}

void insert(struct db *searchspace, char *name, void *ptr)
{
	uint8_t index = (uint8_t) *(int * ) (hashstring(SUM_HASH,name));
	struct entry *new_entry = (struct entry*) malloc(sizeof(struct entry*));
	
	
	new_entry->name = (char *) malloc(strlen(name) * sizeof(char));
	strcpy(new_entry->name,name);
	new_entry->ptr = ptr;

	new_entry->next = searchspace->list[index];
	searchspace->list[index] = new_entry;
	
	//printf("Inserted %s into the Database\n",(searchspace->list[index])->name);

	return;
}


#endif
