#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define CODIGO_NAVIO 3
#define CODIGO_AGUA 0
#define CODIGO_HABILIDADE 5
#define TAMANHO_HABILIDADE 5

// Função para exibir o tabuleiro com símbolos
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("=== TABULEIRO ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == CODIGO_AGUA) printf("~ ");
            else if (tabuleiro[i][j] == CODIGO_NAVIO) printf("N ");
            else if (tabuleiro[i][j] == CODIGO_HABILIDADE) printf("* ");
        }
        printf("\n");
    }
}

// Cria matriz de habilidade em formato de cone
void criarHabilidadeCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int meio = TAMANHO_HABILIDADE / 2;
            matriz[i][j] = (j >= meio - i && j <= meio + i) ? 1 : 0;
        }
    }
}

// Cria matriz de habilidade em formato de cruz
void criarHabilidadeCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (i == meio || j == meio) ? 1 : 0;
        }
    }
}

// Cria matriz de habilidade em formato de octaedro (losango)
void criarHabilidadeOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = (abs(meio - i) + abs(meio - j) <= meio) ? 1 : 0;
        }
    }
}

// Sobrepõe uma matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int meio = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linhaTab = origemLinha - meio + i;
            int colTab = origemColuna - meio + j;
            if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO &&
                colTab >= 0 && colTab < TAMANHO_TABULEIRO &&
                habilidade[i][j] == 1 && tabuleiro[linhaTab][colTab] == CODIGO_AGUA) {
                tabuleiro[linhaTab][colTab] = CODIGO_HABILIDADE;
            }
        }
    }
}

// Posicionamento de navio com verificação
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

void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : (direcao == 'D' ? i : (direcao == 'E' ? -i : 0)));
        int c = coluna + (direcao == 'H' ? i : (direcao == 'D' ? i : (direcao == 'E' ? i : 0)));
        tabuleiro[l][c] = CODIGO_NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Inicializa tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = CODIGO_AGUA;
        }
    }

    // Posiciona navios
    if (podePosicionar(tabuleiro, 2, 3, 'H')) posicionarNavio(tabuleiro, 2, 3, 'H');
    if (podePosicionar(tabuleiro, 5, 6, 'V')) posicionarNavio(tabuleiro, 5, 6, 'V');
    if (podePosicionar(tabuleiro, 0, 0, 'D')) posicionarNavio(tabuleiro, 0, 0, 'D');
    if (podePosicionar(tabuleiro, 9, 0, 'E')) posicionarNavio(tabuleiro, 9, 0, 'E');

    // Cria matrizes de habilidade
    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Aplica habilidades no tabuleiro em pontos fixos
    aplicarHabilidade(tabuleiro, cone, 1, 5);
    aplicarHabilidade(tabuleiro, cruz, 7, 3);
    aplicarHabilidade(tabuleiro, octaedro, 6, 8);

    exibirTabuleiro(tabuleiro);
    return 0;
}

