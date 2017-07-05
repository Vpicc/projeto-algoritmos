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
    bola.x = COLUNAS/2;
    bola.y = LINHAS/2;
    int i;
    int start = tempo + (clock())/CLOCKS_PER_SEC;
    int t = start;
    int lastKey1[4] = {0};
    int lastKey2[4] = {0};
    int velocidadeInicial = 1;
    int velocidade1 = velocidadeInicial;
    int velocidade2 = velocidadeInicial;

    n_jogadores = carregaFormacao(jogador1,jogador2);

    if(n_jogadores > 0){
    while(t) // Enquanto a tecla ESC nao for pressionada
    {

        t = start - clock()/CLOCKS_PER_SEC;
        printf("Tempo: %*d\t", 2, t);

            movimentoJogador1(jogador1, lastKey1, &velocidade1, velocidadeInicial, n_jogadores);

            movimentoJogador2(jogador2, lastKey2, &velocidade2, velocidadeInicial, n_jogadores);
           // movimentoBola(&bola.x, &bola.y, jogador1[i].x, jogador1[i].y, lastKey);


        setCursor(0, 0); //Altera a posicao do cursor para o inicio

        desenhaTela(jogador1, jogador2, bola, mat, n_jogadores);

        Sleep(1000/30); //30 frames por segundo
    }
    }
    system("@cls||clear");
}

// Funcao de movimentacao de todos os personagens do jogador 1
void movimentoJogador1(JOGADOR jogador[], int lastKey[],int *velocidade, int velocidadeInicial, int n_jogadores){
    int i, j;
    int flag[4] = {0};
    int flagParede[4] = {0};

    //  velocidade Define a velocidade dos jogadores
    if(*velocidade == 0){
            // A flag detecta qual tecla foi pressionada e lastKey detecta a ultima tecla que foi pressionada
            if(GetAsyncKeyState('D')){
                flag[0] = 1;
                lastKey[0] = 1;

            }
            if(GetAsyncKeyState('A')){
                flag[1] = 1;

                lastKey[1] = 1;
            }
            if(GetAsyncKeyState('W')){
                flag[2] = 1;

                lastKey[2] = 1;
            }
            if(GetAsyncKeyState('S')){
                flag[3] = 1;

                lastKey[3] = 1;
            }

            // Para cada direcao escolhida para o movimento, primeiro checa se não ha nenhum jogador encostado na parede, depois movimenta
            // FlagParede diz se um jogador esta encostado em uma parede
            if(flag[0] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].x + 1 >= WIDTH - 1){
                        flagParede[0] = 1;
                    }
                }
                for(i = 0; i < n_jogadores; i++){
                    if(flagParede[0] == 0)
                        jogador[i].x+= 1;
                }
           }

            if(flag[1] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].x - 1 <= 0){
                      flagParede[1] = 1;
                    }
                }
                for(i = 0; i < n_jogadores; i++){
                    if(flagParede[1] == 0)
                        jogador[i].x-= 1;
                }
           }

            if(flag[2] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].y  - 1 <= 0){
                        flagParede[2] = 1;
                    }
                }
                 for(i = 0; i < n_jogadores; i++){
                    if(flagParede[2] == 0){
                        jogador[i].y-= 1;
                    }
                 }
           }

            if(flag[3] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].y + 1 >= HEIGHT-1){
                        flagParede[3] = 1;
                    }
                }
                for(i = 0; i < n_jogadores; i++){
                    if(flagParede[3] == 0)
                        jogador[i].y+= 1;
                }
           }
        // Faz com que a velocidade do jogador volte a seu valor inicial
        *velocidade = velocidadeInicial;
    } else{
        // Se velocidade nao for zero, diminui da velocidade
        *velocidade -= 1;
    }

}

// Funcao de movimentacao de todos os personagens do jogador 2, Cópia da funcao movimentoJogador1, só mudam as teclas que são checadas
// Teclas checadas: flechas do teclado
void movimentoJogador2(JOGADOR jogador[], int lastKey[],int *velocidade, int velocidadeInicial, int n_jogadores){
    int i, j;
    int flag[4] = {0};
    int flagParede[4] = {0};
    if(*velocidade == 0){
            if(GetAsyncKeyState(39)){
                flag[0] = 1;
                lastKey[0] = 1;

            }
            if(GetAsyncKeyState(37)){
                flag[1] = 1;

                lastKey[1] = 1;
            }
            if(GetAsyncKeyState(38)){
                flag[2] = 1;

                lastKey[2] = 1;
            }
            if(GetAsyncKeyState(40)){
                flag[3] = 1;

                lastKey[3] = 1;
            }


            if(flag[0] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].x + 1 >= WIDTH - 1){
                        flagParede[0] = 1;
                    }
                }
                for(i = 0; i < n_jogadores; i++){
                    if(flagParede[0] == 0)
                        jogador[i].x+= 1;
                }
           }

            if(flag[1] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].x - 1 <= 0){
                      flagParede[1] = 1;
                    }
                }
                for(i = 0; i < n_jogadores; i++){
                    if(flagParede[1] == 0)
                        jogador[i].x-= 1;
                }
           }

            if(flag[2] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].y  - 1 <= 0){
                        flagParede[2] = 1;
                    }
                }
                 for(i = 0; i < n_jogadores; i++){
                    if(flagParede[2] == 0){
                        jogador[i].y-= 1;
                    }
                 }
           }

            if(flag[3] == 1){
                for(i = 0; i < n_jogadores; i++){
                    if(jogador[i].y + 1 >= HEIGHT-1){
                        flagParede[3] = 1;
                    }
                }
                for(i = 0; i < n_jogadores; i++){
                    if(flagParede[3] == 0)
                        jogador[i].y+= 1;
                }
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
            *aceleracao = 20;
        } else if(*dirX && *dirY){ // Se a bola for para a diagonal
            *aceleracao = 15;// Isso evita que a bota vá muito para frente quando o chute for para a diagonal
        } else if(!*dirX && *dirY){ // Se a bola for para frente
            *aceleracao = 20;
        }
        chute = 0;
    }
    // Apos 2m de conducao, chuta
    if(cnt == 3){

        if(*dirX != 0 && !*dirY){ // Se a bola for para os lados
            *aceleracao = 6;
        } else if(*dirX && *dirY){ // Se a bola for para a diagonal
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

// Funcao que carrega a formacao dos jogadores e retorna o numero de jogadores em campo
int carregaFormacao(JOGADOR jogador1[], JOGADOR jogador2[]){
    FILE *arq;
    char mat[FORMACAO_Y][FORMACAO_X];
    int i, j;
    char nome[MAXLETRAS + 1];
    int n_jogadores = 0;
    //Abrir arquivo
    fflush(stdin);
    printf("Insira o nome do arquivo de formacao: ");
    le_texto(nome,sizeof(nome));
    // Abre o arquivo de texto para leitura
    if(!(arq = fopen(nome, "r"))){
        printf("Erro na abertura");
        return 0;
    } else{

    // Garante que o ponteiro esteja no inicio do arquivo
    fseek(arq, 0, SEEK_SET);

    // Registra a posição inicial dos jogadores
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

    // Copia a formacao para o segundo jogador, espelhada
    for(i = 0; i < n_jogadores; i++){
        jogador2[i].x = jogador1[i].x;
        jogador2[i].y = LINHAS - jogador1[i].y;
    }

    fclose(arq);
    }
    // retorna o numero de jogadores
    return n_jogadores;
}

// Funcao que desenha o jogo
void desenhaTela(JOGADOR jogador1[], JOGADOR jogador2[], BOLA bola, char mat[][COLUNAS], int n_jogadores){
    int i, j, k;
    for(i=0; i<HEIGHT; i++){
            for(j=0; j<WIDTH; j++){
                if(i == 0 || j == 0 || i == LINHAS-1 || j == COLUNAS -1){
                    mat[i][j] = '#';
                    if(j >= 25 && j<= 37){
                        mat[i][j] = ' ';
                    }
                } else{
                    mat[i][j] = '_';
                }
                if(bola.x == j && bola.y == i) mat[i][j] = 'O';
                for(k = 0; k < n_jogadores; k++){
                    if(jogador1[k].x == j && jogador1[k].y == i) mat[i][j] = 'W';
                    if(jogador2[k].x == j && jogador2[k].y == i) mat[i][j] = 'M';
                }
                printf("%c", mat[i][j]);

            }
            printf("\n");
        }
}

