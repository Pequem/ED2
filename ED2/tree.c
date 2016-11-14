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
Branch *tree_searchBranch(Branch *root, bool(*callback)(void*)) {
	if ((root == NULL) || (callback == NULL))
		return NULL;

	if (callback(root->data)) {
		return root;
	}

	Branch* branch;

	branch = NULL;

	//branch = search(root->left, callback);

	if (branch != NULL)
		return branch;

	//branch = search(root->right, callback);

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

//implementar
//retorna o caminho do galho ate a raiz
void tree_getWay(Branch *b, bool(*callback)(void*)) {
	if (b == NULL)
		return;
	while (b != NULL) {
		b = b->before;
		if (callback(b->left)) {
			//soma 1
		}else{
			//soma 0
		}
	}
}

//"anda" na arvore seguindo a direção desejada
bool *tree_walkTree(Branch *b, Direction d) {
	if (b == NULL) {
		return false;
	}
	
	if (d == _right) {
		if (b->right == NULL) {
			return false;
		}
		b->right;
	}
	else {
		if (b->left == NULL) {
			return false;
		}
		b->left;
	}

	return true;
}

void tree_freeBranch(Branch *a) {
	if (a == NULL)
		return;
	free(a);
}