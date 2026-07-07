#ifndef CONSULTA_H
#define CONSULTA_H

#include "../conhecimento/conceitos.h"
#include "../memoria/perfil.h"

int responderConsulta(
        PerfilCrianca *perfil,
        const char *frase,
        char *resposta);

int consultarConhecimento(
        BaseConhecimento *base,
        const char *conceito,
        char *resposta);

int responderConsultaSemantica(
        BaseConhecimento *base,
        const char *conceito,
        char *resposta);

#endif