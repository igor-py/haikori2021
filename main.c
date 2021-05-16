#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char *nome;
    int colunas;
    int linhas;
    int saidas[2][2];
    int espacos[2][2]; // eh um par de coordenadas
    char matriz[1000][1000];
} tabuleiro;

tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual);
void printa_tabuleiro(tabuleiro t, int numero_tabuleiro);
tabuleiro coloca_coordenadas(tabuleiro t);

int main(int argc, char const *argv[])
{
    /* Primeiramente precisamos ler o arquivo de texto */
    FILE *fp;
    char *line = NULL;
    char nome_tabuleiros[2][50];
    size_t len = 0;
    ssize_t read;
    int contador = 1;
    int linha_atual = 0;

    tabuleiro t1 = {"", 0, 0, {{}, {}}, {}};
    tabuleiro t2 = {"", 0, 0, {{}, {}}, {}};

    // Quando o usuario roda apenas o  main
    if (argc == 1)
    {
        fp = fopen("haikori.txt", "r");
        if (fp == NULL)
        {
            printf("O arquivo nao existe!!!\n");
            return -1;
        }
        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (isupper(line[0]))
            {
                // Coleta o nome do tabuleiro no momento
                strcpy(nome_tabuleiros[contador - 1], line);
            }
            else if (contador == 1)
            {
                t1 = incrementa_tabuleiro(t1, line, linha_atual);
                if (t1.colunas == 0)
                {
                    t1.colunas = read - 1;
                }
                linha_atual++;
            }

            // Para o proximo tabuleiro
            if (line[0] == '\n')
            {
                if (t1.linhas == 0)
                {
                    t1.linhas = linha_atual - 1;
                    linha_atual = 0;
                }

                // Para saber em qual configuracao estamos
                if (contador == 1)
                {
                    // montar configuracao 1
                    if (t1.nome[0] == '\0')
                    {
                        ;
                    }
                }

                contador++;
            }
            else if (contador == 2 && !isupper(line[0]))
            {
                // montar configuracao 2
                t2 = incrementa_tabuleiro(t2, line, linha_atual);
                if (t2.colunas == 0 && line[0] == '*')
                {
                    t2.colunas = read - 1;
                }
                linha_atual++;
            }
        }

        if (t2.linhas == 0)
        {
            t2.linhas = linha_atual;
        }

        t1.nome = nome_tabuleiros[0];
        t2.nome = nome_tabuleiros[1];
        t1 = coloca_coordenadas(t1);
        t2 = coloca_coordenadas(t2);
        printa_tabuleiro(t1, 1);

        printa_tabuleiro(t2, 2);
    }

    // Depois lembrar de copiar o feito pro de cima para o abaixo

    // Quando o usuario roda o main -f nomeArquivo.txt
    else if (argc == 3)
    {
        printf("teste: %s\n", *(argv + 2));
        fp = fopen(*(argv + 2), "r");
        if (fp == NULL)
        {
            printf("O arquivo nao existe!!!\n");
            return -1;
        }
        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (isupper(line[0]))
            {
                // Coleta o nome do tabuleiro no momento
                strcpy(nome_tabuleiros[contador - 1], line);
            }
            else if (contador == 1)
            {
                t1 = incrementa_tabuleiro(t1, line, linha_atual);
                if (t1.colunas == 0)
                {
                    t1.colunas = read - 1;
                }
                linha_atual++;
            }

            // Para o proximo tabuleiro
            if (line[0] == '\n')
            {
                if (t1.linhas == 0)
                {
                    t1.linhas = linha_atual - 1;
                    linha_atual = 0;
                }

                // Para saber em qual configuracao estamos
                if (contador == 1)
                {
                    // montar configuracao 1
                    if (t1.nome[0] == '\0')
                    {
                        ;
                    }
                }

                contador++;
            }
            else if (contador == 2 && !isupper(line[0]))
            {
                // montar configuracao 2
                t2 = incrementa_tabuleiro(t2, line, linha_atual);
                if (t2.colunas == 0 && line[0] == '*')
                {
                    t2.colunas = read - 1;
                }
                linha_atual++;
            }
        }

        if (t2.linhas == 0)
        {
            t2.linhas = linha_atual;
        }

        t1.nome = nome_tabuleiros[0];
        t2.nome = nome_tabuleiros[1];

        printa_tabuleiro(t1, 1);

        printa_tabuleiro(t2, 2);
    }

    // Argumentos desconhecidos
    else
    {
        printf("Voce digitou um numero de argumentos invalidos!!!\n");
        return -1;
    }

    fclose(fp);
    return 0;
}

tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual)
{
    for (int i = 0; linha[i] != '\n'; i++)
    {
        t.matriz[linha_atual + 1][i + 1] = linha[i];
    }
    return t;
}

void printa_tabuleiro(tabuleiro t, int numero_tabuleiro)
{
    int j, k;
    char vazio = ' ';

    printf("\n");
    if (numero_tabuleiro == 1)
    {
        printf("   1\n");
    }
    else if (numero_tabuleiro == 2)
    {
        printf("   2\n");
    }
    printf("   %s\n", t.nome);

    // printa as possiveis posicoes do tabuleiro

    j = 0;

    while (j < t.linhas + 1)
    {
        for (k = 0; k < t.colunas + 1; k++)
        {
            if (t.matriz[j][k] == '\0')
            {
                printf("%3c", vazio);
            }
            else
            {
                printf("%3c", t.matriz[j][k]);
            }
        }
        j++;
        printf("\n");
    }
    printf("\n");
}

tabuleiro coloca_coordenadas(tabuleiro t)
{
    int num = 1;

    // Colocando coordenadas das colunas possiveis
    for (int col = 2; col < t.colunas; col++)
    {
        t.matriz[0][col] = num + '0';
        num++;
    }

    num = 1;

    // Colocando coordenadas das linhas possiveis
    for (int lin = 2; lin < t.linhas; lin++)
    {
        t.matriz[lin][0] = num + '0';
        num++;
    }

    return t;
}
