#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_BLOCKS 1000  // Número de blocos de memória externa
#define N_WORDS 4      // Número de palavras por bloco

void gerarMemoriaExterna(const char *nomeArquivo);

int main() {
    gerarMemoriaExterna("memoria_externa.bin");
    return 0;
}

void gerarMemoriaExterna(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo binário.\n");
        return;
    }

    srand(time(NULL));
    int bloco[N_WORDS];  // Cada bloco tem N_WORDS palavras

    // Gerando blocos aleatórios
    for (int i = 0; i < N_BLOCKS; i++) {
        for (int j = 0; j < N_WORDS; j++) {
            bloco[j] = rand() % 1000;  // Valores aleatórios
        }
        fwrite(bloco, sizeof(int), N_WORDS, arquivo);
    }

    fclose(arquivo);
    printf("Memória externa gerada com sucesso em '%s'.\n", nomeArquivo);
}
