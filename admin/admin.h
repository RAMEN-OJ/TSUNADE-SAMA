/* ==========================================================================
 * admin.h — Painel administrativo
 *
 * Menus de diagnóstico e inspecção de subsistemas da Tsunade
 * (memória, conhecimento, emoções, perfil e dashboard).
 * ========================================================================== */

#ifndef ADMIN_H
#define ADMIN_H

#include "../core/tsunade.h"

/** Menu principal do painel administrador (loop até sair). */
void painelAdministrador(Tsunade *t);

/** Resumo geral de indicadores dos subsistemas. */
void menuDashboard(Tsunade *t);

/** Visualização do perfil da criança. */
void menuPerfil(Tsunade *t);

/** Inspecção da memória imediata. */
void menuMemoria(Tsunade *t);

/** Visualização do grafo de conhecimento. */
void menuConhecimento(Tsunade *t);

/** Inspecção do estado emocional da Tsunade. */
void menuEmocoes(Tsunade *t);

/** Módulo educativo (estado da sessão educativa). */
void menuEducacao(Tsunade *t);

/** Estatísticas globais da sessão e do perfil. */
void menuEstatisticas(Tsunade *t);

/** Ferramentas de manutenção e persistência. */
void menuFerramentas(Tsunade *t);

/** Verificação de integridade dos componentes. */
void menuDiagnostico(Tsunade *t);

#endif
