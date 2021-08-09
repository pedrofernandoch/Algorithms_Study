#  SCC0503 - Algoritmos e Estruturas de Dados II - Exercício - Grafos 
#  Nome: Pedro Fernando Christofoletti dos Santos 
#  NUSP: 11218560

CC=gcc
BINARY=main
SOURCES=main.c grafos.c queue.c
INCLUDES=.

all:
	@$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES)

run:
	@./$(BINARY)

clean:
	@find -name "*~" | xargs rm -rf
	@find -name "main" | xargs rm -rf