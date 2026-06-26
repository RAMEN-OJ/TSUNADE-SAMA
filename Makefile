CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g

SRC = \
main.c \
core/tsunade.c \
core/motor.c \
\
conhecimento/vocabulario.c \
conhecimento/conceitos.c \
\
estruturas/trie.c \
\
cognitivo/decisor.c \
cognitivo/interpretador.c \
cognitivo/analisador.c \
cognitivo/aprendizagem.c \
cognitivo/consulta.c \
cognitivo/aprendizagem_conhecimento.c \
cognitivo/consulta_conhecimento.c \
cognitivo/memoria_busca.c \
cognitivo/inferencia.c \
cognitivo/motor_cognitivo.c \
\
educacao/educacao.c \
\
dialogo/contexto.c \
dialogo/respostas.c \
\
memoria/perfil.c \
memoria/episodios.c \
memoria/memoria_imediata.c \
\
personalidade/grafo_emocoes.c \
personalidade/gestor_emocional.c \
personalidade/emocoes.c

OBJ = $(SRC:.c=.o)

EXEC = tsunade

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)

rebuild: clean all