#include "concorrente.h"
#include <stdlib.h>
#include <stdio.h>

void *calcular_bloco(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    
    for (int i = args->inicio_linha; i < args->fim_linha; i++) {
        for (int j = 0; j < args->n; j++) {
            double soma = 0.0;
            for (int k = 0; k < args->n; k++) {
                soma += args->A[i * args->n + k] * args->B[k * args->n + j];
            }
            args->C[i * args->n + j] = soma;
        }
    }
    
    return NULL;
}

void multiplicar_concorrente(const double *A, const double *B, double *C, int n, int num_threads) {
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadArgs *args_array = malloc(num_threads * sizeof(ThreadArgs));
    
    int linhas_por_thread = n / num_threads;
    int resto = n % num_threads;
    int linha_atual = 0;
    
    for (int t = 0; t < num_threads; t++) {
        int linhas_desta_thread = linhas_por_thread + (t < resto ? 1 : 0);
        
        args_array[t].A = A;
        args_array[t].B = B;
        args_array[t].C = C;
        args_array[t].n = n;
        args_array[t].inicio_linha = linha_atual;
        args_array[t].fim_linha = linha_atual + linhas_desta_thread;
        
        pthread_create(&threads[t], NULL, calcular_bloco, &args_array[t]);
        
        linha_atual += linhas_desta_thread;
    }
    
    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }
    
    free(threads);
    free(args_array);
}
