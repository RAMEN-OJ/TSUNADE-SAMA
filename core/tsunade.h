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

typedef struct Tsunade
{
    /* ================= IDENTIDADE ================= */

    char nome[50];

    int ativa;

    /* ================= MEMÓRIA ================= */

    MemoriaImediata *memoria;

    MemoriaEpisodica *episodios;

    PerfilCrianca *perfil;

    /* ================= CONHECIMENTO ================= */

    BaseConhecimento *conhecimento;

    Vocabulario *vocabulario;

    /* ================= CONTEXTO ================= */

    Contexto *contexto;

    /* ================= PERSONALIDADE ================= */

    Emocoes *emocao;

    /* ================= EDUCAÇÃO ================= */

    Educacao *educacao;

    /* ================= FUTUROS MÓDULOS ================= */

    void *moduloPais;

    void *moduloAdministrador;

} Tsunade;

/* Inicialização */

Tsunade *criarTsunade(void);

/* Encerramento */

void destruirTsunade(
        Tsunade *t);

#endif