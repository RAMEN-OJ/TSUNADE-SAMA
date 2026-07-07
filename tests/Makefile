CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -I..
ROOT = ..

SRCS = run_tests.c \
	$(ROOT)/conhecimento/conceitos.c \
	$(ROOT)/conhecimento/grafo_inferencia.c \
	$(ROOT)/estruturas/hash.c \
	$(ROOT)/core/crianca.c \
	$(ROOT)/core/dados.c \
	$(ROOT)/memoria/perfil.c

EXEC = run_tests

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRCS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC)

.PHONY: all run clean
