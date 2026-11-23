
#include <stdio.h>
#include "matriz.h"
#include "operacoes.h"

#define MAX_MATRIZES 10

void exibirMenu(void) {
    printf("\n===== CALCULADORA DE MATRIZES =====\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao matricial\n");
    printf("0 - Sair\n");
    printf("==================================\n");
}

int main(void) {
    Matriz matrizes[MAX_MATRIZES];
    Matriz resultado;

    int quantidade;
    int opcao;

    printf("CALCULADORA DE MATRIZES\n");

    do {
        quantidade = lerInteiro(
            "Quantidade de matrizes (2 a 10): ");

        if (quantidade < 2 || quantidade > MAX_MATRIZES)
            printf("Quantidade invalida!\n");

    } while (quantidade < 2 || quantidade > MAX_MATRIZES);

    for (int i = 0; i < quantidade; i++)
        cadastrarMatriz(&matrizes[i], i + 1);

    do {
        exibirMenu();
        opcao = lerInteiro("Escolha uma opcao: ");

        if (opcao == 0) {
            printf("Sistema encerrado.\n");
            break;
        }

        if (opcao < 1 || opcao > 4) {
            printf("Opcao invalida!\n");
            continue;
        }

        if (executarOperacao(
            matrizes, quantidade, opcao, &resultado)) {

            printf("\nResultado:\n");
            exibirMatriz(resultado);

        } else {
            printf("Nao foi possivel realizar a operacao.\n");
        }

    } while (1);

    return 0;
}
