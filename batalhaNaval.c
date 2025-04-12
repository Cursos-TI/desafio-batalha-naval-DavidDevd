#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define CODIGO_NAVIO 3
#define CODIGO_AGUA 0

// Função para imprimir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio está dentro dos limites e se há sobreposição
int podePosicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : (direcao == 'D' ? i : (direcao == 'E' ? -i : 0)));
        int c = coluna + (direcao == 'H' ? i : (direcao == 'D' ? i : (direcao == 'E' ? i : 0)));

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;
        if (tabuleiro[l][c] != CODIGO_AGUA)
            return 0;
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : (direcao == 'D' ? i : (direcao == 'E' ? -i : 0)));
        int c = coluna + (direcao == 'H' ? i : (direcao == 'D' ? i : (direcao == 'E' ? i : 0)));
        tabuleiro[l][c] = CODIGO_NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = CODIGO_AGUA;
        }
    }

    // Navio 1 - horizontal
    if (podePosicionar(tabuleiro, 2, 3, 'H')) {
        posicionarNavio(tabuleiro, 2, 3, 'H');
    } else {
        printf("Erro: Navio horizontal inválido.\n");
        return 1;
    }

    // Navio 2 - vertical
    if (podePosicionar(tabuleiro, 5, 6, 'V')) {
        posicionarNavio(tabuleiro, 5, 6, 'V');
    } else {
        printf("Erro: Navio vertical inválido.\n");
        return 1;
    }

    // Navio 3 - diagonal principal (↘)
    if (podePosicionar(tabuleiro, 0, 0, 'D')) {
        posicionarNavio(tabuleiro, 0, 0, 'D');
    } else {
        printf("Erro: Navio diagonal principal inválido.\n");
        return 1;
    }

    // Navio 4 - diagonal secundária (↙)
    if (podePosicionar(tabuleiro, 9, 0, 'E')) {
        posicionarNavio(tabuleiro, 9, 0, 'E');
    } else {
        printf("Erro: Navio diagonal secundária inválido.\n");
        return 1;
    }

    exibirTabuleiro(tabuleiro);
    return 0;
}
