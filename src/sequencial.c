#include "sequencial.h"
#include <math.h>

void multiplicar_sequencial(const double *A, const double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double soma = 0.0;
            for (int k = 0; k < n; k++) {
                soma += A[i * n + k] * B[k * n + j];
            }
            C[i * n + j] = soma;
        }
    }
}

int matrizes_iguais(const double *C1, const double *C2, int n, double tolerancia) {
    for (int i = 0; i < n * n; i++) {
        if (fabs(C1[i] - C2[i]) > tolerancia) {
            return 0;
        }
    }
    return 1;
}

double calcular_checksum(const double *C, int n) {
    double soma = 0.0;
    for (int i = 0; i < n * n; i++) {
        soma += C[i];
    }
    return soma;
}
