# Versão mínima do CMake necessária para construir o projeto
cmake_minimum_required(VERSION 3.10)

# Definição do projeto
project(
    maze-exit-search
    VERSION 1.0.0
    DESCRIPTION "Algoritmo estocástico para encontrar a saída de um labirinto"
    LANGUAGES CXX
)

# Configurações de compilação
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Adiciona os arquivos de código-fonte
file(GLOB SRC_FILES *src/*.cpp)

# Cria o executável a partir dos arquivos de código-fonte
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

# Inclui o diretório de cabeçalhos para o projeto
target_include_directories(maze-exit-search PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)


