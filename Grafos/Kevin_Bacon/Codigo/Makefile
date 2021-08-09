#SCC0503 - Algoritmos e Estruturas de Dados II - Trabalho II - Grafos 
#Integrantes:
#Daniel De Marco Fucci                            11218639
#Pedro Fernando Christofoletti dos Santos         11218560

CC=gcc
BINARY=main
SOURCES=main.c grafos.c queue.c stack.c
INCLUDES=.

all:
	@$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES) -lm

run:
	@./$(BINARY)

clean:
	@find -name "*~" | xargs rm -rf
	@find -name "main" | xargs rm -rf