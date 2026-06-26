# 0 "core/tsunade.h"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "core/tsunade.h"



# 1 "core/../memoria/memoria_imediata.h" 1






typedef struct {

    char mensagens[10][256];

    int inicio;

    int fim;

    int total;

} MemoriaImediata;




MemoriaImediata *criarMemoriaImediata(void);



void destruirMemoriaImediata(MemoriaImediata *m);



void adicionarMensagem(MemoriaImediata *m, const char *msg);



void mostrarMemoriaImediata(MemoriaImediata *m);
# 5 "core/tsunade.h" 2
# 1 "core/../memoria/episodios.h" 1





typedef struct
{
    char texto[256];
}
Episodio;

typedef struct
{
    Episodio lista[100];
    int quantidade;
}
MemoriaEpisodica;

MemoriaEpisodica *criarMemoriaEpisodica(void);

void destruirMemoriaEpisodica(
        MemoriaEpisodica *m);

void adicionarEpisodio(
        MemoriaEpisodica *m,
        const char *texto);

void salvarEpisodios(
        MemoriaEpisodica *m);

void carregarEpisodios(
        MemoriaEpisodica *m);
# 6 "core/tsunade.h" 2
# 1 "core/../memoria/perfil.h" 1



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
# 7 "core/tsunade.h" 2

# 1 "core/../conhecimento/conceitos.h" 1





typedef struct
{
    char sujeito[100];
    char relacao[100];
    char objeto[200];
}
Relacao;

typedef struct
{
    Relacao lista[500];
    int quantidade;
}
BaseConhecimento;

BaseConhecimento *criarBaseConhecimento(void);

void destruirBaseConhecimento(
        BaseConhecimento *b);

void adicionarRelacao(
        BaseConhecimento *b,
        const char *sujeito,
        const char *relacao,
        const char *objeto);

void salvarConhecimento(
        BaseConhecimento *b);

void carregarConhecimento(
        BaseConhecimento *b);
# 9 "core/tsunade.h" 2
# 1 "core/../conhecimento/vocabulario.h" 1



# 1 "core/../conhecimento/../estruturas/trie.h" 1



# 1 "core/../conhecimento/../estruturas/../cognitivo/interpretador.h" 1



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
# 5 "core/../conhecimento/../estruturas/trie.h" 2



typedef struct TrieNo {

    struct TrieNo *filhos[26];

    int fimPalavra;

    Intencao intencao;

} TrieNo;

typedef struct {

    TrieNo *raiz;

} Trie;

Trie *criarTrie(void);

void destruirTrie(Trie *trie);

void inserirPalavraTrie(
        Trie *trie,
        const char *palavra,
        Intencao intencao);

Intencao procurarPalavraTrie(
        Trie *trie,
        const char *palavra);
# 5 "core/../conhecimento/vocabulario.h" 2

typedef struct {

    Trie *trie;

} Vocabulario;

Vocabulario *criarVocabulario(void);

void destruirVocabulario(
        Vocabulario *v);

void carregarVocabularioPadrao(
        Vocabulario *v);

Intencao interpretarPalavra(
        Vocabulario *v,
        const char *palavra);
# 10 "core/tsunade.h" 2

# 1 "core/../dialogo/contexto.h" 1



# 1 "core/../dialogo/../cognitivo/interpretador.h" 1
# 5 "core/../dialogo/contexto.h" 2

typedef struct {

    Intencao ultimaIntencao;

    char ultimoAssunto[100];

    int mensagens;
    int profundidadeEmocional;
} Contexto;

Contexto *criarContexto(void);


void destruirContexto(
        Contexto *c);

void atualizarContexto(
        Contexto *c,
        Intencao i,
        const char *frase);

void mostrarContexto(
        Contexto *c);
# 12 "core/tsunade.h" 2

# 1 "core/../personalidade/emocoes.h" 1



typedef enum {

    FELIZ,
    CURIOSA,
    BRINCALHONA,
    ORGULHOSA,
    PREOCUPADA

} EstadoEmocional;

typedef struct {

    EstadoEmocional estado;

    int energia;
    int curiosidade;
    int empatia;

} Emocoes;



Emocoes *criarEmocoes(void);



void destruirEmocoes(Emocoes *e);



void mudarEstado(Emocoes *e, EstadoEmocional novo);



void mostrarEmocoes(Emocoes *e);



const char *nomeEstado(EstadoEmocional estado);
# 14 "core/tsunade.h" 2

# 1 "core/../educacao/educacao.h" 1
# 16 "core/tsunade.h" 2

typedef struct Tsunade
{


    char nome[50];

    int ativa;



    MemoriaImediata *memoria;

    MemoriaEpisodica *episodios;

    PerfilCrianca *perfil;



    BaseConhecimento *conhecimento;

    Vocabulario *vocabulario;



    Contexto *contexto;



    Emocoes *emocao;



    Educacao *educacao;



    void *moduloPais;

    void *moduloAdministrador;

} Tsunade;



Tsunade *criarTsunade(void);



void destruirTsunade(
        Tsunade *t);
