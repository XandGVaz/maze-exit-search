# Imagem oficial para uso de c++
FROM alpine:latest

# Instala as dependências necessárias para compilar o código
RUN apk add --no-cache build-base cmake g++

# Define o diretório de trabalho dentro do container
WORKDIR /app

# Copia os arquivos do projeto para o diretório de trabalho
COPY . .

# Compila o código usando cmake
RUN cmake -S . -B build && cmake --build build

# Define o comando de execução do container
CMD ["./build/maze-exit-search"]