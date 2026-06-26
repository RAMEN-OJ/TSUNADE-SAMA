#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perfil.h"

PerfilCrianca *criarPerfil(void)
{
    PerfilCrianca *p =
        malloc(sizeof(PerfilCrianca));

    strcpy(p->nome, "");

    p->idade = 0;

    strcpy(p->corFavorita, "");
    strcpy(p->animalFavorito, "");
    strcpy(p->comidaFavorita, "");

    p->totalConversas = 0;

    return p;
}

void destruirPerfil(
        PerfilCrianca *p)
{
    free(p);
}

void salvarPerfil(
        PerfilCrianca *p)
{
    FILE *f =
        fopen(
            "dados/perfil.dat",
            "w");

    if(f == NULL)
        return;

    fprintf(
        f,
        "%s\n%d\n%s\n%s\n%s\n%d\n",
        p->nome,
        p->idade,
        p->corFavorita,
        p->animalFavorito,
        p->comidaFavorita,
        p->totalConversas);

    fclose(f);
}

void carregarPerfil(
        PerfilCrianca *p)
{
    FILE *f =
        fopen(
            "dados/perfil.dat",
            "r");

    if(f == NULL)
        return;

    fgets(
        p->nome,
        sizeof(p->nome),
        f);

    p->nome[
        strcspn(
            p->nome,
            "\n")] = '\0';

    fscanf(
        f,
        "%d\n",
        &p->idade);

    fgets(
        p->corFavorita,
        sizeof(p->corFavorita),
        f);

    p->corFavorita[
        strcspn(
            p->corFavorita,
            "\n")] = '\0';

    fgets(
        p->animalFavorito,
        sizeof(p->animalFavorito),
        f);

    p->animalFavorito[
        strcspn(
            p->animalFavorito,
            "\n")] = '\0';

    fgets(
        p->comidaFavorita,
        sizeof(p->comidaFavorita),
        f);

    p->comidaFavorita[
        strcspn(
            p->comidaFavorita,
            "\n")] = '\0';

    fscanf(
        f,
        "%d",
        &p->totalConversas);

    fclose(f);
}
