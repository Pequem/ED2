#include "tree.h"
#include "bitmap.h"
#include <stdlib.h>

struct branch {
	Branch *left, *right, *before;
	void *data;
};

Branch* tree_newBranch(void *data) {
	Branch *branch = malloc(sizeof(Branch));
	branch->left = branch->right = branch->before = NULL;
	branch->data = data;
	return branch;
}

void printbitmap2(bitmap bm) {
	int i;
	for (i = 0; i < bitmapGetLength(bm); i++) {
		printf("%i", bitmapGetBit(bm, i));
	}
}

//coloca o galho b em uma das ramificações do galho a
bool tree_pushBranch(Branch *a, Branch *b, Direction direction) {
	
	if ((a == NULL) || (b == NULL))
		return false;

	b->before = a;

	if (direction == _right) {

		if (a->right != NULL)
			return false;
		a->right = b;
		return true;

	}
	else {

		if (a->left != NULL)
			return false;
		a->left = b;
		return true;
	}
	return false;
}

//retorna o galho contendo o dado especifico
Branch *tree_searchBranch(Branch *root, void *data, bool(*callback)(void*,void*)) {
	if ((root == NULL) || (callback == NULL))
		return NULL;

	if (callback(root->data, data)) {
		return root;
	}

	Branch* branch;

	branch = NULL;

	branch = tree_searchBranch(root->left,data, callback);

	if (branch != NULL)
		return branch;

	branch = tree_searchBranch(root->right, data, callback);

	if (branch != NULL)
		return branch;

	return NULL;
}

void* tree_getData(Branch *b) {
	return b->data;
}

void tree_setData(Branch *b, void *data) {
	b->data = data;
}

//"anda" na arvore seguindo a direção desejada
Branch *tree_walkTree(Branch *b, Direction d) {
	if (b == NULL) {
		return;
	}
	
	if (d == _right) {
		return b->right;
	}
	else {
		return b->left;
	}
}

void checkWay(bitmap bm, Branch *root, Branch *bTest) {
	int i, length = bitmapGetLength(bm);
	unsigned char bit;
	for (i = 0; i < length; i++) {
		bit = bitmapGetBit(bm, i);
		if (bit == 1) {
			root = tree_walkTree(root, _left);
		}
		else {
			root = tree_walkTree(root, _right);
		}
	}
	if (!(root == bTest)) {
		printf("Tree_getway falhou");
		system("PAUSE");
	}
}

bitmap tree_getWay(Branch *b) {
	if (b == NULL)
		return;
	bitmap bm;
	Branch *bTest = b;
	bm = bitmapInit(8);
	while (b->before != NULL) {
		if (b->before->left == b) {
			bitmapAppendLeastSignificantBit(&bm, 1);
		}
		else {
			bitmapAppendLeastSignificantBit(&bm, 0);
		}
		b = b->before;
	}

	int i;
	int length;
	bitmap bm2;
	length = bitmapGetLength(bm);
	bm2 = bitmapInit(length);
	for (i = 1; i <= length; i++) {
		bitmapAppendLeastSignificantBit(&bm2, bitmapGetBit(bm, length - i));
	}
	
	checkWay(bm2, b, bTest);
	//printbitmap2(bm2);

	return bm2;
}

void tree_freeBranch(Branch *a) {
	if (a == NULL)
		return;
	free(a);
}