
#ifndef OPERACOES_H
#define OPERACOES_H

#include "matriz.h"

int mesmasDimensoes(Matriz a, Matriz b);

int somarMatrizes(Matriz a, Matriz b, Matriz *resultado);

int subtrairMatrizes(Matriz a, Matriz b, Matriz *resultado);

int multiplicarMatrizes(Matriz a, Matriz b, Matriz *resultado);

int calcularInversa(Matriz original, Matriz *inversa);

int dividirMatrizes(Matriz a, Matriz b, Matriz *resultado);

int executarOperacao(Matriz matrizes[], int quantidade,
                     int operacao, Matriz *resultado);

#endif
