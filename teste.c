#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void modo_interativo();
void modo_interativo2();
int verifica_sim();

int main(int argc, char const *argv[])
{

    modo_interativo2();

    return 0;
}

void modo_interativo()
{
    int c;
    int last_c;
    char escolha[1];
    char config[2];
    int i = 0;
    int continua = 1;

    while ((c = getchar()) != 'n' && c != EOF)
    {
        printf("c: %c\n", c);
        printf("c2: %c\n", last_c);

        if (c == 'l')
        {
            // Chamar a listagem dos tabuleiros
            ;
        }

        if (c == 'c')
        {

            if (fgets(escolha, 1, stdin) != NULL)
            {
                printf("escolha: %s\n", escolha);
            }
        }

        if (last_c == 'c' && c == ' ' && continua)
        {
            config[0] = 'c';
        }

        last_c = c;
    }
}

void modo_interativo2()
{
    char escolha[60];

    printf("----Modo Interativo----\n\n");

    while (fgets(escolha, 60, stdin) != NULL)
    {
        printf("Escolha: %s\n", escolha);

        if (escolha[0] == 'l')
        {
            printf("Listar todas as configuracoes!!!\n");
        }

        if (escolha[0] == 'c')
        {

            if (verifica_sim() && escolha[1] == ' ' && isdigit(escolha[2]))
            {
                printf("Usar a configuracao %c\n", escolha[2]);
            }
            else
            {
                printf("Essa configuracao nao existe ou digitou numero de parametros invalido!!!\n");
            }
        }
    }
}

int verifica_sim()
{
    char sim[4];
    printf("Voce realmente quer fazer isso ??\n");
    printf("Pois vai perder tudo feito na configuracao anterior!!!\nDigite (s) para sim e (n) para nao\n");

    while (fgets(sim, 4, stdin) != NULL)
    {
        if (sim[0] == 's')
        {
            return 1;
        }
        else
        {
            break;
        }
    }
    return 0;
}