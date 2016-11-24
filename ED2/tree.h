#ifndef TREE_H_
#define TREE_H_

#include "bitmap.h"

#define true 1
#define false 0
typedef int bool;

#define _right 1
#define _left 0
typedef int Direction;

typedef struct branch Branch;

bitmap tree_getWay(Branch *b);
Branch *tree_searchBranch(Branch *root, void *data, bool(*callback)(void*, void*));
void tree_free(Branch *root, void(*callback)(void*));
bool isLastBranch(Branch *auxBranch);
#endif