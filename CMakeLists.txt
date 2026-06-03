cmake_minimum_required(VERSION 3.10)
project(MatrixMultiplication C)

# Configura o padrão C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Aplica estritamente as flags exigidas pelo enunciado
add_compile_options(-O2 -Wall -Wextra)

# Busca o pacote de Threads (pthread)
find_package(Threads REQUIRED)

# Coleta os arquivos fonte
file(GLOB SOURCES "src/*.c")

# Define o executável
add_executable(meu_exe ${SOURCES})

# Linka a biblioteca de Threads de forma portável
target_link_libraries(meu_exe PRIVATE Threads::Threads)
