#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#define MAX_ADD_LINCOL 2
#define MAX_ADD_PEDRA 1
#define TAM 50

typedef struct jogador jog;
struct jogador{

    char id;            //id do jogador (A ou B)
    int jog_add;        //n� de vezes que efetuou adi��o de linhas ou colunas
    int jog_pedra;      //n� de vezes que efetuou adi��o de uma pedra
};

typedef struct tabuleiro tabuleiro, *ptab;
struct tabuleiro{

    char **tab;         //array de ponteiros para o tabuleiro
    int linhas;         //inteiro para o n� de linhas
    int colunas;        //inteiro para o n� de colunas
    int n_jogadas;      //inteiro para o n� de jogadas feitas at� ao momento
    ptab prox;          //ponteiro para o pr�ximo elemento
};

void inicializaTab(int n_lin, int n_col,char* tab[]);

void escreveTab(int n_lin, int n_col,char* tab[]);

char mantemJogador(char jogador);

int ganhaLinha(int n_lin, int n_col, char* tab[]);

int ganhaColuna(int n_lin, int n_col, char* tab[]);

int ganhaDiagonal(int n_lin, int n_col, char* tab[]);

int ganhaJogo(int n_lin, int n_col, char* tab[]);

void adiciona_verde(int n_lin, int n_col, char* t[], int optinicio, char jogador);

void adiciona_amarelo(int n_lin, int n_col, char* t[], int optinicio, char jogador);

void adiciona_vermelho(int n_lin, int n_col, char* t[], int optinicio, char jogador);

int verificaJogada(int n_lin, int n_col, char* t[], char c);

char adicionaColuna(int *n_lin, int *n_col, char* t[], char jogador, jog *lista);

char adicionaLinha(int *n_lin, int *n_col, char* t[], char jogador, jog *lista);

char adicionaPedra(int n_lin, int n_col, char* t[], char jogador, jog *lista, int optinicio);

ptab guardaJogadas(int n_lin, int n_col, int *jogadas, char* t[], ptab lista);

char mostraJogadas(ptab lista, char jogador);

void liberta_listatab(ptab lista);

void guardarJogo(ptab lista, char jogador);

ptab retomaJogo(ptab lista, char *jogador);

void inicializaTabRetoma(ptab lista, char* tab[]);

void guardaFinalJogo(ptab lista, char *nomeF);

int selecionaJogadaPC();

int selecionaLinhaPC(int n_linhas);

int selecionaColunaPC(int n_colunas);

int selecionaLinhaouColuna();



#endif // JOGO_H_INCLUDED
