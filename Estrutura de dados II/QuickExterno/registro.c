#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"

void print_registro(const Registro *r) {
    if (r == NULL) return;

    printf("ID: %ld | Nota: %.2f | Estado: %s | Cidade: %s | Curso: %s\n",
           r->id, r->nota, r->estado, r->cidade, r->curso);
}

Registro lerRegistroLinha(const char *linha) {
    Registro r;
    char campo[100];

    
    strncpy(campo, linha, 8);
    campo[8] = '\0';
    r.id = atol(campo);

    
    strncpy(campo, linha + 9, 5);
    campo[5] = '\0';
    r.nota = atof(campo);

    
    strncpy(r.estado, linha + 15, 2);
    r.estado[2] = '\0';

    
    strncpy(r.cidade, linha + 18, 50);
    r.cidade[50] = '\0';

    
    strncpy(r.curso, linha + 69, 30);
    r.curso[30] = '\0';

    return r;
}


int compararNota(const void *a, const void *b) {
    const Registro *ra = (const Registro *)a;
    const Registro *rb = (const Registro *)b;

    if (ra->nota < rb->nota) return -1;
    if (ra->nota > rb->nota) return 1;
    return 0;
}
