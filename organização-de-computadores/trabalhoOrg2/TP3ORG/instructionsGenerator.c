//Gerador de instruções feito por Luísa Calegari, Thiago Cecote e Josué Vila Real
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_INST 10000  // Número de instruções geradas
#define N_FOR 5       // Número de instruções que vão se repetir
#define N_MEM 1000    // Tamanho da memória para o endereço do bloco
#define N_PROB 90     // Probabilidade de repetição
#define N_OPCODE 4    // Número máximo de opcodes (0, 1, 2, 3)
#define N_WORD 4      // Número de palavras no bloco

int rep[5][7];  // Repetição de instruções
int inst[10001][7];  // Armazena as instruções (incluso espaço para o opcode -1)

void instGenerator();

int main() {
    instGenerator();
    return 0;
}

void instGenerator() {
    FILE *arquivo = fopen("instructions2.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};
    srand(time(NULL));

    // Gerando instruções de repetição
    for (int i = 0; i < N_FOR; i++) {
        random = rand() % N_OPCODE;
        rep[i][0] = random;
        for (int j = 1; j <= instruc[random]; j += 2) {
            rep[i][j] = rand() % N_MEM;
            rep[i][j + 1] = rand() % N_WORD;
        }
    }

    // Gerando as instruções
    for (int i = 0; i < N_INST;) {
        random = (rand() % 100) + 1;
        if (random <= N_PROB && i + N_FOR < N_INST) {
            for (int j = 0; j < N_FOR; j++) {
                for (int k = 0; k < 7; k++) {
                    inst[i + j][k] = rep[j][k];
                }
            }
            i += N_FOR;
        } else {
            random = rand() % N_OPCODE;
            inst[i][0] = random;
            for (int j = 1; j <= instruc[random]; j += 2) {
                inst[i][j] = rand() % N_MEM;
                inst[i][j + 1] = rand() % N_WORD;
            }
            i++;
        }
    }

    // Adiciona a instrução final com opcode -1
    inst[N_INST][0] = -1;  // Opcode de término
    for (int j = 1; j < 7; j++) {
        inst[N_INST][j] = 0;  // Zera os demais campos
    }

    // Escrevendo as instruções no arquivo
    for (int i = 0; i <= N_INST; i++) {  // Inclui a última instrução
        for (int k = 0; k < 6; k++) {
            fprintf(arquivo, "%d:", inst[i][k]);
        }
        fprintf(arquivo, "%d\n", inst[i][6]);
    }

    fclose(arquivo);
    printf("Instruções geradas com sucesso em 'instructions2.txt'.\n");
}
