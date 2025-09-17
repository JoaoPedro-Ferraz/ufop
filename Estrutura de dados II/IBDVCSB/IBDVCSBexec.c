#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "leituraArquivoSB.h"
#include "IBDVCSB.h"

long long leituras = 0;
long long escritas = 0;
long long comparacoes = 0;

void imprimeArquivo(const char *nomeArquivo, int quantidade) {
    FILE *f = fopen(nomeArquivo, "r");
    verificacaoAberturaSB(f);
    Aluno a;
    int lidos = 0;
    while (lidos < quantidade && readAlunoLineSB(f, &a)) {
        printf("%-8s %05.1f %-2s %-50s %-30s\n",
               a.inscricao, a.nota, a.estado, a.cidade, a.curso);
        lidos++;
    }
    fclose(f);
}

int executaIBDVCSB(int quantidade, int imprimir, char *arquivo) {
    clock_t inicio = clock();
    startIntercalacaoSelSub(arquivo, quantidade);
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("\nTempo de execução: %.3f segundos\n", tempo);
    printf("Leituras: %lld\n", leituras);
    printf("Escritas: %lld\n", escritas);
    printf("Comparações: %lld\n", comparacoes);

    if(imprimir == 1)
        imprimeArquivo("resultado.txt", quantidade);
    return 0;
}