#include "lab02.h"

/* Laboratorio 02 - As Janelas da Matriz */

int main(){

	int r, c, m;
	int i, j;
	int **matriz;
	int x1, x2, y1, y2;
	int comando, v;

	scanf("%d %d %d", &r, &c, &m); // le dimensoes e m
	
	if( m <= 0 || r < 0 || c < 0){	 // m tem que ser > 0
		printf("erro\n");
		return 0;
	}

	matriz = (int**) malloc(sizeof(int*) * r); // aloca linhas

	for( i = 0; i < r; i++ ){ // em cada linha
		
		matriz[i] = (int*) malloc(sizeof(int) * c); // aloca colunas
		
		for ( j = 0; j < c; j++ ){ //inicializa matriz

			matriz[i][j] = 0;

		}

	}

	for( i = 0; i < m; i++){ // para cada instrucao

		scanf("%d %d %d %d %d", &comando, &x1, &y1, &x2, &y2); // le os quatro parametros sempre passados

		if (comando < 1 || comando > 3 || x1 < 0 || x1 >= r || x2 < 0 || x2 >= r || y1 < 0 || y1 >= c || y2 < 0 || y2 >= c || x1 > x2 || y1 > y2) { // dimensoes erradas
		
			printf("erro\n");
			return 0;

		}

		if(comando == 3){ 

			print_matrix_metrics(matriz, x1, y1, x2, y2); // chama funcao para imprimir

		} else if(comando != 3){
			
			scanf("%d", &v); // le o quinto parametro que falta

			if(comando == 1)
				increment_matrix(matriz, x1, y1, x2, y2, v); // chama funcao para incremetar
			else
				set_value_into_matrix(matriz, x1, y1, x2, y2,v); // chama funcao para setar valor

		}
	}

	for( i = 0; i < r; i++ ){ // em cada linha
		
		free(matriz[i]);

	}
	free(matriz);

	return 0;
}


// Função que incrementa em v os elementos da sub-matriz com dimensões (x1..x2, y1..y2)
void increment_matrix(int **mat, int x1, int y1, int x2, int y2, int v){
	int i;
	int j;
	for(i=x1; i <= x2; i++){

		for(j = y1; j <= y2; j++){ // para cada posicao (x, y) da matriz

			mat[i][j] += v; // soma v

		}

	}
}

// Seta com valor v, os elementos da sub-matriz com dimensões (x1..x2, y1..y2)
void set_value_into_matrix(int **mat, int x1, int y1, int x2, int y2, int v){
	int i;
	int j;
	for(i=x1; i <= x2; i++){

		for(j = y1; j <= y2; j++){  // para cada posicao (x, y) da matriz

			mat[i][j] = v; // seta v

		}

	}
}

// Imprime a soma, o máx e min dos elementos da sub-matriz com dimensões (x1..x2, y1..y2)
void print_matrix_metrics(int **mat, int x1, int y1, int x2, int y2){

	int max = 0, min = 0;
	long int somatoria = 0;
	int primeiro = 1;
	int i;
	int j;
	for(i=x1; i <= x2; i++){

		for(j = y1; j <= y2; j++){  // para cada posicao (x, y) da matriz


			if(primeiro){ // primeira vez que roda, nao tem minimo nem maximo, seta o primeiro valor
				min = mat[i][j];
				max = mat[i][j];
				primeiro = 0;
			}

			if(mat[i][j] > max) // verifica e seta maximo
				max = mat[i][j];
			
			if(mat[i][j] < min) // verifica e seta minimo
				min = mat[i][j];
			
			somatoria += mat[i][j]; // soma

		}

	}	

	printf("%ld %d %d\n", somatoria, min, max); // imprime
}
