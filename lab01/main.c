#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Laboratorio 01 - Similaridade de Cossenos */

int main(int argc, char const *argv[])
{
	
	int i;
	int dimensao;
	float *vetores[3];
	float produtoInterno[2] = {0.0, 0.0};
	float norma[3] = {0.0, 0.0};;
	float similaridade[2];
	
	scanf("%d", &dimensao);

	// aloca vetores com a dimensao especificada
	for (i = 0; i < 3; i++)
	{
		vetores[i] = (float*) malloc(sizeof(float)*dimensao);
	}

	// faz a leitura dos vetores
	for (i = 0; i < dimensao; i++)
	{	
		scanf("%f %f %f", &vetores[0][i], &vetores[1][i], &vetores[2][i]);
	}
	
	// calcula produto internos e somatoria para norma		
	for(i = 0; i < dimensao; i++){
		produtoInterno[0] += vetores[0][i] * vetores[1][i];
		produtoInterno[1] += vetores[0][i] * vetores[2][i];

		norma[0] += vetores[0][i] * vetores[0][i];
		norma[1] += vetores[1][i] * vetores[1][i];
		norma[2] += vetores[2][i] * vetores[2][i];
	}

	// raiz quadrada da norma
	norma[0] = sqrt(norma[0]);
	norma[1] = sqrt(norma[1]);
	norma[2] = sqrt(norma[2]);

	// calcula a similaridade
	similaridade[0] = produtoInterno[0] / (norma[0] * norma[1]);
	similaridade[1] = produtoInterno[1] / (norma[0] * norma[2]);

	// imprime similaridades
	printf ("%.4f %.4f\n",similaridade[0], similaridade[1]);
	// imprime o mais similar
	if(similaridade[0] > similaridade[1])
		printf("b\n");
	else
		printf("c\n");

	// libera memoria alocada dinamicamente
	free(vetores[0]);
	free(vetores[1]);
	free(vetores[2]);

	return 0;

}