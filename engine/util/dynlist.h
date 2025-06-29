#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	void *data;
	size_t dataSize;
	int size, capacity;
}	Dynlist;

void dynlist_create(Dynlist *list, size_t dataSize, int capacity);
void dynlist_destroy(Dynlist *list);
void dynlist_append(Dynlist *list, void *data);
void dynlist_clear(Dynlist *list);
bool dynlist_contains(Dynlist list, int index);
void *dynlist_get(Dynlist *list, int index);
int dynlist_size(Dynlist list);
size_t dynlist_bytesize(Dynlist list);

#define dynlist_foreach(_list_ptr, ...) \
	do { \
		Dynlist *list = (_list_ptr); \
		for (int index = 0; index < list->size; index++) { \
			void *data = (char*)list->data + index * list->dataSize; \
			__VA_ARGS__ \
		} \
	}	while (0);
