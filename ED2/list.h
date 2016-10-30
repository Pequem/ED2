#ifndef LIST_H_
#define LIST_H_

#define true 1
#define false 0
typedef struct list List;
typedef struct item Item;
typedef int bool;

List* newList();

Item* newItem(void *data);

void pushOnFirst(List* list, Item* item);

void pushOnLast(List * list, Item * item);

int countItems(List * list);

int search(List * list, int(*callback)(void *));

void * pull(List * list, int index);

void freeList(List *list);

#endif
