#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "leitura.h"

#define LINHA_TAM_MAX 200


void trim(char *str) {
    
    char *inicio = str;
    while (*inicio == ' ') inicio++;

    
    char *fim = inicio + strlen(inicio) - 1;
    while (fim > inicio && (*fim == ' ' || *fim == '\n' || *fim == '\r')) {
        *fim = '\0';
        fim--;
    }

    
    if (inicio != str)
        memmove(str, inicio, strlen(inicio) + 1);
}

int carregarRegistros(const char *nomeArquivo, Registro *vetor, int n) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 0;
    }

    char linha[LINHA_TAM_MAX];
    int count = 0;

    while (fgets(linha, sizeof(linha), fp) && count < n) {
        vetor[count++] = lerRegistroLinha(linha);
    }

    fclose(fp);
    return count;
}

void salvarRegistros(const char *nomeArquivo, Registro *vetor, int n) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%08ld %05.1f %s %-50s %-30s\n",
                vetor[i].id,
                vetor[i].nota,
                vetor[i].estado,
                vetor[i].cidade,
                vetor[i].curso);
    }

    fclose(fp);
}

void gerarArquivoOrdenado(const char *entrada, const char *saida, int n, int modo) {
    Registro *vetor = malloc(n * sizeof(Registro));
    if (!vetor) {
        fprintf(stderr, "Erro de alocação de memória\n");
        return;
    }

    int lidos = carregarRegistros(entrada, vetor, n);
    if (lidos < n) {
        fprintf(stderr, "Apenas %d registros foram lidos\n", lidos);
    }

    if (modo == 1) {
        
        qsort(vetor, lidos, sizeof(Registro), compararNota);
    } else if (modo == 2) {
        
        qsort(vetor, lidos, sizeof(Registro), compararNota);
        
        for (int i = 0; i < lidos / 2; i++) {
            Registro temp = vetor[i];
            vetor[i] = vetor[lidos - i - 1];
            vetor[lidos - i - 1] = temp;
        }
    } else if (modo == 3) {
        
        srand(time(NULL));
        for (int i = lidos - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Registro temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    salvarRegistros(saida, vetor, lidos);
    free(vetor);
}

int contar_registros(char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo para contagem de registros");
        return 0;
    }

    char linha[LINHA_TAM_MAX];
    int count = 0;

    while (fgets(linha, sizeof(linha), fp)) {
        count++;
    }

    fclose(fp);
    return count;
}