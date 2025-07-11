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

typedef struct S_REMOVE //struct com os campos que os registros que o arquivo com os registros de remoção terão
{
    char codC[12];
    char codV[8];
}REG_REMOVE;

//PROTOTIPOS(declaracao das funcoes)
void criaArquivo(int *header);
int carregaArq(REG *insere, REG_REMOVE *remove);
int insereReg(REG *insere, int header);
int removeReg(REG_REMOVE *remove, int *header);
void inserirListRemov(int pos);
int compactaArq();

//MAIN
int main(){ 
    REG insere[25]; //vetor do tipo REG para armazenar dados de possíveis registros que serão inseridos no arquivo principal
    REG_REMOVE remove[25]; //vetor do tipo REG_REMOVE para armazenar dados de possíveis registros que serão removidos do arquivo principal
    
    //funcao para carregar os dados de insere.cpp nos vetores insere e remove
    if(carregaArq(insere, remove)) //passando os vetores como parametro para serem "preenchidos"
        printf("Arquivos carregados com sucesso!\n");
    else{
        printf("ERRO - Nao foi possivel carregar os arquivos\n");
        return 0;
    }
    
    int header;
    criaArquivo(&header); //cria o arquivo.bin caso nao exista e coloca header como -1, caso exista le o valor da header e armazena

    int menu;
    while (1)
    {
        printf("\n\t>>>  MENU  <<<\n");
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Compactar\n");
        printf("0 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &menu);

        switch (menu)
        {
            case 1:
                insereReg(insere, header);
                break;
            case 2:
                removeReg(remove, &header);
                break;
            case 3:
                compactaArq();
                break;
            case 0:
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
void criaArquivo(int *header){
    FILE *fp;

    if ((fp = fopen("arquivo.bin","ab+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo arquivo.bin\n");
        return 0; 
    }

    int tamArq=0;
    fseek(fp, 0, SEEK_END); //(arquivo, quantidade de bytes que vai andar dps de ajustar o "cursor", ajusta o "cursor" para o final do arquivo)
    tamArq = ftell(fp); // retorna o tamanho do arquivo até o "cursor", como ele esta no final retorna o tamanho total
    
    if(tamArq <= 0){ // se o arquivo tiver vazio
        *header = -1; //define header para -1
        fwrite(header, 1, sizeof(int), fp); //escreve header no arquivo
    }
    else{
        rewind(fp); //reseta o "cursor" pro começo do arquivo
        fread(header, sizeof(int), 1, fp); //le o valor do header
    }
    fclose(fp);
}

int carregaArq(REG *insere, REG_REMOVE *remove){
    FILE *ins, *rem; 
    REG *auxI;
    REG_REMOVE *auxR;
    int acumI=0, tamI=0, acumR=0, tamR=0;

    // Copiando insere.bin para memoria
    if ((ins = fopen("insere.bin","rb")) == NULL) // abre o arquivo insere.bin já existente para leitura. ins sera o nosso arquivo insere.bin 
    {
        printf("ERRO - Nao foi possivel abrir o arquivo insere.bin\n");
        return 0;
    }
    
    auxI = malloc(sizeof(REG)); //aloca um REG

    while (!feof(ins)) // enquanto nao chegou no final do arquivo(insere.bin)
    { 
        acumI = fread(auxI, sizeof(REG), 1, ins); // acumula a quantidade de blocos do tamanho "REG" do arquivo "ins"
        tamI += acumI; // tamI representa quantidade de "blocos" do tamanho de REG no arquivo (quantidade de registros)
    }

    rewind(ins); // volta no inicio do arquivo
    
    fread(insere, sizeof(REG), tamI, ins); // le todo o arquivo e armazena em "insere"

    fclose(ins); // fecha arquivo

    // Copiando Remove para memoria
    if ((rem = fopen("remove.bin","rb")) == NULL) // abre remove.bin e confere se deu certo
    {
        printf("ERRO - Nao foi possivel abrir o arquivo remove.bin\n");
        return 0;
    } 
    
    auxR = malloc(sizeof(REG_REMOVE)); //aloca um REG_REMOVE

    while (!feof(rem)) // enquanto nao chegou no final do arquivo
    {
        acumR = fread(auxR, sizeof(REG_REMOVE), 1, rem); // acumula a quantidade de blocos do tamanho "REG" do arquivo "ins"
        tamR += acumR; // tamI representa quantidade de "blocos" do tamanho de REG no arquivo (quantidade de registros)
    } 

    rewind(rem); // volta no inicio do arquivo
    
    fread(remove, sizeof(REG_REMOVE), tamR, rem); // le todo o arquivo e armazena em "remove"

    fclose(rem); // fecha arquivo
    
    return 1;
}

int insereReg(REG *insere, int header){
    FILE *fp;
    int ind, acum=0;
    

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

    int esp, pos = header; //esp = espaco disponivel, pos = posicao do espaco disponivel
    int posAnt = 0, posProx;//posicao anterior, proxima posicao
    while (1)
    {
        if(pos == -1){ //caso a lista de removidos esteja vazia ou chegado ao fim
            fseek(fp, 0, SEEK_END); // vai para o final do arquivo para insercao
            break;
        }
        else{
            fseek(fp, pos, SEEK_SET); //vai para posicao armazenada no pos
            fread(&esp, sizeof(int), 1, fp); //le o tamanho do espaco e armazena em "esp"
            fseek(fp, pos+sizeof(int)+sizeof(char), SEEK_SET); //vai ate a posicao, pula o indicador de tamanho, pula '*'
            fread(&posProx, sizeof(int), 1, fp); // le a proxima posicao da lista de removidos
            
            if (esp >= acum){ //caso tenha espaco suficiente para armazena o registro
                fseek(fp, posAnt, SEEK_SET); //volta na posição anterior(caso seja o header volta no inicio do arquivo)
                if(posAnt != 0) // se não for o header
                    fseek(fp, posAnt+sizeof(int)+sizeof(char), SEEK_SET); //vai ate a posicao anterior, pula o indicador de tamanho, pula '*'
                
                fwrite(&posProx, sizeof(int), 1, fp); //escreve o "endereco" da proxima posicao na posicao anterior, removendo a atual da lista
                
                fseek(fp, pos, SEEK_SET); //vai ate a posicao para insercao
                break;
            }
            else{ // atualiza as posicoes
                posAnt = pos;
                pos = posProx;
            }
        } 
    }
    // escreve o tamanho do registro no arquivo (intero)
    fwrite(&acum, sizeof(int), 1, fp);

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
    
    return 1;
}

int removeReg(REG_REMOVE *remove, int *header){
    char cod[20], codV[8], chave[20]="\0";
    int tam=0, pos, ind;

    FILE *fp;
    if ((fp = fopen("arquivo.bin","ab+")) == NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    printf("Insira o indice do registro a ser removido: ");
    scanf("%d", &ind);

    strcat(chave, remove[ind].codC); // concatena chave e codC, o resultado armazena em chave
    strcat(chave, remove[ind].codV); // concatena chave e codV, o resultado armazena em chave

    fseek(fp, sizeof(int), SEEK_SET);// pula o header

    for (int i = 0; i < 25; i++)
    {
        fread(&tam, sizeof(int), 1, fp);// le o tamanho do registro
        if(feof(fp)){
            printf("ERRO - Dados nao encontrados em arquivo.bin\n");
            return 0;
        }
        fgets(cod, 12, fp); // recebe o codigo do cliente e armazena em "cod"
        fseek(fp, sizeof(char), SEEK_CUR); // pula o "|"
        fgets(codV, 8, fp); // recebe o codigo do veiculo e armazena em "codV"
        strcat(cod, codV); // concatena chave e codV, o resultado armazena em chave
        if (strcmp(chave, cod) == 0) // compara se cod é o mesmo digitado pelo usuario(chave)
        {
            fseek(fp, -19-sizeof(int), SEEK_CUR); //caso for volta para a posicao de inicio do registro para remocao(19 = codC+codV)
            pos = ftell(fp); // armazena a posicao do registro em "pos"
            fclose(fp);
            if ((fp = fopen("arquivo.bin","rb+")) == NULL) // abre no modo escrita+
            {
                printf("Nao foi possivel abrir o arquivo\n");
                return 0;
            }
            fseek(fp, pos+sizeof(int), SEEK_SET); // seta o "cursor" na posição do registro, apos o indicador de tamanho
            fwrite("*", sizeof(char), 1, fp);// Poe a "*" sinalizando remocao
            fwrite(header, sizeof(int), 1, fp);// escreve o header apos a "*"
            *header = pos; // atualiza o valor do header com a posicao do registro removido
            fclose(fp);
            inserirListRemov(pos); // atualiza o valor do header com o valor "pos" no arquivo
            break;
        }
        else //caso nao
            fseek(fp, tam-19, SEEK_CUR);// pula o restante do registro e vai pro proximo
    }
}

void inserirListRemov(int pos){
    FILE *fp;

    if ((fp = fopen("arquivo.bin","rb+")) == NULL) //abre para escrita
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    fwrite(&pos, sizeof(int), 1, fp); //escreve o novo valor do header

    fclose(fp);
}

int compactaArq(){
    FILE *fp, *fpaux;
    int header=-1, tam;
    char c, *registro;

    if ((fp = fopen("arquivo.bin","rb+")) == NULL) //abrindo arquivo p leitura
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    if ((fpaux = fopen("arquivoAux.bin","wb+")) == NULL) //abrindo arquivo p leitura
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }
    
    fwrite(&header, sizeof(int), 1, fpaux); //passando o header para o arquivo aux
    fseek(fp, sizeof(int), SEEK_SET); //colocando o cursor após o bloco do header 

    while(!feof(fp)){
        fseek(fp, sizeof(int), SEEK_CUR); //ajustando o cursor para dps do bloco de tamanho do reg
        fread(&c, sizeof(char), 1, fp); //le o caracter seguinte e armazena na variavel c
        
        if(c != '*'){ //caso o registro seja valido
            if (feof(fp))
                {
                    break;
                }
            fseek(fp, -sizeof(int)-sizeof(char), SEEK_CUR);
            fread(&tam, sizeof(int), 1, fp);
            fwrite(&tam, sizeof(int), 1, fpaux);
            registro = malloc(sizeof(char) * tam);
            fread(registro, sizeof(char), tam, fp);
            fwrite(registro, sizeof(char), tam, fpaux);
            free(registro);
        }else{ //caso nao seja valido
            if (feof(fp)){
                    break;
            }
            fseek(fp, -sizeof(int)-sizeof(char), SEEK_CUR);
            fread(&tam, sizeof(int), 1, fp);
            fseek(fp, tam, SEEK_CUR);
        }
    }

    fclose(fp);

    if ((fp = fopen("arquivo.bin","wb")) == NULL) //abrindo arquivo p leitura
    {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    rewind(fpaux);
    unsigned char B64; //Variavel de 64 bits 
    while(1){
        fread (&B64, sizeof(unsigned char), 1, fpaux);
        if (feof(fpaux)){
            break;
        }
        fwrite(&B64, sizeof(unsigned char), 1, fp);
    } 

    fclose(fp);
    fclose(fpaux);

    remove("arquivoAux.bin");
    
    return 0;
}

