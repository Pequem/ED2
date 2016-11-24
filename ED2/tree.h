#ifndef TREE_H_
#define TREE_H_

#include "bitmap.h"

//Constantes criadas para deixar o codigo mais leg�vel
#define true 1
#define false 0
typedef short int bool;

//Constantes criadas para deixar o codigo mais leg�vel
#define _right 1
#define _left 0
typedef int Direction;

//N�s da �rvore
typedef struct branch Branch;

//Retorna um N� da arvore com os dados passados
//@param data Dados a serem colocados na arvore
Branch* tree_newBranch(void *data);

//Insere o N� b na dire��o determinada no N� a
//@param a N� a receber o outro N�
//@param b N� a ser inserido
//@param Direction Dire��o a ser colocado o N� b no a (direita ou esquerda)
bool tree_pushBranch(Branch *a, Branch *b, Direction direction);

//Retorna o N� que contenha do dado especificado
//@param root Raiz da �rvore
//@param data Dados a ser encontrado
//@param callback Fun��o auxiliar que realiza a compara��o dos dados
Branch *tree_searchBranch(Branch *root, void *data, bool(*callback)(void*, void*));

//Retorna os dados de um N�
//@param n N� a qual deseja obter os dados
void* tree_getData(Branch *b);

//Insere os dados em um N�
//@param b N� a qual se quer inserir os dados
//@param data Dados a serem inseridos
void tree_setData(Branch *b, void *data);

//Retorna o N� da dire��o especificada
//@param b N� atual
//@param Direction Dire��o que se deseja "andar"
Branch *tree_walkTree(Branch *b, Direction d);

//Retorna o caminho da raiz at� no N� especificado em um bitmap
//@param b N� que se deseja obter o caminho
bitmap tree_getWay(Branch *b);

//Diz se um N� � folha
//@param auxBranch N� que se deseja verificar
bool isLeaf(Branch *auxBranch);

//Libera a �rvore da mem�ria
//@param root Raiz da �rvore
//@param callback Fun��o auxiliar para liberar os dados dos N�s
void tree_free(Branch *root, void(*callback)(void*));
#endif