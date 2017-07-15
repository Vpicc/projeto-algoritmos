#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define COLUNAS 65
#define LINHAS 64
#define MAXLETRAS 20
#define FORMACAO_X 60
#define FORMACAO_Y 30
#define MAXJOGADORES 11
#define LIMESQGOL 25
#define LIMDIRGOL 39

#define WIDTH COLUNAS
#define HEIGHT LINHAS

// cria o tipo jogador
typedef struct{
    int x;
    int y;
} JOGADOR;

// cria o tipo bola
typedef struct{
    int x;
    int y;
} BOLA;
// cria o tipo goleiro
typedef struct{
    int x;
    int y;
} GOLEIRO;

typedef struct{
    int pontosJog1;
    int pontosJog2;
} PONTUACAO;

// funcao que escolhe posicao do cursor
void setCursor(int x, int y)
{
    COORD coordinate;
    coordinate.X = x;
    coordinate.Y = y;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(screen, coordinate);
}

void iniciaJogo(char mat[][COLUNAS], int tempo, int velocidadeInicial, int tamGol)
{
    // Numero maximo de jogadores em campo: 11
    JOGADOR jogador1[MAXJOGADORES];
    JOGADOR posicaoInicialJogador1[MAXJOGADORES];
    JOGADOR jogador2[MAXJOGADORES];
    JOGADOR posicaoInicialJogador2[MAXJOGADORES];
    GOLEIRO goleiro1;
    GOLEIRO goleiro2;
    BOLA bola;
    int i;
    int start;
    int t;
    int aceleracao = 0;
    int lastKey1[4] = {0};
    int lastKey2[4] = {0};
    int velocidade1 = velocidadeInicial;
    int velocidade2 = velocidadeInicial;
    PONTUACAO pontosDoJogo;
    pontosDoJogo.pontosJog1 = 0;
    pontosDoJogo.pontosJog2 = 0;
    bola.x = COLUNAS/2;
    bola.y = LINHAS/2;
    int n_jogadores = 0;
    goleiro1.y = 0;
    goleiro1.x = WIDTH/2;
    goleiro2.y = HEIGHT-1;
    goleiro2.x = WIDTH/2;

    // Carrega a formação em arquivo de texto e retorna o numero de jogadores
    n_jogadores = carregaFormacao(jogador1,jogador2);
    // Salva as posicoes iniciais
            for(i = 0; i < n_jogadores; i++){
            posicaoInicialJogador1[i] = jogador1[i];
            posicaoInicialJogador2[i] = jogador2[i];
        }

    // Inicia contagem de tempo
    start = tempo + (clock())/CLOCKS_PER_SEC;
    t = start;

    if(n_jogadores > 0){
    while(t) // Enquanto a tecla ESC nao for pressionada
    {

        t = start - clock()/CLOCKS_PER_SEC;
        //printf("Tempo: %*d\t", 2, t);
        imprimeTempoPontuacao(t, pontosDoJogo);
        movimentoGoleiro(bola, &goleiro1, 'D', 'A', velocidade1, velocidadeInicial, lastKey1,tamGol);
        movimentoGoleiro(bola, &goleiro2, 39, 37, velocidade2, velocidadeInicial, lastKey2,tamGol);
        movimentoJogador1(jogador1, lastKey1, &velocidade1, velocidadeInicial, n_jogadores);
        movimentoJogador2(jogador2, lastKey2, &velocidade2, velocidadeInicial, n_jogadores);

        movimentoBola(&bola, jogador1, jogador2, lastKey1, lastKey2, n_jogadores, tamGol, &aceleracao);

        scoreDoJogo(bola, &pontosDoJogo);

        resetaPosicoesGol(&bola, jogador1, jogador2, posicaoInicialJogador1, posicaoInicialJogador2, n_jogadores, &aceleracao);






        setCursor(0, 0); // Altera a posicao do cursor para o inicio

        desenhaTela(jogador1, jogador2, goleiro1, goleiro2, bola, mat, n_jogadores, tamGol);

        Sleep(1000/30); //30 frames por segundo

        // Limpando o buffer a cada frame
        if(kbhit()){
            getch();
        }
    }
    }
    // Limpa a tela
    system("@cls||clear");
    printf("Fim de jogo\n");
    Sleep(2000);


}

// Funcao de movimentacao de todos os personagens do jogadmovimentoGoleiro(bola,goleiro1,'D','A',&velocidade,velocidadeInicial,lastKey1);or 1
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

void movimentoGoleiro(BOLA bola, GOLEIRO *goleiro, int esquerda, int direita, int velocidade, int velocidadeInicial, int lastKey[], int tamGol){
    // Quando o goleiro está conduzindo a bola, o jogador movimenta o goleiro
        if((bola.x <= goleiro->x + 1 && bola.x >= goleiro->x - 1  )&& (bola.y <= goleiro->y + 1 && bola.y >= goleiro->y - 1 )){
             if(velocidade == 0){
                // A flag detecta qual tecla foi pressionada e lastKey detecta a ultima tecla que foi pressionada
                if(GetAsyncKeyState(direita)){
                    lastKey[0] = 1;
                    if(goleiro->x + 1 <= LIMDIRGOL - tamGol/2){
                            goleiro->x += 1;
                        }
                }

                if(GetAsyncKeyState(esquerda)){
                    if(goleiro->x - 1 >= LIMESQGOL + tamGol/2){
                            goleiro->x -= 1;
                    }
                }

            }
        } else{
            // Quando o goleiro não está conduzindo a bola, ele se mexe automaticamente
            if(velocidade == 0){
                if(goleiro->x > bola.x){
                    if(goleiro->x - 1 >= LIMESQGOL + tamGol/2){
                        goleiro->x = goleiro->x - 1;
                    }
                } else if(goleiro->x < bola.x){
                    if(goleiro->x + 1 <= LIMDIRGOL - tamGol/2){
                        goleiro->x = goleiro->x + 1;
                    }

                }
            }

        }


}

void movimentoBola(BOLA *bola, JOGADOR jogador1[], JOGADOR jogador2[], int lastKey1[], int lastKey2[], int n_jogadores, int tamGol, int *aceleracao){
    int i;
    static int dirX = 0, dirY = 0;

    colisoesBolaJogador(jogador1, bola, aceleracao, &dirX, &dirY, lastKey1, n_jogadores, 'X');
    colisoesBolaJogador(jogador2, bola, aceleracao, &dirX, &dirY, lastKey2, n_jogadores, 'L');

    //verifica colisoes com a parede
    if(bola->x+dirX <= 0 || bola->x+dirX >= WIDTH-1) dirX*=-1;
    if((bola->y+dirY <= 0 || bola->y+dirY >= HEIGHT-1) && !(bola->x >= LIMESQGOL + tamGol/2 && bola->x <= LIMDIRGOL - tamGol/2)) dirY*=-1;


    //movimenta a bola
    if(*aceleracao > 0){
        bola->x = bola->x + dirX;
        bola->y = bola->y + dirY;

        *aceleracao = *aceleracao - 1;

        printf("ACELERACAO: %d", *aceleracao);
    }
    for(i = 0; i < 4; i++){
        lastKey1[i] = 0;
    }
    for(i = 0; i < 4; i++){
        lastKey2[i] = 0;
    }


}

void colisoesBolaJogador(JOGADOR jogador[], BOLA *bola, int *aceleracao,int *dirX, int *dirY, int lastKey[], int n_jogadores, int teclaDeChute){
    static int cnt = 0;
    int chute = 0;
    int i;

     //if((posX <= jogador[0].x + 1 && posX >= jogador[0].x - 1  )&& (posY <= jogador[0].y + 1 && posY >= jogador[0].y - 1 ))
    // Colisoes com jogador LastKey => 0 = Direita 1 = Esquerda 2 = Cima 3 = Baixo

    //if((posX == jogador[0].x && posY == jogador[0].y)){
    for(i = 0; i < n_jogadores; i++){
    if((bola->x <= jogador[i].x + 1 && bola->x >= jogador[i].x - 1  )&& (bola->y <= jogador[i].y + 1 && bola->y >= jogador[i].y - 1 )){
        //*aceleracao = 1;
        if(lastKey[0] == 1 && lastKey[2] == 1){
            bola->x = jogador[i].x + 1;
            bola->y = jogador[i].y - 1;
            *dirX = 1;
            *dirY = -1;
            cnt++;
        }else if(lastKey[0] == 1 && lastKey[3] == 1){
            bola->x = jogador[i].x + 1;
            bola->y = jogador[i].y + 1;
            *dirX =1;
            *dirY = 1;
            cnt++;
        }else if(lastKey[1] == 1 && lastKey[2] == 1){
            bola->x = jogador[i].x - 1;
            bola->y = jogador[i].y - 1;
            *dirX = -1;
            *dirY = -1;
            cnt++;
        }else if(lastKey[1] == 1 && lastKey[3] == 1){
            bola->x = jogador[i].x - 1;
            bola->y = jogador[i].y + 1;
            *dirX = -1;
            *dirY = 1;
            cnt++;
        }else if(lastKey[0] == 1){
            bola->x = jogador[i].x + 1;
            bola->y = jogador[i].y;
            *dirX = 1;
            *dirY = 0;
            cnt++;
        }else if(lastKey[1] == 1){
            bola->x = jogador[i].x - 1;
            bola->y = jogador[i].y;
            *dirX = -1;
            *dirY = 0;
            cnt++;
        } else if(lastKey[2] == 1){
            bola->y = jogador[i].y - 1;
            bola->x = jogador[i].x;
           *dirY = -1;
            *dirX = 0;
            cnt++;
        }else if(lastKey[3] == 1){
            bola->y = jogador[i].y + 1;
            bola->x = jogador[i].x;
           *dirY = 1;
            *dirX = 0;
            cnt++;
        }

        // TODO: inversao de direcao

        // Chute longo
        if(GetAsyncKeyState(teclaDeChute)){
            chute = 1;
            cnt = 0;
        }
    }
    }


    // Faz o chute só funcionar quando esta encostado na bola e apertou a tecla de chute
    GetAsyncKeyState(teclaDeChute);

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

void scoreDoJogo(BOLA bola,PONTUACAO *pontosDoJogo){
    if(bola.y > HEIGHT){
        pontosDoJogo->pontosJog1 += 1;
    }
    if(bola.y < 0){
        pontosDoJogo->pontosJog2 += 1;
    }
}

void resetaPosicoesGol(BOLA *bola, JOGADOR jogador1[], JOGADOR jogador2[], JOGADOR posicaoInicialJogador1[], JOGADOR posicaoInicialJogador2[], int n_jogadores, int *aceleracao){
    int i;
    if(bola->y > HEIGHT || bola->y < 0){
        *aceleracao = 0;
        bola->x = COLUNAS/2;
        bola->y = LINHAS/2;
        for(i = 0; i < n_jogadores; i++){
            jogador1[i] = posicaoInicialJogador1[i];
            jogador2[i] = posicaoInicialJogador2[i];
        }
    }

}

void imprimeTempoPontuacao(int t, PONTUACAO score){
    printf("Tempo: %*d\tTime 1: %d\tTime 2: %d\t", 2, t, score.pontosJog1, score.pontosJog2);
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
            if(n_jogadores > MAXJOGADORES){
                n_jogadores = MAXJOGADORES;
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
void desenhaTela(JOGADOR jogador1[], JOGADOR jogador2[], GOLEIRO goleiro1, GOLEIRO goleiro2, BOLA bola, char mat[][COLUNAS], int n_jogadores, int tamGol){
    int i, j, k;
    for(i=0; i<HEIGHT; i++){
            for(j=0; j<WIDTH; j++){
                if(i == 0 || j == 0 || i == LINHAS-1 || j == COLUNAS -1){
                    mat[i][j] = '#';
                    if(j >= LIMESQGOL + tamGol/2 && j<= LIMDIRGOL - tamGol/2){
                        mat[i][j] = ' ';
                    }
                } else{
                    mat[i][j] = ' ';
                }
                if(bola.x == j && bola.y == i) mat[i][j] = 'O';
                for(k = 0; k < n_jogadores; k++){
                    if(jogador1[k].x == j && jogador1[k].y == i) mat[i][j] = 'W';
                    if(jogador2[k].x == j && jogador2[k].y == i) mat[i][j] = 'M';
                }
                if(goleiro1.x == j && goleiro1.y == i) mat[i][j] = 'W';
                if(goleiro2.x == j && goleiro2.y == i) mat[i][j] = 'M';

            }
            mat[i][j] = '\0';
            puts(mat[i]);
        }
}

