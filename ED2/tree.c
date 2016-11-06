#include "tree.h"
#include <stdlib.h>

struct branch {
	Branch *left, *right, *after;
	void *data;
};

Branch* newBranch(void *data) {
	Branch *branch = malloc(sizeof(Branch));
	branch->left = branch->right = branch->after = NULL;
	branch->data = data;
	return branch;
}

bool pushBranch(Branch *a, Branch *b, Direction direction) {
	b->after = a;
	if ((a == NULL) || (b == NULL))
		return false;
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

Branch *searchBranch(Branch *root, bool(*callback)(void*)) {
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

void* getData(Branch *b) {
	return b->data;
}

void setData(Branch *b, void *data) {
	b->data = data;
}

//implementar
void getWay(Branch *b, bool(*callback)(void*)) {
	if (b == NULL)
		return;
	while (b != NULL) {
		b = b->after;
		if (callback(b->left)) {
			//soma 1
		}else{
			//soma 0
		}
	}
}

bool *walkTree(Branch *b, Direction d) {
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

void freeBranch(Branch *a) {
	if (a == NULL)
		return;
	free(a);
}