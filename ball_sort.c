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

int MAIORCOLUNA;
int ColunaAtual = 0;

/* função com o objetivo de inicializar a matriz do jogo, e tornar mais fácil a distinção
de colunas preenchidas */
void inicializarmatriz(char MATRIZPRINCIPAL[][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            MATRIZPRINCIPAL[i][j] = '0';
        }
    }
}

// menu principal do jogo
void menu() {
    system(CLEAR);
    int opcao;

    while (1) {
        system(CLEAR);
        printf("\033[0;36m\n\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("        \033[0;36mJOGO BALL SORT!\033[0m\n");
        printf("\033[0;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
        printf("O que deseja fazer?\n");
        printf("1 - Jogar.\n");
        printf("2 - Ranking.\n");
        printf("3 - Manual.\n");
        printf("4 - Configuracoes.\n");
        printf("5 - Sair.\n");

        scanf("%d", &opcao);
        getchar(); 
        switch (opcao) {
            case 1: MAINLOOP(); break;
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
    printf("O jogo consiste em colunas com caracteres embaralhados que precisa DA SUA ajuda para serem organizados!\n");
    printf("\033[0;36mE como organizá-los?\033[0m\n");
    printf("Você precisa digitar a coluna de onde quer retirá-los e a coluna onde eles vão parar.\n");
    printf("Mas tem algo IMPORTANTE! Os movimentos só podem acontecer se o caractere movido\n");
    printf("e o último caractere da coluna de destino forem IGUAIS!\n");
    printf("Além disso a coluna de destino precisa ter ESPAÇO DISPONÍVEL!\n");
    printf("Você vence o jogo se conseguir organizar TODAS as colunas,\n");
    printf("de modo que o conteúdo delas seja SÓ de caracteres IGUAIS\n");
    printf("ao da linha subsequente na MESMA COLUNA!\n\n");
    printf("\033[0;36mBoa Sorte!\033[0m\n\n");
    printf("Digite <enter> para voltar ao MENU! ");
    getchar();
}

// menu das configuracoes
void configuracoes() {
    system(CLEAR);
    printf("\033[0;36m\n\n\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("        \033[0;36mCONFIGURACOES\033[0m\n");
    printf("\033[0;36m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\033[0m\n");
    printf("O que deseja fazer?\n");
    printf("1 - Zerar Ranking.\n");
    printf("2 - Modo Blind.\n");
    printf("3 - Editor de fases.\n");
    printf("4 - Voltar ao menu principal.\n");
}

// checagem para saber se o jogo chegou ao fim, ou seja, se todas as colunas estão preenchidas
int checagem(char M[][10]) {
    int veredito = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (M[j][i] != '0') {
                if (M[j][i] != M[j+1][i]) {
                    veredito = 0;
                }
            }
        }
    }
    if (veredito) {
        return 1;
    }
    else {
        return 0;
    }
}

// printar a matriz, incluindo uma simulação do frasco de vidro 
void printarmatriz(char M[][10], int tam, int colunas) {
    for (int i = 10-tam; i <= 11; i++) {
        if (i == 11) {
            printf("\n");
        }
        for (int j = 0; j < colunas; j++) {
            if (i == 10) {
                printf("\033[0;36m=-=-= \033[0m");
            }
            else if (i == 11) {
                printf("\033[0;36m  %d   \033[0m", j+1);
            }
            else {
                printf("\033[0;36m| \033[0m");
                if (M[i][j] == '0' || M[i][j] == 'X') {
                    printf(" ");
                }
                else {
                    printf("%c", M[i][j]);
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

// função com o objetivo de preencher a matriz principal e tornar mais fácil a manipulação durante o jogo
void PreencherMatriz() {
    FD *entrada;
    
    entrada = fopen("entrada.txt", "r");

    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return;
    }

    ColunaAtual = 0;
    int TamColuna;
    char caractereEntrada[2];

    while (fread(caractereEntrada, sizeof(char), 1, entrada) != EOF) {
        if (caractereEntrada == '-') {
            MUDARFASE = ftell(entrada);
            break;
        }

        if (caractereEntrada[0] >= 48 && caractereEntrada[0] <= 57) {
            char SegundoDigito[1]; // caso o caractere for um 10
            fread(SegundoDigito, sizeof(char), 1, entrada);

            if (segundoDigito[0] >= 48 && segundoDigito[0] <= 57) {
                TamColuna = 10;
            } else {
                TamColuna = caractereEntrada[0] - 48;
                fseek(entrada, -1, SEEK_CUR);
            }
            if (TamColuna > MAIORCOLUNA) {
                MAIORCOLUNA = TamColuna;
            }
        }

        ColunaAtual++;

        if (TamColuna == 0) {
            for (int j = 0; j < 10; j++) {
                M[j][ColunaAtual - 1] = 'X';
            }
        } else {
            for (int j = 10 - TamColuna; j < 10; j++) {
                fread(caractereEntrada, sizeof(char), 1, entrada);
                M[j][ColunaAtual - 1] = caractereEntrada[0];
            }
        }
    }

    fclose(entrada);
}

// MOSTRAR O RANKING NA TELA
void Ranking() {
    FILE *ranking;
    ranking = fopen("ranking.bin", "rb");

    if (ranking == NULL) {
        printf("O ranking ainda não possui nenhum usuário cadastrado!\n");
        return;
    }

    char nickexistente[MAX_NICK];
    int pontuacaoexistente;

    system(CLEAR);

    printf("%-10s%-20s%-10s", "Posicao", "Nickname", "Pontuacao");
    printf("\n");

    int pos = 1;
    while (fread(nickexistente, sizeof(char), MAX_NICK, ranking) == MAX_NICK) {
        fread(&pontuacaoexistente, sizeof(int), 1, ranking);

        printf("%-10d", pos);
        printf("%-20s", nickexistente);
        printf("%-10d", pontuacaoexistente);
    }
}

// LOOP PRINCIPAL DO JOGO, determina o funcionamento da opção de JOGAR
void MAINLOOP() {
    while (1) {
        system(CLEAR);
        int Movimento = 1;

        printarmatriz(MATRIZPRINCIPAL, ColunaAtual, MAIORCOLUNA);
        printf("Digite a coluna origem: ");
        int posInicial;
        scanf("%d", &posInicial);
        printf("Digite a coluna destino: ");
        int posFinal;
        scanf("%d", &posFinal);

        // checar qual o caractere da posição inicial
        int flag = 0, linhaInicio, MaxTransferidos = 0;
        char aux;
        for (int i = MAIORCOLUNA; i < 10; i++) {
            if (M[i][posInicial] != '0' && flag == 0) {
                aux = M[i][posInicial];
                linhaInicio = i;
                flag++;
                MaxTransferidos++;
            } else if (M[i][posInicial] == aux) {
                MaxTransferidos++;
            }
        }
        flag = 0;

        // checa quantos espaços estão disponíveis na coluna de destino
        int espacoDisponivel = 0, linhaFinal;
        for (int i = 10-MAIORCOLUNA-1; i < 10; i++) { // exemplo, se a maior coluna for 3, ele começa no 10-3-1, ou seja, no 6+3 = 9, o máximo índice é 9
            if (M[i][posFinal] == '0') {
                espacoDisponivel++;
            } else {
                linhaFinal = i;
                if (M[i][posFinal] == aux) {
                    printf("Esse movimento foi autorizado!\n");
                }
                else {
                    printf("Você não pode fazer esse movimento!\n");
                    Movimento = 0;
                }
                break;
            }
        }

        // checar quantos vao ser transferidos ao destino
        int Tranferencia;
        if (MaxTransferidos<espacoDisponivel) {
            Tranferencia = MaxTransferidos;
        }
        else {
            Tranferencia = espacoDisponivel;
        }

        // checar se o movimento pode ocorrer
        for (int i = linhaFinal-Tranferencia; i <= linhaFinal; i++) {
            if (M[i][posFinal] == '0') {
                M[i-1][posFinal] = aux;
                M[linhaInicio][posInicial] = '0';
            }
            linhaInicio++;
        }
    }
}

// SEGUNDO LOOP PRINCIPAL DO JOGO, determina o funcionamento geral
int main() {
    if (sair()) {
        break;
    }
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

    printf("\033[0;36m\n\n\n* * * \033[0m");
    printf("Bem vindo(a) ao Jogo Ball Sort de APC!!");
    printf("\033[0;36m * * *\n\n\n\033[0m");
    printf("Digite seu");
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
        fwrite(pontuacao, sizeof(int), 1, ranking);
    }
    
    menu();

    return 0;
}