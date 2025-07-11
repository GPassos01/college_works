#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCT
typedef struct S_IMGEM
{
    char tip_arq[3];
    int colunas;
    int linhas;
    int max_tons;
    int *matriz;
}S_IMG;

// PROTOTIPOS

void limiarizacao(S_IMG fp);
void negativo(S_IMG fp);
void histograma(S_IMG fp);

// MAIN
int main()
{
    FILE* img_pgm;
    S_IMG fp;

    printf("\n\t >>>  INICIO  <<<\n");

    img_pgm = fopen("exemplo.pgm", "rb");
    if(img_pgm == NULL)
    {
        printf("ERRO - Nao foi possivel abrir o arquivo!\n");
        return 0;
    }
    fscanf(img_pgm, "%c%c\n", &fp.tip_arq[0], &fp.tip_arq[1]);
    fp.tip_arq[2] = 0;
    fscanf(img_pgm, "%d ", &fp.colunas);
    fscanf(img_pgm, "%d\n", &fp.linhas);
    fscanf(img_pgm, "%d\n", &fp.max_tons);
    fp.matriz = calloc(fp.linhas*fp.colunas, sizeof(int));

    for(int i=0; i<fp.linhas; i++)
    {
        for(int j=0; j<fp.colunas; j++)
        {
            fscanf(img_pgm, "%d", (fp.matriz + j + fp.colunas*i));
        }
    }

    limiarizacao(fp);
    negativo(fp);
    histograma(fp);

    printf("\nFinalizando programa...\n");
    fclose(img_pgm);
    free(fp.matriz);

    return 0;
}

// FUNCOES
void limiarizacao(S_IMG fp)
{
    int limiar=150;
    FILE* limiar_PGM;

    limiar_PGM = fopen("limiar.pgm", "wb");

    fprintf(limiar_PGM, "%s\n", fp.tip_arq);
    fprintf(limiar_PGM, "%d %d\n", fp.colunas, fp.linhas);
    fprintf(limiar_PGM, "%d\n", fp.max_tons);
    for(int i=0; i<fp.colunas * fp.linhas; i++)
    {
        if(fp.matriz[i]>150)
            fprintf(limiar_PGM, "%d ", 255);
        else
            fprintf(limiar_PGM, "%d ", 0);
    }

    fflush(limiar_PGM);
    fclose(limiar_PGM);

    printf("\n>> LIMIARIZACAO criada com sucesso!\n");
    return;
}

void negativo(S_IMG fp)
{
    FILE* negativo;
    

    negativo = fopen("negativo.pgm", "wb");

    fprintf(negativo, "%s\n", fp.tip_arq);
    fprintf(negativo, "%d %d\n", fp.colunas, fp.linhas);
    fprintf(negativo, "%d\n", fp.max_tons);
    for(int i=0; i<fp.colunas * fp.linhas; i++)
    {
        fprintf(negativo, "%d ", 255 - fp.matriz[i]);
    }

    fflush(negativo);
    fclose(negativo);

    printf("\n>> NEGATIVO criado com sucesso!\n");
    return;
}

void histograma(S_IMG fp)
{
    FILE* histograma;
    int *cont;

    cont = calloc(fp.max_tons, sizeof(int));
    for(int i=0; i<fp.max_tons; i++)
        cont[i] = 0;
    
    for(int i=0; i<(fp.colunas*fp.linhas); i++)
        cont[fp.matriz[i]]++;

    histograma = fopen("histograma.txt", "w");

    for(int i=0; i<fp.max_tons; i++)
    {
        fprintf(histograma, "%d pixels no tom: %d\n", cont[i], i);
    }

    fflush(histograma);
    fclose(histograma);
    
    printf("\n>> HISTOGRAMA criado com sucesso!\n");
    return;
}