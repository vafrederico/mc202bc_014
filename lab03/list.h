#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>


typedef struct _node {
	char 	file[20]; // nome do arquivo
	int 	size; // tamanho do arquivo
	struct _node *next;
} Node;


typedef struct _list {
	int capacity;
	Node *init; // guarda a referência do início da lista
} List;


/******* OBRIGATÓRIO *********/
int insert_node(List* L, char* file, int size);
int remove_node(List* L, char* file);
int optimize(List* L);

/******* OPCIONAL *********/
void init_list(List** L, int capacity); // Cria uma lista
void destroy_list(List* L);
int disk_status(List* L); // Imprime o status da Lista
