#ifndef SEQUENCIAL_H
#define SEQUENCIAL_H

void multiplicar_sequencial(const double *A, const double *B, double *C, int n);
int matrizes_iguais(const double *C1, const double *C2, int n, double tolerancia);
double calcular_checksum(const double *C, int n);

#endif
