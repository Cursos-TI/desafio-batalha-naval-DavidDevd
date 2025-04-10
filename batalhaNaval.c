#include <stdio.h>

// Tamanho fixo do tabuleiro
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
        int l = linha + (direcao == 'V' ? i : 0);
        int c = coluna + (direcao == 'H' ? i : 0);

        // Verifica se está fora do tabuleiro
        if (l >= TAMANHO_TABULEIRO || c >= TAMANHO_TABULEIRO)
            return 0;

        // Verifica se já existe um navio na posição
        if (tabuleiro[l][c] != CODIGO_AGUA)
            return 0;
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : 0);
        int c = coluna + (direcao == 'H' ? i : 0);
        tabuleiro[l][c] = CODIGO_NAVIO;
    }
}

int main() {
    // Matriz que representa o tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todas as posições do tabuleiro com 0 (água)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = CODIGO_AGUA;
        }
    }

    // Coordenadas iniciais dos navios
    int linha1 = 2, coluna1 = 3; // Navio horizontal
    int linha2 = 5, coluna2 = 6; // Navio vertical

    // Posiciona o primeiro navio (horizontal)
    if (podePosicionar(tabuleiro, linha1, coluna1, 'H')) {
        posicionarNavio(tabuleiro, linha1, coluna1, 'H');
    } else {
        printf("Erro: Não foi possível posicionar o navio horizontal.\n");
        return 1;
    }

    // Posiciona o segundo navio (vertical)
    if (podePosicionar(tabuleiro, linha2, coluna2, 'V')) {
        posicionarNavio(tabuleiro, linha2, coluna2, 'V');
    } else {
        printf("Erro: Não foi possível posicionar o navio vertical.\n");
        return 1;
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

