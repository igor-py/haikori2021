#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char nome; // 'a'
    int tamanho;
    int *colunas;
    int *linhas; // tamanho -1
} peca;

typedef struct
{
    char *nome;
    int colunas;
    int linhas;
    int saidas[2][2];
    //struct peca *pecas;
    char matriz[1000][1000];
} tabuleiro;

// peca monta_peca(char nome, int tamanho, int *col, int *lin);
tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual);

int main(int argc, char const *argv[])
{

    // int col[3] = {1, 2, 3};
    // int lin[3] = {1, 2, 3};
    // peca a = monta_peca('a', 3, col, lin);

    tabuleiro t = {"Teste", 3, 3, {{1, 2}, {1, 2}}, {}};
    tabuleiro t1 = incrementa_tabuleiro(t, "***\n", 0);

    for (int j = 0; j < 3; j++)
    {
        printf("%c\n", t1.matriz[0][j]);
    }

    return 0;
}

// peca monta_peca(char nome, int tamanho, int *col, int *lin)
// {
//     peca p = {nome, tamanho, (int *)malloc(tamanho * sizeof(int)), (int *)malloc(tamanho * sizeof(int))};
//     for (int i = 0; i < tamanho; i++)
//     {
//         p.colunas[i] = col[i];
//         p.linhas[i] = lin[i];
//     }
//     return p;
// }

tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual)
{
    for (int i = 0; linha[i] != '\n'; i++)
    {
        t.matriz[linha_atual][i] = linha[i];
    }
    return t;
}

// peca *monta_todas_as_pecas(char *linha, int tamanho, int coluna_atual)
// {
//     char atual, anterior;
//     peca pecas[tamanho];
//     peca p = {malloc(sizeof(char)), 0, (int *)malloc(tamanho * sizeof(int)), (int *)malloc(tamanho * sizeof(int))};
//     int j = 0;

//     atual = linha[0];
//     anterior = atual;
//     for (int i = 0; linha[i] != '\n'; i++)
//     {
//         if (atual == anterior)
//         {
//             p.nome = linha[i];
//             p.tamanho++;
//             p.colunas[j] = coluna_atual;

//         }
//     }
// }
