#ifndef CONCORRENTE_H
#define CONCORRENTE_H

#include <pthread.h>

typedef struct {
    const double *A;
    const double *B;
    double *C;
    int n;
    int inicio_linha;
    int fim_linha;
} ThreadArgs;

void *calcular_bloco(void *arg);
void multiplicar_concorrente(const double *A, const double *B, double *C, int n, int num_threads);

#endif
