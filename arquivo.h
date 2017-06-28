#include <stdio.h>
#include <stdlib.h>

#define COLUNAS 64
#define LINHAS 100
#define MAXCHAR 20

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

void carregaArquivo(){
    FILE *arq;
    char mat[LINHAS][COLUNAS];
    int i, j;
    char nome[MAXCHAR + 1];

/* TODO: Abrir arquivo
    fflush(stdin);
    le_texto(nome,sizeof(nome));

    if(!(arq = fopen(nome, "rb"))){
        printf("Erro na abertura");
        return;
    }
*/

    for(i = 0; i < LINHAS; i++){
        for(j = 0; j < COLUNAS; j++){
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
            // para teste, enquanto nao sei abrir file
            mat[8][20] = 'X';
            mat[8][COLUNAS-20] = 'X';
            mat[10][28] = 'X';
            mat[10][COLUNAS-28] = 'X';
            mat[LINHAS-8][20] = 'X';
            mat[LINHAS-8][COLUNAS-20] = 'X';
            mat[LINHAS-10][28] = 'X';
            mat[LINHAS-10][COLUNAS-28] = 'X';
            mat[49][31] = 'O';
            //
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }

    //fclose(arq);
}
