/*======================================================================
  tsunade.h
  Definição da estrutura central Tsunade e funções de ciclo de vida.
  Agrega memória, conhecimento, contexto, emoções e educação.
======================================================================*/

#ifndef TSUNADE_H
#define TSUNADE_H

#include "../memoria/memoria_imediata.h"
#include "../memoria/episodios.h"
#include "../memoria/perfil.h"

#include "../conhecimento/conceitos.h"
#include "../conhecimento/vocabulario.h"

#include "../dialogo/contexto.h"

#include "../personalidade/emocoes.h"

#include "../educacao/educacao.h"

/* --- estrutura principal --- */
typedef struct Tsunade
{
    /* --- identidade --- */
    char nome[50];
    int ativa;

    /* --- memória --- */
    MemoriaImediata *memoria;
    MemoriaEpisodica *episodios;
    PerfilCrianca *perfil;

    /* --- conhecimento --- */
    BaseConhecimento *conhecimento;
    Vocabulario *vocabulario;

    /* --- contexto --- */
    Contexto *contexto;

    /* --- personalidade --- */
    Emocoes *emocao;

    /* --- educação --- */
    Educacao *educacao;

    /* --- módulos futuros --- */
    void *moduloPais;
    void *moduloAdministrador;

} Tsunade;

/* Aloca e inicializa todos os submódulos da Tsunade; retorna ponteiro ou termina em erro */
Tsunade *criarTsunade(void);

/* Persiste dados, liberta recursos e destrói a instância; parâmetro: t (pode ser NULL) */
void destruirTsunade(Tsunade *t);
        
#endif
