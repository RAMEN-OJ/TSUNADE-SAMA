#ifndef APRENDIZAGEM_H
#define APRENDIZAGEM_H

#include "../memoria/perfil.h"
#include "../conhecimento/conceitos.h"

int aprenderPerfil(
        PerfilCrianca *perfil,
        const char *frase,
        char *resposta);
      
int aprenderConhecimento(
        BaseConhecimento *base,
        const char *frase,
        char *resposta);
#endif

