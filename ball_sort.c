#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LIMPAR o terminal do WINDOWS e LINUX
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// definir o tamanho da matriz principal
char MATRIZPRINCIPAL[10][10];

// definir a quantidade de caracteres que o nickname pode ter 
#define MAX_NICK 100

long MUDARFASE = -1;

int FASE = 0;

int MAIORCOLUNA = 0;
int ColunaAtual = 0;

int MODOBLIND = 0;
/*para mostrar que as funções existem e não dar conflito*/
void menu();
void configuracoes();

/* função com o objetivo de inicializar a matriz do jogo, e tornar mais fácil a distinção
de colunas preenchidas */
void inicializarmatriz() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            MATRIZPRINCIPAL[i][j] = '0';
        }
    }
}

int sair() {
    printf("\nSaindo do jogo...\n");
    exit(0);
    return 1;
}

void Manual() {
    system(CLEAR);
    printf("\033[0;36m\n\n\n*   *   *   *   *   *   *   *   *   *\033[0m\n\n");
    printf("\033[0;36m  *   *   *   *   *   *   *   *   *   *\033[0m\n\n");
    printf("Esse jogo é inspirado no ");
    printf("\033[0;36mBall Sort\033[0m");
    printf(" da franquia Guru Games!\n\n");
    printf("O jogo consiste em colunas com caracteres embaralhados que precisa da SUA ajuda para serem organizados!\n\n");
    printf("\033[0;36mE como organizá-los?\033[0m\n\n");
    printf("Você precisa digitar a coluna de onde quer retirá-los e a coluna onde eles vão parar.\n\n");
    printf("Mas tem algo IMPORTANTE! Os movimentos só podem acontecer se o caractere movido\n");
    printf("e o último caractere da coluna de destino forem IGUAIS!\n\n");
    printf("Além disso a coluna de destino precisa ter ESPAÇO DISPONÍVEL!\n\n");
    printf("Você vence o jogo se conseguir organizar TODAS as colunas,\n");
    printf("de modo que o conteúdo delas seja SÓ de caracteres IGUAIS\n");
    printf("ao da linha subsequente na MESMA COLUNA!\n\n");
    printf("\033[0;36mBoa Sorte!\033[0m\n\n");
    printf("Digite <enter> para voltar ao MENU! ");
    getchar();
}

void ZerarRanking() {
    FILE *arquivo = fopen("ranking.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    } else {
        fclose(arquivo); 
    }
}

// checagem para saber se o jogo chegou ao fim, ou seja, se todas as colunas estão preenchidas
int checagem(int tam, int colunas) {
    for (int col = 0; col < colunas; col++) {
        char primeiro = '\0';
        int completa = 1;
        int vazia = 1;

        for (int lin = 10 - tam; lin < 10; lin++) {
            char atual = MATRIZPRINCIPAL[lin][col];

            if (atual != '0' && atual != 'X') {
                if (primeiro == '\0') {
                    primeiro = atual;
                } else if (atual != primeiro) {
                    completa = 0;
                }
                vazia = 0;
            }
        }
        if (!vazia && !completa) {
            return 0; 
        }
        if (!vazia) {
            int quantidade = 0;
            for (int lin = 10 - tam; lin < 10; lin++) {
                if (MATRIZPRINCIPAL[lin][col] != '0' && MATRIZPRINCIPAL[lin][col] != 'X') {
                    quantidade++;
                }
            }
            if (quantidade != tam) {
                return 0;
            }
        }
    }
    return 1;
}

int checagemColuna(int tam, int Coluna) {
    for (int lin = 10 - tam; lin < 9; lin++) {
        if (MATRIZPRINCIPAL[lin][Coluna] != MATRIZPRINCIPAL[lin+1][Coluna]) {
            return 0;
        }
    }
    return 1;
}

// printar a matriz, incluindo uma simulação do frasco de vidro 
void printarmatriz(int tam, int colunas) {
    printf("\n\n\n");
    if (MODOBLIND) {
        for (int i = 10-tam; i <= 11; i++) {
            if (i == 11) {
                printf("\n");
            }
            int printed = 0;
            for (int j = 0; j < colunas; j++) {
                if (i == 10 && j > 0) {
                    printf("\033[0;36m=-=-= \033[0m");
                }
                else if (i == 10 && j == 0) {
                    printf("\033[0;36m     =-=-= \033[0m");
                }
                else if (i == 11 && j > 0) {
                    printf("\033[0;36m  %d   \033[0m", j+1);
                }
                else if (i == 11 && j == 0) {
                    printf("\033[0;36m       %d   \033[0m", j+1);
                }
                else {
                    if (j == 0) {
                        printf("\033[0;36m     | \033[0m");
                    }
                    else {
                        printf("\033[0;36m| \033[0m");
                    }
                    if (MATRIZPRINCIPAL[i][j] != '0' && MATRIZPRINCIPAL[i][j] != 'X' && !printed) {
                        printf("%c", MATRIZPRINCIPAL[i][j]);
                        printed++;
                    }
                    else {
                        printf(" ");
                    }
                    if (j < colunas-1) {
                        printf("\033[0;36m | \033[0m");
                    }
                    else {
                        printf("\033[0;36m |\033[0m");
                    }
                }
            }
            printf("\n");
            if (i == 11) {
                printf("\n\n");
            }
        }
    }
    else {
        for (int i = 10-tam; i <= 11; i++) {
            if (i == 11) {
                printf("\n");
            }
            for (int j = 0; j < colunas; j++) {
                if (i == 10 && j > 0) {
                    printf("\033[0;36m=-=-= \033[0m");
                }
                else if (i == 10 && j == 0) {
                    printf("\033[0;36m     =-=-= \033[0m");
                }
                else if (i == 11 && j > 0) {
                    printf("\033[0;36m  %d   \033[0m", j+1);
                }
                else if (i == 11 && j == 0) {
                    printf("\033[0;36m       %d   \033[0m", j+1);
                }
                else {
                    if (j == 0) {
                        printf("\033[0;36m     | \033[0m");
                    }
                    else {
                        printf("\033[0;36m| \033[0m");
                    }
                    if (MATRIZPRINCIPAL[i][j] == '0' || MATRIZPRINCIPAL[i][j] == 'X') {
                        printf(" ");
                    }
                    else {
                        printf("%c", MATRIZPRINCIPAL[i][j]);
                    }
                    if (j < colunas-1) {
                        printf("\033[0;36m | \033[0m");
                    }
                    else {
                        printf("\033[0;36m |\033[0m");
                    }
                }
            }
            printf("\n");
            if (i == 11) {
                printf("\n\n");
            }
        }
    }
}

// função com o objetivo de preencher a matriz principal e tornar mais fácil a manipulação durante o jogo
void PreencherMatriz() {
    inicializarmatriz();
    FILE *entrada;
    
    entrada = fopen("entrada.txt", "r");

    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }

    if (MUDARFASE != 0) {
        fseek(entrada, MUDARFASE, SEEK_SET);
    }

    ColunaAtual = 0;
    int TamColuna;
    char caractereEntrada[2];

    while (fscanf(entrada, " %c", caractereEntrada) != EOF) {
        if (caractereEntrada[0] == '-') {
            MUDARFASE = ftell(entrada);
            break;
        }

        if (caractereEntrada[0] >= 48 && caractereEntrada[0] <= 57) {
            char SegundoDigito[1]; // caso o caractere for um 10
            fscanf(entrada, " %c", SegundoDigito);

            if (SegundoDigito[0] >= 48 && SegundoDigito[0] <= 57 && caractereEntrada[0] != '0') {
                TamColuna = 10;
            } else {
                TamColuna = caractereEntrada[0] - 48;
                fseek(entrada, -1, SEEK_CUR);
            }
            if (TamColuna > MAIORCOLUNA) {
                MAIORCOLUNA = TamColuna;
            }
        }

        if (TamColuna == 0) {
            for (int j = 10 - MAIORCOLUNA; j < 10; j++) {
                MATRIZPRINCIPAL[j][ColunaAtual] = 'X';
            }
        } else {
            for (int j = 10 - TamColuna; j < 10; j++) {
                fscanf(entrada, " %c", caractereEntrada);
                MATRIZPRINCIPAL[j][ColunaAtual] = caractereEntrada[0];
            }
        }
        ColunaAtual++;
    }
    printf("ESSA EH A MAIORCOLUNA %d\n", MAIORCOLUNA);
    fclose(entrada);
}

// MOSTRAR O RANKING NA TELA
void Ranking() {
    system(CLEAR);

    FILE *ranking;
    ranking = fopen("ranking.bin", "rb");

    if (ranking == NULL) {
        printf("O ranking ainda não possui nenhum usuário cadastrado!\n");
        return;
    }

    char nickexistente[MAX_NICK];
    int pontuacaoexistente;
    printf("\n\n\n");
    printf("\033[0;36m     *   *   *   *   *   *   *   *   *   *\033[0m\n\n");
    printf("\033[0;36m     %-10s%-20s%-10s\033[0m\n", "Posicao", "Nickname", "Pontuacao");
    printf("\n");

    int pos = 1;
    while (fread(nickexistente, sizeof(char), MAX_NICK, ranking) == MAX_NICK) {
        fread(&pontuacaoexistente, sizeof(int), 1, ranking);
        printf("     %-10d", pos);
        printf("%-20s", nickexistente);
        printf("%-10d", pontuacaoexistente);
        pos++;
    }
    printf("\n\n\n     Digite <enter> para voltar ao MENU! ");
    getchar();
}

// LOOP PRINCIPAL DO JOGO, determina o funcionamento da opção de JOGAR
void MAINLOOP() {
    FASE++;
    PreencherMatriz();
    while (1) {
        system(CLEAR);
        int Movimento = 1;
        printarmatriz(MAIORCOLUNA, ColunaAtual);
        printf("     Digite a coluna origem: ");
        int posInicial;
        scanf("%d", &posInicial);
        printf("     Digite a coluna destino: ");
        int posFinal;
        scanf("%d", &posFinal);
        posInicial--;
        posFinal--;
        // checar qual o caractere da posição inicial
        int flag = 0, linhaInicio, MaxTransferidos = 0;
        char aux;
        for (int i = MAIORCOLUNA; i < 10; i++) {
            if (MATRIZPRINCIPAL[i][posInicial] != '0' && MATRIZPRINCIPAL[i][posInicial] != 'X' && flag == 0) {
                aux = MATRIZPRINCIPAL[i][posInicial];
                linhaInicio = i;
                flag++;
                MaxTransferidos++;
            } else if (MATRIZPRINCIPAL[i][posInicial] == aux && MATRIZPRINCIPAL[i-1][posInicial] == aux ) {
                MaxTransferidos++;
            }
        }

        flag = 0;

        // checa quantos espaços estão disponíveis na coluna de destino
        int espacoDisponivel = 0, linhaFinal;
        for (int i = 10-MAIORCOLUNA; i < 10; i++) { // exemplo, se a maior coluna for 3, ele começa no 10-3-1, ou seja, no 6+3 = 9, o máximo índice é 9
            if (MATRIZPRINCIPAL[i][posFinal] == '0' || MATRIZPRINCIPAL[i][posFinal] == 'X') {
                espacoDisponivel++;
            } else {
                linhaFinal = i;
                if (MATRIZPRINCIPAL[i][posFinal] == aux) {
                    printf("\033[0;32m\n     Esse movimento foi autorizado!\n\033[0m");
                }
                else {
                    printf("\033[0;31m\n     Você não pode fazer esse movimento!\n\033[0m");
                    Movimento = 0;
                }
                break;
            }
        }
        if (espacoDisponivel == MAIORCOLUNA) {
            printf("\033[0;32m\n     Esse movimento foi autorizado!\n\033[0m");
            linhaFinal = 10;
        }

        // checar quantos vao ser transferidos ao destino
        if (Movimento) {
            int Tranferencia;
            if (MaxTransferidos<espacoDisponivel) {
                Tranferencia = MaxTransferidos;
            }
            else {
                Tranferencia = espacoDisponivel;
            }

            // checar se o movimento pode ocorrer
            for (int i = linhaFinal-Tranferencia; i < linhaFinal; i++) {
                if (MATRIZPRINCIPAL[i][posFinal] == '0' || MATRIZPRINCIPAL[i][posFinal] == 'X') {
                    MATRIZPRINCIPAL[i][posFinal] = aux;
                    MATRIZPRINCIPAL[linhaInicio][posInicial] = '0';
                    int colunaCompleta = checagemColuna(MAIORCOLUNA, posFinal);
                    if (colunaCompleta) {
                        system(CLEAR);
                        printarmatriz(MAIORCOLUNA, ColunaAtual);
                        printf("\033[0;32m\n * . * . Você completou a coluna %d! * . * . \n\033[0m", posFinal+1);
                    }
                }
                linhaInicio++;
            }
        }
        int terminarFase = checagem(MAIORCOLUNA, ColunaAtual);
        if (!terminarFase) {
            printf("\n     Digite <enter> para continuar! ");
            while (getchar() != '\n');
            getchar();
        }
        else if (terminarFase) {
            system(CLEAR);
            printf("\033[0;36m\n\n\n\n*  .       *      . *     *     *  *       .   *   * *     *  *      . *   * *\n\n\033[0m");
            printf("\033[0;36m       *       *  *  .   *     *  *       . *   *     *         .   *    .       *  *   * *\n\n\033[0m");
            printf("     Parabéns! Você completou a ");
            printf("\033[0;36mFASE %d!\n\n\033[0m\n\n", FASE);
            printf("     Digite <enter> para continuar! ");
            while (getchar() != '\n');
            getchar();
            PreencherMatriz();
            FASE++;
        }
    }
}

void Modoblind() {
    system(CLEAR);
    printf("\033[0;36m\n\n\n     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("        \033[0;36m  O QUE É O MODO BLIND?\033[0m\n");
    printf("\033[0;36m     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n\n");
    printf("     Ele deixa visível apenas o último caractere da COLUNA, tornado o jogo MAIS DIFÍCIL!\n");
    printf("     É perfeito para quem gosta de DESAFIOS!\n");
    printf("\033[0;32m\n     Para ATIVAR o modo blind - APERTE 1!\n\033[0m");
    printf("\033[0;31m\n     Para DESATIVAR o modo blind - APERTE 2!\n\n\033[0m");
    printf("     Digite sua opção: ");
    int opcao;
    scanf("%d", &opcao);
    if (opcao == 1) {
        MODOBLIND = 1;
    }
    else if (opcao == 2) {
        MODOBLIND = 0;
    }
}

// menu das configuracoes
void configuracoes() {
    system(CLEAR);
    int opcao;
    while (1) {
        system(CLEAR);
        printf("\033[0;36m\n\n\n     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("             \033[0;36mCONFIGURACOES\033[0m\n");
        printf("     \033[0;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("     O que deseja fazer?\n");
        printf("     1 - Zerar Ranking.\n");
        printf("     2 - Modo Blind.\n");
        printf("     3 - Editor de fases.\n");
        printf("     4 - Voltar ao menu principal.\n");
        printf("     ");
        scanf("%d", &opcao);
        getchar(); 
        switch (opcao) {
            case 1: ZerarRanking(); break;
            case 2: Modoblind(); break;
            case 3: break;
            case 4: menu();
            default:
                printf("Opcao invalida. Pressione Enter para continuar.\n");
                getchar();
                break;
        }
    }
}

// menu principal do jogo
void menu() {
    system(CLEAR);
    int opcao;

    while (1) {
        system(CLEAR);
        printf("\033[0;36m\n\n\n     =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("             \033[0;36mJOGO BALL SORT!\033[0m\n");
        printf("     \033[0;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("     O que deseja fazer?\n");
        printf("     1 - Jogar.\n");
        printf("     2 - Ranking.\n");
        printf("     3 - Manual.\n");
        printf("     4 - Configuracoes.\n");
        printf("     5 - Sair.\n");
        printf("     ");
        scanf("%d", &opcao);
        getchar(); 
        switch (opcao) {
            case 1: MAINLOOP(MATRIZPRINCIPAL); break;
            case 2: Ranking(); break;
            case 3: Manual(); break;
            case 4: configuracoes(); break;
            case 5: sair(); return;
            default:
                printf("Opcao invalida. Pressione Enter para continuar.\n");
                getchar();
                break;
        }
    }
}

// SEGUNDO LOOP PRINCIPAL DO JOGO, determina o funcionamento geral
int main() {
    FILE *ranking;
    char nickname[MAX_NICK];
    int pontuacao = 0;

    ranking = fopen("ranking.bin", "rb+");

    if (ranking == NULL) {
        ranking = fopen("ranking.bin", "wb+");
        if (ranking == NULL) {
            printf("Erro ao abrir o arquivo! Tente novamente!\n");
            return 1;
        }
    }

    printf("\033[0;36m\n\n\n     * * * \033[0m");
    printf("Bem vindo(a) ao Jogo Ball Sort de APC!!");
    printf("\033[0;36m * * *\n\n\n\033[0m");
    printf("     Digite seu");
    printf("\033[0;36m nickname: \033[0m");
    scanf("%s", nickname);

    int usuarioexiste = 0;
    int pontuacaoexistente;
    char nickexistente[MAX_NICK];

    rewind(ranking);
    while (fread(nickexistente, sizeof(char), MAX_NICK, ranking) == MAX_NICK) {
        fread(&pontuacaoexistente, sizeof(int), 1, ranking);
        int usuarioigual = strcmp(nickexistente, nickname);
        if (!usuarioigual) {
            usuarioexiste = 1;
            break;
        }
    }

    if (!usuarioexiste) {
        fseek(ranking, 0, SEEK_END);
        fwrite(nickname, sizeof(char), MAX_NICK, ranking);
        fwrite(&pontuacao, sizeof(int), 1, ranking);
    }

    menu();

    return 0;
}