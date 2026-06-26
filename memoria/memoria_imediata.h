#ifndef MEMORIA_IMEDIATA_H
#define MEMORIA_IMEDIATA_H

#define TAM_MEMORIA 10
#define TAM_MSG 256

typedef struct {

    char mensagens[TAM_MEMORIA][TAM_MSG];

    int inicio;

    int fim;

    int total;

} MemoriaImediata;


/* CriaÃÂ§ÃÂ£o */

MemoriaImediata *criarMemoriaImediata(void);

/* LibertaÃÂ§ÃÂ£o */

void destruirMemoriaImediata(MemoriaImediata *m);

/* Adicionar mensagem */

void adicionarMensagem(MemoriaImediata *m, const char *msg);

/* Mostrar memÃÂ³ria */

void mostrarMemoriaImediata(MemoriaImediata *m);

#endif
