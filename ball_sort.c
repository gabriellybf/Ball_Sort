#include <stdio.h>

int checagem(char M[][10]) {
    int veredito = 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j < 9 && M[j][i] != '0') {
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

void menu() {
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("\033[0;31mBem-vindo(a) ao Ball Sort!\033[0m\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("O que deseja fazer?\n");
    printf("1 - Jogar.\n");
    printf("2 - Ver pontuação.\n");
    printf("3 - Manual.\n");
}

void printarmatriz(char M[][10], int tam, int colunas) {
    for (int i = 10-tam; i < 10; i++) {
        for (int j = 0; j < colunas; j++) {
            /*if (i == 10) {
                printf("————— ");
            }*/
            /*else {*/
                printf("| ");
                if (M[i][j] == '0') {
                    printf(" ");
                }
                else {
                    printf("%c", M[i][j]);
                }
                if (j < colunas-1) {
                    printf(" | ");
                }
                else {
                    printf(" |");
                }
            /*}*/
        }
        printf("\n");
    }
}

int main() {
    int pontuacao = 0;
    char M[10][10]; 
    int tam;
    scanf("%d", &tam);
    int colunas = tam; 
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            M[i][j] = '0';
        }
    }
    for (int i = 10-tam; i < 10; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf(" %c", &M[i][j]);
        }
    }
    while (1) {
        printarmatriz(M, tam, colunas);
        int fimdejogo = checagem(M);
        printf("esse eh o fimdejogo %d\n", fimdejogo);
        if (fimdejogo == 1) {
            printf("Parabéns, você conluiu essa fase!\n");
            pontuacao++;
            printf("Sua pontuação é %d\n", pontuacao);
            break;
        }
        printf("Digite a coluna inicial: ");
        int posiinicial;
        scanf("%d", &posiinicial);
        printf("Digite a coluna final: ");
        int posifinal;
        scanf("%d", &posifinal);
        int flag = 0, linha;
        char aux;
        for (int i = 10-tam; i < 10; i++) {
            if (M[i][posiinicial] != '0' && flag == 0) {
                aux = M[i][posiinicial];
                linha = i;
                flag++;
            }
        }
        flag = 0;
        for (int i = 10-tam; i < 10; i++) {
            if (M[i][posifinal] != '0' && flag == 0) {
                if (M[i][posifinal] == aux && i > 0) {
                    M[i-1][posifinal] = aux;
                    printf("esse movimento foi autorizado!\n");
                    M[linha][posiinicial] = '0';
                    if (i == 10-tam) {
                        tam++;
                    }
                }
                else {
                    printf("você não pode fazer esse movimento!\n");
                }
                flag++;
                break;
            }
        }
    }
    return 0;
}