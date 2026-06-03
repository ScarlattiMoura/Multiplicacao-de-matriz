cmake_minimum_required(VERSION 3.10)
project(multiplicacao_matrizes)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Flags de compilação
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# Encontrar pthreads
find_package(Threads REQUIRED)

# Executável principal
add_executable(matriz_exe 
    src/main.c 
    src/sequencial.c 
    src/concorrente.c
)

# Linkar pthreads
target_link_libraries(matriz_exe Threads::Threads)

# Opção para build com ThreadSanitizer (opcional)
if(TSAN)
    add_compile_options(-fsanitize=thread -g)
    add_link_options(-fsanitize=thread)
endif()
