#include <stdio.h>
#include "ordenacao.h"

int main() {
    int n = 10;
    int v[] = { 4, 3, 6, 8, 9, 7, 1, 2, 0, 5};
    // int v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    heapConstroi(v, n);
    for(int i = 0; i < 10; i++)
        printf(" %d ", v[i]);
    return 0;
}