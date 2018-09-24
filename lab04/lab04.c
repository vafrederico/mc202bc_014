/* Laboratorio 04 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>

typedef struct _boneca{

	int valor;
	int soma;

} boneca;

// Empilha a boneca caso seja possivel e retorna, caso contrario retorna 0.
int empilha(boneca* pilha, int* t, boneca B);

// Desempilha a boneca.
boneca desempilha(boneca* pilha, int* t);

int main(){

	int numOperacoes, i, input;

	while(scanf("%d", &numOperacoes) && numOperacoes != 0){ // Enquanto nao tiver numero 0 de operacoes

		// Aloca a pilha com o tamanho maximo necessario
		boneca* pilha = (boneca*) malloc(sizeof(boneca) * numOperacoes);

		int t = 0;
		int errorFlag = 0;

		if(numOperacoes % 2) // Se for impar, nunca fecha
			errorFlag = 1;

		for(i = 0; i < numOperacoes; i++){

			scanf("%d", &input);

			if(!errorFlag){ // Nao houve erro ainda

				if(input < 0){ // Abre a boneca

					// nova boneca
					boneca temp; 
					temp.valor = input*-1;
					temp.soma = 0;

					if(!empilha(pilha, &t, temp)) //tenta empilhar, se nao for possivel, marca que houve erro
						errorFlag = 1;

				} else {

					if (t == 0) // pilha vazia, nao ha o que retirar
						errorFlag = 1;

					boneca temp = desempilha(pilha, &t); // desempilha a boneca

					if(temp.valor != input) // se nao for o fechamento da boneca correta, marca que houve erro
						errorFlag = 1;

				}

			}

		}

		if(t > 0) // ainda ha bonecas na pilha que nao foram fechadas
			errorFlag = 1;

		// Saida dependendo de ter ocorrido erro
		if(!errorFlag)
			printf(":-) Matrioshka!\n");
		else
			printf(":-( Tente novamente.\n");

		// libera a pilha alocada dinamicamente
		free(pilha);

	}

	return 0;

}

int empilha(boneca* pilha, int* t, boneca B){
	
	if(*t > 0){ // se nao for o primeiro, checa para soma das bonecas dentro da boneca que as contem
		boneca* anterior = &pilha[*t - 1];
		anterior->soma += B.valor;	

		if(anterior->soma >= anterior->valor)
			return 0;
	}
	
	// empilha a boneca e incrementa o contador
	pilha[(*t)++] = B;
	return 1;

}

boneca desempilha(boneca* pilha, int* t){
	
	// desempilha a boneca após decrementar o contador
	return pilha[--(*t)];

}