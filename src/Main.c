#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "sequencial.h"
#include "concorrente.h"

#define TOLERANCIA 1e-6
#define N 1000
#define NUM_EXECUCOES 5

void preencher_matrizes(double *A, double *B, int n) {
    srand(42);
    for (int i = 0; i < n * n; i++) {
        A[i] = (double)rand() / RAND_MAX * 10.0;
        B[i] = (double)rand() / RAND_MAX * 10.0;
    }
}

double cronometrar(void (*func_seq)(const double*, const double*, double*, int),
                   void (*func_conc)(const double*, const double*, double*, int, int),
                   const double *A, const double *B, double *C, 
                   int n, int num_threads, int is_concorrente) {
    double tempos[NUM_EXECUCOES];
    
    for (int exec = 0; exec < NUM_EXECUCOES; exec++) {
        memset(C, 0, n * n * sizeof(double));
        
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        
        if (is_concorrente) {
            func_conc(A, B, C, n, num_threads);
        } else {
            func_seq(A, B, C, n);
        }
        
        clock_gettime(CLOCK_MONOTONIC, &t1);
        tempos[exec] = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
        
        printf("  Execucao %d: %.4f segundos\n", exec + 1, tempos[exec]);
    }
    
    double soma = 0.0;
    for (int exec = 1; exec < NUM_EXECUCOES; exec++) {
        soma += tempos[exec];
    }
    double media = soma / (NUM_EXECUCOES - 1);
    
    return media;
}

int main(int argc, char *argv[]) {
    int num_threads = 4;
    if (argc > 1) {
        num_threads = atoi(argv[1]);
        if (num_threads <= 0) {
            fprintf(stderr, "Numero de threads invalido. Usando 4.\n");
            num_threads = 4;
        }
    }
    
    printf("=== Multiplicacao de Matrizes (P1) ===\n");
    printf("Dimensao da matriz: %d x %d\n", N, N);
    printf("Numero de threads: %d\n\n", num_threads);
    
    double *A = malloc(N * N * sizeof(double));
    double *B = malloc(N * N * sizeof(double));
    double *C_seq = malloc(N * N * sizeof(double));
    double *C_par = malloc(N * N * sizeof(double));
    
    if (!A || !B || !C_seq || !C_par) {
        fprintf(stderr, "Erro ao alocar memoria!\n");
        return 1;
    }
    
    printf("Preenchendo matrizes...\n");
    preencher_matrizes(A, B, N);
    
    printf("\n--- Execucao Sequencial ---\n");
    double tempo_seq = cronometrar(multiplicar_sequencial, NULL, 
                                    A, B, C_seq, N, 0, 0);
    printf("Tempo medio (sequencial): %.4f segundos\n", tempo_seq);
    
    printf("\n--- Execucao Concorrente (%d threads) ---\n", num_threads);
    double tempo_par = cronometrar(NULL, multiplicar_concorrente,
                                    A, B, C_par, N, num_threads, 1);
    printf("Tempo medio (concorrente): %.4f segundos\n", tempo_par);
    
    printf("\n--- Verificacao de Corretude ---\n");
    if (matrizes_iguais(C_seq, C_par, N, TOLERANCIA)) {
        printf("OK: Matrizes resultado sao iguais (dentro da tolerancia de %.1e)\n", TOLERANCIA);
    } else {
        printf("FALHA: Matrizes resultado diferem alem da tolerancia!\n");
    }
    
    printf("\n--- Speedup ---\n");
    double speedup = tempo_seq / tempo_par;
    printf("Speedup (T_seq / T_par) = %.4f / %.4f = %.2fx\n", 
           tempo_seq, tempo_par, speedup);
    
    free(A);
    free(B);
    free(C_seq);
    free(C_par);
    
    return 0;
}
