#include "dynlist.h"
#include "assert.h"
#include <string.h>

void dynlist_create(Dynlist *list, size_t dataSize, int capacity)
{
	*list = (Dynlist){0};

	list->capacity = capacity;
	list->dataSize = dataSize;
	list->data = malloc(dataSize * capacity);
	assert(list->data, "failed to allocate for %zu bytes",
		dataSize * capacity);
}

void dynlist_destroy(Dynlist *list)
{
	free(list->data);
	*list = (Dynlist){0};
}

void dynlist_append(Dynlist *list, void *data)
{
	if (list->size >= list->capacity)
	{
		list->capacity *= 2;
		list->data = realloc(list->data, list->capacity * list->dataSize);
	}
	memcpy((char*)list->data + list->dataSize * list->size, data, list->dataSize);
	list->size++;
}

void dynlist_clear(Dynlist *list)
{
	list->size = 0;
}

bool dynlist_contains(Dynlist list, int index)
{
	return (index >= 0 && index < list.size);
}

void *dynlist_get(Dynlist *list, int index)
{
	if (dynlist_contains(*list, index))
		return ((char*)list->data + index * list->dataSize);
	return (NULL);
}

int dynlist_size(Dynlist list) {
	return (list.size);
}

size_t dynlist_bytesize(Dynlist list) {
	return (list.size * list.dataSize);
}
