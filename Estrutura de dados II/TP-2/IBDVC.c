#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IBDVC.h"
#include "leituraArquivo.h"
#include "ordenacao.h"

static char nomesFitas[NUM_FITAS][16];

//---------- Inicio Intercalacao ----------//
void startIntercalacao(char *arquivo) {
    FILE *fR = fopen(arquivo, "r");
    verificacaoAbertura(fR);

    //prepara nomes das fitas
    for (int i = 0; i < NUM_FITAS; i++) {
        snprintf(nomesFitas[i], sizeof(nomesFitas[i]), "fita%d.txt", i+1);
    }

    int metade = NUM_FITAS / 2; //numero de fitas de origem /destino

    //abre as fitas de escrita iniciais
    FILE *fPrimeiras[metade];
    for (int i = 0; i < metade; i++) {
        fPrimeiras[i] = fopen(nomesFitas[i], "w");
        verificacaoAbertura(fPrimeiras[i]);
    }

    //Alocacao do vetor "Alunos" para leitura dos blocos
    Aluno *alunos = (Aluno *) malloc(sizeof(Aluno) * memorysize);
    if (!alunos) {
        for (int i = 0; i < metade; i++) if (fPrimeiras[i]) fclose(fPrimeiras[i]);
        fclose(fR);
        return;
    }
    //Preenche arquivos (Inicialmente ordenados)
    int contadorBlocos = 0;
    while (true) {
        int qnt = leituraDados(fR, alunos); // le até memorysize registros
        if (qnt == 0) break; //Nao houve leitura
        quickSort(alunos, qnt);
        // grava todo o bloco em uma fita 
        int indice = contadorBlocos % metade;
        for (int i = 0; i < qnt; i++) escreveAluno(fPrimeiras[indice], &alunos[i]);
        contadorBlocos++;
    }

    free(alunos);
    for (int i = 0; i < metade; i++) fclose(fPrimeiras[i]);
    fclose(fR);

    int bloco = memorysize;

    //Vetor de nomes para manipular trocas de papeis entre fases
    const char *origens[metade];
    const char *destinos[metade];

    for (int i = 0; i < metade; i++) {
        origens[i] = nomesFitas[i];
        destinos[i] = nomesFitas[i + metade];
    }

    while (true) {
        int runs = faseIntercalacaoList(origens, destinos, metade, bloco);
        //Nenhuma run feita
        if (runs == 0) {
            
            FILE *f = fopen(nomesFitas[0], "w");
            if (f) fclose(f);
            break;
        }
        //Uma run feita, copia dados (resultado) para fita 1
        if (runs == 1) {
            
            if (strcmp(destinos[0], nomesFitas[0]) != 0) {
                copiaArquivo(destinos[0], nomesFitas[0]);
            }
            break;
        }

        //Inversao dos papeis (Destino = Origem, Origem = Destino)
        for (int i = 0; i < metade; i++) {
            const char *tmp = origens[i];
            origens[i] = destinos[i];
            destinos[i] = tmp;
        }

        bloco *= 2;
    }
}

static int faseIntercalacaoList(const char **origens, const char **destinos, int k, int bloco) {
    //abre arquivos de destino 
    FILE *arquivosDestino[k];
    for (int i = 0; i < k; i++) {
        arquivosDestino[i] = fopen(destinos[i], "w");
        verificacaoAbertura(arquivosDestino[i]);
    }

    int indiceDestino = 0;
    int totalDeRuns = 0;

    //processa pares de fitas de origem
    for (int s = 0; s < k; s += 2) {
        FILE *fitaA = fopen(origens[s], "r");
        FILE *fitaB = fopen(origens[s+1], "r");
        if (!fitaA && !fitaB) continue;
        verificacaoAbertura(fitaA);
        verificacaoAbertura(fitaB);

        while (true) {
            //Inicia um novo run de cada fita
            Aluno alunoA, alunoB;
            int temA = 0, temB = 0;
            int contA = 0, contB = 0;

            //tenta ler um registro da fita A para iniciar o run
            if (contA < bloco) {
                if (readAlunoLine(fitaA, &alunoA)) {
                    temA = 1;
                    contA = 1;
                }
            }

            //tenta ler um registro da fita B para iniciar o run
            if (contB < bloco) {
                if (readAlunoLine(fitaB, &alunoB)) {
                    temB = 1;
                    contB = 1;
                }
            }

            //se ambas sem dados, acabou
            if (!temA && !temB) break;

            // escolhe destino para este run (round-robin entre arquivosDestino)
            FILE *saidaAtual = arquivosDestino[indiceDestino];
            indiceDestino = (indiceDestino + 1) % k;
            totalDeRuns++;

            //merge de ate bloco registros de cada run 
            while (temA || temB) {
                if (!temA) {
                    //apenas B remanescente
                    escreveAluno(saidaAtual, &alunoB);
                    temB = 0;
                    if (contB < bloco && readAlunoLine(fitaB, &alunoB)) {
                        temB = 1;
                        contB++;
                    }
                } else if (!temB) {
                    //apenas A remanescente
                    escreveAluno(saidaAtual, &alunoA);
                    temA = 0;
                    if (contA < bloco && readAlunoLine(fitaA, &alunoA)) {
                        temA = 1;
                        contA++;
                    }
                } else {
                    //comparar e escrever menor
                    if (cmpAlunoRun(&alunoA, &alunoB) <= 0) {
                        escreveAluno(saidaAtual, &alunoA);
                        temA = 0;
                        if (contA < bloco && readAlunoLine(fitaA, &alunoA)) {
                            temA = 1;
                            contA++;
                        }
                    } else {
                        escreveAluno(saidaAtual, &alunoB);
                        temB = 0;
                        if (contB < bloco && readAlunoLine(fitaB, &alunoB)) {
                            temB = 1;
                            contB++;
                        }
                    }
                }
            }
            //terminou um bloco mesclado 
        }

        fclose(fitaA);
        fclose(fitaB);
    }

    for (int i = 0; i < k; i++) {
        fclose(arquivosDestino[i]);
    }
    return totalDeRuns;
}

//---------- Funcoes Auxiliares ----------//
//Copia dados para uma fita especifica
static void copiaArquivo(const char *origem, const char *destino) {
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

//Compara nota, se empatar, verifica inscricao
static int cmpAlunoRun(const Aluno *a, const Aluno *b) {
    if (a->nota < b->nota) return -1;
    if (a->nota > b->nota) return 1;
    return strcmp(a->inscricao, b->inscricao);
}
