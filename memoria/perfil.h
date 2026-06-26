#ifndef PERFIL_H
#define PERFIL_H

typedef struct {

    char nome[50];

    int idade;

    char corFavorita[50];

    char animalFavorito[50];

    char comidaFavorita[50];

    int totalConversas;

} PerfilCrianca;

PerfilCrianca *criarPerfil(void);

void destruirPerfil(
        PerfilCrianca *p);

void salvarPerfil(
        PerfilCrianca *p);

void carregarPerfil(
        PerfilCrianca *p);

#endif
