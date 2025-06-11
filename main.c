#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_HABILIDADE 5

// Função para inicializar o tabuleiro com água e alguns navios
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // água
        }
    }

    // Exemplo de navios (valor 3)
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[2][4] = 3;
    tabuleiro[5][5] = 3;
    tabuleiro[5][6] = 3;
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Cria a matriz de habilidade em forma de cone
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= TAM_HABILIDADE / 2 - i && j <= TAM_HABILIDADE / 2 + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade em forma de cruz
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria a matriz de habilidade em forma de octaedro (losango)
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Sobrepõe uma matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemX, int origemY) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int tabX = origemX + (i - offset);
            int tabY = origemY + (j - offset);

            // Verifica se está dentro dos limites do tabuleiro
            if (tabX >= 0 && tabX < TAM_TABULEIRO && tabY >= 0 && tabY < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[tabX][tabY] != 3) {
                    tabuleiro[tabX][tabY] = 5; // marca como área afetada
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    int habilidade[TAM_HABILIDADE][TAM_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    // Aplicar habilidade Cone
    criarCone(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 3, 3); // origem no tabuleiro
    printf("Tabuleiro com habilidade Cone:\n");
    exibirTabuleiro(tabuleiro);

    // Reconfigura tabuleiro e aplica Cruz
    inicializarTabuleiro(tabuleiro);
    criarCruz(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 5, 5);
    printf("Tabuleiro com habilidade Cruz:\n");
    exibirTabuleiro(tabuleiro);

    // Reconfigura tabuleiro e aplica Octaedro
    inicializarTabuleiro(tabuleiro);
    criarOctaedro(habilidade);
    aplicarHabilidade(tabuleiro, habilidade, 6, 6);
    printf("Tabuleiro com habilidade Octaedro:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
