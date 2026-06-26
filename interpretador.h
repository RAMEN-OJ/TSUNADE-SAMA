#ifndef INTERPRETADOR_H
#define INTERPRETADOR_H

typedef enum {

    INTENCAO_DESCONHECIDA,

    INTENCAO_SAUDACAO,

    INTENCAO_HISTORIA,

    INTENCAO_ESTUDO,

    INTENCAO_JOGO,

    INTENCAO_EMOCIONAL,

    INTENCAO_AJUDA,

    INTENCAO_DESPEDIDA

} Intencao;

Intencao interpretar(const char *frase);

const char *nomeIntencao(Intencao i);

#endif
