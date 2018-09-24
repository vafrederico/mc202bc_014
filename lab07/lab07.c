/* Laboratorio 07 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _no {

	char valor;
	struct _no* esq;
	struct _no* dir;
	int soma;

 } no;

int buscaInt(int* string, int busca, int inicio, int fim);
no* montaArvore(int* posPre, int inicioEm, int fimEm, int* pre, int* em);
no* criarNo(char valor);
void libera(no* no);
no* buscaCaminho(no* n, int soma, no* menor);

int main(){

	int numNos, i;
	int* pre, *em;
	int posPre;
	while( scanf("%d", &numNos) && numNos != 0){ // numero de nos
		
		pre = (int*) malloc(sizeof(int)*(numNos+1)); // aloca a string, +1 para o \n
		em = (int*) malloc(sizeof(int)*(numNos+1));

		for(i = 0; i < numNos; i++)
			scanf("%d", &pre[i]);
		
		for(i = 0; i < numNos; i++)
			scanf("%d", &em[i]);

		posPre = 0; // posicao inicial
		no* raiz = montaArvore(&posPre, 0, numNos-1, pre, em); // retorna o no raiz da arvore

		no* menor = buscaCaminho(raiz, 0, NULL); // retorna o no com o menor caminho
		printf("%d\n", menor->valor);
		
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
	n->soma = 0;

	return n;
}

no* montaArvore(int* posPre, int inicioEm, int fimEm, int* pre, int* em){

	// se inicio > final, chegou ao fim do ramo
	if(inicioEm > fimEm)
		return NULL;

	// aloca no
	no* n = criarNo(pre[*posPre]);
	// incremento da posicao no vetor pre
	(*posPre)++;

	// posicao no vetor em
	int posEm  = buscaInt(em, n->valor, inicioEm, fimEm);

	if(inicioEm != fimEm){ // enquanto inicio != final, ha no

		// montaArvore para esquerda e direita
		n->esq = montaArvore( posPre, inicioEm, posEm - 1, pre, em);
		n->dir = montaArvore( posPre, posEm+1, fimEm, pre, em);
	
	}

	return n;

}

// procura um int em dado vetor, entre um intervalo
int buscaInt(int* string, int busca, int inicio, int fim){

	int i;

	for(i = inicio; i <= fim; i++){

		if(string[i] == busca)
			return i;
	}

	return -1;
}


// libera a arvore criada
void libera(no* no){

	if(no->esq)
		libera(no->esq);

	if(no->dir)
		libera(no->dir);

	free(no);
}

no* buscaCaminho(no* n, int soma, no* menor){

	if(!n->esq && !n->dir){ // fim da arvore
		n->soma = soma + n->valor; // seta a soma e se retorna
		return n;
	}

	no* temp;
	if(n->esq){ // se tiver esquerda
		temp = buscaCaminho(n->esq, soma+n->valor, menor); // desce ate o ultimo nivel
		if(menor == NULL || menor->soma > temp->soma || (menor->soma == temp->soma && menor->valor > temp->valor))
			// se primeira folha, ou se a soma desse for menor que a da que era menor, ou se forem iguais mas esse no tiver menor valor
			menor = temp;
	}

	if(n->dir){ // se tiver direita
		temp = buscaCaminho(n->dir, soma+n->valor, menor); // desce ate o ultimo nivel
		if(menor == NULL || menor->soma > temp->soma || (menor->soma == temp->soma && menor->valor > temp->valor))
			// se primeira folha, ou se a soma desse for menor que a da que era menor, ou se forem iguais mas esse no tiver menor valor
			menor = temp;
	
	}

	return menor;

}