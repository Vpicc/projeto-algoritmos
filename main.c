#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "jogo.h"
#include "menu.h"


int main(){
    char opt;
    char mat[LINHAS][COLUNAS];
    JOGADOR jogador1[11];
    JOGADOR jogador2[11];

    // Laço principal do programa
    do{
    menuPrincipal();

    scanf("%c", &opt);

    //opt = getc(stdin);

    system("@cls||clear");

    switch(opt){
        case '1':
            iniciaJogo(mat,15);
            break;
        case '2':
            menuOpcoes();

            break;
        case '3':
            break;
        default:
            printf("Opcao invalida\n");
    }



    }while(opt != '3');
    return 0;
}
