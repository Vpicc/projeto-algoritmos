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
    int i, j, posX=WIDTH/2 + 1, posY=HEIGHT/2;
    int posXPlayer=WIDTH/2, posYPlayer=HEIGHT/2;
    int start = tempo + (clock())/CLOCKS_PER_SEC;
    int t = start;
    int lastKey[4] = {0};
    int velocidadeInicial = 2;
    int velocidade = velocidadeInicial;

    while(t) // Enquanto a tecla ESC nao for pressionada
    {


        //currentTime = clock();

        t = start - clock()/CLOCKS_PER_SEC;
        printf("Tempo: %*d\n", 2, t);


        movimentoJogador1(&posXPlayer,&posYPlayer, lastKey, &velocidade, velocidadeInicial);

        movimentoBola(&posX, &posY, posXPlayer, posYPlayer, lastKey);

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

        Sleep(1000/120); //120 frames por segundo
    }
    system("@cls||clear");
}

void movimentoJogador1(int *posXPlayer, int *posYPlayer, int lastKey[], int *velocidade, int velocidadeInicial){
    if(*velocidade == 0){
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
        *velocidade = velocidadeInicial;
    } else{
        *velocidade -= 1;
    }

}

void movimentoBola(int *posX, int *posY, int posXPlayer1, int posYPlayer1, int lastKey1[]){
    int i;
    static int aceleracao = 0;
    static int dirX = 1, dirY = 1;

    colisoesBolaJogador(posXPlayer1, posYPlayer1, *posX, *posY,&aceleracao,&dirX,&dirY,lastKey1);

    //verifica colisoes com a parede
    if(*posX+dirX <= 0 || *posX+dirX >= WIDTH-1) dirX*=-1;
    if(*posY+dirY <= 0 || *posY+dirY >= HEIGHT-1) dirY*=-1;


    //movimenta a bola
    if(aceleracao > 0){
        *posX = *posX + dirX;
        *posY = *posY + dirY;



        // retorna a velocidade normal apos um chute

      /*  if(dirX % 2 == 0 || dirY % 2 == 0){
            dirX = dirX/2;
            dirY = dirY/2;
        }*/
        aceleracao = aceleracao - 1;

        printf("ACELERACAO: %d", aceleracao);
    }
    for(i = 0; i < 4; i++){
        lastKey1[i] = 0;
    }

}

void colisoesBolaJogador(int posXPlayer, int posYPlayer, int posX, int posY, int *aceleracao,int *dirX, int *dirY, int lastKey[]){
    static int cnt = 0;
    int chute = 0;
    // Colisoes com jogador LastKey => 0 = D 1 = A 2 = W 3 = S
    if(posX == posXPlayer && posY == posYPlayer){
        *aceleracao = 1;
        if(lastKey[0] == 1){
            *dirX = 1;
            *dirY = 0;
        }
        if(lastKey[1] == 1){
            *dirX = -1;
            *dirY = 0;
        }
        if(lastKey[2] == 1){
            *dirY = -1;
            *dirX = 0;
        }
        if(lastKey[3] == 1){
            *dirY = 1;
            *dirX = 0;
        }
        if(lastKey[0] == 1 && lastKey[2] == 1){
            *dirX = 1;
            *dirY = -1;
        }
        if(lastKey[0] == 1 && lastKey[3] == 1){
             *dirX = 1;
            *dirY = 1;
        }
        if(lastKey[1] == 1 && lastKey[2] == 1){
            *dirX = -1;
            *dirY = -1;
        }
        if(lastKey[1] == 1 && lastKey[3] == 1){
            *dirX = -1;
            *dirY = 1;
        }

        cnt++;

        // Chute longo
        if(GetAsyncKeyState('X')){
            chute = 1;
            cnt = 0;
        }
    }

    // Faz o chute só funcionar quando esta encostado na bola e apertou a tecla de chute
    GetAsyncKeyState('X');

    // Se a tecla de chute longo foi pressionada
    if(chute == 1){
        // Se a bola for para frente
        if((dirX && !dirY) || !dirX && dirY){
            /*dirX = *dirX*4;
            *dirY = *dirY*4;*/
            *aceleracao = 9;
        } else if(dirX && dirY){ // Se a bola for para a diagonal
           /* *dirX = *dirX*4;
            *dirY = *dirY*4;*/
            *aceleracao = 5;
        } // Isso evita que a bota vá muito para frente quando o chute for para a diagonal
        chute = 0;
    }
    // Apos 2m de conducao, chuta
    if(cnt == 2){
        // Se a bola for para frente
        if((dirX && !dirY) || !dirX && dirY){
           /* *dirX = *dirX*2;
            *dirY = *dirY*2;*/
            *aceleracao = 6;
        } else if(dirX && dirY){ // Se a bola for para a diagonal
          /*  *dirX = *dirX*2;
            *dirY = *dirY*2;*/
            *aceleracao = 3;
        } // Isso evita que a bota vá muito para frente quando o chute for para a diagonal
        cnt = 0;
    }


}
