#include <stdlib.h>
#include <stdio.h>
#include "compress.h"
#include "tree.h"
#include "list"

typedef struct{
	unsigned int dataLength;
	unsigned int frequencyArray[256];
	Branch *tree;
}CompresserdFileData;

void frequencyCount(CompresserdFileData* CFData, FILE *f) {
	int i;
	for (i = 0; i < 256; i++) {
		CFData->frequencyArray[i] = 0;
	}

	char bit;
	bool whileControl = true;

	while (whileControl) {

		fread(&bit, sizeof(char), 1, f);
		if (feof(f)) {
			whileControl = false;
			break;
		}

		CFData->frequencyArray[bit]++;
	}
}

void CreateDecoderTree(CompresserdFileData *CFData) {

	int i,countRoots = 0;

	//Conta quantas raizes precisam ser criadas
	for (i = 0; i < 256; i++) {
		if (CFData->frequencyArray[i] > 0) {
			countRoots++;
		}
	}

}

bool Compress(char *fileName) {
	
	FILE *f;

	f = fopen(fileName, "rb");
	
	if (f == NULL) {
		return false;
	}

	CompresserdFileData CFData;

	frequencyCount(&CFData,f);
}

void Descompress(char *fileName) {

}