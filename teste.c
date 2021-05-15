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
    struct peca *pecas;
    char matriz[1000][1000];
} tabuleiro;

peca monta_peca(char nome, int tamanho, int *col, int *lin);

int main(int argc, char const *argv[])
{

    int col[3] = {1, 2, 3};
    int lin[3] = {1, 2, 3};
    peca a = monta_peca('a', 3, col, lin);
    printf("%d\n", a.colunas[0]);

    return 0;
}

peca monta_peca(char nome, int tamanho, int *col, int *lin)
{
    peca p = {nome, tamanho, (int *)malloc(tamanho * sizeof(int)), (int *)malloc(tamanho * sizeof(int))};
    for (int i = 0; i < tamanho; i++)
    {
        p.colunas[i] = col[i];
        p.linhas[i] = lin[i];
    }
    return p;
}

tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual)
{
    for (int i = 0; linha[i] != '\n'; i++)
    {
    }
}
