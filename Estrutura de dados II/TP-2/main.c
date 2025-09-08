#define _POSIX_C_SOURCE 199309L //Funcao para calculo de temp (execucao)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "leituraArquivo.h"

#include "IBDVC.h"

int main(int argc, char *argv[]) {
    // Verificação quantidade de argumentos
    if (argc != 2) {
        printf("Quantidade de argumentos invalida!\n");
        exit(EXIT_FAILURE);
    }

    struct timespec t_inicio, t_fim; // Variáveis para armazenar o tempo

    // Marca o tempo inicial
    clock_gettime(CLOCK_MONOTONIC, &t_inicio);

    // Executa a intercalação
    startIntercalacao(argv[1]);

    // Marca o tempo final
    clock_gettime(CLOCK_MONOTONIC,&t_fim);

    // Calcula o tempo decorrido em segundos e nanossegundos
    unsigned long long inicio_ns = t_inicio.tv_sec * 1000000000ULL + t_inicio.tv_nsec;
    unsigned long long fim_ns    = t_fim.tv_sec    * 1000000000ULL + t_fim.tv_nsec;
    unsigned long long tempo_ns  = fim_ns - inicio_ns;

    // Mostra o tempo total em segundos com casas decimais
    printf("Tempo total de execucao: %.6f segundos\n", tempo_ns / 1e9);

    return 0;
}