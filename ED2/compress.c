#include <stdlib.h>
#include <stdio.h>
#include "compress.h"
#include "tree.h"
#include "list.h"
#include <string.h>

//Struct com a arvore
typedef struct{
	unsigned int frequencyArray[256];
	Branch *tree;
	List *branchList;
}CompresserdFileData;

//Struct para a varialvel data dos nós da arvore
typedef struct {
	char letter;
	int frequency;
} BranchData;

void frequencyCount(CompresserdFileData* CFData, FILE *f) {
	int i;
	//Zerando o vetor de frequencia
	for (i = 0; i < 256; i++) {
		CFData->frequencyArray[i] = 0;
	}

	unsigned char bit;

	while (true) {

		fread(&bit, sizeof(char), 1, f);
		if (feof(f)) {
			break;
		}
		//bit += 127;
		CFData->frequencyArray[bit]++;
	}
}

//função auxiliar para list_order
int compare(void* i1, void* i2) {
	BranchData *bd1 = tree_getData(i1);
	BranchData *bd2 = tree_getData(i2);

	if (bd1->frequency > bd2->frequency) {
		return -1;
	}
	return 0;
}

//função auxiliar para list_print
void printItem(void *i) {
	BranchData *bd = tree_getData(i);
	printf("\n%c %i", bd->letter, bd->frequency);
}

void PreCreateDecoderTree(CompresserdFileData *CFData) {

	int i;

	//variaveis auxiliares
	BranchData *bd;
	CFData->branchList = list_new();

	//Tranformando as frequencias em raizes
	for (i = 0; i < 256; i++) {
		if (CFData->frequencyArray[i] > 0) {
			bd = malloc(sizeof(BranchData));
			bd->frequency = CFData->frequencyArray[i];
			bd->letter = i;
			list_pushOnLast(CFData->branchList,list_newItem(tree_newBranch(bd)));
		}
	}

	list_order(CFData->branchList,compare);
	list_print(CFData->branchList, printItem);
}

void CreateDecoderTree(CompresserdFileData *CFData) {
	Branch *b1, *b2, *bf;

	while (list_countItems(CFData->branchList) > 1) {
		b1 = list_pull(CFData->branchList, 0);
		b2 = list_pull(CFData->branchList, 0);

		bf = tree_newBranch(NULL);

		tree_pushBranch(bf, b1, _left);
		tree_pushBranch(bf, b2, _right);

		list_pushOnLast(CFData->branchList, list_newItem(bf));
	}
	CFData->tree = list_pull(CFData->branchList, 0);

	list_free(CFData->branchList, NULL);
}

void serializeList(CompresserdFileData *CFData, FILE *fc) {
	
	int nItens = list_countItems(CFData->branchList);
	int i;
	Branch *b;
	BranchData *bd;

	fwrite(&nItens, sizeof(int), 1, fc);

	for (i = 0; i < nItens; i++) {
		b = list_pullWithoutRemove(CFData->branchList, i);
		bd = tree_getData(b);
		fwrite(bd, sizeof(BranchData), 1, fc);
	}
}

void code(CompresserdFileData *CFData, FILE *f, FILE *fc) {
	char byte;
	while (true) {
		fread(&byte, sizeof(char), 1, f);
		fwrite(&byte, sizeof(char), 1, fc);
		if (feof(f)) {
			break;
		}
	}

}

bool Compress(char *fileName) {
	
	FILE *f, *fc;
	char *fileCompressedName;

	fileCompressedName = malloc(sizeof(char)*(strlen(fileName) + 10));
	
	strcpy(fileCompressedName, fileName);
	strcat(fileCompressedName, ".compress");

	f = fopen(fileName, "rb");
	fc = fopen(fileCompressedName, "wb");
	
	if (f == NULL) {
		return false;
	}

	CompresserdFileData CFData;

	frequencyCount(&CFData,f);

	PreCreateDecoderTree(&CFData);

	serializeList(&CFData, fc);

	CreateDecoderTree(&CFData);

	fclose(f);
	f = fopen(fileName, "rb");
	fclose(fc);
	fc = fopen(fileCompressedName, "wb");
	
	code(&CFData, f, fc);
}

void Descompress(char *fileName) {

}