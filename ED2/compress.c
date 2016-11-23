#include <stdlib.h>
#include <stdio.h>
#include "compress.h"
#include "tree.h"
#include "list.h"
#include "bitmap.h"
#include <string.h>

//Struct com a arvore
typedef struct{
	int frequencyArray[256];
	Branch *tree;
	List *branchList;
}CompressedFileData;

//Struct para a varialvel data dos nós da arvore
typedef struct {
	unsigned char letter;
	short int frequency;
} BranchData;

void printbitmap(bitmap bm) {
	int i;
	for (i = 0; i < bitmapGetLength(bm); i++) {
		printf("%i", bitmapGetBit(bm, i));
	}
}

void frequencyCount(CompressedFileData* CFData, FILE *f) {
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

void compareData(void *b1, void *b2) {
	if ((b1 == NULL) || (b2 == NULL)) {
		return false;
	}
	BranchData *bd1, *bd2;
	bd1 = b1;
	bd2 = b2;
	if (bd1->letter == bd2->letter)
		return true;
	return false;
}

void PreCreateDecoderTree(CompressedFileData *CFData) {

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

void CreateDecoderTree(CompressedFileData *CFData) {
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

void serializeList(CompressedFileData *CFData, FILE *fc) {
	
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

void code(CompressedFileData *CFData, FILE *f, FILE *fc) {
	unsigned char byte, byte2;
	bitmap bm1, bm2;
	bm1  = bitmapInit(8);
	int bm1Length,bm2Position,bm2Length;
	int i;
	while (true) {
		bm1Length = bitmapGetLength(bm1);
		while (bm1Length < 8) {
			fread(&byte, sizeof(char), 1, f);
			bm2 = tree_getWay(tree_searchBranch(CFData->tree, &byte ,compareData));	
			for (i = 0; i < bitmapGetLength(bm2); i++) {
					bitmapAppendLeastSignificantBit(&bm1, bitmapGetBit(bm2, i));
					if (bitmapGetLength(bm1) > 7) {
						bm2Position = i+1;
						break;
					}
				}
				bm1Length = bitmapGetLength(bm1);
		}
		byte2 = bm1.contents[0];
		
		printbitmap(bm1);

		fwrite(&byte2, sizeof(char), 1, fc);
		bm1 = bitmapInit(8);
		bm2Length = bitmapGetLength(bm2);
		if (bm2Position < bm2Length) {
			for (i = bm2Position; i < bitmapGetLength(bm2); i++) {
				bitmapAppendLeastSignificantBit(&bm1, bitmapGetBit(bm2, i));
			}
		}
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

	CompressedFileData CFData;

	frequencyCount(&CFData,f);

	PreCreateDecoderTree(&CFData);

	serializeList(&CFData, fc);

	CreateDecoderTree(&CFData);

	fclose(f);
	f = fopen(fileName, "rb");
	
	code(&CFData, f, fc);
}

void CreateBranchDataList(CompressedFileData *CFData, int numItens, FILE *f) {
	int i;

	CFData->branchList = list_new();
	BranchData *auxData;

	for (i = 0; i < numItens; i++) {
		auxData = malloc(sizeof(BranchData));
		fread(auxData, sizeof(BranchData), 1, f);
		list_pushOnLast(CFData->branchList, list_newItem(tree_newBranch(auxData)));
	}
	list_print(CFData->branchList, printItem);
}

void Decode(CompressedFileData *CFData, FILE *f, FILE *fd) {
	
	Branch *auxBranch;
	BranchData *auxBranchData = NULL;
	bitmap bm;
	unsigned char byte,bit;
	int i;

	bm.length = bm.max_size = 8;
	
	auxBranch = CFData->tree;

	while (true) {
		fread(&byte, sizeof(char), 1, f);
		if (feof(f))
			break;
		bm.contents = &byte;

		printbitmap(bm);

		for (i = 0; i < 8; i++) {
			bit = bitmapGetBit(bm, i);
			if (bit == 1) {
				auxBranch = tree_walkTree(auxBranch, _left);
			}
			else {
				auxBranch = tree_walkTree(auxBranch, _right);
			}
			auxBranchData = tree_getData(auxBranch);
			if (auxBranchData != NULL) {
				fwrite(&(auxBranchData->letter), sizeof(char), 1, fd);
				auxBranch = CFData->tree;
			}
		}
	}
}

void Descompress(char *fileName) {
	
	CompressedFileData CFData;
	FILE *f;
	FILE *fd;
	char *fileDescompressName;

	fileDescompressName = malloc(sizeof(char)*(strlen(fileName) + 1));
	strcpy(fileDescompressName, fileName);
	strcat(fileDescompressName, ".txt");
	
	f = fopen(fileName, "rb");
	fd = fopen(fileDescompressName, "wb");

	if (f == NULL) {
		return;
	}

	if (fd == NULL) {
		return;
	}

	int numBranchDataItens;

	fread(&numBranchDataItens, sizeof(int), 1, f);

	CFData.branchList = malloc(sizeof(BranchData)*numBranchDataItens);

	CreateBranchDataList(&CFData, numBranchDataItens, f);

	CreateDecoderTree(&CFData);

	Decode(&CFData, f, fd);
}