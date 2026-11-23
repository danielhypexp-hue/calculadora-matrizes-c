
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "matriz.h"

int lerInteiro(const char *mensagem) {
    char entrada[100];
    char *fim;
    long valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            exit(1);

        errno = 0;
        valor = strtol(entrada, &fim, 10);

        if (fim == entrada || errno == ERANGE ||
            valor < -2147483647L - 1 ||
            valor > 2147483647L) {
            printf("Valor invalido!\n");
            continue;
        }

        while (*fim == ' ' || *fim == '\t' ||
               *fim == '\n' || *fim == '\r')
            fim++;

        if (*fim != '\0') {
            printf("Entrada invalida!\n");
            continue;
        }

        return (int) valor;
    }
}

double lerReal(const char *mensagem) {
    char entrada[100];
    char *fim;
    double valor;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
            exit(1);

        errno = 0;
        valor = strtod(entrada, &fim);

        if (fim == entrada || errno == ERANGE ||
            !isfinite(valor)) {
            printf("Numero invalido!\n");
            continue;
        }

        while (*fim == ' ' || *fim == '\t' ||
               *fim == '\n' || *fim == '\r')
            fim++;

        if (*fim != '\0') {
            printf("Entrada invalida!\n");
            continue;
        }

        return valor;
    }
}

void cadastrarMatriz(Matriz *m, int numero) {
    char mensagem[100];

    printf("\nCadastro da matriz %d\n", numero);

    do {
        m->linhas = lerInteiro("Quantidade de linhas (1 a 10): ");
    } while (m->linhas < 1 || m->linhas > MAX_DIM);

    do {
        m->colunas = lerInteiro("Quantidade de colunas (1 a 10): ");
    } while (m->colunas < 1 || m->colunas > MAX_DIM);

    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {

            snprintf(mensagem, sizeof(mensagem),
                     "Elemento [%d][%d]: ", i + 1, j + 1);

            m->dados[i][j] = lerReal(mensagem);
        }
    }
}

void exibirMatriz(Matriz m) {
    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            printf("%10.2f ", m.dados[i][j]);
        }
        printf("\n");
    }
}
