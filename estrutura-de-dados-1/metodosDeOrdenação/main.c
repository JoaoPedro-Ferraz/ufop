#include <stdio.h>
#include "ordenacao.h"

int main() {
    int n = 10;
    int v[] = { 4, 3, 6, 8, 9, 7, 1, 2, 5, 0};
    // int v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    buubleSort(v, n);
    for(int i = 0; i < n; i++)
        printf(" %d ", v[i]);
    printf("\n");
    return 0;
}