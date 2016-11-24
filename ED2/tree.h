#ifndef TREE_H_
#define TREE_H_

#include "bitmap.h"

//Constantes criadas para deixar o codigo mais legível
#define true 1
#define false 0
typedef short int bool;

//Constantes criadas para deixar o codigo mais legível
#define _right 1
#define _left 0
typedef int Direction;

//Nós da árvore
typedef struct branch Branch;

//Retorna um Nó da arvore com os dados passados
//@param data Dados a serem colocados na arvore
Branch* tree_newBranch(void *data);

//Insere o Nó b na direção determinada no Nó a
//@param a Nó a receber o outro Nó
//@param b Nó a ser inserido
//@param Direction Direção a ser colocado o Nó b no a (direita ou esquerda)
bool tree_pushBranch(Branch *a, Branch *b, Direction direction);

//Retorna o Nó que contenha do dado especificado
//@param root Raiz da árvore
//@param data Dados a ser encontrado
//@param callback Função auxiliar que realiza a comparação dos dados
Branch *tree_searchBranch(Branch *root, void *data, bool(*callback)(void*, void*));

//Retorna os dados de um Nó
//@param n Nó a qual deseja obter os dados
void* tree_getData(Branch *b);

//Insere os dados em um Nó
//@param b Nó a qual se quer inserir os dados
//@param data Dados a serem inseridos
void tree_setData(Branch *b, void *data);

//Retorna o Nó da direção especificada
//@param b Nó atual
//@param Direction Direção que se deseja "andar"
Branch *tree_walkTree(Branch *b, Direction d);

//Retorna o caminho da raiz até no Nó especificado em um bitmap
//@param b Nó que se deseja obter o caminho
bitmap tree_getWay(Branch *b);

//Diz se um Nó é folha
//@param auxBranch Nó que se deseja verificar
bool isLeaf(Branch *auxBranch);

//Libera a árvore da memória
//@param root Raiz da árvore
//@param callback Função auxiliar para liberar os dados dos Nós
void tree_free(Branch *root, void(*callback)(void*));
#endif