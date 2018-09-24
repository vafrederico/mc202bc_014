/* Laboratorio 03 - GERENTE DE ESPAÇO */

#include "list.h"

void imprimeDisco(List* L, int size){
	
	char saida[8];
	int piece = 0;
	
	int pieceSize;
	pieceSize = size/8; // tamanho de cada uma das oito partes
	int posInicio, ocupado;

	for(piece = 0; piece < 8; piece++){ // para cada parte

		Node* n = L->init;

		posInicio = 0; ocupado = 0;

		while(n != NULL && posInicio < (piece+1)*pieceSize){ // passa por cada arquivo ou bloco vazio, ate que chegue ao fim do bloco

			if(posInicio+n->size >= piece*pieceSize){ // arquivo pertence ao bloco

				if(n->file[0] != '\0'){ // garante que nao seja espaco em branco
					
					ocupado += n->size; // soma ao ocupado

					if(posInicio < piece*pieceSize) // arquivo tem parte no bloco anterior
						ocupado -= piece*pieceSize - posInicio;

					if(posInicio+n->size > (piece+1)*pieceSize) // arquivo tem parte no bloco seguinte
						ocupado -= posInicio+n->size - (piece+1)*pieceSize;

				}
			}

			// proximo arquivo
			posInicio += n->size; 
			n = n->next;
		}

		// porcentagem ocupada		
		float p = (100 - (float)ocupado /pieceSize * 100);
		
		// marca a saida do pedaco
		if(p > 75)
			saida[piece] = ' ';
		else if (p > 25)
			saida[piece] = '-';
		else 
			saida[piece] = '#';

	
	}

	for(piece = 0; piece < 8; piece++){ // imprime
		printf("[%c]", saida[piece]);
	}

	printf("\n");
}

int main(){
	
	int size = 0;
	
	int i;
	char cmd[8], tamanho[10], file[11], sfileSize[11];
	int fileSize;
	int operacoes;
	int flag = 0;

	while (scanf("%d", &operacoes) && operacoes != 0){ // le o numero de operacoes ate que seja 0

		// le tamanho
		scanf("%s", tamanho);
		size = atoi(tamanho);

		// converte M e G
		if(strstr(tamanho, "M") != NULL)
			size *= 1024;
		if(strstr(tamanho, "G") != NULL)
			size *= 1024*1024;

			
		// inicializa TAD
		List* L;
		L = (List*) malloc(sizeof(List));
		L->init = (Node*) malloc(sizeof(Node));
		L->init->size = size;
		L->init->file[0] = '\0';
		L->init->next = NULL;
		L->capacity = size;

		// flag de disco cheio
		flag = 0;

		for(i = 0; i < operacoes; i++){ // le cada uma das operacoes

			// le instrucao
			scanf("%s", cmd);

			if(strcmp(cmd, "insere") == 0){ // insere

				// le nome e tamanho
				scanf("%s %s", file, sfileSize);
				
				// tamanho para int
				fileSize = atoi(sfileSize);

				// converte M e G
				if(strstr(sfileSize, "M") != NULL)
					fileSize *= 1024;

				if(strstr(sfileSize, "G") != NULL)
					fileSize *= 1024*1024;

				if(!flag) // se nao houve erro ate o momento
					if(!insert_node(L, file, fileSize)){ // se nao conseguir inserir, imprime erro e marca que houve erro
						printf("ERRO: disco cheio\n");
						flag = 1;
					}


			} else if (strcmp(cmd, "remove") == 0) {
				
				scanf("%s", file);
				if(!flag) // se nao houve erro ate o momento, remove
					remove_node(L, file);

				
			} else if (strcmp(cmd, "otimiza") == 0) {

				if(!flag) // se nao houve erro ate o momento, otimiza
					optimize(L);

				
			}
			
		}
		
		if(flag == 0) // se nao houve erro, imprime disco
			imprimeDisco(L, size);

		// desaloca toda memoria
		destroy_list(L);

	}

	return 0;

}


int remove_node(List* L, char* file){

	Node* n;
	n = L->init;
	Node* prev = NULL;

	// achou o que queria?
	int achou = 0;

	while(n != NULL){ // enquanto houver um no
		
		if(strcmp(n->file, file) == 0){ // no = arquivo procurado? se sim, marca que achou e marca que nao ha arquivo (nome = \0 => sem arquivo, bloco vazio)

			n->file[0] = '\0';
			achou = 1;
			break;

		}

		// proximo no
		prev = n;
		n = n->next;

	}

	if(achou){ // se achou arquivo, tenta juntar blocos adjacentes vazios
		
		if(prev != NULL && prev->file[0] == '\0'){ // junta bloco vazio anterior

			prev->next = n->next;
			prev->size += n->size;
			free(n);
			n = prev;
		}

		if(n->next != NULL && n->next->file[0] == '\0'){ // junta bloco vazio posterior

			n->size += n->next->size;
			Node* temp = n->next->next;

			free(n->next);
			n->next = temp;

		}

	}

	return 0;

}

Node* find_empty(List *L, int size){ // procura bloco vazio

	Node* atual = L->init;

	while(atual->next != NULL){

		if(atual->file[0] == '\0'){ // bloco vazio
			if(atual->size >= size){ // tamanho suficiente
				break;
			}
		}
		atual = atual->next;

	}

	if(atual->size < size){
		return NULL;	
	}

	return atual;

}

int insert_node(List* L, char* file, int size){

	Node* atual = find_empty(L, (int) size); // tenta achar um bloco vazio, grande o suficiente

	if(atual == NULL){ // se nao tiver, otimiza e tenta de novo, se nao conseguir, retorna erro
		optimize(L);
		atual = find_empty(L, (int) size);	
		if(atual == NULL)
			return 0;
	}

	// aloca bloco vazio que estara apos o arquivo
	Node* novo;
	novo = (Node*) malloc(sizeof(Node));
	novo->file[0] = '\0';
	
	// arruma proximos blocos e tamanho do bloco novo	
	novo->next = atual->next;
	novo->size = atual->size - size;
	
	// copia nome e tamanho do arquivo para o bloco que estava vazio
	strcpy(atual->file, file);
	atual->size = size;
	atual->next = novo;
	
	return 1;

}

void destroy_list(List* L) {

	if(L != NULL){ // se houver lista
	
		Node* n = L->init;
		Node* temp;

		while( n != NULL){ // enquanto tive no, destroi

			temp = n->next;
			free(n);
			n = temp;

		}

		free(L); // destroi lista

	}

}

int optimize(List* L){

	Node* prev = NULL;

	Node* atual = L->init;
	Node* temp;
	int size = 0;

	while(atual->next != NULL){ // enquanto tiver bloco

		if(atual->file[0] == '\0'){ // bloco vazio
			
			// checagem de primeiro bloco da lista
			if(prev != NULL)
				prev->next = atual->next;
			else
				L->init = atual->next;

			// destroi o bloco vazio
			temp = atual->next;
			free(atual);
			atual = temp;

		} else {

			// soma o tamanho do arquivo para saber o espaco final livre
			size += atual->size;
			prev = atual;
			atual = atual->next;

		}

	}

	// ultimo bloco sera vazio e tera todo o espaco livre
	atual->size = L->capacity - size;

	return 1;

}