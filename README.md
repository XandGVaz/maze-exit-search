# Maze Exit Search

Método para encontrar o caminho de saída de um labirinto usando A* e DFS implementados com C++23.

## Descrição

- Geração dinâmica de labirintos com obstáculos
- Busca otimizada com algoritmo A* e DFS
- Visualização do caminho encontrado
- Benchmark de performance entre algoritmos de busca
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
- **Benchmark**: Testa em 5 tamanhos diferentes de labirintos (30 execuções por tamanho para média estatística)

## Geração de Labirintos Aleatórios

### Algoritmo: Recursive Backtracking (Profundidade)

O projeto utiliza o algoritmo de **Backtracking** para gerar labirintos aleatórios :

**Processo:**
1. Inicia na célula central do mapa
2. Marca a célula atual como caminho
3. Seleciona aleatoriamente uma de 4 direções (Norte, Sul, Leste, Oeste)
4. Move 2 células na direção escolhida
5. Se a célula vizinha é parede (não visitada):
   - Marca ambas as células intermediárias como caminho
   - Continua recursivamente da nova célula
6. Se todas as direções foram exploradas, volta ao passo anterior
7. Rastreia possíveis saídas enquanto constrói o labirinto
8. Escolhe uma saída aleatória entre as encontradas

**Características:**
- Garante um caminho conectado entre entrada e saída
- Gera labirintos com uma única solução ótima
- Representação em matriz: 0 = caminho, 1 = parede, 7 = saída

### Exemplo de Labirinto Gerado

<img src="./docs/example.png" alt="Exemplo de labirinto gerado pelo algoritmo" />

## Resultados de Desempenho

### Análise Comparativa (Média de 30 execuções)

O projeto compara dois algoritmos de busca em labirintos de tamanhos crescentes:

| Tamanho | Área | A* (ms) | DFS (ms) | Speedup |
|---------|------|---------|----------|---------|
| 20x20   | 400  | 0.468   | 0.524    | 1.12x   |
| 40x40   | 1600 | 4.221   | 4.996    | 1.18x   |
| 60x60   | 3600 | 20.186  | 20.689   | 1.02x   |
| 80x80   | 6400 | 59.607  | 66.866   | 1.12x   |
| 100x100 | 10000| 136.19  | 156.311  | 1.15x   |

### Conclusões

**A* vs DFS:**
- **Eficiência consistente**: A* mantém-se entre 1.02x e 1.18x mais rápido que DFS em todos os tamanhos
- **Escalabilidade**: Ambos os algoritmos crescem de forma similar (291x vs 298x), indicando complexidade comparable
- **Heurística Manhattan**: O uso da heurística Manhattan no A* proporciona ganho modesto em labirintos menores, com convergência em tamanhos maiores
- **Iteração vs Recursão**: A implementação iterativa do Backtracking mantém performance estável sem risco de stack overflow
- **Recomendação**: A* é o algoritmo preferível para qualquer aplicação prática, oferecendo speedup consistente, especialmente em labirintos menores.
