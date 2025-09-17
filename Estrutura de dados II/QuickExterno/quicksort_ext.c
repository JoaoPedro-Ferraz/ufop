#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glob.h>   
#include <unistd.h> 
#include "quicksort_ext.h"
#include "leitura.h"
#include "metrica.h"
#include "registro.h"

#define MAX_MEMORIA 20

int contador_recursao = 0;

void limpar_arquivos_temporarios() {
    glob_t globbuf;
    int ret = glob("tmp_quick_*.txt", 0, NULL, &globbuf);
    
    if (ret == 0) {
        for (size_t i = 0; i < globbuf.gl_pathc; i++) {
            unlink(globbuf.gl_pathv[i]);
        }
        globfree(&globbuf);
    }
}

void troca(Registro *a, Registro *b, Metricas *stats) {
    Registro temp = *a;
    *a = *b;
    *b = temp;
    contar_comparacao(stats);
}

float selecionar_pivo(char *arquivo, int situacao, Metricas *stats) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo para seleção de pivô");
        return -1;
    }

    Registro memoria[MAX_MEMORIA];
    char linha[200];
    int lidos = 0;

    while (fgets(linha, sizeof(linha), fp) && lidos < MAX_MEMORIA) {
        memoria[lidos++] = lerRegistroLinha(linha);
        contar_leitura(stats);
    }

    fclose(fp);

    for (int i = 0; i < lidos - 1; i++) {
        for (int j = i + 1; j < lidos; j++) {
            contar_comparacao(stats);
            if (memoria[i].nota > memoria[j].nota) {
                troca(&memoria[i], &memoria[j], stats);
            }
        }
    }

    return memoria[lidos / 2].nota;
}

void particionar_arquivo(char *arquivo_entrada, char *arquivo_menores, char *arquivo_maiores, float pivo, Metricas* stats) {
    FILE *entrada = fopen(arquivo_entrada, "r");
    FILE *menores = fopen(arquivo_menores, "w");
    FILE *maiores = fopen(arquivo_maiores, "w");

    if (!entrada || !menores || !maiores) {
        perror("Erro ao abrir arquivos para particionamento");
        if (entrada) fclose(entrada);
        if (menores) fclose(menores);
        if (maiores) fclose(maiores);
        return;
    }

    char linha[200];
    while (fgets(linha, sizeof(linha), entrada)) {
        Registro reg = lerRegistroLinha(linha);
        contar_leitura(stats);
        contar_comparacao(stats);

        if (reg.nota <= pivo) {
            fprintf(menores, "%08ld %05.1f %s %-50s %-30s\n",
                    reg.id, reg.nota, reg.estado, reg.cidade, reg.curso);
            contar_escrita(stats);
        } else {
            fprintf(maiores, "%08ld %05.1f %s %-50s %-30s\n",
                    reg.id, reg.nota, reg.estado, reg.cidade, reg.curso);
            contar_escrita(stats);
        }
    }

    fclose(entrada);
    fclose(menores);
    fclose(maiores);
}

void mesclar_arquivos(char *arquivo_saida, char *arquivo1, char *arquivo2, int situacao, Metricas *stats) {
    FILE *fp1 = fopen(arquivo1, "r");
    FILE *fp2 = fopen(arquivo2, "r");
    FILE *saida = fopen(arquivo_saida, "w");

    if (!fp1 || !fp2 || !saida) {
        perror("Erro ao abrir arquivos para mesclagem");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        if (saida) fclose(saida);
        return;
    }

    char linha1[200], linha2[200];
    int tem1 = fgets(linha1, sizeof(linha1), fp1) != NULL;
    int tem2 = fgets(linha2, sizeof(linha2), fp2) != NULL;

    Registro r1, r2;
    if (tem1) {
        r1 = lerRegistroLinha(linha1);
        contar_leitura(stats);
    }
    if (tem2) {
        r2 = lerRegistroLinha(linha2);
        contar_leitura(stats);
    }

    while (tem1 && tem2) {
        contar_comparacao(stats);
        if (r1.nota <= r2.nota) {
            fprintf(saida, "%08ld %05.1f %s %-50s %-30s\n", r1.id, r1.nota, r1.estado, r1.cidade, r1.curso);
            contar_escrita(stats);
            tem1 = fgets(linha1, sizeof(linha1), fp1) != NULL;
            if (tem1) {
                r1 = lerRegistroLinha(linha1);
                contar_leitura(stats);
            }
        } else {
            fprintf(saida, "%08ld %05.1f %s %-50s %-30s\n", r2.id, r2.nota, r2.estado, r2.cidade, r2.curso);
            contar_escrita(stats);
            tem2 = fgets(linha2, sizeof(linha2), fp2) != NULL;
            if (tem2) {
                r2 = lerRegistroLinha(linha2);
                contar_leitura(stats);
            }
        }
    }

    while (tem1) {
        fprintf(saida, "%08ld %05.1f %s %-50s %-30s\n", r1.id, r1.nota, r1.estado, r1.cidade, r1.curso);
        contar_escrita(stats);
        tem1 = fgets(linha1, sizeof(linha1), fp1) != NULL;
        if (tem1) {
            r1 = lerRegistroLinha(linha1);
            contar_leitura(stats);
        }
    }

    while (tem2) {
        fprintf(saida, "%08ld %05.1f %s %-50s %-30s\n", r2.id, r2.nota, r2.estado, r2.cidade, r2.curso);
        contar_escrita(stats);
        tem2 = fgets(linha2, sizeof(linha2), fp2) != NULL;
        if (tem2) {
            r2 = lerRegistroLinha(linha2);
            contar_leitura(stats);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(saida);
}

void quicksort_externo_recursivo(char *arquivo, int situacao, Metricas *stats) {
    int n = contar_registros(arquivo);
    if (n <= 1) return;

    char arq_menores[50], arq_maiores[50];
    sprintf(arq_menores, "tmp_quick_menores_%d.txt", contador_recursao);
    sprintf(arq_maiores, "tmp_quick_maiores_%d.txt", contador_recursao);
    contador_recursao++;

    float pivo = selecionar_pivo(arquivo, situacao, stats);
    particionar_arquivo(arquivo, arq_menores, arq_maiores, pivo, stats);

    int qtd_menores = contar_registros(arq_menores);
    int qtd_maiores = contar_registros(arq_maiores);
    if (qtd_menores == 0 || qtd_maiores == 0) return;

    quicksort_externo_recursivo(arq_menores, situacao, stats);
    quicksort_externo_recursivo(arq_maiores, situacao, stats);

    mesclar_arquivos(arquivo, arq_menores, arq_maiores, situacao, stats);
}

void quicksort_externo(char *arquivo, int quantidade, int situacao, int imprime) {
    limpar_arquivos_temporarios();

    Metricas stats;
    iniciar_metricas(&stats);

    
    char arquivo_temp[] = "saida_quick.txt";

    
    Registro *vetor = malloc(sizeof(Registro) * quantidade);
    if (!vetor) {
        fprintf(stderr, "Erro ao alocar vetor\n");
        return;
    }

    int lidos = carregarRegistros(arquivo, vetor, quantidade);
    if (lidos == 0) {
        fprintf(stderr, "Nenhum registro lido. Abortando.\n");
        free(vetor);
        return;
    }
    if (lidos < quantidade) {
        fprintf(stderr, "Apenas %d registros foram lidos.\n", lidos);
    }

    salvarRegistros(arquivo_temp, vetor, lidos);
    contar_escrita(&stats);  
    free(vetor);

    
    quicksort_externo_recursivo(arquivo_temp, situacao, &stats);

    finalizar_metricas(&stats);

    
    if (imprime > 0) {
        printf("\nRegistros ordenados:\n");
        FILE *fp = fopen(arquivo_temp, "r");
        if (fp) {
            char linha[200];
            while (fgets(linha, sizeof(linha), fp)) {
                Registro r = lerRegistroLinha(linha);
                print_registro(&r);
            }
            fclose(fp);
        } else {
            fprintf(stderr, "Erro ao abrir %s para impressão\n", arquivo_temp);
        }
    }

    
    const char *situacao_txt = (situacao == 1) ? "Ascendente" :
                               (situacao == 2) ? "Descendente" : "Aleatório";

    printf("\n==> MÉTRICAS (QuickSort Externo - %s - %d registros)\n", situacao_txt, quantidade);
    imprimir_metricas(&stats);

    
    

    limpar_arquivos_temporarios();
}
