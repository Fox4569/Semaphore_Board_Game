#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "jogo.h"
#include "menu.h"

int main()
{
    int n_linhas, n_colunas, i, n_jogadas = 0;
    int opt, optinicio;                                                                                     //opções dos menus
    char jogador = 'B';                                                                                     //declaração e inicialização da variavel jogador
    jog lista_jogadas[2] = {{'A', MAX_ADD_LINCOL, MAX_ADD_PEDRA} , {'B', MAX_ADD_LINCOL, MAX_ADD_PEDRA}};   //vetor do tipo jogador que regula o nº de jogadas disponiveis
    ptab lista_tab = NULL, aux;                                                                             //declaração das listas ligadas
    char nomeF[TAM];                                                                                        //variavel para o nome do ficheiro

    initRandom();                                               // Inicializa o gerador de numeros aleatorios

    char** tab = NULL;                                          //declaração do tabuleiro de jogo

    lista_tab = retomaJogo(lista_tab, &jogador);                //vamos verificar se o jogador pretende retomar o jogo anterior
    if(lista_tab == NULL){                                      //Caso o jogador não pretenda retomar (lista está a NULL)
        n_linhas = intUniformRnd(3, 5);                         //tamanho do tabuleiro inicial (entre 3 e 5 linhas/colunas)
        n_colunas = n_linhas;

        tab = malloc(sizeof(char*) * n_linhas);                 //alocação de memoria do tabuleiro

        if(tab == NULL){
            printf("\nErro na alocacao de memoria!\n");
            return 0;
        }
        for(i = 0; i < n_colunas; i++){
            tab[i] = malloc(sizeof(char) * n_colunas);
        }

    }else{                                                      //Caso o jogador pretenda retomar

        aux = lista_tab;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        tab = malloc(sizeof(char*) * aux->linhas);               //alocação de memoria do tabuleiro

        if(tab == NULL){
            printf("\nErro na alocacao de memoria!\n");
            return 0;
        }

        for(i = 0; i < n_colunas; i++){
            tab[i] = malloc(sizeof(char) * aux->colunas);
        }

    }

    optinicio = menu_inicio();                                    //Menu inicial (modo 1 ou 2 jogadores)
        switch(optinicio){
            case OPT_1_JOG:
            case OPT_2_JOG:
                if(lista_tab == NULL)
                    inicializaTab(n_linhas, n_colunas, tab);
                else
                    inicializaTabRetoma(lista_tab, tab);

                escreveTab(n_linhas, n_colunas, tab);

                do
                {
                    if(ganhaJogo(n_linhas, n_colunas, tab) == 1){                     //verificar o final do jogo
                        printf("\nO jogador %c ganhou!\n",jogador);
                        printf("\nIntroduza o nome do ficheiro: ");
                        scanf("%s", nomeF);
                        guardaFinalJogo(lista_tab, nomeF);
                        return 0;
                    }else{
                        if(jogador == 'A')                                           //trocar o jogador (jogada seguinte)
                            jogador = 'B';
                        else
                            jogador = 'A';
                    }


                    printf("\nE a vez do jogador %c\n", jogador);

                    if(optinicio == 1 && jogador == 'B'){                             //modo 1 jogador (jogada do PC)
                        opt = selecionaJogadaPC();
                        // printf("\n\n%d\n\n", opt);
                    }else
                        opt = menu_jogo();                                            //Menu de jogo (escolher a jogada a fazer)
                    switch(opt){
                        case OPT_ADD_PECA:                                            //Adicionar peça verde
                            if(verificaJogada(n_linhas, n_colunas, tab, 'G') == 0){
                                printf("\nNao e possivel fazer essa jogada!\n\n");
                                jogador = mantemJogador(jogador);
                                continue;
                            }else{
                                adiciona_verde(n_linhas, n_colunas, tab, optinicio, jogador);
                                escreveTab(n_linhas, n_colunas, tab);
                                lista_tab = guardaJogadas(n_linhas, n_colunas, &n_jogadas, tab, lista_tab);
                                break;
                            }
                        case OPT_TR_VERDE:                                            //Adicionar peça amarela
                            if(verificaJogada(n_linhas, n_colunas, tab, 'Y') == 0){
                                printf("\nNao e possivel fazer essa jogada!\n\n");
                                jogador = mantemJogador(jogador);
                                continue;
                            }else{
                                adiciona_amarelo(n_linhas, n_colunas, tab, optinicio, jogador);
                                escreveTab(n_linhas, n_colunas, tab);
                                lista_tab = guardaJogadas(n_linhas, n_colunas, &n_jogadas, tab, lista_tab);
                                break;
                            }
                        case OPT_TR_AMARELA:                                          //Adicionar peça vermelha
                            if(verificaJogada(n_linhas, n_colunas, tab, 'R') == 0){
                                printf("\nNao e possivel fazer essa jogada!\n\n");
                                jogador = mantemJogador(jogador);
                                continue;
                            }else{
                                adiciona_vermelho(n_linhas, n_colunas, tab, optinicio, jogador);
                                escreveTab(n_linhas, n_colunas, tab);
                                lista_tab = guardaJogadas(n_linhas, n_colunas, &n_jogadas, tab, lista_tab);
                                break;
                            }
                        case OPT_ADD_LIN_COL:                                         //Adicionar coluna/linha
                            if(optinicio == 1 && jogador == 'B')
                                opt = selecionaLinhaouColuna();
                            else
                                opt = menu_col_lin();

                            switch(opt){
                                case OPT_ADD_COL:
                                    jogador = adicionaColuna(&n_linhas, &n_colunas, tab, jogador, lista_jogadas);
                                    escreveTab(n_linhas, n_colunas, tab);
                                    lista_tab = guardaJogadas(n_linhas, n_colunas, &n_jogadas, tab, lista_tab);
                                    break;
                                case OPT_ADD_LIN:
                                    jogador = adicionaLinha(&n_linhas, &n_colunas, tab, jogador, lista_jogadas);
                                    escreveTab(n_linhas, n_colunas, tab);
                                    lista_tab = guardaJogadas(n_linhas, n_colunas, &n_jogadas, tab, lista_tab);
                                    break;
                                case OPT_ATRAS:
                                    jogador = mantemJogador(jogador);
                            }
                            break;
                        case OPT_ADD_PEDRA:                                         //Adicionar pedra
                            if(verificaJogada(n_linhas, n_colunas, tab, 'P') == 0){
                                printf("\nNao e possivel fazer essa jogada!\n\n");
                                jogador = mantemJogador(jogador);
                                continue;
                            }else{
                                jogador = adicionaPedra(n_linhas, n_colunas, tab, jogador, lista_jogadas, optinicio);
                                escreveTab(n_linhas, n_colunas, tab);
                                lista_tab = guardaJogadas(n_linhas, n_colunas, &n_jogadas, tab, lista_tab);
                                break;
                            }
                        case OPT_VER_JOG:                                            //Ver jogadas anteriores
                            jogador = mostraJogadas(lista_tab, jogador);
                            break;
                        case OPT_GUARDAR:                                            //Guardar e sair
                            guardarJogo(lista_tab, jogador);
                            opt = 8;                                                 //para sair do menu (terminar o programa)
                            break;
                    };
                }
                while(opt != OPT_SAIR);

            break;

    for(i = 0; i < n_colunas; i++){
        free(tab[i]);                                                                //libertar os arrays de cada ponteiro
    }
    free(tab);                                                                       //libertar o array principal

    liberta_listatab(lista_tab);                                                     //libertar a lista ligada das jogadas anteriores


        }

    return 0;
}
