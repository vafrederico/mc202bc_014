/* Laboratorio 08 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lista ligada de disciplinas
typedef struct _disciplina {

	char nome[5];
	struct _disciplina* prox;
} disciplina;

// lista ligada de alunos
typedef struct  _aluno
{
	char nome[100];
	disciplina* disciplinas;
	struct _aluno* prox;

} aluno;

// tabela de espelhamento
typedef struct _hashTable{

	aluno** alunos;

} hashTable;

// inicia uma tabela de espelhamento
hashTable* iniciaHashTable(int hashTableSize){ 

	int i;
	// aloca
	hashTable* table = (hashTable*) malloc(sizeof(hashTable));
	// inicia listagem de alunos
	table->alunos = (aluno**) malloc(sizeof(aluno)*hashTableSize);

	// cria no cabeça de alunos para todas posicoes
	for(i = 0; i < hashTableSize; i++){
		table->alunos[i] = (aluno*) malloc(sizeof(aluno));
		table->alunos[i]->nome[0] = '\0';
		table->alunos[i]->prox = NULL;
		table->alunos[i]->disciplinas = NULL;
	}

	return table;
}

// retorna a posicao na tabela de espelhamento referente ao nome
int positionHashTable(char* nome, int hashTableSize){

	// soma ASCII % tamanho
	int soma = 0;
	int i = 0;
	for(i =0; nome[i] != '\0'; i++){
		soma += nome[i];
	}

	return soma%hashTableSize;

}

// retorna aluno a partir do nome
aluno* getAluno(char* nome, hashTable* table, int hashTableSize){

	// pega posiao na tabela
	int posHash = positionHashTable(nome, hashTableSize);

	// primeiro aluno
	aluno* n = table->alunos[posHash]->prox;

	// busca aluno por nome
	while(n) {
		
		if(strcmp(n->nome, nome) == 0)
			return n;

		n = n->prox;
	}

	return NULL;

}

// insere um aluno com nome dado
void insereAluno(char* nome, hashTable* table, int hashTableSize){

	// pega posicao na tabela
	int posHash = positionHashTable(nome, hashTableSize);

	// primeiro aluno
	aluno* n = table->alunos[posHash];

	// vai ate o ultimo
	while(n->prox) {
			
		// verifica se ja existe aluno
		if(strcmp(n->nome, nome) == 0)
			return;

		n = n->prox;

	}

	// verifica que o ultimo nao tem o mesmo nome
	if(strcmp(n->nome, nome) == 0)
		return;

	// aloca
	aluno* novo = (aluno*) malloc(sizeof(aluno));
		
	// nome	
	strcpy(novo->nome, nome);

	// aloca e inicia no cabeca de disciplinas
	novo->disciplinas = (disciplina*) malloc(sizeof(disciplina));
	novo->disciplinas->nome[0] = '\0';
	novo->disciplinas->prox = NULL;

	// seta proximos
	n->prox = novo;
	novo->prox = NULL;


}

// remove aluno a partir do nome
void removeAluno(char* nome, hashTable* table, int hashTableSize){

	// pega posicao na tabela
	int posHash = positionHashTable(nome, hashTableSize);

	// primeiro aluno
	aluno* n = table->alunos[posHash]->prox;
	// raiz
	aluno* prev = table->alunos[posHash];

	int flag = 0;

	// procura aluno com o nome
	while(n && !flag) {
		
		if(strcmp(n->nome, nome) == 0){
			flag = 1;
		} else {
			prev = n;
			n = n->prox;
		}

	}

	// achou aluno?
	if(!flag){
		printf("ERRO: %s nao esta matriculado.\n", nome);
		return;
	}

	// aruma proximos	
	prev->prox = n->prox;

	// disciplinas do aluno
	disciplina* d = n->disciplinas;
	disciplina* temp;
	
	// libera memoria alocada para disciplinas
	while(d){
		temp = d;
		d = d->prox;
		free(temp);
	}

	// libera memoria do aluno
	free(n);

}

// lista disciplinas de um aluno a partir do nome
void consultaAluno(char* nome, hashTable* table, int hashTableSize){
		
	// pega aluno
	aluno* n = getAluno(nome, table, hashTableSize);

	// existe aluno?
	if(!n){
		printf("%s nao esta matriculado.\n", nome);
		return;
	}

	// tem disciplinas?
	if(n->disciplinas->prox == NULL){
		printf("%s trancou o semestre.\n", n->nome);
		return;
	}

	// imprime nome
	printf("%s", n->nome);

	// primeira disciplina
	disciplina* d = n->disciplinas->prox;
	// para cada disciplina imprime nome
	while(d){
		printf(" %s", d->nome);
		d = d->prox;
	}

	printf("\n");
}

// insere aluno em determinada materia a partir do nome de ambos
void matriculaAluno(char* nome, char* disciplinaNome, hashTable* table, int hashTableSize){

	// pega aluno
	aluno* n = getAluno(nome, table, hashTableSize);

	// existe aluno?
	if(!n){
		printf("ERRO: %s nao esta matriculado.\n", nome);
		return;
	}

	// no cabeca de disciplinas
	disciplina* d = n->disciplinas;
	
	// vai ate o final da lista
	while(d->prox) {
		
		// verifica se disciplina ja esta matriculada
		if(strcmp(d->nome, disciplinaNome) == 0)
			return;

		d = d->prox;

	}

	// verifica se a ultima matricula nao eh a que vai ser inserida
	if(strcmp(d->nome, disciplinaNome) == 0)
		return;

	// aloca nova disciplina
	disciplina* novo = (disciplina*) malloc(sizeof(disciplina));

	// seta nome
	strcpy(novo->nome, disciplinaNome);

	// seta proximos
	d->prox = novo;
	novo->prox = NULL;

}

// remove aluno de disciplina dado nome de ambos
void desmatriculaAluno(char* nome, char* disciplinaNome, hashTable* table, int hashTableSize){

	// pega aluno
	aluno* a = getAluno(nome, table, hashTableSize);

	// existe aluno?
	if(!a){
		printf("ERRO: %s nao esta matriculado.\n", nome);
		return;
	}

	// primeira disciplina
	disciplina* n = a->disciplinas->prox;
	// no cabeca de disciplinas
	disciplina* prev = a->disciplinas;

	int flag = 0;

	// para cada no
	while(n && !flag) {
		
		if(strcmp(n->nome, disciplinaNome) == 0){ // procura disciplina
			flag = 1;
		} else {
			prev = n;
			n = n->prox;
		}

	}

	// achou?
	if(!flag){
		printf("ERRO: %s nao esta matriculado em %s.\n", nome, disciplinaNome);
		return;
	}

	// seta proximo
	prev->prox = n->prox;

	// libera memoria da disciplina
	free(n);

	// ainda possui disciplinas?
	if(a->disciplinas->prox == NULL)
		printf("%s trancou o semestre.\n", n->nome);

}

// lista alunos que cursam uma disciplina a partir do nome da disciplina
void listaAlunos(char* disciplinaNome, hashTable* table, int hashTableSize){

	int i;

	aluno* aluno;

	disciplina* disciplina;

	// para cada posicao da tabela de espelhamento
	for( i = 0; i < hashTableSize; i++){

		// primeiro aluno
		aluno = table->alunos[i]->prox;

		// para cada aluno
		while(aluno){

			// primeira disciplina
			disciplina = aluno->disciplinas->prox;

			// para cada disciplina
			while(disciplina){

				// esta matriculado na disciplina buscada?
				if(strcmp(disciplina->nome, disciplinaNome) == 0)
					printf("%s\n", aluno->nome);

				disciplina = disciplina->prox;

			}

			aluno = aluno->prox;
		}
	}

}

void* destroiHashTable(hashTable* table, int hashTableSize){

	int i;
	
	aluno* n;
	aluno* alunoTemp;
	
	disciplina* d;
	disciplina* disciplinaTemp;

	// para cada posicao da tabela de espelhamento
	for(i = 0; i < hashTableSize; i++){
		
		// no cabeca de alunos
		n = table->alunos[i];

		// para cada aluno
		while(n) {
				
			// no cabeca de disciplinas
			d = n->disciplinas;
				
			// para cada disciplina
			while(d){

				disciplinaTemp = d;
				d = d->prox;
				
				// libera memoria da disciplina
				free(disciplinaTemp);

			}

			alunoTemp = n;
			n = n->prox;

			// libera memoria do aluno
			free(alunoTemp);

		}

	}
	
	// libera memoria do vetor da posicao na tabela
	free(table->alunos);

	// libera memoria da tabela
	free(table);

}

int main (){

	int hashTableSize, comandos;
	int i;
	
	char comando[13];
	char aluno[101];
	char disciplina[6];

	hashTable* table;

	// tem comandos do caso de teste
	while(scanf("%d", &comandos) && comandos !=0){

		// tamanho da tabela
		scanf("%d", &hashTableSize);

		// inicia tabela
		table = iniciaHashTable(hashTableSize);

		// para cada comando
		for(i = 0; i < comandos; i++){

			// le o comando
			scanf("%s", comando);

			// roda a funcao associada
			if(strcmp(comando, "insere") == 0){

				scanf("%s", aluno);
				insereAluno(aluno, table, hashTableSize);

			} else if(strcmp(comando, "remove") == 0){

				scanf("%s", aluno);
				removeAluno(aluno, table, hashTableSize);

			} else if(strcmp(comando, "consulta") == 0){

				scanf("%s", aluno);
				consultaAluno(aluno, table, hashTableSize);
			
			} else if(strcmp(comando, "matricula") == 0){
			
				scanf("%s %s", aluno, disciplina);
				matriculaAluno(aluno, disciplina, table, hashTableSize);
			
			} else if(strcmp(comando, "desmatricula") == 0){
			
				scanf("%s %s", aluno, disciplina);
				desmatriculaAluno(aluno, disciplina, table, hashTableSize);
			
			} else if(strcmp(comando, "alunos") == 0){
			
				scanf("%s", disciplina);
				listaAlunos(disciplina, table, hashTableSize);

			}

		}

		// libera toda memoria alocada para a tabela do caso de teste
		destroiHashTable(table, hashTableSize);

	}
	return 0;
}