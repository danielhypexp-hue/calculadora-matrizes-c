
#ifndef MATRIZ_H
#define MATRIZ_H

#define MAX_DIM 10

typedef struct {
    int linhas;
    int colunas;
    double dados[MAX_DIM][MAX_DIM];
} Matriz;

int lerInteiro(const char *mensagem);
double lerReal(const char *mensagem);

void cadastrarMatriz(Matriz *m, int numero);
void exibirMatriz(Matriz m);

#endif
