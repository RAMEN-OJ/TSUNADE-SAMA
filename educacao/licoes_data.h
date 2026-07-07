#ifndef LICOES_DATA_H
#define LICOES_DATA_H

#include "educacao.h"

typedef struct
{
    TipoLicao tipo;
    const char *disciplina;
    const char *intro;
    const char *pergunta;
    const char *palavrasCertas;
    const char *feedbackOk;
    const char *feedbackErr;

} DadosLicao;

const DadosLicao *obterDadosLicao(TipoLicao tipo);
TipoLicao detectarLicaoFrase(const char *frase);
TipoLicao escolherLicaoRotativa(Educacao *e);

#endif
