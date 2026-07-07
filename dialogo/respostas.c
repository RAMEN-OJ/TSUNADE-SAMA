/* ==========================================================================
 * respostas.c — Geração de respostas dialogais
 *
 * Selecção de respostas por intenção, detecção emocional na frase e
 * adaptação progressiva ao perfil e profundidade da conversa.
 * ========================================================================== */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "respostas.h"
#include "../personalidade/emocoes.h"

/* ---------- Classificação emocional auxiliar ---------- */

/** Tipos de emoção detectáveis a partir de palavras-chave na frase. */
typedef enum{
    EMOC_NENHUMA,
    EMOC_TRISTE,
    EMOC_FELIZ,
    EMOC_MEDO,
    EMOC_RAIVA,
    EMOC_CANSADO,
    EMOC_SOLIDAO,
    EMOC_SAUDADE,
    EMOC_PREOCUPADO,
    EMOC_CHATEADO,
    EMOC_DOENTE

} TipoEmocao;

/**
 * Verifica se a frase contém a palavra-alvo (comparação case-insensitive).
 */
static int contemPalavra(const char *frase, const char *palavra)
{
    char copia[256];
    char alvo[64];
    size_t i;

    if(frase == NULL || palavra == NULL)
        return 0;

    for(i = 0; frase[i] != '\0' && i < sizeof(copia) - 1; i++)
        copia[i] = (char)tolower((unsigned char)frase[i]);
    copia[i] = '\0';

    for(i = 0; palavra[i] != '\0' && i < sizeof(alvo) - 1; i++)
        alvo[i] = (char)tolower((unsigned char)palavra[i]);
    alvo[i] = '\0';

    return strstr(copia, alvo) != NULL;
}

/**
 * Infere o tipo emocional predominante a partir de palavras na frase.
 */
static TipoEmocao detectarEmocao(const char *frase)
{
    if(frase == NULL)
        return EMOC_NENHUMA;

    if(contemPalavra(frase, "triste") || contemPalavra(frase, "chorar") ||
       contemPalavra(frase, "lagrima") || contemPalavra(frase, "magoa"))
        return EMOC_TRISTE;

    if(contemPalavra(frase, "medo") || contemPalavra(frase, "assustad") ||
       contemPalavra(frase, "susto") || contemPalavra(frase, "terror"))
        return EMOC_MEDO;

    if(contemPalavra(frase, "brav") || contemPalavra(frase, "raiva") ||
       contemPalavra(frase, "nervos"))
        return EMOC_RAIVA;

    if(contemPalavra(frase, "cansad") || contemPalavra(frase, "sono") ||
       contemPalavra(frase, "exaust"))
        return EMOC_CANSADO;

    if(contemPalavra(frase, "sozinh") || contemPalavra(frase, "solidao") ||
       contemPalavra(frase, "abandonad"))
        return EMOC_SOLIDAO;

    if(contemPalavra(frase, "saudade"))
        return EMOC_SAUDADE;

    if(contemPalavra(frase, "preocupad") || contemPalavra(frase, "ansios"))
        return EMOC_PREOCUPADO;

    if(contemPalavra(frase, "chatead") || contemPalavra(frase, "aborrecid"))
        return EMOC_CHATEADO;

    if(contemPalavra(frase, "doente") || contemPalavra(frase, "dor"))
        return EMOC_DOENTE;

    if(contemPalavra(frase, "feliz") || contemPalavra(frase, "alegre") ||
       contemPalavra(frase, "contente") || contemPalavra(frase, "animad") ||
       contemPalavra(frase, "orgulhos"))
        return EMOC_FELIZ;

    return EMOC_NENHUMA;
}

/**
 * Selecciona resposta empática conforme emoção detectada e profundidade dialogal.
 */
static const char *respostaEmocional(TipoEmocao emoc, int profundidade)
{
    switch(emoc)
    {
        case EMOC_TRISTE:
            switch(profundidade)
            {
                case 0:
                    return "Oh... sinto muito que estejas triste.\n"
                           "Queres contar-me o que aconteceu? Estou aqui contigo.";
                case 1:
                    return "Percebo que isto te magoa.\n"
                           "Falar sobre o que sentes pode ajudar. Eu ouço-te com calma.";
                case 2:
                    return "É normal sentirmo-nos assim por vezes.\n"
                           "Não estás sozinho — podes confiar em mim.";
                default:
                    return "Obrigada por partilhares isto comigo.\n"
                           "És muito corajoso por falar sobre os teus sentimentos.";
            }

        case EMOC_MEDO:
            switch(profundidade)
            {
                case 0:
                    return "Não te preocupes, estou aqui.\n"
                           "O que é que te dá medo? Podemos falar sobre isso juntos.";
                case 1:
                    return "Ter medo faz parte de crescer.\n"
                           "Respira fundo comigo... estás seguro comigo aqui.";
                default:
                    return "Cada vez que falas do teu medo, ele fica um bocadinho mais pequeno.\n"
                           "Estou orgulhosa de ti por teres coragem.";
            }

        case EMOC_RAIVA:
            switch(profundidade)
            {
                case 0:
                    return "Vejo que estás chateado. Isso acontece.\n"
                           "Queres dizer-me o que te deixou assim?";
                case 1:
                    return "Quando ficamos com raiva, o coração bate mais depressa.\n"
                           "Vamos respirar juntos e acalmar aos poucos.";
                default:
                    return "Sentir raiva é normal, mas o importante é sabermos lidar com ela.\n"
                           "Estou aqui para te ajudar.";
            }

        case EMOC_FELIZ:
            switch(profundidade)
            {
                case 0:
                    return "Que maravilha! Fico tão contente por te ver feliz!\n"
                           "Conta-me — o que te deixou assim tão alegre?";
                case 1:
                    return "Adoro quando estás assim! A tua alegria contagia-me.\n"
                           "Vamos aproveitar este momento bonito!";
                default:
                    return "Guardar estes momentos felizes no coração é muito especial.\n"
                           "Obrigada por partilhares a tua alegria comigo!";
            }

        case EMOC_CANSADO:
            return profundidade == 0
                ? "Parece que estás cansado. Já fizeste muita coisa hoje!\n"
                  "Que tal descansarmos um bocadinho juntos?"
                : "O descanso também é importante para aprender e brincar.\n"
                  "Quando quiseres, podemos continuar — sem pressa.";

        case EMOC_SOLIDAO:
            return profundidade == 0
                ? "Não te sinto sozinho — estou aqui contigo.\n"
                  "Queres conversar ou brincar um pouco juntos?"
                : "Mesmo quando nos sentimos sozinhos, há sempre alguém que se importa.\n"
                  "Eu importo-me contigo, sabias?";

        case EMOC_SAUDADE:
            return profundidade == 0
                ? "Ter saudades mostra o quanto amamos alguém.\n"
                  "De quem sentes saudade? Posso ouvir-te."
                : "A saudade é como um abraço que o coração guarda.\n"
                  "Falar dessa pessoa pode trazer um sorriso, mesmo com saudade.";

        case EMOC_PREOCUPADO:
            return profundidade == 0
                ? "Percebo que estás preocupado. Isso é natural.\n"
                  "Queres dizer-me o que te está a inquietar?"
                : "Quando partilhamos as nossas preocupações, elas pesam menos.\n"
                  "Estou aqui para te ajudar a pensar nisto juntos.";

        case EMOC_CHATEADO:
            return profundidade == 0
                ? "Compreendo que estejas chateado.\n"
                  "O que aconteceu? Quero perceber o que te fez sentir assim."
                : "Às vezes as coisas correm mal, mas podemos encontrar uma solução.\n"
                  "Conta-me mais — estou a ouvir.";

        case EMOC_DOENTE:
            return "Espero que te sintas melhor em breve.\n"
                   "Queres descansar um pouco? Posso contar-te uma história suave.";

        default:
            break;
    }

    switch(profundidade)
    {
        case 0:
            return "Percebo que algo te preocupa.\n"
                   "Estou aqui contigo. Queres falar sobre o que sentes?";
        case 1:
            return "Os teus sentimentos são importantes para mim.\n"
                   "Podes contar-me mais — ouço-te com atenção.";
        case 2:
            return "Obrigada por confiares em mim.\n"
                   "Falar sobre o que sentimos ajuda-nos a sentir-nos melhor.";
        default:
            return "És muito corajoso por partilhares isto.\n"
                   "Estarei sempre aqui quando precisares de conversar.";
    }
}

/**
 * Prefixa a resposta com o nome da criança quando disponível no perfil.
 */
static void copiarComNome(const char *nome, const char *texto, char *dest, size_t tamanho)
{
    if(nome != NULL && nome[0] != '\0')
        snprintf(dest, tamanho, "%s, %s", nome, texto);
    else
        snprintf(dest, tamanho, "%s", texto);
}

/**
 * Gera a resposta principal da Tsunade com base na intenção e contexto.
 */
const char *gerarResposta(Intencao i, Contexto *c, PerfilCrianca *perfil)
{
    static char resposta[512];
    TipoEmocao emoc;
    const char *nome = (perfil != NULL) ? perfil->nome : "";

    resposta[0] = '\0';

    switch(i)
    {
        case INTENCAO_SAUDACAO:
            if(strlen(nome) > 0)
            {
                snprintf(resposta, sizeof(resposta),
                    "Olá %s! Que alegria falar contigo!\nComo te sentes hoje?", nome);
                return resposta;
            }
            if(c->mensagens <= 2)
                return "Olá! Que alegria falar contigo!\nComo te sentes hoje?";
            return "Olá outra vez! Fico sempre feliz quando conversamos.\n"
                   "Em que posso ajudar-te hoje?";

        case INTENCAO_HISTORIA:
            return "Adoro contar histórias!\n"
                   "Prepara-te — vamos entrar numa aventura mágica...";

        case INTENCAO_ESTUDO:
            return "Aprender coisas novas é divertido!\n"
                   "Sobre o que gostarias de aprender hoje?";

        case INTENCAO_JOGO:
            if(strlen(nome) > 0 && perfil != NULL && strlen(perfil->animalFavorito) > 0)
            {
                snprintf(resposta, sizeof(resposta),
                    "Brincar é ótimo! Já que gostas de %s, que tal um jogo divertido?",
                    perfil->animalFavorito);
                return resposta;
            }
            return "Brincar é uma das melhores coisas do dia!\n"
                   "Vamos jogar — escolhe: adivinhas ou números?";

        case INTENCAO_EMOCIONAL:
            emoc = detectarEmocao(c->ultimoAssunto);
            copiarComNome(nome, respostaEmocional(emoc, c->profundidadeEmocional),
                          resposta, sizeof(resposta));
            return resposta;

        case INTENCAO_AJUDA:
            if(contemPalavra(c->ultimoAssunto, "obrigad"))
                return "De nada! Fico feliz por ter ajudado.\n"
                       "Estou sempre aqui quando precisares.";
            if(contemPalavra(c->ultimoAssunto, "desculpa"))
                return "Não te preocupes, está tudo bem.\n"
                       "Todos cometemos erros — o importante é aprendermos.";
            return "Claro, estou aqui para ajudar!\n"
                   "Diz-me o que precisas e vamos resolver juntos.";

        case INTENCAO_DESPEDIDA:
            if(strlen(nome) > 0)
            {
                snprintf(resposta, sizeof(resposta),
                    "Até logo, %s! Foi um prazer estar contigo.\nVolta quando quiseres!",
                    nome);
                return resposta;
            }
            return "Até logo! Foi um prazer estar contigo.\n"
                   "Volta quando quiseres — estarei aqui!";

        default:
            if(c->ultimaIntencao == INTENCAO_EMOCIONAL)
            {
                emoc = detectarEmocao(c->ultimoAssunto);
                if(emoc != EMOC_NENHUMA)
                {
                    copiarComNome(nome, respostaEmocional(emoc, c->profundidadeEmocional),
                                  resposta, sizeof(resposta));
                    return resposta;
                }
                copiarComNome(nome,
                    "Compreendo. Continua — estou a ouvir-te com atenção.\n"
                    "Queres dizer-me mais sobre isso?",
                    resposta, sizeof(resposta));
                return resposta;
            }
            return "Hmm, não percebi bem o que quiseste dizer.\n"
                   "Podes tentar explicar de outra forma? Estou aqui para ajudar.";
    }
}

/**
 * Prefixa ou complementa a resposta conforme o estado emocional da Tsunade.
 */
void enriquecerComEmocao(Emocoes *emocoes, char *resposta, size_t tamanho)
{
    const char *prefixo = NULL;
    const char *sufixo = NULL;
    char buffer[1024];
    size_t len;

    if(emocoes == NULL || resposta == NULL || tamanho == 0 || resposta[0] == '\0')
        return;

    switch(emocoes->estado)
    {
        case CURIOSA:
            prefixo = "Hmm, interessante! ";
            sufixo = "\nQueres explorar mais isto comigo?";
            break;

        case BRINCALHONA:
            sufixo = "\nHehe, isto está a ficar divertido!";
            break;

        case ORGULHOSA:
            prefixo = "Estou orgulhosa de ti! ";
            break;

        case PREOCUPADA:
            prefixo = "Com calma... ";
            sufixo = "\nEstou aqui contigo, não te preocupes.";
            break;

        case FELIZ:
        default:
            if(emocoes->empatia >= 80)
                sufixo = "\nGosto muito de falar contigo!";
            break;
    }

    strncpy(buffer, resposta, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    resposta[0] = '\0';

    if(prefixo != NULL)
        strncat(resposta, prefixo, tamanho - 1);

    strncat(resposta, buffer, tamanho - strlen(resposta) - 1);

    if(sufixo != NULL)
    {
        len = strlen(resposta);
        if(len > 0)
            strncat(resposta, sufixo, tamanho - len - 1);
    }
}
