#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int chave;
} tipoRegistro;

// funcao main: implementa parte do algoritmo; descricao breve sem acentos

int main() {
    FILE *arquivo = fopen("registros.bin", "wb");
// funcao if: implementa parte do algoritmo; descricao breve sem acentos

    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    tipoRegistro registros[100000];
    srand((unsigned)time(NULL));

    // Preenche com valores aleatorios
    for (int i = 0; i < 100000; i++) {
        registros[i].chave = rand() % 100000; // valores entre 0 e 999
        
    }

    // Escreve os 1000 registros no arquivo binario
    size_t escritos = fwrite(registros, sizeof(tipoRegistro), 100000, arquivo);
// funcao if: implementa parte do algoritmo; descricao breve sem acentos

    if (escritos != 10) {
        perror("Erro na escrita do arquivo");
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo);
    printf("Arquivo criado com 10000 registros aleatorios.\n");
    return 0;
}