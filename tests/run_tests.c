/*======================================================================
  run_tests.c
  Testes unitários: grafo de inferência, registo de interações e dados/.
======================================================================*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../conhecimento/conceitos.h"
#include "../conhecimento/grafo_inferencia.h"
#include "../core/crianca.h"
#include "../core/dados.h"
#include "../memoria/perfil.h"

static int testes_ok = 0;
static int testes_total = 0;

#define TEST(nome, bloco) do { \
    testes_total++; \
    printf("  [TEST] %s ... ", nome); \
    bloco; \
    testes_ok++; \
    printf("OK\n"); \
} while(0)

static int fatoInferidoExiste(BaseConhecimento *b, const char *conceito,
                              const char *relacao, const char *objeto)
{
    FatoGrafo fatos[MAX_FATOS_GRAFO];
    int total = coletarFatosGrafo(b, conceito, fatos, MAX_FATOS_GRAFO);
    int i;

    for(i = 0; i < total; i++)
    {
        if(fatos[i].inferido &&
           strcmp(fatos[i].relacao, relacao) == 0 &&
           strcmp(fatos[i].objeto, objeto) == 0)
            return 1;
    }

    return 0;
}

static void test_grafo_inferencia_cao(void)
{
    BaseConhecimento *b = criarBaseConhecimento();
    char resposta[1024];

    assert(b != NULL);

    adicionarRelacaoNormalizada(b, "cao", "eh", "animal");
    adicionarRelacaoNormalizada(b, "animal", "vive em", "terra");

    assert(fatoInferidoExiste(b, "cao", "vive em", "terra"));
    assert(responderConhecimentoGrafo(b, "cao", resposta, sizeof(resposta)));
    assert(strstr(resposta, "terra") != NULL);
    assert(strstr(resposta, "Inferido") != NULL || strstr(resposta, "inferid") != NULL);

    destruirBaseConhecimento(b);
}

static void test_grafo_inferencia_multinivel(void)
{
    BaseConhecimento *b = criarBaseConhecimento();

    adicionarRelacaoNormalizada(b, "cao", "eh", "animal");
    adicionarRelacaoNormalizada(b, "animal", "eh", "vertebrado");
    adicionarRelacaoNormalizada(b, "vertebrado", "eh", "ser vivo");
    adicionarRelacaoNormalizada(b, "ser vivo", "vive em", "terra");

    assert(fatoInferidoExiste(b, "cao", "eh", "vertebrado"));
    assert(fatoInferidoExiste(b, "cao", "eh", "ser vivo"));
    assert(fatoInferidoExiste(b, "cao", "vive em", "terra"));

    destruirBaseConhecimento(b);
}

static void test_grafo_sinonimos(void)
{
    BaseConhecimento *b = criarBaseConhecimento();
    FatoGrafo fatos[MAX_FATOS_GRAFO];
    int total;

    adicionarRelacaoNormalizada(b, "cao", "eh", "animal");
    adicionarSinonimo(b, "cao", "dog");

    assert(procurarConceitoGrafo(b, "dog") != NULL);

    total = coletarFatosGrafo(b, "dog", fatos, MAX_FATOS_GRAFO);
    assert(total >= 1);

    destruirBaseConhecimento(b);
}

static void test_grafo_normalizacao_relacao(void)
{
    BaseConhecimento *b = criarBaseConhecimento();

    adicionarRelacaoNormalizada(b, "gato", "e", "animal");
    adicionarRelacaoNormalizada(b, "animal", "vive na", "terra");

    assert(fatoInferidoExiste(b, "gato", "vive em", "terra"));

    destruirBaseConhecimento(b);
}

static void test_grafo_actualiza_relacao(void)
{
    BaseConhecimento *b = criarBaseConhecimento();
    FatoGrafo fatos[MAX_FATOS_GRAFO];
    int total;

    adicionarRelacaoNormalizada(b, "sol", "eh", "estrela");
    adicionarRelacaoNormalizada(b, "sol", "eh", "planeta");

    total = coletarFatosGrafo(b, "sol", fatos, MAX_FATOS_GRAFO);
    assert(total >= 1);

    destruirBaseConhecimento(b);
}

static void test_registrar_interacao(void)
{
    PerfilCrianca *p = criarPerfil();

    assert(p != NULL);
    assert(p->totalConversas == 0);

    registrarInteracao(p, ACAO_CONHECIMENTO, INTENCAO_ESTUDO);
    assert(p->totalConversas == 1);
    assert(p->conhecimentosAprendidos == 1);

    registrarInteracao(p, ACAO_DESCONHECIDA, INTENCAO_JOGO);
    assert(p->totalConversas == 2);
    assert(p->tempoBrincadeira == 1);
    assert(p->humor > 80);

    registrarInteracao(p, ACAO_INFERENCIA, INTENCAO_DESCONHECIDA);
    assert(p->totalConversas == 3);
    assert(p->perguntasRespondidas == 1);

    destruirPerfil(p);
}

static void test_garantir_diretorio_dados(void)
{
    assert(garantirDiretorioDados() == 1);
    assert(garantirDiretorioDados() == 1);
}

static void test_libertar_grafo(void)
{
    BaseConhecimento *b = criarBaseConhecimento();

    adicionarRelacaoNormalizada(b, "a", "eh", "b");
    adicionarRelacaoNormalizada(b, "b", "eh", "c");
    adicionarRelacaoNormalizada(b, "c", "vive em", "d");

    destruirBaseConhecimento(b);
}

int main(void)
{
    printf("\n=== Tsunade-Sama — Testes Unitarios ===\n\n");

    TEST("inferencia cao -> animal -> terra", test_grafo_inferencia_cao());
    TEST("inferencia multi-nivel (cadeia de e)", test_grafo_inferencia_multinivel());
    TEST("sinonimos no grafo (cao/dog)", test_grafo_sinonimos());
    TEST("normalizacao de relacoes (e / vive na)", test_grafo_normalizacao_relacao());
    TEST("actualizacao de relacao no grafo", test_grafo_actualiza_relacao());
    TEST("registrar interacao no perfil", test_registrar_interacao());
    TEST("garantir pasta dados/", test_garantir_diretorio_dados());
    TEST("libertar grafo sem crash", test_libertar_grafo());

    printf("\n=== Resultado: %d/%d testes passaram ===\n\n", testes_ok, testes_total);

    return (testes_ok == testes_total) ? 0 : 1;
}
