#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCTS
typedef struct S_REG //struct com os campos que os registros que o arquivo com os registros de inserção terão
{
    char codC[12];
    char codV[8];
    char nomeC[50];
    char nomeV[50];
    char dias[4];
}REG;

typedef struct S_BUSCA //struct com os campos que os registros que o arquivo com os registros de remoção terão
{
    char codC[12];
    char codV[8];
}REG_BUSCA;

typedef struct S_INDICES
{
    char chave[19];
    int desloc;
}INDICES;

//PROTOTIPOS(declaracao das funcoes)
void criaArquivos();
int carregaArq(REG *insere, REG_BUSCA *busca);
int carregarIndices(INDICES *indices, int *qntIndices);
int insereReg(REG *insere, INDICES *indices, int *qntIndices);
int buscaReg(REG_BUSCA *busca, INDICES *indices, int qntIndices);
int ordenaReg(INDICES *indices, int qntIndices);
void atualizaIndices(INDICES *indices, int qntIndices);

//MAIN
int main(){ 
    REG insere[25]; //vetor do tipo REG para armazenar dados de possíveis registros que serão inseridos no arquivo principal
    REG_BUSCA busca[25]; //vetor do tipo REG_BUSCA para armazenar dados de possíveis registros que serão removidos do arquivo principal
    INDICES indices[25];
    int qntIndices;

    criaArquivos(); //cria o arquivo.bin caso nao exista e coloca header como -1, caso exista le o valor da header e armazena

    //funcao para carregar os dados de insere.cpp nos vetores insere e busca
    if(carregaArq(insere, busca)) //passando os vetores como parametro para serem "preenchidos"
        printf("Arquivos carregados com sucesso!\n");
    else{
        printf("ERRO - Nao foi possivel carregar os arquivos\n");
        return 0;
    }    
    if(carregarIndices(indices, &qntIndices)) //passando os vetores como parametro para serem "preenchidos"
        printf("Arquivos carregados com sucesso!\n");
    else{
        printf("ERRO - Nao foi possivel carregar o arquivo indices.bin\n");
        return 0;
    }    

    int menu;
    while (1)
    {
        printf("\n\t>>>  MENU  <<<\n");
        printf("1 - Inserir\n");
        printf("2 - Buscar\n");
        printf("0 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &menu);

        switch (menu)
        {
            case 1:
                insereReg(insere, indices, &qntIndices);
                ordenaReg(indices, qntIndices);
                break; 
            case 2:
                buscaReg(busca, indices, qntIndices);
                break;
            case 0:
                atualizaIndices(indices, qntIndices);
                printf("Encerrando programa\n");
                return 0;
                break;
            
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }
}

// FUNCOES
void criaArquivos(){
    FILE *fp;

    if ((fp = fopen("arquivo.bin","ab+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo arquivo.bin\n");
        return; 
    }
    fclose(fp);

    if ((fp = fopen("indices.bin","ab+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo arquivo.bin\n");
        return; 
    }
    fclose(fp);
}

int carregaArq(REG *insere, REG_BUSCA *busca){
    // Copiando insere.bin para memoria
    FILE *ins; 
    int tamI;

    if ((ins = fopen("insere.bin","rb")) == NULL) // abre o arquivo insere.bin já existente para leitura. ins sera o nosso arquivo insere.bin 
    {
        printf("ERRO - Nao foi possivel abrir o arquivo insere.bin\n");
        return 0;
    }

    fseek(ins, 0, SEEK_END);
    tamI = ftell(ins)/sizeof(REG);    

    rewind(ins); // volta no inicio do arquivo
    
    fread(insere, sizeof(REG), tamI, ins); // le todo o arquivo e armazena em "insere"

    fclose(ins); // fecha arquivo

    // Copiando busca para memoria
    FILE *buc;
    int tamB;

    if ((buc = fopen("busca_p.bin","rb")) == NULL) // abre busca.bin e confere se deu certo
    {
        printf("ERRO - Nao foi possivel abrir o arquivo busca.bin\n");
        return 0;
    } 
    
    fseek(buc, 0, SEEK_END);
    tamB = ftell(buc)/ sizeof(REG_BUSCA);

    rewind(buc); // volta no inicio do arquivo
    
    fread(busca, sizeof(REG_BUSCA), tamB, buc); // le todo o arquivo e armazena em "busca"

    fclose(buc); // fecha arquivo
    
    return 1;
}

int carregarIndices(INDICES *indices, int *qntIndices){
    FILE *ind;
    int acumIndices=0;

    if ((ind = fopen("indices.bin","rb")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo indices.bin\n");
        return 0;
    }

    fseek(ind, 0, SEEK_END); //coloca o ponteiro do arquivo no final
    
    *qntIndices = ftell(ind)/(sizeof(INDICES)-1); // faz o tamanho do arquivo dividido pelo tamanho da struct pra ter o tam de structs

    rewind(ind); // reseta o ponteiro pra arquivo no começo

    for (int i = 0; i < *qntIndices; i++)
    {
        fread(&indices[i].chave, sizeof(char), 19, ind);
        fread(&indices[i].desloc, sizeof(int), 1, ind);
    }
    
    // fread(indices, sizeof(INDICES), (*qntIndices), ind); //le todo o arquivo e armazena em "indices"

    fclose(ind); 

    printf("qnt = %d\n", *qntIndices);
    for (int i = 0; i < *qntIndices; i++)
    {
        printf("-%d-\n", indices[i].desloc);
    }

    return 1;
}

int insereReg(REG *insere, INDICES *indices, int *qntIndices){
    FILE *fp;
    int ind, acum=0, deslocamento;
    char chave[20]="\0";
    

    printf("Insira o indice do registro: ");
    scanf("%d", &ind);
    
    // acumula o tamanho do registro (variavel)
    acum += strlen(insere[ind].codC);
    acum += strlen(insere[ind].codV);
    acum += strlen(insere[ind].nomeC);
    acum += strlen(insere[ind].nomeV);
    acum += strlen(insere[ind].dias);
    acum += 5; // total de "|" por registro

    if ((fp = fopen("arquivo.bin","rb+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo arquivo.bin\n");
        return 0;
    }
    
    fseek(fp, 0, SEEK_END); // vai para o final do arquivo

    deslocamento = ftell(fp); // armazena o deslocamento ate a nova posicao

    // escreve o tamanho do registro no arquivo (intero)
    fwrite(&acum, sizeof(char), 1, fp);

    // escreve o registro no arquivo dividindo os campos com "|"
    fwrite(&insere[ind].codC, sizeof(char), strlen(insere[ind].codC), fp);
    fprintf(fp, "|");
    fwrite(&insere[ind].codV, sizeof(char), strlen(insere[ind].codV), fp);
    fprintf(fp, "|");
    fwrite(&insere[ind].nomeC, sizeof(char), strlen(insere[ind].nomeC), fp);
    fprintf(fp, "|");
    fwrite(&insere[ind].nomeV, sizeof(char), strlen(insere[ind].nomeV), fp);
    fprintf(fp, "|");
    fwrite(&insere[ind].dias, sizeof(char), strlen(insere[ind].dias), fp);
    fprintf(fp, "|");
    
    fclose(fp); // fecha arquivo

    strcat(chave, insere[ind].codC);
    strcat(chave, insere[ind].codV); // concatena formando a chave
    strcpy(indices[(*qntIndices)].chave, chave); // coloca na ultima posicao do vetor
    indices[(*qntIndices)].desloc = deslocamento; //armazena o deslocamento

    (*qntIndices)++; //soma a quantidade de indices

    return 1;
}

int buscaReg(REG_BUSCA *busca, INDICES *indices, int qntIndices){
    char aux[124]="\0", chave[20]="\0";
    int tam=0, ind;
    FILE *fp;

    printf("Insira o indice do registro a ser buscado: ");
    scanf("%d", &ind);

    strcat(chave, busca[ind].codC); // concatena chave e codC, o resultado armazena em chave
    strcat(chave, busca[ind].codV); // concatena chave e codV, o resultado armazena em chave

    for (int i = 0; i < qntIndices; i++) //percorre o vetor indices
    {
        if (strcmp(chave, indices[i].chave) == 0) // compara se a posicao no vetor é o mesmo digitado pelo usuario(chave)
        {
            printf("\n>> Registro encontrado: <<\n");
            if ((fp = fopen("arquivo.bin","rb+")) == NULL) // abre no modo escrita+
            {
                printf("ERRO - Nao foi possivel abrir o arquivo\n");
                return 0;
            }

            fseek(fp, indices[i].desloc, SEEK_SET); // seta o "cursor" na posição do registro
            
            fread(&tam, sizeof(char), 1, fp); // le o tamanho do registro

            fread(aux, sizeof(char), tam, fp); //le o registro todo
          
            // printf("%s\n", aux);  //printa o registro
            for (int i = 0; i < tam; i++)
            {
                if (aux[i] == '|')
                {
                    printf("\n");
                    i++;
                }
                printf("%c", aux[i]);
            }
            
            fclose(fp);
            return 1;
        } 
    }
    printf("Arquivo nao encontrado\n");
    return 0;
}

void atualizaIndices(INDICES *indices, int qntIndices){// escreve o vetor no arquivo indices.bin
    FILE *ind;

    if ((ind = fopen("indices.bin","rb+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo arquivo.bin\n");
        return;
    }

    for (int i = 0; i < qntIndices; i++)
    {
        fwrite(&indices[i].chave, sizeof(char), 19, ind); //escreve a chave inclusa do \0
        fwrite(&indices[i].desloc, sizeof(int), 1, ind); //escreve o delocamento
    }

    fclose(ind);
}

int ordenaReg(INDICES *indices, int qntIndices){ //insertion sort
    int i, j;
    INDICES cop;

    for(i = 1; i < qntIndices; i++)
    {
        strcpy(cop.chave, indices[i].chave);
        cop.desloc = indices[i].desloc;

        for(j = i-1; j >= 0 && strcmp(cop.chave, indices[j].chave) == -1; j--)
        {
            strcpy(indices[j+1].chave, indices[j].chave);
            indices[j+1].desloc = indices[j].desloc;
        }
        strcpy(indices[j+1].chave, cop.chave);
        indices[j+1].desloc = cop.desloc;
    }
}