#ifndef TREE_H_
#define TREE_H_

#include "bitmap.h"

#define true 1
#define false 2
typedef int bool;

#define _right 0
#define _left 1
typedef int Direction;

typedef struct branch Branch;

bitmap tree_getWay(Branch *b);
Branch *tree_searchBranch(Branch *root, void *data, bool(*callback)(void*, void*));

#endif