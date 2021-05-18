#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHAR_POSSIVEIS "abcdefghijklmD"
typedef struct
{
    char *nome;
    int colunas;
    int linhas;
    int saidas[2][2];  // eh um par de coordenadas da onde se encontra as saidas [[x1, y1], [x2, y2]]
    int espacos[2][2]; // eh um par de coordenadas da onde se encontra o espaco vazio
    char matriz[1000][1000];
} tabuleiro;

typedef struct
{
    char nome; // 'a'
    int tamanho;
    int *colunas;
    int *linhas; // tamanho -1
} peca;

tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual);
void printa_tabuleiro(tabuleiro t, int numero_tabuleiro);
tabuleiro coloca_coordenadas(tabuleiro t);
tabuleiro verifica_espacos(tabuleiro t);
void modo_interativo(char *movimento, char movimentos[sizeof(long)][60], int numero_de_movimentos, tabuleiro tabuleiros[2]);
int verifica_sim();
int verifica_movimento(int y, int x, char mov, tabuleiro t);
int eh_possivel_mover(tabuleiro t, int linha, int coluna);
void apaga_movimentos(char movimentos[sizeof(long)][60], int tamanho);
void tem_corpo(tabuleiro t, char peca, int linha, int coluna, int coordenadas[9]);
int verifica_locais(tabuleiro t, char c, int locais[8]);
peca monta_peca(char nome, int tamanho, int *col, int *lin);

int eh_char_possivel(char c);

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
    // Variavel para guardar o numero de movimentos
    char movimentos[sizeof(long)][60];
    // numero de movimentos ja feitos
    int numero_de_movimentos = 0;
    char movimento[7];
    // Lista com todos os tabuleiros
    tabuleiro tabuleiros[2];

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

        t1 = verifica_espacos(t1);
        t2 = verifica_espacos(t2);

        tabuleiros[0] = t1;
        tabuleiros[1] = t2;

        // Entra no modo interativo
        modo_interativo(movimento, movimentos, numero_de_movimentos, tabuleiros);
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
            t2.linhas = linha_atual - 1;
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

    // temporario apagar depois
    printf("Linhas: %d\n", t.linhas);
    printf("Colunas: %d\n\n", t.colunas);

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

tabuleiro verifica_espacos(tabuleiro t)
{
    // Verificar aonde se encontra os espacos possiveis de se mover e aonde fica a saida
    int x1, x2, y1, y2;
    x1 = -1;
    x2 = -1;
    y1 = -1;
    y2 = -1;

    // x1, x2 --> espaco
    for (int linha = 2; linha < t.linhas; linha++)
    {
        for (int coluna = 2; coluna < t.colunas; coluna++)
        {
            if (t.matriz[linha][coluna] == ' ')
            {
                // Pras colunas
                if (x1 != -1)
                {
                    x2 = coluna;
                }
                else
                {
                    x1 = coluna;
                }

                // Pras linhas
                if (y1 != -1)
                {
                    y2 = linha;
                }
                else
                {
                    y1 = linha;
                }
            }
        }
    }

    // Preencher as coordenadas dos espacos no tabuleiro
    t.espacos[0][0] = x1;
    t.espacos[1][0] = x2;
    t.espacos[0][1] = y1;
    t.espacos[1][1] = y2;

    // Para as saidas
    x1 = -1;
    x2 = -1;
    y1 = -1;
    y2 = -1;

    // x1, x2, y1, y2 --> saidas
    for (int linha = 1; linha <= t.linhas; linha++)
    {
        for (int coluna = 1; coluna <= t.colunas; coluna++)
        {
            if ((linha == 1) || (linha == t.linhas) || (coluna == 1) || (coluna == t.colunas))
            {

                if (t.matriz[linha][coluna] == ' ')
                {
                    // Pras colunas
                    if (x1 != -1)
                    {
                        x2 = coluna;
                    }
                    else
                    {
                        x1 = coluna;
                    }

                    // Pras linhas
                    if (y1 != -1)
                    {
                        y2 = linha;
                    }
                    else
                    {
                        y1 = linha;
                    }
                }
            }
        }
    }

    // Preencher as coordenadas das saidas no tabuleiro
    t.saidas[0][0] = x1;
    t.saidas[1][0] = x2;
    t.saidas[0][1] = y1;
    t.saidas[1][1] = y2;

    return t;
}

void modo_interativo(char *movimento, char movimentos[sizeof(long)][60], int numero_de_movimentos, tabuleiro tabuleiros[2])
{
    char escolha[60];
    // Se usar config for -1 o usuario precisa selecionar a configuracao que deseja antes de poder fazer a movimentacao
    int usar_config = -1;
    int ja_escolheu_config = 0;
    int sim = 1;
    int tem_erro = 0;

    printf("----Modo Interativo----\n");

    while (fgets(escolha, 60, stdin) != NULL)
    {
        printf("Escolha: %s\n", escolha);

        if (escolha[0] == 'l')
        {
            printa_tabuleiro(tabuleiros[0], 1);
            printa_tabuleiro(tabuleiros[1], 2);
        }

        else if (escolha[0] == 'c')
        {

            if (ja_escolheu_config)
            {
                sim = verifica_sim();
            }

            if (sim && escolha[1] == ' ' && isdigit(escolha[2]))
            {
                usar_config = (int)escolha[2] - '0';
                printa_tabuleiro(tabuleiros[usar_config - 1], usar_config);
                ja_escolheu_config = 1;
                apaga_movimentos(movimentos, numero_de_movimentos);
            }
            else if (sim == 0)
            {
                continue;
            }
            else
            {
                printf("Essa configuracao nao existe ou digitou numero de parametros invalido!!!\n");
            }
        }

        else if (escolha[0] == 'p')
        {
            if (numero_de_movimentos > 0)
            {
                printf("Chamar todas as movimentacoes ja feitas\n");
            }
            else
            {
                printf("Voce ainda nao fez nenhuma jogada!!!\n");
            }
        }

        else if (escolha[0] == 'm')
        {

            if (ja_escolheu_config == 0)
            {
                printf("Voce ainda nao escolheu qual a configuracao usar!!!\n");
                continue;
            }

            if (escolha[1] == ' ' && isdigit(escolha[2]) && escolha[3] == ' ' && isdigit(escolha[4]) && escolha[5] == ' ' && isupper(escolha[6]))
            {
                tem_erro = verifica_movimento((int)escolha[2] - '0', (int)escolha[4] - '0', escolha[6], tabuleiros[usar_config - 1]);

                if (tem_erro == 0)
                {
                    strcpy(movimentos[numero_de_movimentos], escolha);
                    numero_de_movimentos++;
                    printf("Movimento %d\n\n\n", numero_de_movimentos);
                    printa_tabuleiro(tabuleiros[usar_config - 1], usar_config);
                }
            }
            else
            {
                printf("Esse movimento nao eh valido!!!\nDigitar novamente\n");
            }
        }

        else
        {
            printf("Essa opcao eh invalida!!!\n");
        }
    }
}

int verifica_sim()
{
    char sim[4];
    printf("Voce realmente quer fazer isso ??\n");
    printf("Pois vai perder tudo feito na configuracao anterior!!!\nDigite (s) para sim e (n) para nao\n\n");

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

// Retorna 1 quando tiver algum tipo de erro
int verifica_movimento(int y, int x, char mov, tabuleiro t)
{
    char char_atual;
    int possivel_mover = 1;
    int corpo[9];
    int linha, coluna;
    int quantidade_peca = 0;
    int locais[8];
    int cont = 0;
    int k = 0;
    int rastro = 0;

    char_atual = t.matriz[y + 1][x + 1];

    printf("Peca atual: %c\n\n", char_atual);

    if ((y + 1 > t.linhas) || (x + 1 > t.colunas))
    {
        printf("Movimento Invalido!!!\n");
        return 1;
    }

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
        linha = y;
        coluna = x;
        if (mov == 'D')
        {
            printf("mover 1 pra direita\n");
        }
        else if (mov == 'E')
        {
            printf("mover 1 pra esquerda\n");
        }
        else if (mov == 'B')
        {
            printf("mover 1 pra baixo\n");
        }
        else if (mov == 'C')
        {
            printf("mover 1 pra cima\n");
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

// Quando eh possivel mover retorna 1
int eh_possivel_mover(tabuleiro t, int linha, int coluna)
{
    if (coluna == t.espacos[0][0] && linha == t.espacos[0][1])
    {
        return 1;
    }

    if (coluna == t.espacos[1][0] && linha == t.espacos[1][1])
    {
        return 1;
    }

    return 0;
}

void apaga_movimentos(char movimentos[sizeof(long)][60], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        memset(movimentos[i], '\0', strlen(movimentos[i]));
    }
}

int eh_ele_mesmo(tabuleiro t, char c, int linha, int coluna)
{
    if (t.matriz[linha][coluna] == c)
    {
        return 1;
    }

    return 0;
}
