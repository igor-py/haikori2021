#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CHAR_POSSIVEIS "abcdefghijklmD"
#define MSG_FALHA "Peça não pode ser movida."

typedef struct peca
{
    char nome; // 'a'
    int tamanho;
    int colunas[100];
    int linhas[100];
} peca;

typedef struct tabuleiro
{
    char nome[50];
    int colunas;
    int linhas;
    int saidas[2][2]; // eh um par de coordenadas da onde se encontra as saidas [[x1, y1], [x2, y2]]
    char matriz[50][50];
    int num_pecas;
    peca pecas[100];
} tabuleiro;

typedef struct node
{
    struct node *pai;
    struct node *filho;
    struct node *irmao;
    struct node *raiz;
    tabuleiro t;
    char chave[100];
    int tamanho_chave;
} node;

tabuleiro incrementa_tabuleiro(tabuleiro t, char *linha, int linha_atual);
void printa_tabuleiro(tabuleiro t, int numero_tabuleiro);
tabuleiro coloca_coordenadas(tabuleiro t);
void modo_interativo(char *movimento, char movimentos[sizeof(long)][60], int numero_de_movimentos, tabuleiro tabuleiros[2]);
int verifica_sim();
int verifica_movimento(int y, int x, char mov, tabuleiro *t);
void apaga_movimentos(char movimentos[sizeof(long)][60], int tamanho);
void tem_corpo(tabuleiro t, char peca, int linha, int coluna, int coordenadas[9]);
int verifica_locais(tabuleiro t, char c, int locais[8]);
peca monta_peca(char nome, int tamanho, int *col, int *lin);
tabuleiro *copia_tabuleiro(tabuleiro *t);
void carrega_tabuleiro(tabuleiro *t);
peca carrega_peca(tabuleiro *t, char p_nome);
void printa_pecas_tabuleiro(tabuleiro t);
int move_peca_tabuleiro(tabuleiro *t, char c, char m);
int eh_char_possivel(char c);
node *create_node(tabuleiro t);
int pode_mover(tabuleiro *t, peca *p, int mov_linha, int mov_coluna);
char *verificar_char_diferentes(tabuleiro t);

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

    tabuleiro t1 = {"", 0, 0, {{}, {}}, {}, 0, {}};
    tabuleiro t2 = {"", 0, 0, {{}, {}}, {}, 0, {}};

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

        strcpy(t1.nome, nome_tabuleiros[0]);
        strcpy(t2.nome, nome_tabuleiros[1]);

        t1 = coloca_coordenadas(t1);
        t2 = coloca_coordenadas(t2);

        tabuleiros[0] = t1;
        tabuleiros[1] = t2;

        // Entra no modo interativo
        modo_interativo(movimento, movimentos, numero_de_movimentos, tabuleiros);
    }

    // Depois lembrar de copiar o feito pro de cima para o abaixo

    // Quando o usuario roda o main -f nomeArquivo.txt
    else if (argc == 3)
    {
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

        strcpy(t1.nome, nome_tabuleiros[0]);
        strcpy(t2.nome, nome_tabuleiros[1]);

        t1 = coloca_coordenadas(t1);
        t2 = coloca_coordenadas(t2);

        tabuleiros[0] = t1;
        tabuleiros[1] = t2;

        // Entra no modo interativo
        modo_interativo(movimento, movimentos, numero_de_movimentos, tabuleiros);
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

void modo_interativo(char *movimento, char movimentos[sizeof(long)][60], int numero_de_movimentos, tabuleiro tabuleiros[2])
{
    char escolha[60];
    // Se usar config for -1 o usuario precisa selecionar a configuracao que deseja antes de poder fazer a movimentacao
    int usar_config = -1;
    int ja_escolheu_config = 0;
    int sim = 1;
    int tem_erro = 0;
    char *pecas_diferentes;
    node arvore_tabuleiro;
    node *no_atual;
    tabuleiro *t_tabuleiro = malloc(sizeof(struct tabuleiro));
    tabuleiro *t_comando_p = malloc(sizeof(struct tabuleiro));

    printf("----Modo Interativo----\n");

    while (fgets(escolha, 60, stdin) != NULL)
    {

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
                // t_tabuleiro = &tabuleiros[usar_config - 1];
                // t_comando_p = &tabuleiros[usar_config - 1];

                t_tabuleiro = copia_tabuleiro(&tabuleiros[usar_config - 1]);
                t_comando_p = copia_tabuleiro(&tabuleiros[usar_config - 1]);
                // t_comando_s = *copia_tabuleiro(&tabuleiros[usar_config - 1]);

                carrega_tabuleiro(t_tabuleiro);
                // Tabuleiro copia a ser chamado no comando 'p'
                carrega_tabuleiro(t_comando_p);
                pecas_diferentes = verificar_char_diferentes(*t_comando_p);
                printa_tabuleiro(*t_tabuleiro, usar_config);
                //printa_pecas_tabuleiro(t_tabuleiro);
                ja_escolheu_config = 1;
                apaga_movimentos(movimentos, numero_de_movimentos);
                numero_de_movimentos = 0;
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
                printa_tabuleiro(*t_comando_p, usar_config);
                for (int tmp = 0; tmp < numero_de_movimentos; tmp++)
                {
                    verifica_movimento(movimentos[tmp][2] - '0', movimentos[tmp][4] - '0', movimentos[tmp][6], t_comando_p);
                    printa_tabuleiro(*t_comando_p, usar_config);
                }
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
                tem_erro = verifica_movimento((int)escolha[2] - '0', (int)escolha[4] - '0', escolha[6], t_tabuleiro);

                if (tem_erro == 0)
                {
                    strcpy(movimentos[numero_de_movimentos], escolha);
                    numero_de_movimentos++;
                    printf("Movimento %d\n", numero_de_movimentos);
                    printa_tabuleiro(*t_tabuleiro, usar_config);
                }
            }
            else
            {
                printf("Esse movimento nao eh valido!!!\nDigitar novamente\n");
            }
        }
        else if (escolha[0] == 's')
        {
            if (ja_escolheu_config == 0)
            {
                printf("Voce ainda nao escolheu qual a configuracao usar!!!\n");
                continue;
            }

            printf("----- MODO s -----\n");
            arvore_tabuleiro = *create_node(*t_comando_p);
            no_atual = &arvore_tabuleiro;
            tabuleiro *copia_tabuleiro_atual = copia_tabuleiro(&(no_atual->t));

            //Verificar todos os movimentos possiveis
            while (1)
            {
                // Mostrar todos os movimentos possiveis
                for (int n = 0; n < 9; n++)
                {
                    // Verificar pecas diferentes
                    for (int x = 0; pecas_diferentes[x] != '\0'; x++)
                    {

                        if (move_peca_tabuleiro(copia_tabuleiro_atual, pecas_diferentes[x], 'D') == 0)
                        {
                            printf("1---> \n");
                            printa_tabuleiro(*copia_tabuleiro_atual, 1);
                            printf("2---> \n");
                            printa_tabuleiro(no_atual->t, 1);
                            break;
                        }
                    }
                }
                break;
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
int verifica_movimento(int y, int x, char mov, tabuleiro *t)
{
    char char_atual;

    char_atual = t->matriz[y + 1][x + 1];

    if ((y + 1 > t->linhas) || (x + 1 > t->colunas))
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
        int sucesso_movimento = 0;
        if (mov == 'D')
        {
            sucesso_movimento = move_peca_tabuleiro(t, char_atual, 'D');
        }
        else if (mov == 'E')
        {
            sucesso_movimento = move_peca_tabuleiro(t, char_atual, 'E');
        }
        else if (mov == 'B')
        {
            sucesso_movimento = move_peca_tabuleiro(t, char_atual, 'B');
        }
        else if (mov == 'C')
        {
            sucesso_movimento = move_peca_tabuleiro(t, char_atual, 'C');
        }
        else
        {
            printf("Esse movimento nao existe!!!\n");
            return 1;
        }
        return sucesso_movimento;
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

void printa_peca(peca p)
{
    printf("Peca %c\n", p.nome);
    for (int i = 0; i < p.tamanho; i++)
    {
        printf("P%d\n", i);
        printf("linha %d\n", p.linhas[i]);
        printf("coluna %d\n", p.colunas[i]);
        printf("\n");
    }
}

void printa_pecas_tabuleiro(tabuleiro t)
{
    printf("Printa Tab");
    for (int i = 0; i < t.num_pecas; i++)
    {
        printa_peca(t.pecas[i]);
    }
}

peca carrega_peca(tabuleiro *t, char p_nome)
{
    peca p;
    p.nome = p_nome;
    p.tamanho = 0;
    for (int i = 2; i < t->linhas; i++)
    {
        for (int j = 2; j < t->colunas; j++)
        {
            if (t->matriz[i][j] == p_nome)
            {
                p.linhas[p.tamanho] = i;
                p.colunas[p.tamanho] = j;
                p.tamanho++;
            }
        }
    }
    return p;
}

void carrega_tabuleiro(tabuleiro *t)
{
    char pecas_carregadas[256];
    for (int i = 0; i < 256; i++)
    {
        pecas_carregadas[i] = 0;
    }
    t->num_pecas = 0;
    for (int i = 0; i < 100; i++)
    {
        peca t_peca = {0, 0, {}, {}};
        t->pecas[i] = t_peca;
    }
    for (int i = 2; i < t->linhas; i++)
    {
        for (int j = 2; j < t->colunas; j++)
        {
            if (eh_char_possivel(t->matriz[i][j]) == 1)
            {
                if (pecas_carregadas[t->matriz[i][j]] == 0)
                {
                    pecas_carregadas[t->matriz[i][j]] = 1;
                    t->pecas[t->num_pecas] = carrega_peca(t, t->matriz[i][j]);
                    t->num_pecas += 1;
                }
            }
        }
    }
}

int pode_mover(tabuleiro *t, peca *p, int mov_linha, int mov_coluna)
{
    int pode_m = 1;
    for (int i = 0; i < p->tamanho; i++)
    {
        char t_pos = t->matriz[p->linhas[i] + mov_linha][p->colunas[i] + mov_coluna];
        if (t_pos != p->nome && t_pos != ' ')
        {
            pode_m = 0;
        }
    }
    return pode_m;
}

void move_peca(tabuleiro *t, peca *p, int mov_linha, int mov_coluna)
{
    for (int i = 0; i < p->tamanho; i++)
    {
        t->matriz[p->linhas[i]][p->colunas[i]] = ' ';
        p->linhas[i] += mov_linha;
        p->colunas[i] += mov_coluna;
    }
    for (int i = 0; i < p->tamanho; i++)
    {
        t->matriz[p->linhas[i]][p->colunas[i]] = p->nome;
    }
}

int move_peca_tabuleiro(tabuleiro *t, char c, char m)
{
    int mov_coluna = 0;
    int mov_linha = 0;
    switch (m)
    {
    case 'D':
        mov_coluna = 1;
        break;
    case 'E':
        mov_coluna = -1;
        break;
    case 'C':
        mov_linha = -1;
        break;
    case 'B':
        mov_linha = 1;
        break;
    }
    peca *p = malloc(sizeof(struct peca));
    for (int i = 0; i < t->num_pecas; i++)
    {
        if (t->pecas[i].nome == c)
        {
            p = &t->pecas[i];
        }
    }
    if (pode_mover(t, p, mov_linha, mov_coluna) == 1)
    {
        move_peca(t, p, mov_linha, mov_coluna);
        return 0;
    }
    return 1;
}

node *create_node(tabuleiro t)
{
    node *no = malloc(sizeof(node));
    int pos = 0;

    no->filho = NULL;
    no->pai = NULL;
    no->irmao = NULL;
    no->raiz = NULL;
    no->t = t;

    for (int i = 2; i < t.linhas; i++)
    {
        for (int j = 2; j < t.colunas; j++)
        {
            no->chave[pos++] = t.matriz[i][j];
        }
    }
    no->tamanho_chave = pos;

    return no;
}

// void encontra_solucao(tabuleiro t)
// {
//     // verifica se o tabuleiro é repetido
//         // se sim retorna
//     // armazena tabuleiro
//     // verifica se é solução
//         // se sim retorna
//     // verifica se o numero de movimentos é zero
//         // se sim retorna
//     // loop das peças
//         // loop dos movimentos
//             // verifica se pode mover
//                 // reduz numero de movimentos
//                 // chama encontra solucao tabuleiro novo
// }

// void encontra_solucao(tabuleiro *t, node *arvore_tabuleiro, node *no_atual)
// {
//     peca *p;
//     for (int i = 0; i < t->num_pecas; i++)
//     {
//         p = &t->pecas[i];
//         for (int mov = -1; i < 2; i += 2)
//         {
//             if (pode_mover(t, p, mov, 0))
//             {
//                 move_peca(t, p, mov, 0);
//                 if (verifica_tabuleiro_novo(t, arvore_tabuleiro) == 0)
//                 {
//                     tabuleiro *copia = copia_tabuleiro(t);
//                     printa_tabuleiro(*copia, 1);
//                     // armazena_tabuleiro(copia, no_atual);
//                 }
//                 // if (verifica_soluca(t))
//                 // {
//                 //     t->solucao = 1;
//                 // }
//                 move_peca(t, p, (-1) * mov, 0);
//             }
//         }
//     }
// }

tabuleiro *copia_tabuleiro(tabuleiro *t)
{
    tabuleiro *copia = malloc(sizeof(struct tabuleiro));
    strcpy(copia->nome, t->nome);

    copia->colunas = t->colunas;
    copia->linhas = t->linhas;
    copia->num_pecas = t->num_pecas;
    for (int i = 0; i < 2; i++)
    {
        for (int l = 0; l < 2; l++)
        {
            copia->matriz[i][l] = t->saidas[i][l];
        }
    }
    for (int i = 0; i < 1000; i++)
    {
        for (int l = 0; l < 1000; l++)
        {
            copia->matriz[i][l] = t->matriz[i][l];
        }
    }
    for (int i = 0; i < 100; i++)
    {
        copia->pecas[i] = t->pecas[i];
    }
    return copia;
}

int verifica_tabuleiro_novo(node n1, node n2)
{
    // Verificar se o tabuleiro eh novo

    // Se sim retornar 1
    for (int i = 0; i < n1.tamanho_chave; i++)
    {
        if (n1.chave[i] != n2.chave[i])
        {
            return 0;
        }
    }
    return 1;
}

char *verificar_char_diferentes(tabuleiro t)
{
    int atual = 0;
    char anterior;
    char *diferentes = malloc(sizeof(char *));

    for (int i = 2; i < t.linhas; i++)
    {
        for (int j = 2; j < t.colunas; j++)
        {
            if (j == 2 && i == 2)
            {
                diferentes[atual++] = t.matriz[i][j];
            }
            else if ((strchr(diferentes, t.matriz[i][j]) == NULL) && t.matriz[i][j] != ' ')
            {
                diferentes[atual++] = t.matriz[i][j];
            }
        }
    }

    return diferentes;
}