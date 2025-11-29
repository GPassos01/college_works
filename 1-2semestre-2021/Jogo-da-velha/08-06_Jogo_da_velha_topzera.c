#include <stdio.h>
#include <windows.h> 
#define TAM 3

void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

int main()
{
    int tab[TAM][TAM]={0};
    int a, b, i, j, jogo=1, turno=0, verif; //auxiliares
    int diagonal1, diagonal2, diagonalS1, diagonalS2, linha1, linha2, coluna1, coluna2, all=0;
    
    printf("\t>>>INICIO DO JOGO<<<\n");
    printf("\n\n");
    printf("\t   0   1   2 \n");
    printf("\t0    %c   %c   \n", 179, 179);
    printf("\t  %c%c%c%c%c%c%c%c%c%c%c\n", 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196);
    printf("\t1    %c   %c   \n", 179, 179);
    printf("\t  %c%c%c%c%c%c%c%c%c%c%c\n", 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196);
    printf("\t2    %c   %c   \n", 179, 179);
    while(jogo)
    {
        verif=1;
        do{
            gotoxy(1,11);
            if(turno%2==0)
                printf("\t>>Jogador 1<<");
            else
                printf("\t>>Jogador 2<<");
            printf("\nEscolha a linha e coluna: ");
            scanf("%d", &a);
            //printf("Escolha a coluna: ");
            scanf("%d", &b);
            gotoxy(27,12);
            printf("    ");
            if(tab[a][b]==0 && a<3 && b<3 && a>=0 && b>=0)
            {
                if(turno%2==0)
                {
                    tab[a][b]=1;
                    gotoxy(4*b+12,2*a+5);
                    printf("X");
                }
                else
                {
                    tab[a][b]=2;
                    gotoxy(4*b+12,2*a+5);
                    printf("O");
                }
                turno++;
                verif=0;
                
            }
            else
                printf("\nErro\n");
        }while(verif);
        all++;
        diagonal1=0;
        diagonal2=0;
        diagonalS1=0;
        diagonalS2=0;
        for(i=0; i<TAM; i++)
        {

            linha1=0;
            linha2=0;
            coluna1=0;
            coluna2=0;
            for(j=0; j<TAM; j++)
            {
                //verificando linhas
                if(tab[i][j]==1)
                {
                    linha1++;
                }
                else if(tab[i][j]==2)
                {
                    linha2++;
                }
                //verificando colunas
                if(tab[j][i]==1)
                {
                    coluna1++;
                }
                else if(tab[j][i]==2)
                {
                    coluna2++;
                }
            }
                //verificando diagonal principal
                if(tab[i][i]==1)
                {
                    diagonal1++;
                }
                else if(tab[i][i]==2)
                {
                    diagonal2++;
                }
                //verificando diagonal secundaria
                if(tab[i][2-i]==1)
                {
                    diagonalS1++;
                }
                else if(tab[i][2-i]==2)
                {
                    diagonalS2++;
                }
                //verificando se tem linha ganhador
                if(linha1==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 1 venceu!!\n");
                    printf("Linha %d\n", i);
                    jogo=0;
                }
                else if(linha2==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 2 venceu!!\n");
                    printf("Linha %d\n", i);
                    jogo=0;
                }
                //verificando vitora colunas
                else if(coluna1==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 1 venceu!!\n");
                    printf("Coluna %d\n", i);
                    jogo=0;
                }
                else if(coluna2==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 2 venceu!!\n");
                    printf("Coluna %d\n", i);
                    jogo=0;
                }
                //verificando vitora diagonal principal
                else if(diagonal1==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 1 venceu!!\n");
                    printf("Diagonal principal\n");
                    jogo=0;
                }
                else if(diagonal2==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 2 venceu!!\n");
                    printf("Diagonal principal\n");
                    jogo=0;
                }
                //verificando vitoria diag secundaria
                else if(diagonalS1==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 1 venceu!!\n");
                    printf("Diagonal secundaria\n");
                    jogo=0;
                }
                else if(diagonalS2==3)
                {
                    gotoxy(27,12);
                    printf("\n");
                    printf("\nJogador 2 venceu!!\n");
                    printf("Diagonal secundaria\n");
                    jogo=0;
                }
        }
        if(all==9)
        {
            gotoxy(27,12);
            printf("\n");
            printf("\nEmpate!!\n");
            jogo=0;
        }
    }
}