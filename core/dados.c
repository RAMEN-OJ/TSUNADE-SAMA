/*======================================================================
  dados.c
  Garante a existência da pasta dados/ para persistência em disco.
======================================================================*/

#include <stdio.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define DADOS_DIR "dados"
#define dir_existe(path) (_access((path), 0) == 0)
#define criar_dir(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <unistd.h>
#define DADOS_DIR "dados"
#define dir_existe(path) (access((path), F_OK) == 0)
#define criar_dir(path) mkdir((path), 0755)
#endif

#include "dados.h"

int garantirDiretorioDados(void)
{
    if(dir_existe(DADOS_DIR))
        return 1;

    if(criar_dir(DADOS_DIR) == 0)
        return 1;

    return 0;
}
