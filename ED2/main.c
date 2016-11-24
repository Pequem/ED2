#include <stdio.h>
#include "compress.h"
#include <string.h>

int main(int argc, char *argv[]) {
	
	char function[20], fileName[50];

	if (argc < 3) {
		printf("\nA entrada precisa ser '[Descompacta/Compacta] [Nome do arquivo]'\n");
		scanf("%s %s", function, fileName);
	}
	else {
		strcpy(function, argv[1]);
		strcpy(fileName, argv[2]);
	}

	if (strcmp(function, "Compacta") == 0) {
		Compress(fileName);
	}
	else
		if (strcmp(function, "Descompacta") == 0) {
			Descompress(fileName);
		}
		return 0;
}

/*
Tem que reordenar a arvore a cada galho sim OKOK
Os programas precisam ser separados ou em arquivos separados sim
O tad bitmap pode ser violado/ pode ser personalizado  sim
Programa lançando breakPoint's

Reordenar a lista em cada passagem da arvora OKOK
Criar o sistema para fazer parar
Organizar o cod prototipando as função no inicio do arquivo
Separar compactador de descompactador
Criar lib comum a ambos
*/