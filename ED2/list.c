#include "list.h"
#include <stdlib.h>

struct list {
	Item *first, *last;
};

struct item {
	Item *before, *after;
	void *data;
};

void freeItem(Item *item, bool freeData);
void remove(List *list, Item *item, bool _delete);

List* newList() {
	List *list = malloc(sizeof(List));
	list->first = list->last = NULL;
	return list;
}

Item* newItem(void *data) {

	if (data == NULL) {
		return;
	}

	Item *item = malloc(sizeof(Item));
	item->after = item->before = NULL;
	item->data = data;
	return item;
}

void pushOnFirst(List *list, Item *item) {
	if (item == NULL) {
		return;
	}
	if (list == NULL) {
		return;
	}

	if (list->first == NULL) {
		list->first = list->last = item;
		return;
	}

	list->first->before = item;
	item->after = list->first;
	list->first = item;
	return;
}

void pushOnLast(List *list, Item *item) {
	if (item == NULL) {
		return;
	}
	if (list == NULL) {
		return;
	}

	if (list->first == NULL) {
		list->first = list->last = item;
		return;
	}

	list->last->after = item;
	item->before = list->last;
	list->last = item;
	return;
}

int countItems(List *list) {
	if (list->first == NULL) {
		return 0;
	}

	int count = 0;

	Item *aux = list->first;

	while (aux != NULL) {
		count++;
		aux = aux->after;
	}

	return count;
}

int search(List *list, int(*callback)(void*)) {
	if (list == NULL) {
		return;
	}
	if (callback == NULL) {
		return;
	}
	if (list->first == NULL) {
		return;
	}

	int index = 0;

	Item *aux = list->first;

	while (aux != NULL) {
		if (callback(aux->data)) {
			index++;
			return index;
		}
		index++;
		aux = aux->after;
	}

	return;
}

void* pull(List* list, int index) {
	
	if (list == NULL) {
		return;
	}

	if (list->first == NULL) {
		return;
	}

	if (index > countItems(list)) {
		return;
	}

	Item *aux;
	int i;

	aux = list->first;

	for (i = 1; i < index; i++) {
		aux = aux->after;
	}

	void* data = aux->data;

	remove(list, aux, false);

	return data;
}

void remove(List *list, Item *item, bool _delete) {

	if (item == NULL) {
		return;
	}

	if (list == NULL) {
		return;
	}

	if (list->first == item) {
		list->first = list->first->after;
	}
	else if (list->last == item) {
		list->last = list->last->before;
	}
	else {
		item->before->after = item->after;
		item->after->before = item->before;
	}
	
	freeItem(item, _delete);
	return;
}

void freeItem(Item *item, bool freeData) {

	if (item == NULL) {
		return;
	}

	if(freeData)
		free(item->data);
	free(item);
}

void freeList(List *list) {

	if (list == NULL) {
		return;
	}

	if (list->first == NULL) {
		return;
	}

	Item *aux = list->first;

	while (1) {
		if (aux->after == NULL) {
			remove(list, aux, true);
			break;
		}
		else {
			aux = aux->after;
			remove(list, aux->before, true);
		}
	}

	free(list);

	return;
}