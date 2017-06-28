#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH COLUNAS
#define HEIGHT LINHAS

void setCursor(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(screen, coordinate);
}

void iniciaJogo(char mat[][COLUNAS], int tempo)
{
    int i, j, posX=WIDTH/2 + 1, posY=HEIGHT/2, dirX=1, dirY=1;
    int posXPlayer=WIDTH/2, posYPlayer=HEIGHT/2;
    int start = tempo + (clock())/CLOCKS_PER_SEC;
    int t = start;
    int aceleracao = 0;
    int lastKey[4] = {0};

    while(t) // Enquanto a tecla ESC nao for pressionada
    {


        //currentTime = clock();

        t = start - clock()/CLOCKS_PER_SEC;
        printf("Tempo: %*d\n", 2, t);


        movimentoJogador1(&posXPlayer,&posYPlayer, lastKey);

        movimentoBola(&posX, &posY, &aceleracao, posXPlayer, posYPlayer, &dirX, &dirY, lastKey);

        setCursor(0, 0); //Altera a posicao do cursor para o inicio


        for(i=0; i<HEIGHT; i++){ //desenha a tela
            for(j=0; j<WIDTH; j++){
                if(i == 0 || j == 0 || i == LINHAS-1 || j == COLUNAS -1){
                mat[i][j] = '#';
                if(j >= 25 && j<= 37){
                    mat[i][j] = ' ';
                }
            } else if(i > 20 && i <= 50) {
               // fgets(mat[i],COLUNAS,arq);
               mat[i][j] = '_';
            } else{
                mat[i][j] = '_';
            }

                if(posX == j && posY == i) printf("O");
                else if(posXPlayer == j && posYPlayer == i) printf("A");
                else printf("%c", mat[i][j]);
            }
            printf("\n");
        }

        Sleep(1000/60); //60 frames por segundo
    }
    return;
}

void movimentoJogador1(int *posXPlayer, int *posYPlayer, int lastKey[]){
    if(GetAsyncKeyState('D')){
        if(*posXPlayer + 1 != WIDTH - 1)
            *posXPlayer+= 1;
        lastKey[0] = 1;
    }
    if(GetAsyncKeyState('A')){
        if(*posXPlayer - 1 != 0)
            *posXPlayer-= 1;
        lastKey[1] = 1;
    }
    if(GetAsyncKeyState('W')){
        if(*posYPlayer - 1 != 0)
            *posYPlayer-= 1;
        lastKey[2] = 1;
    }
    if(GetAsyncKeyState('S')){
        if(*posYPlayer + 1 != HEIGHT-1)
            *posYPlayer+= 1;
        lastKey[3] = 1;
    }

}

void movimentoBola(int *posX, int *posY, int *aceleracao, int posXPlayer1, int posYPlayer1, int *dirX, int *dirY, int lastKey1[]){
    int i;

    // Colisoes com jogador LastKey => 0 = D 1 = A 2 = W 3 = S
    if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[0] == 1){
        *aceleracao = 6;
        *dirX = 1;
        *dirY = 0;
    }
    if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[1] == 1){
        *aceleracao = 6;
        *dirX = -1;
        *dirY = 0;
    }
    if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[2] == 1){
        *aceleracao = 6;
        *dirY = -1;
        *dirX = 0;
    }
    if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[3] == 1){
        *aceleracao = 6;
        *dirY = 1;
        *dirX = 0;
    } if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[0] == 1 && lastKey1[2] == 1){
        *aceleracao = 6;
        *dirX = 1;
        *dirY = -1;
    } if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[0] == 1 && lastKey1[3] == 1){
        *aceleracao = 6;
        *dirX = 1;
        *dirY = 1;
    }if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[1] == 1 && lastKey1[2] == 1){
        *aceleracao = 6;
        *dirX = -1;
        *dirY = -1;
    } if(*posX == posXPlayer1 && *posY == posYPlayer1 && lastKey1[1] == 1 && lastKey1[3] == 1){
        *aceleracao = 6;
        *dirX = -1;
        *dirY = 1;
    }



    //verifica colisoes com a parede
    if(*posX+*dirX == 0 || *posX+*dirX == WIDTH-1) *dirX*=-1;
    if(*posY+*dirY == 0 || *posY+*dirY == HEIGHT-1) *dirY*=-1;


    //movimenta a bola
    if(*aceleracao > 0){
        *posX += *dirX;
        *posY += *dirY;

        *aceleracao = *aceleracao - 1;

        printf("ACELERACAO: %d", *aceleracao);
    }

    for(i = 0; i < 4; i++){
        lastKey1[i] = 0;
    }

}
