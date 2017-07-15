#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "jogo.h"
#include "menu.h"


int main(){
    int opt;
    int tempo = 3;
    int tamGol = 0;
    static int velocidade = 1; // static evita um bug em que a velocidade zera apos um jogo
    char mat[LINHAS][COLUNAS];
    JOGADOR jogador1[11];
    JOGADOR jogador2[11];




    // Laço principal do programa
    do{
    menuPrincipal();

    fflush(stdin);
    scanf("%d", &opt);

    system("@cls||clear");

    switch(opt){
        case 1:
            // Opcao 1: Inicia o Jogo
            iniciaJogo(mat,tempo,velocidade,tamGol);
            break;
        case 2:
            // Opcao 2: Faz a escolha de tamanho de gol, velocidade e tempo.
            menuOpcoes(&tamGol,&velocidade,&tempo);
            break;
        case 3:
            break;
        default:
            printf("Opcao invalida\n");
    }


    }while(opt != 3);
    return 0;
}
