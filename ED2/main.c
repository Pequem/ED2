#include <stdio.h>
#include "compress.h"

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("entrada precisa ser '[Descompacta/Compacta] [Nome do arquivo]'");
	}

	if (strcmp(argv[1], "Compacta") == 0) {
		Compress(argv[2]);
	}
	else
		if (strcmp(argv[1], "Descompacta") == 0) {
			Descompress(argv[2]);
		}
		else {
			printf("Comando Invalido!");
		}

		return 0;
}