#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "jogo.h"

void inicializaTab(int n_lin, int n_col, char* tab[]){              //inicializa o tabuleiro vazio

    int i,j;

    for(i=0; i<n_lin; i++){
        for(j=0; j<n_col; j++){
            tab[i][j] = '_';
        }
    }
}

void liberta_listatab(ptab lista){                                  //liberta a lista ligada com as posições anteriores do tabuleiro
    ptab aux;
    while(lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

void escreveTab(int n_lin, int n_col, char* tab[]){                 //mostra o tabuleiro a cada jogada efetuada

    int i,j;

    printf("\n\n");
    for(i=0; i<n_lin; i++){
        for(j=0; j<n_col; j++){
            printf(" %c ",tab[i][j]);
        }
        putchar('\n');
    }
}

char mantemJogador(char jogador){                                   //mantem o jogador que jogou a jogada anterior
    if(jogador == 'A')
            return 'B';
        else
            return 'A';
}

int ganhaLinha(int n_lin, int n_col, char* tab[]){                  //verifica se foi efetuada uma linha com peças iguais

    int i,j;

    for(i=0; i<n_lin; i++){
        if(tab[i][0] != '_'){
            for(j=0; j<n_col-1 && tab[i][j] == tab[i][j+1]; j++);
            if(j==n_col-1)
                return 1;
        }
    }
    return 0;
}

int ganhaColuna(int n_lin, int n_col, char* tab[]){                 //verifica se foi efetuada uma coluna com peças iguais

    int i,j;

    for(j=0; j<n_col; j++){
        if(tab[0][j] != '_'){
            for(i=0; i<n_lin-1 && tab[i][j] == tab[i+1][j]; i++);
            if(i==n_lin-1)
                return 1;
        }
    }
    return 0;
}

int ganhaDiagonal(int n_lin, int n_col, char* tab[]){               //verifica se foi efetuada uma diagonal com peças iguais

    int i,j;
    char c;

    if (n_lin != n_col)
        return 0;

    //diagonal descendente

    if(tab[0][0] != '_')
        c = tab[0][0];

    for(i = 0, j = 0; i < n_lin; i++, j++){
        if (tab[i][j] == c)
            continue;
        else
            break;
    }

    if(i == n_lin)                                                  //verifica se o i é igual ao numero de linhas, se sim, devolve 1 e dá vitória
        return 1;

    //diagonal ascendente (ERRO: dá vitória independentemente das peças)

    if(tab[0][n_lin-1] != '_')
        c = tab[0][n_lin-1];
    else
        return 0;

    for(i = 0 ; i < n_lin; i++){
        for(j = n_lin-1; j < 0; j--){
            if (tab[i][j] == c)
                continue;
            else
                break;
        }
    }

    if(i == n_lin)
        return 1;
    else
        return 0;
}

int ganhaJogo(int n_lin, int n_col, char* tab[]){                   //chama as funções anteriores e vê se o jogo terminou

     if(ganhaLinha(n_lin, n_col, tab) == 1 || ganhaColuna(n_lin, n_col, tab) == 1 || ganhaDiagonal(n_lin, n_col, tab) == 1){
        return 1;
     }

     return 0;
}

void adiciona_verde(int n_lin, int n_col, char* t[], int optinicio, char jogador){          //Adiciona uma peça verde ao tabuleiro

    int lin, col, res;

    if(optinicio == 1 && jogador == 'B'){
            do{
               lin = selecionaLinhaPC(n_lin);
               col = selecionaColunaPC(n_col);
           }while(t[lin-1][col-1] != '_');
    }else{
        do{
                printf("\nLinha: ");
                fseek(stdin,0,SEEK_END);
                res = scanf(" %d", &lin);


                printf("\nColuna: ");
                fseek(stdin,0,SEEK_END);
                res = scanf(" %d", &col);

        }while(res != 1 || lin<1 || col<1 || lin>n_lin || col>n_col || t[lin-1][col-1] != '_');

    }

    t[lin-1][col-1] = 'G';

    return;
}

void adiciona_amarelo(int n_lin, int n_col, char* t[], int optinicio, char jogador){            //Adiciona uma peça amarela ao tabuleiro

    int lin, col, res;

    do{
    if(optinicio == 1 && jogador == 'B'){
            do{
               lin = selecionaLinhaPC(n_lin);
               col = selecionaColunaPC(n_col);
            }while(t[lin-1][col-1] != 'G');
    }else{
                printf("\nLinha: ");
                fseek(stdin,0,SEEK_END);
                res = scanf(" %d", &lin);

                printf("\nColuna: ");
                fseek(stdin,0,SEEK_END);
                res = scanf(" %d", &col);

    }
    }while(res != 1 || lin<1 || col<1 || lin>n_lin || col>n_col || t[lin-1][col-1] != 'G');

    t[lin-1][col-1] = 'Y';

    return;
}

void adiciona_vermelho(int n_lin, int n_col, char* t[], int optinicio, char jogador){           //Adiciona uma peça vermelha ao tabuleiro

    int lin, col, res;

    if(optinicio == 1 && jogador == 'B'){
        do{
            lin = selecionaLinhaPC(n_lin);
            col = selecionaColunaPC(n_col);
        }while(t[lin-1][col-1] != 'Y');
    }else{
        do{
                printf("\nLinha: ");
                fseek(stdin,0,SEEK_END);
                res = scanf(" %d", &lin);

                printf("\nColuna: ");
                fseek(stdin,0,SEEK_END);
                res = scanf(" %d", &col);

    }while(res != 1 || lin<1 || col<1 || lin>n_lin || col>n_col || t[lin-1][col-1] != 'Y');

    }

    t[lin-1][col-1] = 'R';

    return;
}

int verificaJogada(int n_lin, int n_col, char* t[], char c){                                    //Verifica se a jogada pedida pelo utilizador é permitida
    int i,j;

    switch(c){
    case 'G':                                   //Caso seja uma verde, verifica se tem '_' no tabuleiro
        for(i = 0; i < n_lin; i++){
            for(j = 0; j < n_col; j++){
                if(t[i][j] == '_'){
                    return 1;
                }
            }
        }
        return 0;
        break;
    case 'Y':                                   //Caso seja uma amarela, verifica se tem 'G' no tabuleiro
        for(i = 0; i < n_lin; i++){
            for(j = 0; j < n_col; j++){
                if(t[i][j] == 'G'){
                    return 1;
                }
            }
        }
        return 0;
        break;
    case 'R':                                   //Caso seja uma vermelha, verifica se tem 'Y' no tabuleiro
        for(i = 0; i < n_lin; i++){
            for(j = 0; j < n_col; j++){
                if(t[i][j] == 'Y'){
                    return 1;
                }
            }
        }
        return 0;
        break;
    case 'P':                                   //Caso seja uma pedra, verifica se tem '_' no tabuleiro
        for(i = 0; i < n_lin; i++){
            for(j = 0; j < n_col; j++){
                if(t[i][j] == '_'){
                    return 1;
                }
            }
        }
        return 0;
        break;
    }
    return 0;
}

char adicionaColuna(int *n_lin, int *n_col, char* t[], char jogador, jog *lista){               //Adiciona uma coluna ao tabuleiro (ERRO: se o tabuleiro começar com 4 colunas, preenche com lixo)

    char** aux;
    int i, j;

    //verifica se o jogador ainda tem jogadas disponíveis

    for(j=0; jogador != lista[j].id; j++);

    if(lista[j].jog_add == 0){
        printf("\nNao pode efetuar mais esta jogada!\n");
        return mantemJogador(jogador);
    }

    //alocação de memoria

    aux = (char**) realloc(t, sizeof(char*) * (*n_col+1));                                      //Realocação do array principal

    if(aux == NULL){
        printf("\nErro ao alocar memoria!\n");
        return mantemJogador(jogador);
    }

    t = aux;
    t[*n_col] = (char *) malloc(sizeof(char) * (*n_lin+1));                                       //alocação da nova coluna

    if(t[*n_col] == NULL){
        printf("\nErro na alocacao de memoria\n");
        return mantemJogador(jogador);
    }

    for(i = 0; i <= (*n_lin); i++){
        t[i][(*n_col)] = '_';
    }

    (*n_col)++;

    (lista[j].jog_add)--;

    return jogador;
}

char adicionaLinha(int *n_lin, int *n_col, char* t[], char jogador, jog *lista){                //Adiciona uma linha ao tabuleiro

    int i, j;
    char** aux = {NULL};

    //verifica se o jogador ainda tem jogadas disponíveis

    for(j=0; jogador != lista[j].id; j++);

    if(lista[j].jog_add == 0){
        printf("\nNao pode efetuar mais esta jogada!\n");
        return mantemJogador(jogador);
    }

    //alocação de memoria

    for(i = 0; i < *n_col-1; i++){
        aux[i] = (char *) realloc(t[i], sizeof(char) * (*n_lin+1));

        if(aux[i] == NULL){
            printf("\nErro ao alocar memoria!\n");
            return mantemJogador(jogador);
        }
    }

    t = aux;
    for(i = 0; i < *n_col-1; i++){
        t[*n_lin][i] = '_';
    }

    (*n_lin)++;
    (lista[j].jog_add)--;

    return jogador;
}

char adicionaPedra(int n_lin, int n_col, char* t[], char jogador, jog *lista, int optinicio){           //Adiciona uma pedra ao tabuleiro

    int lin, col, j;


    //verifica se o jogador ainda tem jogadas disponíveis

    for(j=0; jogador != lista[j].id; j++);

    if(lista[j].jog_pedra == 0){
        printf("\nNao pode efetuar mais esta jogada!\n");
        return mantemJogador(jogador);
    }

    if(optinicio == 1 && jogador == 'B'){
            do{
               lin = selecionaLinhaPC(n_lin);
               col = selecionaColunaPC(n_col);
           }while(t[lin-1][col-1] != '_');
    }else{
        do{
                printf("\nLinha: ");
                scanf(" %d", &lin);

                printf("\nColuna: ");
                scanf(" %d", &col);
    }while(lin<1 || col<1 || lin>n_lin || col>n_col || t[lin-1][col-1] != '_');

    }

    t[lin-1][col-1] = 'P';

    (lista[j].jog_pedra)--;

    return jogador;
}

ptab guardaJogadas(int n_lin, int n_col, int *jogadas, char* t[], ptab lista){              //guarda as sucuessivas posições do tabuleiro na lista ligada

    ptab novo, aux1;
    char** aux;
    int i = 0, j = 0;

    novo = malloc(sizeof(tabuleiro));
    if(novo == NULL){
        printf("\nErro na alocacao de memoria!\n");
        return lista;
    }

    aux = malloc(sizeof(char*) * (n_col));

    if(aux == NULL){
        printf("\nErro ao alocar memoria!\n");
        return lista;
    }

    novo->tab = aux;
    for(i = 0; i < n_col; i++){
       novo->tab[i] = malloc(sizeof(char) * (n_lin-1));
    }

    for(i = 0; i < n_lin; i++){
        for(j = 0; j < n_col; j++){
            novo->tab[i][j] = t[i][j];
        }
    }

    (*jogadas)++;

    novo->linhas = n_lin;
    novo->colunas = n_col;
    novo->n_jogadas = *jogadas;

    if(lista == NULL)       // Lista vazia
        lista = novo;
    else{
        aux1 = lista;
        while(aux1->prox != NULL){
            aux1 = aux1->prox;
        }
        aux1->prox = novo;
    }
    novo->prox = NULL;

    return lista;
}

char mostraJogadas(ptab lista, char jogador){                           //mostra as posições anteriores do tabuleiro, quando pedidas pelo jogador

    int n, n_lin, n_col, jogadas_efetuadas;
    ptab aux;

    if(lista == NULL){
        printf("\nNao existem jogadas!\n");
        return mantemJogador(jogador);
    }

    aux = lista;
    while(aux->prox != NULL){
        aux = aux->prox;                               //ir até à ultima jogada
    }

    do{
        printf("Indique o numero de jogadas que deseja ver: ");
        scanf("%d",&n);
    }while(n<=0 || n>aux->n_jogadas);

    jogadas_efetuadas = aux->n_jogadas;               //nº de jogadas efetuadas ate ao momento

    aux = lista;
    while(aux->n_jogadas <= jogadas_efetuadas-n){     //ir para numero de jogadas efetuadas ate ao momento subtraindo o numero que o utilizador pediu (mostrar todos a partir daí até ao final)
        aux = aux->prox;
    }

    while(aux != NULL){         // aux != NULL porque senão não mostrava o ultimo nó
        n_lin = lista->linhas;
        n_col = lista->colunas;
        escreveTab(n_lin, n_col, aux->tab);
        putchar('\n');
        aux = aux->prox;
    }

    return mantemJogador(jogador);
}

void guardarJogo(ptab lista, char jogador){                         //guarda o jogo num ficheiro binário (opção 7 do menu)

    FILE *f = NULL;
//    int i, j;

    f = fopen("jogo.bin", "wb");
    if(f == NULL){
        printf("\nErro no acesso ao ficheiro\n");
        return;
    }

    while(lista != NULL){

        fwrite(&lista->n_jogadas, sizeof(int), 1, f);
        fwrite(&lista->linhas, sizeof(int), 1, f);
        fwrite(&lista->colunas, sizeof(int), 1, f);
        fwrite(lista->tab, sizeof(lista->colunas * lista->linhas), 1, f);
        fwrite(&jogador, sizeof(char), 1, f);

//        fprintf(f, "%d\t%d\t%d\t%c\n", lista->n_jogadas, lista->linhas, lista->colunas, jogador);
//        for(i = 0; i < lista->linhas; i++){
//            for(j = 0; j < lista->colunas; j++){
//                fputc(lista->tab[i][j], f);
//                fputc(' ', f);
//            }
//            fputc('\n', f);
//        }
        lista = lista->prox;
    }

    printf("\nGravado com sucesso!\n");

    fclose(f);
}

ptab retomaJogo(ptab lista, char *jogador){                        //vai buscar ao ficheiro binario as informações para retomar o jogo  (não funciona)

    FILE *f = NULL;
    char opt;
    int jogadas, i /*,linhas, colunas*/;
//    char **tab;
    ptab novo = NULL, aux = NULL;
//    int j;

    f = fopen("jogo.bin", "rb");

    if(f == NULL){
        return NULL;
    }

    do{
        printf("\nPretende retomar o jogo anterior?(sim -> s / nao -> n): ");
        scanf("%c", &opt);

        if(opt == 'n')
            return NULL;
        else
            break;
    }while(opt != 's' || opt != 'n');

    while(fread(&jogadas, sizeof(int), 1, f) == 1){
//      while(fscanf(f, "%d", &jogadas) == 1){
//
//        novo = malloc(sizeof(tabuleiro));
//        if(novo == NULL){
//            printf("\nNão foi possivel retomar o jogo\n\n");
//            liberta_listatab(lista);
//            return lista;
//        }
//                fscanf(f, "%d %d %c", &linhas, &colunas, jogador);
//
//            novo->linhas = linhas;
//            novo->colunas = colunas;
//            novo->n_jogadas = jogadas;
//
//            novo->tab = malloc(sizeof(char*) * novo->linhas);
//
//            if(novo->tab == NULL){
//                printf("\nErro na alocacao de memoria!\n");
//                return 0;
//            }
//            for(i = 0; i < novo->colunas; i++){
//                novo->tab[i] = malloc(sizeof(char) * novo->colunas);
//            }
//
//            for(i = 0; i < novo->linhas; i++){
//                for(j = 0; j < novo->colunas; j++){
//                    fscanf(f, "%c", novo->tab[i][j]);
//                }
//            }

        fread(&novo->linhas, sizeof(int), 1, f);
        fread(&novo->colunas, sizeof(int), 1, f);
        novo->tab = malloc(sizeof(char*) * novo->linhas);

        if(novo->tab == NULL){
            printf("\nErro na alocacao de memoria!\n");
            return 0;
        }
        for(i = 0; i < novo->colunas; i++){
            novo->tab[i] = malloc(sizeof(char) * novo->colunas);
        }
        fread(novo->tab, sizeof(novo->colunas * novo->linhas), 1, f);
        fread(&jogador, sizeof(char), 1, f);
        novo->n_jogadas = jogadas;

        if(lista == NULL)       // Lista vazia
            lista = novo;
        else{
            aux = lista;
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
        }

        novo->prox = NULL;
        aux = aux->prox;
    }

    printf("\nJogo retomado com sucesso!\n");
    fclose(f);

    return lista;
}

void inicializaTabRetoma(ptab lista, char* tab[]){              //inicializa o tabuleiro com as peças que estavam na ultima jogada do ultimo save

    int i, j;

    while(lista->prox != NULL){
        lista = lista->prox;
    }

    for(i = 0; i < lista->linhas; i++){
        for(j = 0; j < lista->colunas; j++){
            tab[i][j] = lista->tab[i][j];
        }
    }

    return;
}

void guardaFinalJogo(ptab lista, char *nomeF){                  //guarda num ficheiro de texto todas as posições do tabuleiro (só chamada quando houver um vencedor)

    FILE* f = NULL;
    ptab aux = NULL;
    int i, j;

    f = fopen(nomeF, "w");
    if(f == NULL){
        printf("\nErro no acesso ao ficheiro\n");
        return;
    }

    aux = lista;
    while(aux != NULL){
        for(i = 0; i < aux->linhas; i++){
            for(j = 0; j < aux->colunas; j++){
                fputc(aux->tab[i][j], f);
                fputc(' ', f);
            }
            fputc('\n', f);
        }
        aux = aux->prox;
        fputc('\n', f);
    }

    fclose(f);
    return;
}

int selecionaJogadaPC(){                                                            //seleciona uma jogada para o PC (modo 1 jogador)
    int opt1 = probEvento(0.6), opt2 = probEvento(0.35), opt3 = probEvento(0.35), opt4 = probEvento(0.10);

        if(opt1 == 1)
            return 1;
        else if(opt2 == 1)
            return 2;
        else if(opt3 == 1)
            return 3;
        else if(opt4 == 1)
            return 4;
        else
            return 5;

    return 0;
}

int selecionaLinhaPC(int n_linhas){                                                 //seleciona uma linha para a peça na jogada do PC (modo 1 jogador)
    int valor = 10; // =10 para nunca ser menor que n_linhas na primeira iteração

     while(valor > n_linhas)
        valor = intUniformRnd(1,10);

     return valor;
}

int selecionaColunaPC(int n_colunas){                                               //seleciona uma coluna para a peça na jogada do PC (modo 1 jogador)
    int valor = 10; // =10 para nunca ser menor que n_linhas na primeira iteração

     while(valor > n_colunas)
        valor = intUniformRnd(1,10);

     return valor;
}

int selecionaLinhaouColuna(){
    int opt1 = probEvento(0.5);

    if(opt1 == 1)
        return 1;
    else
        return 0;

}
