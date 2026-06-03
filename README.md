# Relatório: Trabalho Prático 1 - Programação Concorrente

## 1. Identificação
* **Nome:** Scarlatti Bervely Livia Sousa Medeiros de Moura
* **Matrícula:** 20240037700
* **Problema escolhido:** P1 - Multiplicação de matrizes grandes

---

## 2. Descrição
Este projeto implementa a multiplicação de matrizes quadradas (n x n) nas versões sequencial e concorrente com pthreads. 
A versão paralela divide as linhas da matriz resultado entre as threads, onde cada thread calcula um bloco contínuo de linhas,
garantindo escrita em posições disjuntas sem necessidade de sincronização.

---

## 3. Instruções de Compilação e Execução

## Compilação e Execução

### Com CMake (recomendado)

mkdir -p build
cd build
cmake ..
make
./matriz_exe [num_threads]

### Com GCC
``bash
gcc -O2 -Wall -Wextra -pthread src/*.c -o matriz_exe
./matriz_exe [num_threads]
