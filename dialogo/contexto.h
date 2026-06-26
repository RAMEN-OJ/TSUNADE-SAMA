#ifndef CONTEXTO_H
#define CONTEXTO_H

#include "../cognitivo/interpretador.h"

typedef struct {
    
    Intencao ultimaIntencao;

    char ultimoAssunto[100];

    int mensagens;
    int profundidadeEmocional;
} Contexto;

Contexto *criarContexto(void);


void destruirContexto(
        Contexto *c);

void atualizarContexto(
        Contexto *c,
        Intencao i,
        const char *frase);

void mostrarContexto(
        Contexto *c);

#endif
