#include "list.h"
#include <stdlib.h>

struct list {
	Item *first, *last;
};

struct item {
	Item *before, *after;
	void *data;
};

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

void insertItemOnFirst(List *list, Item *item) {
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

void insertItemOnLast(List *list, Item *item) {
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

Item* search(List *list, int (*callback)(void*)) {
	if (list == NULL) {
		return;
	}
	if (callback == NULL) {
		return;
	}
	if (list->first == NULL){
		return;
	}

	Item *aux = list->first;

	while (aux != NULL) {
		if (callback(aux->data)) {
			return aux;
		}
		aux = aux->after;
	}

	return NULL;
}