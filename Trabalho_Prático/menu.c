#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "jogo.h"
#include "menu.h"

int menu_jogo(){
    int opt;
    int res = 0;

    do
    {
        printf("\n**** Escolha a Jogada ****\n");
        printf("1 - Adicionar uma peca Verde\n");
        printf("2 - Substituir uma peca Verde por uma Amarela\n");
        printf("3 - Substituir uma peca Amarela por uma Vermelha\n");
        printf("4 - Adicionar Linha/Coluna\n");
        printf("5 - Adicionar uma Pedra\n");
        printf("6 - Jogadas realizadas anteriormente\n");
        printf("7 - Guardar jogo e sair\n");
        printf("8 - Sair\n");
        printf("\nOpcao: ");
        fseek(stdin,0,SEEK_END);
        res = scanf("%d", &opt);

        printf("\n");
    }
    while(res != 1 || opt < OPT_ADD_PECA || opt > OPT_SAIR);

    return opt;
}

int menu_inicio(){
    int opt;
    int res = 0;

    do
    {
        printf("\n**** Bem-Vindo ao jogo do Semaforo ****\n");
        printf("1 - 1 Jogador\n");
        printf("2 - 2 Jogadores\n");
        printf("3 - Sair\n");
        printf("\nOpcao: ");
        fseek(stdin,0,SEEK_END);
        res = scanf("%d", &opt);

        printf("\n");
    }
    while(res != 1 || opt < OPT_1_JOG || opt > OPT_SAIR_INICIO);

    return opt;
}

int menu_col_lin(){
    int opt;
    int res = 0;

    do
    {
        printf("\n**** Selecione a jogada ****\n");
        printf("1 - Adicionar Coluna\n");
        printf("2 - Adicionar Linha\n");
        printf("3 - Voltar Atras\n");
        printf("\nOpcao: ");
        fseek(stdin,0,SEEK_END);
        res = scanf("%d", &opt);

        printf("\n");
    }
    while(res != 1 || opt < OPT_ADD_COL || opt > OPT_ATRAS);

    return opt;
}

