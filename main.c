//////////////////////////
// Nomes:
// Victor de Almeida Piccoli Ferreira
// Thana Aguiar Correa
// JOGO: PELÉ SOCCER
// Como jogar: Jogador 1 utiliza W, A, S, D para se movimentar, X para chutar. Jogador 2 Utiliza as flechas para se movimentar, L para chutar. Os menus sao controlados por numeros e enter.
// O jogador 1 faz gol no gol de baixo, o jogador 2 faz gol no gol de cima. Quando o tempo chegar a zero, o jogo acaba.
// Há 3 variacoes de velocidade e 2 variacoes de tamanho de gol. O tempo de jogo tambem pode ser alterado no menu opções.
// O arquivo de formação é um arquivo 30x60 de texto consistido de '_' e 'X', o jogo carrega a formação de um arquivo. Se nenhum arquivo valido for escolhido o jogo carrega uma formação default.
// O jogador tambem pode escolher de continuar de um recorde, se não houver nenhum arquivo de recorde, ele é criado.
//////////////////////////
#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "jogo.h"
#include "menu.h"


int main(){
    int opt;
    int tempo = 60;
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
            iniciaJogo(tempo,velocidade,tamGol);
            break;
        case 2:
            // Opcao 2: Faz a escolha de tamanho de gol, velocidade e tempo.
            menuOpcoes(&tamGol,&velocidade,&tempo);
            break;
        case 3:
            // Opcao 3: Encerra o jogo
            break;
        default:
            printf("Opcao invalida\n");
    }


    }while(opt != 3);
    return 0;
}
