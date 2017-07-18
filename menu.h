#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Lida Com os menus de jogo e opcoes

void menuPrincipal(){
    system("@cls||clear");
    printf("1 - Novo jogo\n");
    printf("2 - Opcoes\n");
    printf("3 - Fim\n");
    printf("Sua opcao: ");
}


// Dá duas opções de escolha de tamanho de gol, 14 e 7 metros
int escolheTamanho(){
    int tamgol;
    int opt1;



    do{
        printf("1 - 14 metros\n");
        printf("2 - 8 metros\n");

        fflush(stdin);
        scanf("%d", &opt1);
        system("@cls||clear");
        switch(opt1){
            case 1:
                tamgol = 0;
                break;
            case 2:
                tamgol = 7;
                break;
            default:
                printf("Opcao Invalida.\n");
        }
    }while(opt1 > 2 || opt1 < 1);
    return tamgol;
}

int escolheVelocidade(){
    int opt2;
    int velocidade;



    do{
        printf("1 - Velocidade normal\n");
        printf("2 - Metade da Velocidade\n");
        printf("3 - 1/3 da Velocidade\n");

        fflush(stdin);
        scanf("%d", &opt2);
        system("@cls||clear");
        switch(opt2){
            case 1:
                velocidade = 1;
                break;
            case 2:
                velocidade = 3;
                break;
            case 3:
                velocidade = 5;
                break;
            default:
                printf("Opcao Invalida.\n");
        }
    }while(opt2 > 3 || opt2 < 1);

    return velocidade;
}

int escolheTempo(){
    int tempo;
    printf("Digite o tempo de jogo (em segundos)\n");
    fflush(stdin);
    scanf("%d", &tempo);
    return tempo;

}

void imprimeOpcoes(){
    system("@cls||clear");
    printf("1 - Escolher tamanho de gol\n");
    printf("2 - Escolher velocidade de jogadores\n");
    printf("3 - Escolher tempo de jogo\n");
    printf("4 - Voltar ao menu inicial\n");

}

int menuOpcoes(int *tamGol,int *velocidade, int *tempo){
    int opt;


    do{
        imprimeOpcoes();

        fflush(stdin);
        scanf("%d", &opt);

        system("@cls||clear");

        switch(opt){
            case 1:
                *tamGol = escolheTamanho();
                break;
            case 2:
                *velocidade = escolheVelocidade();
                break;
            case 3:
                *tempo = escolheTempo();
                break;
            case 4:
                break;
            default:
                printf("Opcao Invalida.\n");
        }

    }while(opt!=4);

    // Evita um bug em que a velocidade vira zero quando o jogo é jogado uma vez
    return *velocidade;
}

