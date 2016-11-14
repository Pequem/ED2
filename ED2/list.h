#ifndef LIST_H_
#define LIST_H_

#define true 1
#define false 0
typedef struct list List;
typedef struct item Item;
typedef int bool;

List* list_new();

Item* list_newItem(void *data);

void list_pushOnFirst(List* list, Item* item);

void list_pushOnLast(List * list, Item * item);

int list_countItems(List * list);

int list_searchList(List * list, bool(*callback)(void *));

void * list_pull(List * list, int index);

void list_free(List *list, void(*callback)(void*));

#endif
