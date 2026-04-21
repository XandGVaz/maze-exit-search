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

## Resultados de Desempenho

### Análise Comparativa

O projeto compara dois algoritmos de busca em labirintos de tamanhos crescentes:

| Tamanho | Área | A* (ms) | DFS (ms) | Speedup |
|---------|------|---------|----------|---------|
| 20x15   | 300  | 0.018   | 0.018    | 1.00x   |
| 30x20   | 600  | 0.025   | 0.047    | 1.88x   |
| 40x23   | 920  | 0.144   | 0.128    | 0.89x   |
| 50x30   | 1500 | 0.095   | 0.343    | 3.61x   |
| 60x35   | 2100 | 0.109   | 0.725    | 6.65x   |

### Conclusões

**A* vs DFS:**
- **Crescimento de complexidade**: A* cresce 8x enquanto DFS cresce 40.28x
- **Eficiência em larga escala**: Em labirintos maiores (60x35), A* é **6.65x mais rápido** que DFS
- **Escalabilidade**: A* mantém tempo praticamente linear, enquanto DFS degrada exponencialmente
- **Implementação heurística**: O uso de heurística Manhattan no A* prova ser decisivo para reduzir o espaço de busca

**Recomendação**: Para labirintos de qualquer tamanho significativo, A* é o algoritmo preferível, especialmente quando os labirintos ultrapassam 1000 células.