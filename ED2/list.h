#ifndef LIST_H_
#define LIST_H_

/*
Essa lista é uma lista Genérica, duplamente encadeada e com sentinela
*/

//Constantes criadas para deixar o codigo mais legível
#define true 1
#define false 0
typedef int bool;

//Sentinela da lista
typedef struct list List;

//Nó da lista
typedef struct item Item;

//Retorna um ponteiro sentinela inicializada
List* list_new();

//Retorna um ponteiro para nó da lista com a data passada
//@param data Dados que estaram no nó da lista
Item* list_newItem(void *data);

//Insere um nó no inicio da lista
//@param list Sentinela da lista
//@param item Nó a ser adicionando
void list_pushOnFirst(List* list, Item* item);

//Insere um nó no final da lista
//@param list Sentinela da lista
//@param item Nó a ser adicionando
void list_pushOnLast(List * list, Item * item);

//Retorna o número de nós na lista
//@param list Sentinela da lista
int list_countItems(List * list);

//Função implementada parcialmente, pois não foi utilizada no trabalho
//int list_searchList(List * list, bool(*callback)(void *));

//Retira o Nó no index expecificado (liberando-o da memória) e retorna seus dados
//@param list Sentinala da lista
//@param index Posição do Nó
void* list_pull(List * list, int index);

//Retorna os dados de um Nó especifico sem remove-lo da lista
//@param list Sentinala da lista
//@param index Posição do Nó
void* list_pullWithoutRemove(List* list, int index);

//Ordena a lista seguindo as orientações do callback
//@param list Sentinela da lista
//@param callback Função auxiliar que compara os dados dos Nós
void list_order(List *list, int(*callback)(void*,void*));

//Imprime a lista
//@param list Sentinela da lista
//@param callback Função auxiliar que realiza a impressão dos dados do Nó
void list_print(List* list, void(callback)(void*));

//Libera a lista da memória
//@param list Sentinela da lista
//@param callback Função que libera os dados do Nó
void list_free(List *list, void(*callback)(void*));

#endif
