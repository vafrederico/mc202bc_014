/* Laboratorio 05 - Jogando Cartas */

#include <stdio.h>
#include <stdlib.h>

typedef struct _no {

	int valor;
	struct _no* prox;

} no;

typedef struct _fila {

	no* cabeca;
	int tam;

} fila;

// Inicia a fila
fila* iniciaFila();
// Insere carta no final da fila com valor especificado
void insere(fila*, int valor);
// Retorna a carta do topo e coloca a proxima carta no fim da fila
no* topo(fila*);

int main () {

	int num, i;

	while(scanf("%d", &num) && num != 0){

		// flag para colocar ou nao virgula
		int primeiro = 1;

		// inicia fila
		fila* fila = iniciaFila();

		// insere as cartas no baralho
		for(i = 1; i <= num; i++){

			insere(fila, i);

		}

		printf("Cartas jogadas:");
		// enquanto tiver pelo menos 2 cartas
		while(fila->tam > 1){
			
			if(!primeiro)
				printf(",");
			else
				primeiro = 0;

			printf(" ");

			// pega a carta do topo e passa a proxima para o fim do baralho
			no* no = topo(fila);
			
			// imprime o valor da carta que estava no topo
			printf("%d", no->valor);

			// libera o no da carta
			free(no);
		}

		printf("\nCarta restante: ");
		// imprime a carta que sobrou
		printf("%d\n", fila->cabeca->prox->valor);

		// libera o que sobrou
		free(fila->cabeca->prox);
		free(fila->cabeca);
		free(fila);
	
	}

	return 0;

}

void insere(fila* fila, int valor){

	no* c = fila->cabeca;
	no* n;

	// percorre até o final da fila
	while(c->prox != NULL){
		c = c->prox;
	}

	// aloca a carta
	n = (no*) malloc(sizeof(no));
	n->valor = valor;
	n->prox = NULL;

	// coloca no final da fila
	c->prox = n;

	// soma ao tamanho
	fila->tam += 1;

}

no* topo(fila* fila){

	no* c = fila->cabeca;

	if(c->prox != NULL){

		// topo = carta no topo
		no* topo = c->prox;

		// primeira carta sera a segunda carta apos o topo
		c->prox = topo->prox->prox;

		// percorre ate o final
		while(c->prox != NULL)
			c = c->prox;

		// coloca a carta que estava apos o topo no final do baralho
		c->prox = topo->prox;
		c->prox->prox = NULL;

		// diminui o tamanho
		fila->tam -= 1;

		// retorna a carta a jogar
		return topo;

	} else {
		
		return NULL;

	}

}

fila* iniciaFila(){

	// aloca fila
	fila* f = (fila*) malloc(sizeof(fila));
	// coloca tamanho 0
	f->tam = 0;

	// aloca cabeca
	f->cabeca = (no*) malloc(sizeof(no));
	f->cabeca->valor = -1;
	f->cabeca->prox = NULL;

	return f;

}