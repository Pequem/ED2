#include <stdio.h>
#include "compress.h"
#include <string.h>

int main(int argc, char *argv[]) {
	
	char *function[20], *fileName[50];

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
Tem que reordenar a arvore a cada galho
Os programas precisam ser separados ou em arquivos separados
O tad bitmap pode ser violado/ pode ser personalizado
� necessario criar a tabela de compacta��o ou posso usar minha forma de implementa��o
Tem problema a tad arvore ser hibrida
Mostrar se o processo de compacta��o � suficiente manipula��o de bitmap
Tenho que armazena a exten��o do arquivo
Tenho que usar o serialize de travesia especificado no trabalho
Tenho que usar caracter final na sequencia de bit ou posso fazer de outro jeito
Tem uma maneira de escrever um unico bit no arquivo
Compactar arquivos executavei ou maiores de 500MB
Minha forma de armazenar o cabe�alho
Posso deixar lixo na pasta
Tem como apagar o arquivo em C, � especifico para cada sistema
No c � possivel add no inicio ou ele sobescreve
Programa lan�ando breakPoint's

Criar o sistema para fazer parar
Organizar o cod prototipando as fun��o no inicio do arquivo
Separar compactador de descompactador
Criar lib comum a ambos
*/