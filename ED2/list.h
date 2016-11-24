#ifndef LIST_H_
#define LIST_H_

/*
Essa lista � uma lista Gen�rica, duplamente encadeada e com sentinela
*/

//Constantes criadas para deixar o codigo mais leg�vel
#define true 1
#define false 0
typedef int bool;

//Sentinela da lista
typedef struct list List;

//N� da lista
typedef struct item Item;

//Retorna um ponteiro sentinela inicializada
List* list_new();

//Retorna um ponteiro para n� da lista com a data passada
//@param data Dados que estaram no n� da lista
Item* list_newItem(void *data);

//Insere um n� no inicio da lista
//@param list Sentinela da lista
//@param item N� a ser adicionando
void list_pushOnFirst(List* list, Item* item);

//Insere um n� no final da lista
//@param list Sentinela da lista
//@param item N� a ser adicionando
void list_pushOnLast(List * list, Item * item);

//Retorna o n�mero de n�s na lista
//@param list Sentinela da lista
int list_countItems(List * list);

//Fun��o implementada parcialmente, pois n�o foi utilizada no trabalho
//int list_searchList(List * list, bool(*callback)(void *));

//Retira o N� no index expecificado (liberando-o da mem�ria) e retorna seus dados
//@param list Sentinala da lista
//@param index Posi��o do N�
void* list_pull(List * list, int index);

//Retorna os dados de um N� especifico sem remove-lo da lista
//@param list Sentinala da lista
//@param index Posi��o do N�
void* list_pullWithoutRemove(List* list, int index);

//Ordena a lista seguindo as orienta��es do callback
//@param list Sentinela da lista
//@param callback Fun��o auxiliar que compara os dados dos N�s
void list_order(List *list, int(*callback)(void*,void*));

//Imprime a lista
//@param list Sentinela da lista
//@param callback Fun��o auxiliar que realiza a impress�o dos dados do N�
void list_print(List* list, void(callback)(void*));

//Libera a lista da mem�ria
//@param list Sentinela da lista
//@param callback Fun��o que libera os dados do N�
void list_free(List *list, void(*callback)(void*));

#endif
