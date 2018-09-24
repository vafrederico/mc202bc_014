#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Função que incrementa em v os elementos da sub-matriz com dimensões (x1..x2, y1..y2)
void increment_matrix(int **mat, int x1, int y1, int x2, int y2, int v);

// Seta com valor v, os elementos da sub-matriz com dimensões (x1..x2, y1..y2)
void set_value_into_matrix(int **mat, int x1, int y1, int x2, int y2, int v);

// Imprime a soma, o máx e min dos elementos da sub-matriz com dimensões (x1..x2, y1..y2)
void print_matrix_metrics(int **mat, int x1, int y1, int x2, int y2);