/* ==========================================================================
 * perfil.c — Perfil da criança
 *
 * Ciclo de vida do perfil, normalização do nome e persistência em
 * ficheiro com suporte a formatos legado e TSUNADE2.
 * ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "perfil.h"
#include "../core/dados.h"

/**
 * Remove prefixos indesejados ("é", "e") do nome antes de persistir.
 */
static void limparPrefixoNome(char *nome)
{
    char *p = nome;

    while(*p == ' ')
        p++;

    if(strncmp(p, "é ", 3) == 0 || strncmp(p, "e ", 2) == 0)
    {
        p += (p[1] == ' ' ? 2 : 3);
        if(*p == ' ')
            p++;
    }
    else if((unsigned char)p[0] == 0xC3 && (unsigned char)p[1] == 0xA9)
    {
        p += 2;
        while(*p == ' ')
            p++;
    }
    else if(*p == 'e')
    {
        p++;
        while(*p == ' ')
            p++;
    }

    if(p != nome)
        memmove(nome, p, strlen(p) + 1);
}

/**
 * Aloca perfil com identidade vazia e indicadores nos valores iniciais.
 */
PerfilCrianca *criarPerfil(void)
{
    PerfilCrianca *p = malloc(sizeof(PerfilCrianca));

    strcpy(p->nome, "");
    p->idade = 0;
    p->energia = 100;
    p->humor = 80;
    p->curiosidade = 70;
    p->atencao = 70;
    p->fome = 0;
    p->tempoEstudo = 0;
    p->tempoBrincadeira = 0;
    p->tempoDescanso = 0;
    p->historiasOuvidas = 0;
    p->perguntasRespondidas = 0;
    p->conhecimentosAprendidos = 0;
    strcpy(p->corFavorita, "");
    strcpy(p->animalFavorito, "");
    strcpy(p->comidaFavorita, "");
    p->totalConversas = 0;

    return p;
}

/**
 * Liberta a memória do perfil da criança.
 */
void destruirPerfil(PerfilCrianca *p)
{
    free(p);
}

/**
 * Grava todos os campos do perfil no formato TSUNADE2.
 */
void salvarPerfil(PerfilCrianca *p)
{
    FILE *f;

    if(p == NULL)
        return;

    if(!garantirDiretorioDados())
        return;

    f = fopen("dados/perfil.dat", "w");

    if(f == NULL)
        return;

    limparPrefixoNome(p->nome);

    fprintf(f, "TSUNADE2\n");
    fprintf(f, "%s\n", p->nome);
    fprintf(f, "%d\n", p->idade);
    fprintf(f, "%s\n", p->corFavorita);
    fprintf(f, "%s\n", p->animalFavorito);
    fprintf(f, "%s\n", p->comidaFavorita);
    fprintf(f, "%d\n", p->energia);
    fprintf(f, "%d\n", p->humor);
    fprintf(f, "%d\n", p->curiosidade);
    fprintf(f, "%d\n", p->atencao);
    fprintf(f, "%d\n", p->fome);
    fprintf(f, "%d\n", p->tempoEstudo);
    fprintf(f, "%d\n", p->tempoBrincadeira);
    fprintf(f, "%d\n", p->tempoDescanso);
    fprintf(f, "%d\n", p->historiasOuvidas);
    fprintf(f, "%d\n", p->perguntasRespondidas);
    fprintf(f, "%d\n", p->conhecimentosAprendidos);
    fprintf(f, "%d\n", p->totalConversas);

    fclose(f);
}

/**
 * Restaura o perfil a partir de disco (formato TSUNADE2 ou legado).
 */
void carregarPerfil(PerfilCrianca *p)
{
    FILE *f = fopen("dados/perfil.dat", "r");
    char cabecalho[32];

    if(f == NULL)
        return;

    if(fgets(cabecalho, sizeof(cabecalho), f) == NULL)
    {
        fclose(f);
        return;
    }

    cabecalho[strcspn(cabecalho, "\n")] = '\0';

    if(strcmp(cabecalho, "TSUNADE2") == 0)
    {
        fgets(p->nome, sizeof(p->nome), f);
        p->nome[strcspn(p->nome, "\n")] = '\0';
        limparPrefixoNome(p->nome);

        fscanf(f, "%d\n", &p->idade);
        fgets(p->corFavorita, sizeof(p->corFavorita), f);
        p->corFavorita[strcspn(p->corFavorita, "\n")] = '\0';
        fgets(p->animalFavorito, sizeof(p->animalFavorito), f);
        p->animalFavorito[strcspn(p->animalFavorito, "\n")] = '\0';
        fgets(p->comidaFavorita, sizeof(p->comidaFavorita), f);
        p->comidaFavorita[strcspn(p->comidaFavorita, "\n")] = '\0';

        fscanf(f, "%d\n", &p->energia);
        fscanf(f, "%d\n", &p->humor);
        fscanf(f, "%d\n", &p->curiosidade);
        fscanf(f, "%d\n", &p->atencao);
        fscanf(f, "%d\n", &p->fome);
        fscanf(f, "%d\n", &p->tempoEstudo);
        fscanf(f, "%d\n", &p->tempoBrincadeira);
        fscanf(f, "%d\n", &p->tempoDescanso);
        fscanf(f, "%d\n", &p->historiasOuvidas);
        fscanf(f, "%d\n", &p->perguntasRespondidas);
        fscanf(f, "%d\n", &p->conhecimentosAprendidos);
        fscanf(f, "%d\n", &p->totalConversas);
    }
    else
    {
        strncpy(p->nome, cabecalho, sizeof(p->nome) - 1);
        p->nome[sizeof(p->nome) - 1] = '\0';
        limparPrefixoNome(p->nome);

        fscanf(f, "%d\n", &p->idade);
        fgets(p->corFavorita, sizeof(p->corFavorita), f);
        p->corFavorita[strcspn(p->corFavorita, "\n")] = '\0';
        fgets(p->animalFavorito, sizeof(p->animalFavorito), f);
        p->animalFavorito[strcspn(p->animalFavorito, "\n")] = '\0';
        fgets(p->comidaFavorita, sizeof(p->comidaFavorita), f);
        p->comidaFavorita[strcspn(p->comidaFavorita, "\n")] = '\0';
        fscanf(f, "%d", &p->totalConversas);
    }

    fclose(f);
}
