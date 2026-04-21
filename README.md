# Maze Exit Search

Algoritmo estocástico para encontrar a saída de um labirinto usando A* em C++23.

## Descrição

- Geração dinâmica de labirintos com obstáculos
- Busca otimizada com algoritmo A*
- Visualização do caminho encontrado
- Benchmark de performance
- C++23 com otimizações

## Compilação e Execução

### Com Makefile

```bash
make         # Compilar
make run     # Executar
make clean   # Limpar
make rebuild # Recompilar tudo
```

### Com CMake

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./maze-exit-search
```

## Estrutura

```
├── CMakeLists.txt
├── Makefile
├── main.cpp
├── include/          # Headers
├── src/              # Implementação
└── build/            # Saída compilada
```

## Requisitos

- g++ 11+ ou Clang 14+ (C++23)
- make ou cmake 3.10+

## Funcionalidades

- **Demonstração**: Gera labirinto 20x15 e encontra saída com A*
- **Benchmark**: Testa em 5 tamanhos diferentes de labirintos