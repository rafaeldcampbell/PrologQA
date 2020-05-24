#include "utils.h"
#include <stdio.h>
#include <string.h>

void showMenuAndGetAns(int* ans){
    int invalid = 1;
    do {
        printf("*** MENU ***\n1 - Desenhar grafo de conhecimento\n2 - Adicionar aresta ao grafo\n3 - Adicionar arquivo de fatos\n4 - Fazer consulta\n0 - Sair\n\nEscolha uma opcao:");
        scanf(" %d", ans);
        if(*ans != 0 && *ans != 1 && *ans != 2 && *ans != 3 && *ans != 4) printf("\nEscolha uma das opcoes disponiveis!\n");
        else invalid = 0;
    } while (invalid);
}
