#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IBDVC.h"
#include "leituraArquivo.h"
#include "ordenacao.h"

static char nomesFitas[NUM_FITAS][16];


void startIntercalacao(char *arquivo, int *leitura, int *escrita, int *comparacoes) {
    FILE *fR = fopen(arquivo, "r");
    verificacaoAbertura(fR);

    
    for (int i = 0; i < NUM_FITAS; i++) {
        snprintf(nomesFitas[i], sizeof(nomesFitas[i]), "fita%d.txt", i+1);
    }

    int metade = NUM_FITAS / 2; 

    
    FILE *fPrimeiras[metade];
    for (int i = 0; i < metade; i++) {
        fPrimeiras[i] = fopen(nomesFitas[i], "w");
        verificacaoAbertura(fPrimeiras[i]);
    }

    
    Aluno *alunos = (Aluno *) malloc(sizeof(Aluno) * memorysize);
    if (!alunos) {
        for (int i = 0; i < metade; i++) if (fPrimeiras[i]) fclose(fPrimeiras[i]); 
        fclose(fR);
        return;
    }
    
    int contadorBlocos = 0;
    while (true) {
        int qnt = leituraDados(fR, alunos, leitura); 
        if (qnt == 0) break; 
        quickSort(alunos, qnt, comparacoes);
        
        int indice = contadorBlocos % metade; 
        for (int i = 0; i < qnt; i++) escreveAluno(fPrimeiras[indice], &alunos[i], escrita);
        contadorBlocos++;
    }

    free(alunos);
    for (int i = 0; i < metade; i++) fclose(fPrimeiras[i]);
    fclose(fR);

    int bloco = memorysize; 

    
    char *origens[metade];
    char *destinos[metade];

    
    for (int i = 0; i < metade; i++) {
        origens[i] = nomesFitas[i];
        destinos[i] = nomesFitas[i + metade];
    }

    while (true) {
        int runs = faseIntercalacaoList(origens, destinos, metade, bloco, leitura, escrita, comparacoes);
        
        if (runs == 0) {
            
            FILE *f = fopen(nomesFitas[0], "w");
            if (f) fclose(f);
            break;
        }
        
        if (runs == 1) {
            
            if (strcmp(destinos[0], nomesFitas[0]) != 0) {
                copiaArquivo(destinos[0], nomesFitas[0]);
            }
            break;
        }

        
        for (int i = 0; i < metade; i++) {
            char *tmp = origens[i];
            origens[i] = destinos[i];
            destinos[i] = tmp;
        }

        bloco *= 2;
    }
}

int faseIntercalacaoList(char **origens, char **destinos, int k, int bloco, int *leitura, int *escrita, int *comparacoes) {
    
    FILE *arquivosDestino[k];
    for (int i = 0; i < k; i++) {
        arquivosDestino[i] = fopen(destinos[i], "w");
        verificacaoAbertura(arquivosDestino[i]);
    }

    int indiceDestino = 0;
    int totalDeRuns = 0;

    
    for (int s = 0; s < k; s += 2) {
        FILE *fitaA = fopen(origens[s], "r");
        FILE *fitaB = fopen(origens[s+1], "r");
        if (!fitaA && !fitaB) continue;
        verificacaoAbertura(fitaA);
        verificacaoAbertura(fitaB);

        while (true) {
            
            Aluno alunoA, alunoB;
            int temA = 0, temB = 0;
            int contA = 0, contB = 0;

            
            if (contA < bloco) {
                if (readAlunoLine(fitaA, &alunoA, leitura)) {
                    temA = 1;
                    contA = 1;
                }
            }

            
            if (contB < bloco) {
                if (readAlunoLine(fitaB, &alunoB, leitura)) {
                    temB = 1;
                    contB = 1;
                }
            }

            
            if (!temA && !temB) break;

            
            FILE *saidaAtual = arquivosDestino[indiceDestino];
            indiceDestino = (indiceDestino + 1) % k;
            totalDeRuns++;

            
            while (temA || temB) {
                if (!temA) {
                    
                    escreveAluno(saidaAtual, &alunoB, escrita);
                    temB = 0;
                    if (contB < bloco && readAlunoLine(fitaB, &alunoB, leitura)) {
                        temB = 1;
                        contB++;
                    }
                } else if (!temB) {
                    
                    escreveAluno(saidaAtual, &alunoA, escrita);
                    temA = 0;
                    if (contA < bloco && readAlunoLine(fitaA, &alunoA, leitura)) {
                        temA = 1;
                        contA++;
                    }
                } else {
                    
                    (*comparacoes)++;
                    if (cmpAlunoRun(&alunoA, &alunoB) <= 0) {
                        escreveAluno(saidaAtual, &alunoA, escrita);
                        temA = 0;
                        if (contA < bloco && readAlunoLine(fitaA, &alunoA, leitura)) {
                            temA = 1;
                            contA++;
                        }
                    } else {
                        escreveAluno(saidaAtual, &alunoB, escrita);
                        temB = 0;
                        if (contB < bloco && readAlunoLine(fitaB, &alunoB, leitura)) {
                            temB = 1;
                            contB++;
                        }
                    }
                }
            }
            
        }

        fclose(fitaA);
        fclose(fitaB);
    }

    for (int i = 0; i < k; i++) {
        fclose(arquivosDestino[i]);
    }
    return totalDeRuns;
}



void copiaArquivo(char *origem, char *destino) {
    FILE *fo = fopen(origem, "r");
    FILE *fd = fopen(destino, "w");
    if (!fo || !fd) {
        if (fo) fclose(fo);
        if (fd) fclose(fd);
        return;
    }
    char buf[1024];
    while (fgets(buf, sizeof(buf), fo) != NULL) fputs(buf, fd);
    fclose(fo);
    fclose(fd);
}


int cmpAlunoRun(Aluno *a, Aluno *b) {
    if (a->nota < b->nota) return -1;
    if (a->nota > b->nota) return 1;
    return strcmp(a->inscricao, b->inscricao);
}
