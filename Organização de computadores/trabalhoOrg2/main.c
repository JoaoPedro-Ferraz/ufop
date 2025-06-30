#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "ram.h"
#include "instrucao.h"

// Função para carregar instruções de um arquivo no formato correto
Instrucao *carregarInstrucoes(const char *nomeArquivo, int *numInstrucoes);

int menuCache()
{
    int aux;
    printf("\n");
    printf("---------------------------------------------------\n");
    printf("|  -1 - Fechar programa !                         |\n");
    printf("|  1 - Cache 1: 16 - Cache 2: 32 - Cache 3: 64 !  |\n");
    printf("|  2 - Cache 1: 32 - Cache 2: 64 - Cache 3: 128!  |\n");
    printf("|  3 - Cache 1: 16 - Cache 2: 64 - Cache 3: 256!  |\n");
    printf("|  4 - Cache 1: 8  - Cache 2: 32 - Cache 3: 128!  |\n");
    printf("|  5 - Digite o tamanho da propria memoria !      |\n");
    printf("---------------------------------------------------\n");
    scanf("%d", &aux);

    return aux;
}

int main()
{
    // Criar RAM com 1000 blocos
    RAM *ram = criarRAM_aleatoria(10000);

    // Inicializar CPU com caches de tamanhos definidos
    int tam1, tam2, tam3;
    int opcao;
    do
    {
        opcao = menuCache();
        switch (opcao)
        {
        case 1:
            tam1 = 16;
            tam2 = 32;
            tam3 = 64;
            break;
        case 2:
            tam1 = 32;
            tam2 = 64;
            tam3 = 128;
            break;
        case 3:
            tam1 = 16;
            tam2 = 64;
            tam3 = 256;
            break;
        case 4:
            tam1 = 8;
            tam2 = 32;
            tam3 = 128;
            break;
        case 5:
            printf("Digite o tamanho da cache 1: ");
            scanf("%d", &tam1);
            getchar(); // Limpa o buffer de entrada para evitar problemas
            printf("Digite o tamanho da cache 2: ");
            scanf("%d", &tam2);
            getchar(); // Limpa o buffer de entrada
            printf("Digite o tamanho da cache 3: ");
            scanf("%d", &tam3);
            getchar(); // Limpa o buffer de entrada
            break;
        case -1:
            exit(EXIT_SUCCESS);
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }
    } while (opcao < 1 || opcao > 6); // Ajuste no limite superior para incluir a opção 6

    CPU *cpu = inicializarCPU(tam1, tam2, tam3);

    // Número de instruções no programa
    int numInstrucoes = 0;

    // Carregar instruções do arquivo "instructions2.txt"
    Instrucao *programa = carregarInstrucoes("instructions2.txt", &numInstrucoes);

    // Definir o programa da CPU
    cpu->programa = programa;

    // Política de substituição: "LRU" ou "LFU"
    char politica[] = "LRU";

    // Executar o programa carregado
    executarPrograma(cpu, ram, politica, tam1, tam2, tam3);

    // Salvar dados de volta para a memória externa, se necessário
    for (int i = 0; i < numInstrucoes; i++) {
        salvarMemoriaExterna("memoria_externa.bin", &ram->memoria[i], i);
    }

    // Libera recursos
    liberarCPU(cpu);
    free(ram->memoria);
    free(ram);
    free(programa);

    return 0;
}
