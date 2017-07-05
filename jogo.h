#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define COLUNAS 64
#define LINHAS 62
#define MAXLETRAS 20
#define FORMACAO_X 60
#define FORMACAO_Y 30

#define WIDTH COLUNAS
#define HEIGHT LINHAS

// cria o tipo jogador
typedef struct{
    int x;
    int y;
} JOGADOR;

typedef struct{
    int x;
    int y;
} BOLA;

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
    // Numero maximo de jogadores em campo: 11
    JOGADOR jogador1[11];
    JOGADOR jogador2[11];
    int n_jogadores = 0;
    BOLA bola;
    int i, j, k, posX=WIDTH/2 + 1, posY=HEIGHT/2;
    int posXPlayer=WIDTH/2, posYPlayer=HEIGHT/2;
    int start = tempo + (clock())/CLOCKS_PER_SEC;
    int t = start;
    int lastKey[4] = {0};
    int velocidadeInicial = 1;
    int velocidade = velocidadeInicial;

    n_jogadores = carregaFormacao(jogador1,jogador2);

    while(t) // Enquanto a tecla ESC nao for pressionada
    {

        t = start - clock()/CLOCKS_PER_SEC;
        printf("Tempo: %*d\t", 2, t);


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
               mat[i][j] = '_';
            } else{
                mat[i][j] = '_';
            }
            if(posX == j && posY == i) mat[i][j] = 'O';
            if(posXPlayer == j && posYPlayer == i) mat[i][j] = 'A';
                for(k = 0; k < n_jogadores; k++){
                    if(jogador1[k].x == j && jogador1[k].y == i) mat[i][j] = 'W';
                    if(jogador2[k].x == j && jogador2[k].y == i) mat[i][j] = 'M';
                }
                printf("%c", mat[i][j]);

            }
            printf("\n");
        }

        Sleep(1000/30); //30 frames por segundo
    }
    system("@cls||clear");
}

void movimentoJogador1(int *posXPlayer, int *posYPlayer, int lastKey[],int *velocidade, int velocidadeInicial){
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
             *dirX =1;
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
        if(*dirX && !*dirY){ // Se a bola for para os lados
            /*dirX = *dirX*4;
            *dirY = *dirY*4;*/
            *aceleracao = 20;
        } else if(*dirX && *dirY){ // Se a bola for para a diagonal
           /* *dirX = *dirX*4;
            *dirY = *dirY*4;*/
            *aceleracao = 15;// Isso evita que a bota vá muito para frente quando o chute for para a diagonal
        } else if(!*dirX && *dirY){ // Se a bola for para frente
            *aceleracao = 20;
        }
        chute = 0;
    }
    // Apos 2m de conducao, chuta
    if(cnt == 3){

        if(*dirX != 0 && !*dirY){ // Se a bola for para os lados
           /* *dirX = *dirX*2;
            *dirY = *dirY*2;*/
            *aceleracao = 6;
        } else if(*dirX && *dirY){ // Se a bola for para a diagonal
          /*  *dirX = *dirX*2;
            *dirY = *dirY*2;*/
            *aceleracao = 3; // Isso evita que a bota vá muito para frente quando o chute for para a diagonal
        } else if(!*dirX && *dirY){ // Se a bola for para frente
            *aceleracao = 4;
        }
        cnt = 0;
    }


}

void le_texto (char texto[ ], int size_texto) // string: ponteiro implícito
{
     char dummy[size_texto + 1]; // cabe um caractere a mais do que no texto:
     fflush(stdin);
     fgets(dummy, sizeof(dummy), stdin); // lê caracteres
     // O último caractere tem que ser '\n' para estar correto:
     while(dummy[strlen(dummy) -1] != '\n')
     {
        printf("\nNumero de caracteres digitados excedeu tamanho do campo.\n"
    );
        printf("Numero maximo de caracteres eh %d.\n", size_texto - 1);
        printf("Digite o conteudo novamente.\n");
        fflush(stdin);
        fgets(dummy, sizeof(dummy), stdin); // lê caracteres novamente
     }
     dummy[strlen(dummy)-1]= '\0'; // sempre precisa substituir o '\n'
     strcpy(texto, dummy); // transfere conteúdo digitado e sem o '\n' para texto
}

int carregaFormacao(JOGADOR jogador1[], JOGADOR jogador2[]){
    FILE *arq;
    char mat[FORMACAO_Y][FORMACAO_X];
    int i, j;
    char nome[MAXLETRAS + 1];
    int n_jogadores = 0;
    //Abrir arquivo
    fflush(stdin);
    printf("Inisira o nome do arquivo de formacao: ");
    le_texto(nome,sizeof(nome));

    if(!(arq = fopen(nome, "r"))){
        printf("Erro na abertura");
        return 0;
    } else{

    fseek(arq, 0, SEEK_SET);

    for(i = 0; i < FORMACAO_Y; i++){
        for(j = 0; j < FORMACAO_X; j++){
            mat[i][j] = getc(arq);
            if(mat[i][j] == 'X'){
            jogador1[n_jogadores].x = j+2;
            jogador1[n_jogadores].y = i;
            n_jogadores++;
            }
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i < n_jogadores; i++){
        jogador2[i].x = jogador1[i].x;
        jogador2[i].y = jogador1[i].y + 30;
    }

    fclose(arq);
    }
    return n_jogadores;
}

