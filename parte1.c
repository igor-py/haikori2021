#include <stdio.h>
#include <stdlib.h>

#define CHAR_POSSIVEIS "abcdefghijklmD"

void monta_config(int n, int m, char tabuleiro[m + 2][n + 2], int config, int movimento);
void printa_tabuleiro(int n, int m, char tabuleiro[m + 2][n + 2]);
int seleciona_config(char const *conf);
void preenche_corpo(int n, int m, char tabuleiro[m + 2][n + 2], int config, int i);
int verifica_movimento(int linha, int coluna, char mov, int m, int n, char tabuleiro[m + 2][n + 2]);
int eh_char_possivel(char c);

int main(int argc, char const *argv[])
{
    int m, n, config, linha, coluna, tem_erro;
    char mov;
    char temp;

    if (argc == 1)
    {
        config = 1;
    }
    else if (argc == 2)
    {
        config = seleciona_config(*(argv + 1));
    }
    else if (argc == 6)
    {
        config = seleciona_config(*(argv + 1));
        temp = argv[2][1];
        if (temp == 'm')
        {
            linha = atoi(argv[3]);
            coluna = atoi(argv[4]);
            mov = argv[5][0];
        }
        else
        {
            printf("Esse parametro nao existe!!!\n");
            config = -1;
        }
    }
    else
    {
        printf("Voce passou um numero de argumentos de coluna errado!!!\n");
    }

    if (config != -1)
    {
        if (config == 1)
        {
            // n linha m
            m = 5;
            n = 4;
        }
        else if (config == 2)
        {
            // n linha m
            m = 5;
            n = 6;
        }

        char tabuleiro[m + 2][n + 2];
        monta_config(n, m, tabuleiro, config, 3);
        printa_tabuleiro(n, m, tabuleiro);
        tem_erro = verifica_movimento(linha, coluna, mov, m, n, tabuleiro);
        if (tem_erro == 0)
        {
            printa_tabuleiro(n, m, tabuleiro);
        }
    }
    return 0;
}

int seleciona_config(char const *conf)
{
    int config = conf[2] - '0';

    if (config == 1 || config == 2)
    {
        return config;
    }
    printf("Essa configuracao nao existe\n");
    return -1;
}

void monta_config(int n, int m, char tabuleiro[m + 2][n + 2], int config, int movimento)
{
    int i;

    // Primeira e ultima coluna sao sempre com asteristicos (Tomando cuidado apenas com a saida)
    for (i = 0; i < n + 2; i++)
    {
        tabuleiro[0][i] = '*';
        tabuleiro[m + 1][i] = '*';

        // Preenchendo o corpo do tabuleiro
        preenche_corpo(n, m, tabuleiro, config, i);
    }
}

void printa_tabuleiro(int n, int m, char tabuleiro[m + 2][n + 2])
{
    int j, k;

    printf("\n");

    j = 0;
    while (j < m + 2)
    {
        for (k = 0; k < n + 2; k++)
        {
            printf("%3c", tabuleiro[j][k]);
        }
        j++;
        printf("\n");
    }
    printf("\n");
}

void preenche_corpo(int n, int m, char tabuleiro[m + 2][n + 2], int config, int i)
{
    int k = 1;

    while (k <= m + 1)
    {
        // Interagindo com a configuracao escolhida
        if (config == 1)
        {
            if ((k == 1 || k == 2) && (i == 2 || i == 3))
            {
                tabuleiro[k++][i] = 'D';
                continue;
            }

            if ((k == 5 || k == 6) && (i == 2 || i == 3))
            {
                tabuleiro[k++][i] = ' ';
                continue;
            }
        }
        else if (config == 2)
        {
            if ((k == 1 || k == 2) && (i == 1 || i == 2))
            {
                tabuleiro[k++][i] = 'D';
                continue;
            }

            if (((k == 1 || k == 2) && (i == 3)) || ((k == 4 || k == 5) && i == 7))
            {
                tabuleiro[k++][i] = ' ';
                continue;
            }
        }

        if (i == 0)
        {
            tabuleiro[k++][i] = '*';
        }
        else if (i == n + 1)
        {
            tabuleiro[k++][i] = '*';
        }
        // Trocar essa parte quando estiver preenchendo com as letras diferentes
        else
        {
            if (config == 1)
            {
                if ((k == 1 || k == 2) && i == 1)
                {
                    tabuleiro[k++][i] = 'a';
                    continue;
                }

                if ((k == 3 || k == 4) && i == 1)
                {
                    tabuleiro[k++][i] = 'c';
                    continue;
                }

                if ((k == 3) && (i == 2 || i == 3))
                {
                    tabuleiro[k++][i] = 'd';
                    continue;
                }

                if ((k == 3 || k == 4) && i == 4)
                {
                    tabuleiro[k++][i] = 'e';
                    continue;
                }

                if ((k == 1 || k == 2) && i == 4)
                {
                    tabuleiro[k++][i] = 'b';
                    continue;
                }

                if ((k == 4) && i == 2)
                {
                    tabuleiro[k++][i] = 'g';
                    continue;
                }

                if ((k == 4) && i == 3)
                {
                    tabuleiro[k++][i] = 'h';
                    continue;
                }

                if ((k == 5) && i == 4)
                {
                    tabuleiro[k++][i] = 'i';
                    continue;
                }

                if ((k == 5) && i == 1)
                {
                    tabuleiro[k++][i] = 'f';
                    continue;
                }
            }

            if (config == 2)
            {
                if (k == 1)
                {
                    if (i == 4 || i == 5)
                    {
                        tabuleiro[k++][i] = 'a';
                        continue;
                    }

                    if (i == 6)
                    {
                        tabuleiro[k++][i] = 'b';
                        continue;
                    }
                }
                if (k == 2)
                {
                    if (i == 4)
                    {
                        tabuleiro[k++][i] = 'a';
                        continue;
                    }

                    if (i == 5)
                    {
                        tabuleiro[k++][i] = 'c';
                        continue;
                    }

                    if (i == 6)
                    {
                        tabuleiro[k++][i] = 'd';
                        continue;
                    }
                }
                if (k == 3)
                {
                    if (i == 1 || i == 2)
                    {
                        tabuleiro[k++][i] = 'e';
                        continue;
                    }

                    if (i == 3)
                    {
                        tabuleiro[k++][i] = 'f';
                        continue;
                    }

                    if (i == 4)
                    {
                        tabuleiro[k++][i] = 'g';
                        continue;
                    }

                    if (i == 5 || i == 6)
                    {
                        tabuleiro[k++][i] = 'd';
                        continue;
                    }
                }
                if (k == 4)
                {
                    if (i == 1 || i == 2)
                    {
                        tabuleiro[k++][i] = 'k';
                        continue;
                    }

                    if (i == 3)
                    {
                        tabuleiro[k++][i] = 'i';
                        continue;
                    }

                    if (i == 4)
                    {
                        tabuleiro[k++][i] = 'j';
                        continue;
                    }

                    if (i == 5)
                    {
                        tabuleiro[k++][i] = 'k';
                        continue;
                    }

                    if (i == 6)
                    {
                        tabuleiro[k++][i] = 'l';
                        continue;
                    }
                }
                if (k == 5)
                {
                    if (i == 1)
                    {
                        tabuleiro[k++][i] = 'h';
                        continue;
                    }

                    if (i == 2 || i == 3)
                    {
                        tabuleiro[k++][i] = 'i';
                        continue;
                    }

                    if (i == 4)
                    {
                        tabuleiro[k++][i] = 'm';
                        continue;
                    }

                    if (i == 5)
                    {
                        tabuleiro[k++][i] = 'k';
                        continue;
                    }

                    if (i == 6)
                    {
                        tabuleiro[k++][i] = 'l';
                        continue;
                    }
                }
            }

            k++;
        }
    }
}

// Retorna 1 quando tiver algum tipo de erro
int verifica_movimento(int linha, int coluna, char mov, int m, int n, char tabuleiro[m + 2][n + 2])
{
    char char_atual;

    char_atual = tabuleiro[linha][coluna];

    // "-m 1 1 D"
    if (char_atual == '*' || char_atual == ' ')
    {
        printf("Voce nao pode mover * nem espacos\n");
        return 1;
    }

    if (eh_char_possivel(char_atual) == 0)
    {
        printf("Essa peca nao eh valida\n");
        return 1;
    }
    else
    {
        if (mov == 'D')
        {

            while ((char_atual == tabuleiro[linha][coluna++]) && coluna < n + 2)
            {
                if (tabuleiro[linha][coluna] == ' ')
                {
                    tabuleiro[linha][coluna] = char_atual;
                    tabuleiro[linha][coluna - 1] = ' ';

                    if (tabuleiro[linha - 1][coluna - 1] == char_atual)
                    {
                        verifica_movimento(linha - 1, coluna - 1, 'D', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha + 1][coluna - 1] == char_atual)
                    {
                        verifica_movimento(linha + 1, coluna - 1, 'D', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha][coluna - 2] == char_atual)
                    {
                        verifica_movimento(linha, coluna - 2, 'D', m, n, tabuleiro);
                    }

                    break;
                }
                else if (tabuleiro[linha][coluna] != char_atual)
                {
                    printf("Impossivel movimentar peca (%c) para a Direita\n", char_atual);
                    return 1;
                    break;
                }
            }
        }
        else if (mov == 'E')
        {
            while ((char_atual == tabuleiro[linha][coluna--]) && coluna >= 0)
            {
                if (tabuleiro[linha][coluna] == ' ')
                {
                    tabuleiro[linha][coluna] = char_atual;
                    tabuleiro[linha][coluna + 1] = ' ';

                    if (tabuleiro[linha][coluna + 2] == char_atual)
                    {
                        verifica_movimento(linha, coluna + 2, 'E', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha + 1][coluna + 1] == char_atual)
                    {
                        verifica_movimento(linha + 1, coluna + 1, 'E', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha - 1][coluna + 1] == char_atual)
                    {
                        verifica_movimento(linha - 1, coluna + 1, 'E', m, n, tabuleiro);
                    }

                    break;
                }
                else if (tabuleiro[linha][coluna] != char_atual)
                {
                    printf("Impossivel movimentar peca (%c) para a Esquerda\n", char_atual);
                    return 1;
                    break;
                }
            }
        }
        else if (mov == 'B')
        {
            while ((char_atual == tabuleiro[linha++][coluna]) && linha < m + 2)
            {
                if (tabuleiro[linha][coluna] == ' ')
                {
                    tabuleiro[linha][coluna] = char_atual;
                    tabuleiro[linha - 1][coluna] = ' ';

                    if (tabuleiro[linha - 1][coluna + 1] == char_atual)
                    {
                        verifica_movimento(linha - 1, coluna + 1, 'B', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha - 1][coluna - 1] == char_atual)
                    {
                        verifica_movimento(linha - 1, coluna - 1, 'B', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha - 2][coluna] == char_atual)
                    {
                        verifica_movimento(linha - 2, coluna, 'B', m, n, tabuleiro);
                    }

                    break;
                }
                else if (tabuleiro[linha][coluna] != char_atual)
                {
                    printf("Impossivel movimentar peca (%c) para Baixo\n", char_atual);
                    return 1;
                    break;
                }
            }
        }
        else if (mov == 'C')
        {
            while ((char_atual == tabuleiro[linha--][coluna]) && linha >= 0)
            {
                if (tabuleiro[linha][coluna] == ' ')
                {
                    tabuleiro[linha][coluna] = char_atual;
                    tabuleiro[linha + 1][coluna] = ' ';

                    if (tabuleiro[linha + 1][coluna + 1] == char_atual)
                    {
                        verifica_movimento(linha + 1, coluna + 1, 'C', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha + 2][coluna] == char_atual)
                    {
                        verifica_movimento(linha + 2, coluna, 'C', m, n, tabuleiro);
                    }
                    if (tabuleiro[linha + 1][coluna - 1] == char_atual)
                    {
                        verifica_movimento(linha + 1, coluna - 1, 'C', m, n, tabuleiro);
                    }

                    break;
                }
                else if (tabuleiro[linha][coluna] != char_atual)
                {
                    printf("Impossivel movimentar peca (%c) para Cima\n", char_atual);
                    return 1;
                    break;
                }
            }
        }
        else
        {
            printf("Esse movimento nao existe!!!\n");
            return 1;
        }
        return 0;
    }
}

int eh_char_possivel(char c)
{
    int i = 0;

    while (CHAR_POSSIVEIS[i] != '\0')
    {
        if (CHAR_POSSIVEIS[i++] == c)
        {
            return 1;
        }
    }
    return 0;
}
