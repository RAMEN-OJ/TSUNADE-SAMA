#include <stdio.h>
#include <string.h>

#include "aprendizagem_conhecimento.h"

int aprenderConhecimento(
        BaseConhecimento *base,
        const char *frase,
        char *resposta)
{
    char copia[256];

    strcpy(copia, frase);

    copia[
        strcspn(
            copia,
            "\n")] = '\0';

    printf(
        "\n[DEBUG] aprenderConhecimento recebeu: %s\n",
        copia);

    /* Ignorar perguntas */

    if(strchr(copia, '?'))
    {
        printf("[DEBUG] Pergunta detectada\n");
        return 0;
    }

    if(strncmp(copia, "o que", 5) == 0)
    {
        printf("[DEBUG] Pergunta detectada\n");
        return 0;
    }

    if(strncmp(copia, "quem", 4) == 0)
    {
        printf("[DEBUG] Pergunta detectada\n");
        return 0;
    }

    if(strncmp(copia, "onde", 4) == 0)
    {
        printf("[DEBUG] Pergunta detectada\n");
        return 0;
    }

    char *pos = NULL;

    char relacao[100];

    /* foi criado por */

    pos = strstr(
            copia,
            " foi criado por ");

    if(pos)
    {
        strcpy(
            relacao,
            "foi criado por");
    }

    /* fica em */

    if(pos == NULL)
    {
        pos = strstr(
                copia,
                " fica em ");

        if(pos)
        {
            strcpy(
                relacao,
                "fica em");
        }
    }

    /* é */

    if(pos == NULL)
    {
        pos = strstr(
                copia,
                " é ");

        if(pos)
        {
            strcpy(
                relacao,
                "é");
        }
    }

    /* e */

    if(pos == NULL)
    {
        pos = strstr(
                copia,
                " e ");

        if(pos)
        {
            strcpy(
                relacao,
                "é");
        }
    }

    if(pos == NULL)
    {
        printf(
            "[DEBUG] Nao encontrou separador\n");

        return 0;
    }

    char sujeito[100];
    char objeto[200];

    int tamanhoRelacao =
        strlen(relacao);

    strncpy(
        sujeito,
        copia,
        pos - copia);

    sujeito[
        pos - copia] = '\0';

    strcpy(
        objeto,
        pos + tamanhoRelacao + 2);

    if(strlen(sujeito) == 0 ||
       strlen(objeto) == 0)
    {
        printf(
            "[DEBUG] sujeito ou objeto vazio\n");

        return 0;
    }

    printf(
        "[DEBUG] Sujeito: %s\n",
        sujeito);

    printf(
        "[DEBUG] Relacao: %s\n",
        relacao);

    printf(
        "[DEBUG] Objeto: %s\n",
        objeto);

    adicionarRelacao(
        base,
        sujeito,
        relacao,
        objeto);

    sprintf(
        resposta,
        "Aprendi que %s %s %s.",
        sujeito,
        relacao,
        objeto);

    return 1;
}
