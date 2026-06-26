#include "respostas.h"

#include "respostas.h"

const char *gerarResposta(
        Intencao i,
        Contexto *c)
{
    switch(i)
    {
        case INTENCAO_SAUDACAO:

            return "Ola! Fico feliz por te ver.";

        case INTENCAO_HISTORIA:

            return "Era uma vez um pequeno dragao aventureiro.";

        case INTENCAO_ESTUDO:

            return "Vamos aprender algo novo hoje.";

        case INTENCAO_JOGO:

            return "Vamos brincar juntos.";

        case INTENCAO_EMOCIONAL:

            switch(c->profundidadeEmocional)
            {
                case 0:
                    return "Estou aqui contigo. Queres contar-me mais?";

                case 1:
                    return "Entendo. Parece algo importante para ti.";

                case 2:
                    return "Deve ser dificil passar por isso. Continua, estou a ouvir.";

                case 3:
                    return "Os teus sentimentos sao importantes. Podes falar comigo.";

                default:
                    return "Obrigado por confiares em mim para falar sobre isso.";
           }

        case INTENCAO_AJUDA:

            return "Claro! Vou tentar ajudar-te.";

        case INTENCAO_DESPEDIDA:

            return "Ate logo!";

       default:

        if(c->ultimaIntencao ==
        INTENCAO_EMOCIONAL)
        {
            return "Entendo. Parece algo que te deixou triste. Conta-me mais.";
        }

        return "Nao compreendi muito bem. Podes explicar de outra forma?";
    }  
}
