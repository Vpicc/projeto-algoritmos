#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "arquivo.h"
#include "menu.h"
#include "jogo.h"

int main(){
    int opt;
    char mat[LINHAS][COLUNAS];

    // Laço principal do programa
    do{
    menuPrincipal();
    fflush(stdin);
    scanf("%d", &opt);

    system("@cls||clear");

    switch(opt){
        case 1:
            //carregaArquivo(/*mat*/);
            iniciaJogo(mat,15);
            break;
        case 2:
            menuOpcoes();

            break;
        case 3:
            break;
        default:
            printf("Opcao invalida\n");
    }



    }while(opt != 3);
    return 0;
}
