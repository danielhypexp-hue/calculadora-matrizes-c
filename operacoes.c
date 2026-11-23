
#include <stdio.h>
#include <math.h>
#include "operacoes.h"

#define EPSILON 1e-10

int mesmasDimensoes(Matriz a, Matriz b) {
    return a.linhas == b.linhas &&
           a.colunas == b.colunas;
}

int somarMatrizes(Matriz a, Matriz b, Matriz *r) {
    if (!mesmasDimensoes(a, b))
        return 0;

    r->linhas = a.linhas;
    r->colunas = a.colunas;

    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            r->dados[i][j] =
                a.dados[i][j] + b.dados[i][j];

    return 1;
}

int subtrairMatrizes(Matriz a, Matriz b, Matriz *r) {
    if (!mesmasDimensoes(a, b))
        return 0;

    r->linhas = a.linhas;
    r->colunas = a.colunas;

    for (int i = 0; i < a.linhas; i++)
        for (int j = 0; j < a.colunas; j++)
            r->dados[i][j] =
                a.dados[i][j] - b.dados[i][j];

    return 1;
}

int multiplicarMatrizes(Matriz a, Matriz b, Matriz *r) {
    if (a.colunas != b.linhas)
        return 0;

    r->linhas = a.linhas;
    r->colunas = b.colunas;

    for (int i = 0; i < r->linhas; i++) {
        for (int j = 0; j < r->colunas; j++) {

            r->dados[i][j] = 0;

            for (int k = 0; k < a.colunas; k++)
                r->dados[i][j] +=
                    a.dados[i][k] * b.dados[k][j];
        }
    }

    return 1;
}

int calcularInversa(Matriz original, Matriz *inversa) {
    if (original.linhas != original.colunas)
        return 0;

    int n = original.linhas;
    double aux[MAX_DIM][2 * MAX_DIM];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aux[i][j] = original.dados[i][j];
            aux[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        int pivo = i;

        for (int k = i + 1; k < n; k++)
            if (fabs(aux[k][i]) > fabs(aux[pivo][i]))
                pivo = k;

        if (fabs(aux[pivo][i]) < EPSILON)
            return 0;

        if (pivo != i) {
            for (int j = 0; j < 2 * n; j++) {
                double temp = aux[i][j];
                aux[i][j] = aux[pivo][j];
                aux[pivo][j] = temp;
            }
        }

        double divisor = aux[i][i];

        for (int j = 0; j < 2 * n; j++)
            aux[i][j] /= divisor;

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double fator = aux[k][i];

                for (int j = 0; j < 2 * n; j++)
                    aux[k][j] -= fator * aux[i][j];
            }
        }
    }

    inversa->linhas = n;
    inversa->colunas = n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inversa->dados[i][j] = aux[i][j + n];

    return 1;
}

int dividirMatrizes(Matriz a, Matriz b, Matriz *r) {
    Matriz inversa;

    if (b.linhas != b.colunas) {
        printf("A matriz divisora deve ser quadrada.\n");
        return 0;
    }

    if (a.colunas != b.linhas) {
        printf("Dimensoes incompatíveis para divisao.\n");
        return 0;
    }

    if (!calcularInversa(b, &inversa)) {
        printf("A matriz divisora e singular.\n");
        return 0;
    }

    return multiplicarMatrizes(a, inversa, r);
}

int executarOperacao(Matriz matrizes[], int quantidade,
                     int operacao, Matriz *resultado) {

    *resultado = matrizes[0];

    for (int i = 1; i < quantidade; i++) {
        Matriz temporaria;
        int sucesso = 0;

        switch (operacao) {
            case 1:
                sucesso = somarMatrizes(
                    *resultado, matrizes[i], &temporaria);
                break;

            case 2:
                sucesso = subtrairMatrizes(
                    *resultado, matrizes[i], &temporaria);
                break;

            case 3:
                sucesso = multiplicarMatrizes(
                    *resultado, matrizes[i], &temporaria);
                break;

            case 4:
                sucesso = dividirMatrizes(
                    *resultado, matrizes[i], &temporaria);
                break;

            default:
                return 0;
        }

        if (!sucesso)
            return 0;

        *resultado = temporaria;
    }

    return 1;
}
