CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g

OBJS = \
main.o \
core/tsunade.o \
core/motor.o \
core/crianca.o \
core/dados.o \
conhecimento/vocabulario.o \
conhecimento/conceitos.o \
conhecimento/grafo_inferencia.o \
estruturas/trie.o \
estruturas/hash.o \
cognitivo/parser.o \
cognitivo/interpretacao.o \
cognitivo/executor.o \
cognitivo/decisor.o \
cognitivo/interpretador.o \
cognitivo/analisador.o \
cognitivo/aprendizagem.o \
cognitivo/consulta.o \
cognitivo/memoria_busca.o \
cognitivo/inferencia.o \
cognitivo/motor_cognitivo.o \
cognitivo/bfs_semantico.o \
educacao/educacao.o \
educacao/atividades.o \
educacao/licoes_data.o \
educacao/historias_data.o \
educacao/jogos_data.o \
interface/ui.o \
dialogo/contexto.o \
dialogo/respostas.o \
memoria/perfil.o \
memoria/episodios.o \
memoria/memoria_imediata.o \
personalidade/grafo_emocoes.o \
personalidade/gestor_emocional.o \
personalidade/emocoes.o \
admin/admin.o \
crianca/painel_crianca.o \
crianca/comportamento.o \
crianca/decisao.o \
crianca/grafo_decisao.o \
pais/painel_pais.o

EXEC = tsunade

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC)

rebuild: clean all

test:
	$(MAKE) -C tests run