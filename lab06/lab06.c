/* Laboratorio 06 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _no {

	char valor;
	struct _no* esq;
	struct _no* dir;

 } no;

int buscaChar(char* string, char busca, int inicio, int fim);
no* roda(int* posPre, int inicioEm, int fimEm, char* pre, char* em);
no* criarNo(char valor);
void imprimePosOrdem(no* no);
void libera(no* no);

int main(){

	int numTestes, numNos, i;
	char* pre, *em;
	int posPre;
	scanf("%d", &numTestes);

	for(i = 0; i < numTestes; i++){ // para cada teste

		scanf("%d", &numNos); // numero de nos
		
		pre = (char*) malloc(sizeof(char)*(numNos+1)); // aloca a string, +1 para o \n
		em = (char*) malloc(sizeof(char)*(numNos+1));
		scanf("%s %s", pre, em);
		
		posPre = 0; // posicao inicial
		no* raiz = roda(&posPre, 0, numNos-1, pre, em); // retorna o no raiz da arvore

		// imprime
		imprimePosOrdem(raiz);
		printf("\n");

		// libera a memoria
		free(pre);
		free(em);
		libera(raiz);
	}

	return 0;
}

// aloca um no e seta seu valor
no* criarNo(char valor){

	no* n;
	n = (no*) malloc(sizeof(no));
	n->esq = NULL;
	n->dir = NULL;
	n->valor = valor;

	return n;
}

no* roda(int* posPre, int inicioEm, int fimEm, char* pre, char* em){

	// se inicio > final, chegou ao fim do ramo
	if(inicioEm > fimEm)
		return NULL;

	// aloca no
	no* n = criarNo(pre[*posPre]);
	// incremento da posicao na string pre
	(*posPre)++;

	// posicao na string em
	int posEm  = buscaChar(em, n->valor, inicioEm, fimEm);

	if(inicioEm != fimEm){ // enquanto inicio != final, ha no

		// roda para esquerda e direita
		n->esq = roda( posPre, inicioEm, posEm - 1, pre, em);
		n->dir = roda( posPre, posEm+1, fimEm, pre, em);
	
	}

	return n;

}

// procura um char em dada string, entre um intervalo
int buscaChar(char* string, char busca, int inicio, int fim){

	int i;

	for(i = inicio; i <= fim; i++){

		if(string[i] == busca)
			return i;
	}

	return -1;
}

// imprime em pos ordem
void imprimePosOrdem(no* no){

	if(no->esq)
		imprimePosOrdem(no->esq);

	if(no->dir)
		imprimePosOrdem(no->dir);
	
	printf("%c", no->valor);

}

// libera a arvore criada
void libera(no* no){

	if(no->esq)
		libera(no->esq);

	if(no->dir)
		libera(no->dir);

	free(no);
}