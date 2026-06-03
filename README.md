# Relatório: Trabalho Prático 1 - Programação Concorrente

## 1. Identificação
* **Nome:** Scarlatti Bervely Livia Sousa Medeiros de Moura
* **Matrícula:** 20240037700

---

## 2. Problema Escolhido e Descrição
**P1 — Multiplicação de matrizes grandes (Padrão: mapa por linhas)**
O problema consiste em calcular o produto de duas matrizes quadradas de números reais ($C = A \times B$) de dimensões $1200 \times 1200$. A estratégia concorrente adota uma decomposição de domínio baseada em fatiamento de linhas da matriz resultante $C$. Cada thread recebe um intervalo exclusivo de linhas consecutivas para computar, garantindo acessos de escrita totalmente disjuntos em memória, o que elimina a necessidade de sincronização via exclusão mútua (*mutexes*) ou operações de *merge* posteriores.

---

## 3. Instruções de Compilação e Execução

### Compilação via CMake (Máquinas do Laboratório)
Na raiz do projeto, execute:
```bash
cmake -B build && cmake --build build
