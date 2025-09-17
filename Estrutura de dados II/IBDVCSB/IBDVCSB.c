#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IBDVCSB.h"
#include "leituraArquivoSB.h"
#include "heap.h"

extern long long leituras, escritas, comparacoes;

#define FITAS 20
static char nomesFitas[2 * FITAS][20];

static void inicializaNomesFitas() {
    for (int i = 0; i < 2 * FITAS; i++) {
        sprintf(nomesFitas[i], "fita%d.txt", i + 1);
    }
}

static void copiaArquivo(const char *origem, const char *destino) {
    FILE *fo = fopen(origem, "r");
    FILE *fd = fopen(destino, "w");
    verificacaoAberturaSB(fo);
    verificacaoAberturaSB(fd);

    char buf[1024];
    while (fgets(buf, sizeof(buf), fo) != NULL) {
        fputs(buf, fd);
    }
    fclose(fo);
    fclose(fd);
}


static int faseIntercalacaoSB(char entradas[FITAS][20], char saidas[FITAS][20], int bloco) {
    FILE *fIn[FITAS], *fOut[FITAS];
    for (int i = 0; i < FITAS; i++) {
        fIn[i] = fopen(entradas[i], "r");
        verificacaoAberturaSB(fIn[i]);
        fOut[i] = fopen(saidas[i], "w");
        verificacaoAberturaSB(fOut[i]);
    }

    int totalRuns = 0;
    Aluno *runs[FITAS];
    int tam[FITAS], idx[FITAS];

    for (int i = 0; i < FITAS; i++) {
        runs[i] = malloc(sizeof(Aluno) * bloco);
        idx[i] = 0;
        tam[i] = 0;
    }

    int fitaOutAtual = 0;

    while (1) {
        
        int vazias = 0;
        for (int i = 0; i < FITAS; i++) {
            idx[i] = 0;
            tam[i] = 0;
            while (tam[i] < bloco && readAlunoLineSB(fIn[i], &runs[i][tam[i]])) {
                leituras++;
                tam[i]++;
            }
            if (tam[i] == 0) vazias++;
        }
        if (vazias == FITAS) break; 

        totalRuns++;

        
        while (1) {
            int menorFita = -1;
            for (int i = 0; i < FITAS; i++) {
                if (idx[i] < tam[i]) {
                    if (menorFita == -1 || cmpAlunoRunSB(&runs[i][idx[i]], &runs[menorFita][idx[menorFita]]) < 0) {
                        menorFita = i;
                    }
                }
            }
            if (menorFita == -1) break; 
            escreveAlunoSB(fOut[fitaOutAtual], &runs[menorFita][idx[menorFita]++]);
        }

        fitaOutAtual = (fitaOutAtual + 1) % FITAS;
    }

    for (int i = 0; i < FITAS; i++) {
        free(runs[i]);
        fclose(fIn[i]);
        fclose(fOut[i]);
    }
    return totalRuns;
}


void startIntercalacaoSelSub(char *arquivo, int quantidade) {
    inicializaNomesFitas();

    FILE *fR = fopen(arquivo, "r");
    verificacaoAberturaSB(fR);

    FILE *fOut[FITAS];
    for (int i = 0; i < FITAS; i++) {
        fOut[i] = fopen(nomesFitas[i], "w");
        verificacaoAberturaSB(fOut[i]);
    }

    int fitaAtual = 0;
    HeapItem *heap = malloc(sizeof(HeapItem) * memorysize);
    int heapSize = 0;

    while (heapSize < memorysize && quantidade > 0) {
        if (!readAlunoLineSB(fR, &heap[heapSize].dado)) break;
        leituras++;
        heap[heapSize].ativo = 1;
        heapSize++;
        quantidade--;
    }
    constroiHeap(heap, heapSize);

    int ativos = heapSize;
    Aluno ultimoEscrito;

    while (heapSize > 0) {
        HeapItem menor = heap[0];
        heap[0] = heap[heapSize - 1];
        heapSize--;
        heapify(heap, heapSize, 0);

        escreveAlunoSB(fOut[fitaAtual], &menor.dado);
        ultimoEscrito = menor.dado;

        if (quantidade > 0) {
            Aluno novo;
            if (readAlunoLineSB(fR, &novo)) {
                leituras++;
                quantidade--;
                int ativoNovo = (cmpAlunoRunSB(&novo, &ultimoEscrito) >= 0) ? 1 : 0;
                HeapItem itemNovo = { novo, ativoNovo };
                heap[heapSize] = itemNovo;
                heapSize++;
                heapify(heap, heapSize, 0);
                if (!ativoNovo) ativos--;
            }
        }

        if (ativos == 0) {
            fitaAtual = (fitaAtual + 1) % FITAS;
            for (int i = 0; i < heapSize; i++) heap[i].ativo = 1;
            ativos = heapSize;
        }
    }

    free(heap);
    for (int i = 0; i < FITAS; i++) fclose(fOut[i]);
    fclose(fR);

    
    int bloco = memorysize;
    char entradas[FITAS][20], saidas[FITAS][20];
    for (int i = 0; i < FITAS; i++) strcpy(entradas[i], nomesFitas[i]);
    for (int i = 0; i < FITAS; i++) strcpy(saidas[i], nomesFitas[i + FITAS]);

    while (1) {
        int runs = faseIntercalacaoSB(entradas, saidas, bloco);
        if (runs <= 1) {
            copiaArquivo(saidas[0], "resultado.txt");
            break;
        }
        for (int i = 0; i < FITAS; i++) {
            char tmp[20];
            strcpy(tmp, entradas[i]);
            strcpy(entradas[i], saidas[i]);
            strcpy(saidas[i], tmp);
        }
        bloco *= 2;
    }
}
