# Variáveis de compilação
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -O2
INCLUDES := -I./include
SRCDIR := src
BUILDDIR := build
TARGET := maze-exit-search

# Arquivos fonte
SOURCES := main.cpp \
           $(SRCDIR)/benchmark.cpp \
           $(SRCDIR)/graph.cpp \
           $(SRCDIR)/map.cpp \
           $(SRCDIR)/maze.cpp \
           $(SRCDIR)/visualization.cpp

# Objetos
OBJECTS := $(SOURCES:%.cpp=$(BUILDDIR)/%.o)

# Alvo padrão
.PHONY: all clean run rebuild info

all: $(BUILDDIR)/$(TARGET)

# Criar diretório de build
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Compilar executável
$(BUILDDIR)/$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $@
	@echo "✓ Compilação concluída: $@"

# Compilar objetos
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	@echo "✓ Compilado: $<"

# Executar o programa
run: $(BUILDDIR)/$(TARGET)
	@echo "▶ Executando $(BUILDDIR)/$(TARGET)..."
	@cd $(dir $(BUILDDIR)/$(TARGET)) && ./$(TARGET)

# Limpar arquivos compilados
clean:
	@rm -rf $(BUILDDIR)
	@echo "✓ Limpeza concluída"

# Recompilar tudo
rebuild: clean all
	@echo "✓ Recompilação concluída"

# Mostrar informações
info:
	@echo "Variáveis do Makefile:"
	@echo "  CXX: $(CXX)"
	@echo "  CXXFLAGS: $(CXXFLAGS)"
	@echo "  TARGET: $(TARGET)"
	@echo "  BUILDDIR: $(BUILDDIR)"
	@echo "  SOURCES: $(SOURCES)"
