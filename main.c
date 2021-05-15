#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    /* Primeiramente precisamos ler o arquivo de texto */
    FILE *fp;
    char *line = NULL;
    char *nome_tabuleiro;
    size_t len = 0;
    ssize_t read;
    int contador = 1;

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
                nome_tabuleiro = line;
            }
            printf("%s\n", line);
            // Para o proximo tabuleiro
            if (line[0] == '\n')
            {
                printf("Linha vazia!!!\n");
                // Para saber em qual configuracao estamos
                if (contador == 1)
                {
                    // montar configuracao 1
                    ;
                }

                contador++;
            }
            else if (contador == 2)
            {
                // montar configuracao 2
                ;
            }
        }
    }
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
            printf("Retrieved line of length %zu:\n", read);
            printf("%s\n", line);
            if (strcmp(line, "") == 0)
            {
                printf("Linha vazia!!!\n");
            }
        }
    }
    else
    {
        printf("Voce digitou um numero de argumentos invalidos!!!\n");
        return -1;
    }

    fclose(fp);
    return 0;
}
