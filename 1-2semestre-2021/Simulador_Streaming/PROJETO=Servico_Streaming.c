#include <stdio.h>
#include <string.h>

//================================================================================================================
//>>>>  STRUCTS/ENUM/UNION  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//================================================================================================================

//>>>>  CLIENTE  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef struct S_CLIENT                                 //
{                                                       //
    char CPF[50];   
    char c;                                    //
    char nome[50];                                      //
    char email[50];                                     //
    char telefone[16];                                  //
    int status;                                         //
}CLIENTE;                                               //
//>>>>  CLIENTE  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//>>>>  FILME  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef enum E_GENERO                                   //
{                                                       //
    aventura, comedia, drama, terror, acao, romance     //
}GENERO;                                                //
typedef enum E_CLASSIFIC                                //
{                                                       //
    livre, dez, doze, quatorze, dezessei, dezoito       //
}CLASSIFICACAO;                                         //
//------------------------------------------------------//
typedef struct S_FILM                                   //
{                                                       //
    int cod;                                            //
    char nome[50];                                      //
    GENERO gen;                                         //
    CLASSIFICACAO class;                                //
}FILME;                                                 //
//>>>>  FILME  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//>>>>  PLANOS  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef struct S_PLAN_BASIC                             //
{                                                       //
    int qnt_film;                                       //
    float valor_base;                                   //
    float valor_exce;                                   //
}PLAN_BAS;                                              //
typedef struct S_PAN_PREMI                              //
{                                                       //
    float valor_base;                                   //
}PLAN_PREMIUM;                                          //
typedef enum E_PLANS                                    //
{                                                       //
    plan_basc, plan_prem                                //
}E_PLANS;                                               //
typedef union U_TIP_PLAN                                //
{                                                       //
    PLAN_BAS p_basic;                                   //
    PLAN_PREMIUM p_premium;                             //
}TIP_PLANO;                                             //
//------------------------------------------------------//
typedef struct S_PLAN                                   //
{                                                       //
    E_PLANS tip_plan;                                   //
    TIP_PLANO plano;                                    //
}PLANOS;                                                //
//>>>>  PLANOS  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//


//>>>>  CONTRATO  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef enum E_TIP_PAG                                  //
{                                                       //
    debito, credito                                     //
}E_PAGAMENTS;                                           //
typedef struct S_CREDIT                                 //
{                                                       //
    char n_cartao[50];                                  //
}CREDITO;                                               //
typedef struct S_DEBITO                                 //
{                                                       //
    int n_agencia;                                      //
    int n_conta;                                        //
}DEBITO;                                                //
typedef union U_TIP_PAG                                 //
{                                                       //
    CREDITO credito;                                    //
    DEBITO debito;                                      //
}PAGAMENTOS;                                            //
typedef struct S_TIP_PAG                                //
{                                                       // 
    E_PAGAMENTS tip_pag;                                //
    PAGAMENTOS pagamentos;                              //
}TIP_PAGAMENTOS;                                        //
//------------------------------------------------------//
typedef struct S_CONTRAT                                //
{                                                       //
    char CPF[50];                                       //
    PLANOS tip_plan;                                    //
    int dia_contrat;                                    //
    int mes_contrat;                                    //
    int dia_cancel;                                     //
    int mes_cancel;                                     //
    TIP_PAGAMENTOS pagamento;                           //
}CONTRATO;                                              //
//>>>>  CONTRATO  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//>>>>  ALL  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef struct S_ALL                                    //
{                                                       //
    CLIENTE clt;                                        //
    FILME film;                                         //
    PLANOS plan;                                        //
    CONTRATO contrat;                                   //
}BANCO_DADOS;                                           //
//>>>>  ALL  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//>>>>  HISTORICO  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef struct S_HIST                                   //
{                                                       //  
    int cod;                                            //
    int dia;                                            //
    int mes;                                            //
}HISTORICO;                                             //
//>>>>  HISTORICO  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//>>>>  AUXIAR_RECOMEND_FILM  <<<<<<<<<<<<<<<<<<<<<<<<<<//
typedef struct S_AUX                                    //
{                                                       //
    int total_cont;                                     //
    int cont;                                           //
    int gen;                                            //
}CONTADOR;                                              //
//>>>>  AUXIAR_RECOMEND_FILM  <<<<<<<<<<<<<<<<<<<<<<<<<<//

//================================================================================================================
//>>>>  PROTOTIPOS  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//================================================================================================================

void cadastroclt(BANCO_DADOS* infos, int* cont_clt);
void cadastrofilm(BANCO_DADOS* infos, int* cont_film, int* codfilm);
void cadastroplan_bas(BANCO_DADOS* infos);
void cadastroplan_premium(BANCO_DADOS* infos);
void cadastro_contrat(BANCO_DADOS* infos, int cont_clt, int* cont_contrat, int mes);
void carrega_film(BANCO_DADOS* infos, HISTORICO hist_m[][30], int cont_clt, int cont_film, int* cont_Histfilm, int* qnt_exced, int mes, int cont_freqfilm[][10], int cont_contrat);
void cancel_contrat(BANCO_DADOS* infos, int* cont_contrat, int cont_clt, int* qnt_exced, int mes);
void gerar_fatura(BANCO_DADOS* infos, HISTORICO hist_m[][30], int cont_clt, int cont_contrat, int* mes, int* cont_Histfilm, int cont_film, int* qnt_exced);
void list_client(BANCO_DADOS* infos, int cont_clt);
void list_hist(BANCO_DADOS* infos, int cont_clt, HISTORICO hist_m[][30], int* cont_Histfilm, int cont_film);
void list_excedent(BANCO_DADOS* infos, int cont_clt, int* qnt_exced, int cont_contrat);
void freq_client(BANCO_DADOS* infos, int cont_freqfilm[][10], int cont_film, int cont_clt);
void recomend_film(BANCO_DADOS* infos, HISTORICO hist_m[][30], int* cont_Histfilm, int cont_film, int cont_clt);

//================================================================================================================
//>>>>  MAIN  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//================================================================================================================

int main()
{
    BANCO_DADOS infos[10];
    HISTORICO hist_m[10][30];
    
    int cont_clt=0, cont_film=0, cont_contrat=0, mes=1, codfilm=1001;
    int cont_Histfilm[10]={0}, qnt_exced[10]={0}, cont_freqfilm[10][10]={0};
    int cmd;
    
    printf("\n\t\t\t%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 187);
    printf("\n\t\t\t%c Inicio %c", 186, 186);
    printf("\n\t\t\t%c%c%c%c%c%c%c%c%c%c\n", 200, 205, 205, 205, 205, 205, 205, 205, 205, 188);
    while(1)
    {
        printf("\n===============================================================================================\n");
        printf("\n\t MENU\n\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Filme\n");
        printf("3 - Cadastrar Plano Basico\n");
        printf("4 - Cadastrar Plano Premium\n");
        printf("5 - Cadastrar Contrato\n");
        printf("6 - Assistir Filme \n");
        printf("7 - Cancelar Contrato\n");
        printf("8 - Gerar Fatura\n");
        printf("9 - Listar os dados de um cliente\n");
        printf("10 - Listar o histórico de um cliente\n");
        printf("11 - Listar clientes que excederam a cota mensal\n");
        printf("12 - Ver frequencia de um dado filme\n");
        printf("13 - Recomendar filme\n");
        printf("0 - Sair\n");
        printf("\nEscolha a opcao desejada: ");
        
        scanf("%d", &cmd);

        switch (cmd)
        {
            case 1:// Cadastro cliente
                cadastroclt(infos, &cont_clt);    
                break;
                
            case 2:// Cadastro filme
                cadastrofilm(infos, &cont_film, &codfilm);
                break;

            case 3:// Cadastro plano basico
                cadastroplan_bas(infos);
                break;

            case 4:// Cadastro plano premium
                cadastroplan_premium(infos);
                break;

            case 5:// Cadastro contrato
                cadastro_contrat(infos, cont_clt, &cont_contrat, mes);
                break;

            case 6:// Carregar filme
                carrega_film(infos, hist_m, cont_clt, cont_film, cont_Histfilm, qnt_exced, mes, cont_freqfilm, cont_contrat);
                break;

            case 7:// Cancelar contrato
                cancel_contrat(infos, &cont_contrat, cont_clt, qnt_exced, mes);
                break;

            case 8:// Gerar fatura
                gerar_fatura(infos, hist_m, cont_clt, cont_contrat, &mes, cont_Histfilm, cont_film, qnt_exced);
                break;

            case 9:// Listar os dados de um dado cliente
                list_client(infos, cont_clt);
                break;

            case 10:// Listar o histórico de uma dado cliente 
                list_hist(infos, cont_clt, hist_m, cont_Histfilm, cont_film);
                break;

            case 11:// Listar clientes que excederam a cota mensal
                list_excedent(infos, cont_clt, qnt_exced, cont_contrat);
                break;

            case 12:// Frequência de um dado filme
                freq_client(infos, cont_freqfilm, cont_film, cont_clt);             
                break;

            case 13:// Recomendar filme
                recomend_film(infos, hist_m, cont_Histfilm, cont_film, cont_clt);
                break;

            case 0:// Sair
                printf("Finalizando programa...");
                return 0;;
            
            default:
                printf("ERRO: Opcao invalida\n");
                break;
        }
    }
}

//================================================================================================================
//>>>>  FUNCOES  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//================================================================================================================

void cadastroclt(BANCO_DADOS* infos, int* cont_clt)
{   
    /*
    Cliente: Um cliente é uma pessoa que possui um CPF (chave de busca), nome, e-mail, telefone e status 
    (ativo ou inativo). O telefone segue o formato: 19-9-XXXX-XXXX. Para facilitar, supõe-se que é possível 
    cadastrar no máximo 10 clientes.
    Cadastrar Cliente: cadastra um cliente. Sempre que o cliente é cadastrado seu status é colocado como inativo.
    */
    char cpf_local[50];
    printf("\n===============================================================================================\n");
    printf("\n\t CADASTRAR CLIENTE\n\n");
    if((*cont_clt) >= 10)
    {
        printf("ERRO: Numero maximo de clientes no sistema atingido\n");
        return;
    }
    printf("Digite o CPF: ");
    scanf(" %[^\n]%*c", cpf_local); 

    for(int i=0; i<(*cont_clt); i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF) == 0)
        {
            printf("ERRO: CPF do cliente ja cadastrado\n");
            return;
        }
    }

    strcpy(infos[*cont_clt].clt.CPF, cpf_local);
    printf("Digite o nome: ");
    scanf(" %[^\n]%*c", infos[*cont_clt].clt.nome); 
    printf("Digite o email: ");
    scanf(" %[^\n]%*c", infos[*cont_clt].clt.email); 
    printf("Digite o telefone: ");
    scanf(" %[^\n]%*c", infos[*cont_clt].clt.telefone); 
    infos[*cont_clt].clt.status = 0; 
    printf("\n>> Cliente cadastrado com sucesso <<\n");
    (*cont_clt)++;
}

void cadastrofilm(BANCO_DADOS* infos, int* cont_film, int* codfilm)
{
    int gen_local, clas_local;
    printf("\n===============================================================================================\n");
    printf("\n\t CADASTRAR FILME\n\n");
    if((*cont_film) >= 10)
    {
        printf("ERRO: Numero maximo de filmes no sistema atingido\n");
        return;
    }
    printf("\nDigite o nome do filme: ");
    scanf(" %[^\n]%*c", infos[*cont_film].film.nome);

    printf("\n0 = aventura\n");
    printf("1 = comedia\n");
    printf("2 = drama\n");
    printf("3 = terror\n");
    printf("4 = acao\n");
    printf("5 = romance\n");
    while(1)
    {
        printf("\nDigite o genero do filme: ");
        scanf(" %d", &gen_local);
        if(gen_local > 5 || gen_local < 0)
        {
            printf("ERRO: Genero invalido\n");
        }
        else 
            break;
    }
    printf("\n0 = livre\n");
    printf("1 = Maiores de 10 anos\n");
    printf("1 = Maiores de 12 anos\n");
    printf("1 = Maiores de 14 anos\n");
    printf("1 = Maiores de 16 anos\n");
    printf("1 = Maiores de 18 anos\n");
    while (1)
    {
        printf("\nDigite a classificacao do filme: ");
        scanf(" %d", &clas_local);
        if(clas_local > 5 || clas_local < 0)
        {
            printf("ERRO: Classificao invalida\n");
        }
        else
            break;
    }
    infos[*cont_film].film.cod=(*codfilm);
    infos[*cont_film].film.gen = (GENERO)gen_local;
    infos[*cont_film].film.class = (CLASSIFICACAO)clas_local;
    (*cont_film)++;
    (*codfilm)++;
    printf("\n>> Filme cadastrado com sucesso <<\n");
}

void cadastroplan_bas(BANCO_DADOS* infos)
{
    printf("\n===============================================================================================\n");
    printf("\n\t CADASTRO PLANO BASICO\n\n");
    infos[0].plan.tip_plan = plan_basc;
    printf("Digite a cota mensal de filmes do plano: ");
    scanf(" %d", &infos[0].plan.plano.p_basic.qnt_film);
    printf("Digite o valor base do plano: ");
    scanf(" %f", &infos[0].plan.plano.p_basic.valor_base);
    printf("Digite o valor por filme excedente: ");
    scanf(" %f", &infos[0].plan.plano.p_basic.valor_exce);
    printf("Plano Basico cadastrado com sucesso\n");
}

void cadastroplan_premium(BANCO_DADOS* infos)
{
    printf("\n===============================================================================================\n");
    printf("\n\t CADASTRO PLANO PREMIUM\n\n");
    infos[1].plan.tip_plan = plan_prem;
    printf("Digite o valor base do plano: ");
    scanf(" %f", &infos[1].plan.plano.p_premium.valor_base);
    printf("Plano Premium cadastrado com sucesso\n");
}

void cadastro_contrat(BANCO_DADOS* infos, int cont_clt, int* cont_contrat, int mes)
{
    char cpf_local[50];
    int plan_loval, pag_local, dia_local;

    printf("\n===============================================================================================\n");
    printf("\n\t CADASTRO CONTRATO\n\n");
    if(cont_clt == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    if((*cont_contrat) >= 10)
    {
        printf("ERRO: Numero maximo de contratos no sistema atingido\n");
        return;
    }
    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]%*c", cpf_local);

    for(int i=0; i<cont_clt; i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF)==0)
        {
            if(infos[i].clt.status == 0)
            {
                printf("Digite o plano desejado(0 = basico, 1 = premium): ");
                while(1)
                {
                    scanf(" %d", &plan_loval);// plano
                    if(plan_loval>1 || plan_loval<0)
                    {
                        printf("ERRO: Tipo de plano invalido\n");
                    }
                    else
                        break;
                }
                printf("Digite a forma de pagamento(0 = debito, 1 = credito): ");
                while(1)
                {
                    scanf(" %d", &pag_local);//pagamento
                    if(pag_local>1 || pag_local<0)
                    {
                        printf("ERRO: Tipo de pagamento invalido\n");
                    }
                    else
                        break;
                }
                if(pag_local == debito)
                {
                    printf("Digite o numero da agencia: ");
                    scanf(" %d", &infos[*cont_contrat].contrat.pagamento.pagamentos.debito.n_agencia);
                    printf("Digite o numero da conta: ");
                    scanf(" %d", &infos[*cont_contrat].contrat.pagamento.pagamentos.debito.n_conta);
                }
                else
                {
                    printf("Digite o numero do cartao: ");
                    scanf(" %[^\n]%*c", infos[*cont_contrat].contrat.pagamento.pagamentos.credito.n_cartao);
                }
                printf("Digite o dia atual: ");
                while(1)
                {
                    scanf(" %d", &dia_local);
                    if(dia_local>31 || dia_local<=0)
                    {
                        printf("ERRO: Dia invalido\n");
                    }
                    else
                        break;
                }
                strcpy(infos[*cont_contrat].contrat.CPF, cpf_local);
                infos[*cont_contrat].contrat.tip_plan.tip_plan = (E_PLANS)plan_loval;
                if(plan_loval == plan_basc)
                    infos[*cont_contrat].contrat.tip_plan.plano.p_basic = infos[0].plan.plano.p_basic;
                else
                    infos[*cont_contrat].contrat.tip_plan.plano.p_premium = infos[1].plan.plano.p_premium;
                infos[*cont_contrat].contrat.dia_contrat = dia_local;
                infos[*cont_contrat].contrat.mes_contrat = mes;
                infos[*cont_contrat].contrat.dia_cancel = 0;
                infos[*cont_contrat].contrat.mes_cancel = 0;
                infos[*cont_contrat].contrat.pagamento.tip_pag = (E_PAGAMENTS)pag_local;
                infos[i].clt.status = 1;
                (*cont_contrat)++;
                printf("Contrato cadastrado com sucesso\n");
                return;
            }
            printf("ERRO: Cliente com contrato existente\n");
            return;
        }
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}

void carrega_film(BANCO_DADOS* infos, HISTORICO hist_m[][30], int cont_clt, int cont_film, int* cont_Histfilm, int* qnt_exced, int mes, int cont_freqfilm[][10], int cont_contrat)
{
    char cpf_local[50];
    int dia_local, filtro, filtro2, cod_film_local, opcao;

    printf("\n===============================================================================================\n");
    printf("\n\t CARREGAR FILME\n\n");
    if(cont_clt == 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]%*c", cpf_local);
    for(int i=0; i<cont_clt; i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF)==0)
        {
            if(cont_Histfilm[i]>=30)
            {
                printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                return;
            }
            if(infos[i].clt.status == 0)
            {
                printf("ERRO: Cliente nao ativo\n");
                return;
            }
            printf("Digite o dia atual: ");
            while(1)
            {
                scanf(" %d", &dia_local);
                if(dia_local>31 || dia_local<=0)
                {
                    printf("ERRO: Dia invalido\n");
                }
                else
                    break;
            }
            printf("0 = genero\n1 = classificacao\nDeseja listar os filmes por: ");
            while(1)
            {
                scanf(" %d", &filtro);//escolha entre gen ou classificacao
                if(filtro>1 || filtro<0)
                    printf("ERRO: Escolha invalida\n");
                else
                    break;
            }
            printf("      GENERO | CLASSIFICACAO\n");
            printf("0 = aventura | livre\n");
            printf("1 = comedia  | maiores de 10 anos\n");
            printf("2 = drama    | maiores de 12 anos\n");
            printf("3 = terror   | maiores de 14 anos\n");
            printf("4 = acao     | maiores de 16 anos\n");
            printf("5 = romance  | maiores de 18 anos\n");
            printf("Digite a genero\\classificacao desejada: \n");
            while(1)
            {
                scanf(" %d", &filtro2);//escpecifica o gen ou class
                if(filtro2>5 || filtro2<0)
                    printf("ERRO: Escolha invalida\n");
                else
                    break;
            }
            if (filtro == 0)
            {
                for(int j=0; j<cont_film; j++)
                {
                    if(infos[j].film.gen == filtro2)
                    {
                        printf("Codigo: %d\n", infos[j].film.cod);
                        printf("Nome: %s\n", infos[j].film.nome);
                    }
                }
            }
            else
            {
                for(int j=0; j<cont_film; j++)
                {
                    if(infos[j].film.class == filtro2)
                    {
                        printf("Codigo: %d\n", infos[j].film.cod);
                        printf("Nome: %s\n", infos[j].film.nome);
                    }
                }
            }
            printf("Selecione o codigo do filme: ");
            scanf(" %d", &cod_film_local);
            for(int j=0; j<cont_film; j++)
            {
                if(cod_film_local == infos[j].film.cod)
                {
                    for(int k=0; k<cont_contrat; k++)
                    {
                        if(strcmp(infos[i].clt.CPF, infos[k].contrat.CPF) == 0)
                        {
                            if(infos[k].contrat.tip_plan.tip_plan == plan_prem)
                            {
                                printf("Filme carregado com sucesso\n");
                                hist_m[i][cont_Histfilm[i]].cod = cod_film_local;
                                hist_m[i][cont_Histfilm[i]].dia = dia_local;
                                hist_m[i][cont_Histfilm[i]].mes = mes;
                                cont_Histfilm[i]++;
                                cont_freqfilm[i][j]++;
                                return;
                            }
                            else if(infos[k].contrat.tip_plan.tip_plan == plan_basc)
                            {
                                if (cont_Histfilm[i] >= infos[k].contrat.tip_plan.plano.p_basic.qnt_film)
                                {
                                    printf(">>ATENCAO VOCE ATINGIU SUA COTA DO PLANO, CARREGAR ESSE FILME RESULTARA EM ACRECIMO AO VALOR MENSAL<<\n");
                                    printf(">>Deseja continuar (0 = nao, 1 = sim)? ");
                                    while(1)
                                    {
                                        scanf(" %d", &opcao);
                                        if (opcao>1 || opcao<0)
                                        {
                                            printf("ERRO: Escolha invalida\n");
                                        }
                                        else
                                            break;
                                    }
                                    if(opcao == 1)
                                    {
                                        printf("Filme carregado com sucesso\n");
                                        hist_m[i][cont_Histfilm[i]].cod = cod_film_local;
                                        hist_m[i][cont_Histfilm[i]].dia = dia_local;
                                        hist_m[i][cont_Histfilm[i]].mes = mes;
                                        cont_Histfilm[i]++;
                                        qnt_exced[i]++;
                                        cont_freqfilm[i][j]++;
                                    }
                                    else
                                        printf("Taxa adicional negada\n");
                                    return; 
                                }
                                printf("Filme carregado com sucesso\n");
                                hist_m[i][cont_Histfilm[i]].cod = cod_film_local;
                                hist_m[i][cont_Histfilm[i]].dia = dia_local;
                                hist_m[i][cont_Histfilm[i]].mes = mes;
                                cont_Histfilm[i]++;
                                cont_freqfilm[i][j]++;
                                return;
                            }
                        }
                    }
                }
            }
            printf("ERRO: Filme nao encontrado\n");
            return;
        }
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}

void cancel_contrat(BANCO_DADOS* infos, int* cont_contrat, int cont_clt, int* qnt_exced, int mes)
{
    char cpf_local[50];
    int dia_local;

    printf("\n===============================================================================================\n");
    printf("\n\t CANCELAR CONTRATO\n\n");
    if((*cont_contrat) == 0)
    {
        printf("ERRO: Nenhum contrato cadastrado no sistema\n");
        return;
    }
    printf("Digite o CPF: ");
    scanf(" %[^\n]%*c", cpf_local);
    for(int i=0; i<cont_clt; i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF) == 0)
        {
            if(infos[i].clt.status == 0)
            {
                printf("ERRO: Cliente inativo\n");
                return;
            }
            while (1)
            {
                printf("Digite o dia atual: ");
                scanf(" %d", &dia_local);
                if(dia_local>31 || dia_local<=0)
                    printf("ERRO: Dia invalido\n");
                else
                    break;
            }
            for(int j=0; j<(*cont_contrat); j++)
            {
                if(strcmp(infos[i].clt.CPF, infos[j].contrat.CPF) == 0)
                {
                    if(mes > infos[j].contrat.mes_contrat)
                    {
                        if(infos[j].contrat.tip_plan.tip_plan == plan_prem)
                        {
                            printf("Valor devido: %.2f\n", infos[j].contrat.tip_plan.plano.p_premium.valor_base);
                        }
                        else
                        {
                            printf("Valor devido: %.2f\n", infos[j].contrat.tip_plan.plano.p_basic.valor_base + infos[j].contrat.tip_plan.plano.p_basic.valor_exce * qnt_exced[i]);
                        }
                        infos[i].clt.status = 0;
                        for(int k=j; k<(*cont_contrat); k++)
                        {
                            strcpy(infos[k].contrat.CPF, infos[k+1].contrat.CPF);
                            infos[k].contrat.tip_plan = infos[k+1].contrat.tip_plan;
                            infos[k].contrat.dia_contrat = infos[k+1].contrat.dia_contrat;
                            infos[k].contrat.mes_contrat = infos[k+1].contrat.mes_contrat;
                            infos[k].contrat.dia_cancel = infos[k+1].contrat.dia_cancel;
                            infos[k].contrat.mes_cancel = infos[k+1].contrat.mes_cancel;
                            infos[k].contrat.pagamento = infos[k+1].contrat.pagamento;
                        }
                        (*cont_contrat)--;
                        printf("Cancelamento feito com sucesso\n");
                        return;
                    }
                    else if(dia_local >= infos[j].contrat.dia_contrat && mes == infos[j].contrat.mes_contrat)
                    {
                        if(infos[j].contrat.tip_plan.tip_plan == plan_prem)
                        {
                            printf("Valor devido: %.2f\n", infos[j].contrat.tip_plan.plano.p_premium.valor_base);
                        }
                        else
                        {
                            printf("Valor devido: %.2f\n", infos[j].contrat.tip_plan.plano.p_basic.valor_base + infos[j].contrat.tip_plan.plano.p_basic.valor_exce * qnt_exced[i]);
                        }
                        infos[i].clt.status = 0;
                        for(int k=j; k<(*cont_contrat); k++)
                        {
                            strcpy(infos[k].contrat.CPF, infos[k+1].contrat.CPF);
                            infos[k].contrat.tip_plan = infos[k+1].contrat.tip_plan;
                            infos[k].contrat.dia_contrat = infos[k+1].contrat.dia_contrat;
                            infos[k].contrat.mes_contrat = infos[k+1].contrat.mes_contrat;
                            infos[k].contrat.dia_cancel = infos[k+1].contrat.dia_cancel;
                            infos[k].contrat.mes_cancel = infos[k+1].contrat.mes_cancel;
                            infos[k].contrat.pagamento = infos[k+1].contrat.pagamento;
                        }
                        (*cont_contrat)--;
                        printf("Cancelamento feito com sucesso\n");
                        return;
                    }
                    printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                    return;
                }
            }
        }
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}

void gerar_fatura(BANCO_DADOS* infos, HISTORICO hist_m[][30], int cont_clt, int cont_contrat, int* mes, int* cont_Histfilm, int cont_film, int* qnt_exced)
{
    int opcao;
    char cpf_local[50];

    printf("\n===============================================================================================\n");
    printf("\n\t GERAR FATURA\n\n");
    printf("0 = Gerar fatura de cliente especifico\n");
    printf("1 = Gerar fatura de todos os clientes\n");
    while(1)
    {
        scanf(" %d", &opcao);
        if(opcao>1 || opcao<0)
            printf("ERRO: Escolha invalida\n");
        else
            break;
    }
    
    if(opcao == 0)// er especifico
    {

        if(cont_clt <= 0)
        {
            printf("ERRO: Nenhum cliente cadastrado no sistema\n");
            return;
        }
        if(cont_contrat <= 0)
        {
            printf("ERRO: Nenhum contrato cadastrado no sistema\n");
            return;
        }
        printf("Digite o CPF: ");
        scanf(" %[^\n]%*c", cpf_local);
        
        for(int i=0; i<cont_clt; i++)
        {
            if(strcmp(cpf_local, infos[i].clt.CPF) == 0)
            {
                if(infos[i].clt.status == 0)
                {
                    printf("ERRO: Cliente nao possui contrato\n");
                    return;
                }
                for(int j=0; j<cont_Histfilm[i]; j++)
                {
                    for(int k=0; k<cont_film; k++)
                    {
                        if(infos[k].film.cod == hist_m[i][j].cod)
                        {
                            printf("Nome: %s\n", infos[k].film.nome); //nome do filme
                            break;
                        }
                    }
                    printf("Data: %d/%d\n", hist_m[i][j].dia, *mes); //data do carregamento
                }
                for(int k=0; k<cont_contrat; k++)
                {
                    if(strcmp(infos[i].clt.CPF, infos[k].contrat.CPF) == 0)
                    {
                        if(infos[k].contrat.tip_plan.tip_plan == plan_prem)
                        {
                            printf("Valor devido: %.2f\n", infos[k].contrat.tip_plan.plano.p_premium.valor_base);
                        }
                        else
                        {
                            printf("Valor devido: %.2f\n", infos[k].contrat.tip_plan.plano.p_basic.valor_base + infos[k].contrat.tip_plan.plano.p_basic.valor_exce * qnt_exced[i]);
                        }
                        break;
                    }
                }
                return;
            }
        }
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    else//ver todos
    {
        for(int i=0; i<cont_clt; i++)
        {
            if(infos[i].clt.status == 1)
            {
                printf("CPF: %s\n", infos[i].clt.CPF);
                printf("Nome: %s\n", infos[i].clt.nome); //nome do cliente
                for(int k=0; k<cont_contrat; k++)
                {
                    if(strcmp(infos[i].clt.CPF, infos[k].contrat.CPF) == 0)
                    {
                        if(infos[k].contrat.tip_plan.tip_plan == plan_prem)
                        {
                            printf("Valor devido: %.2f\n", infos[k].contrat.tip_plan.plano.p_premium.valor_base);
                        }
                        else
                        {
                            printf("Valor devido: %.2f\n", infos[k].contrat.tip_plan.plano.p_basic.valor_base + infos[k].contrat.tip_plan.plano.p_basic.valor_exce * qnt_exced[i]);
                        }
                        break;
                    }
                }
            }
            cont_Histfilm[i] = 0;
            qnt_exced[i] = 0;
            for(int j=0; j<30; j++)
            {
                hist_m[i][j].cod = 0;
                hist_m[i][j].dia = 0;
                hist_m[i][j].mes = 0;
            }
        }
        (*mes)++;
        printf("Mes vigente apos a fatura: %d\n", *mes);
    }
}

void list_client(BANCO_DADOS* infos, int cont_clt)
{
    char cpf_local[50];

    printf("\n===============================================================================================\n");
    printf("\n\t LISTAR DADOS DE UM CLIENTE\n\n");
    if(cont_clt <= 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    printf("Digite o CPF: ");
    scanf(" %[^\n]%*c", cpf_local);
    for(int i=0; i<cont_clt; i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF) == 0)
        {
            printf("Nome: %s\n", infos[i].clt.nome);
            printf("Email: %s\n", infos[i].clt.email);
            printf("Telefone: %s\n", infos[i].clt.telefone);
            printf("Status: %d\n", infos[i].clt.status);
            return;
        }
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}

void list_hist(BANCO_DADOS* infos, int cont_clt, HISTORICO hist_m[][30], int* cont_Histfilm, int cont_film)
{
    char cpf_local[50];

    printf("\n===============================================================================================\n");
    printf("\n\t LISTAR HISTORICO DE UM CLIENTE\n\n");
    if(cont_clt <= 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    printf("Digite o CPF: ");
    scanf(" %[^\n]%*c", cpf_local);
    for(int i=0; i<cont_clt; i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF) == 0)
        {
            if(infos[i].clt.status == 1)
                printf("Estado: Ativo\n");
            else
                printf("Estado: Inativo\n");
            if(cont_Histfilm[i] <= 0)
            {
                printf("ERRO: Nenhum filme assistido\n");
                return;
            }
            for(int j=0; j<cont_Histfilm[i]; j++)
            {
                printf("Codigo: %d\n", hist_m[i][j].cod); //codigo do filme
                for(int k=0; k<cont_film; k++)
                    if(infos[k].film.cod == hist_m[i][j].cod)
                    {
                        printf("Nome: %s\n",infos[k].film.nome); //nome do filme
                        if(infos[k].film.gen == aventura)
                            printf("Genero: aventura\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[k].film.gen == comedia)
                            printf("Genero: comedia\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[k].film.gen == drama)
                            printf("Genero: drama\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[k].film.gen == terror)
                            printf("Genero: terror\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[k].film.gen == acao)
                            printf("Genero: acao\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[k].film.gen == romance)
                            printf("Genero: romance\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        
                        if(infos[k].film.class == livre)
                            printf("Classificacao: livre\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[k].film.class == dez)
                            printf("Classificacao: +10\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[k].film.class == doze)
                            printf("Classificacao: +12\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[k].film.class == quatorze)
                            printf("Classificacao: +14\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[k].film.class == dezessei)
                            printf("Classificacao: +16\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[k].film.class == dezoito)
                            printf("Classificacao: +18\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                    }
                printf("Data do carregamento: %d/%d\n\n",hist_m[i][j].dia, hist_m[i][j].mes);
            }
            return;
        }
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}

void list_excedent(BANCO_DADOS* infos, int cont_clt, int* qnt_exced, int cont_contrat)
{
    printf("\n===============================================================================================\n");
    printf("\n\t LISTAR CLIENTES EXCEDENTES\n\n");
    for(int i=0; i<cont_clt; i++)
    {
        if(qnt_exced[i] > 0)
        {
            printf("CPF: %s\n", infos[i].clt.CPF);
            printf("Nome: %s\n", infos[i].clt.nome);
            for(int j=0; j<cont_contrat; j++)
            {
                if(strcmp(infos[i].clt.CPF, infos[j].contrat.CPF) == 0)
                {
                    printf("Valor excedente: %.2f\n\n", infos[j].contrat.tip_plan.plano.p_basic.valor_exce * qnt_exced[i]);
                    return;
                }
            }
        }
    }
    printf("ERRO: Nenhum cliente excedente\n");
    return;
}

void freq_client(BANCO_DADOS* infos, int cont_freqfilm[][10], int cont_film, int cont_clt)
{
    printf("\n===============================================================================================\n");
    printf("\n\t VER FREQUENCIA DE UM FILME\n\n");
    int cod_local, aux=0, acum=0, total=0;

    if(cont_film <= 0)
    {
        printf("ERRO: Nenhum filme cadastrado no sistema\n");
        return;
    }
    for(int i=0; i<cont_clt; i++)
    {
        for(int j=0; j<cont_film; j++)
        {
            if(cont_freqfilm[i][j] != 0)
            {
                aux = 1;
                break;
            }
        }
    }
    printf("Digite o codigo do filme: ");
    scanf("%d", &cod_local);
    if(aux == 0)
    {
        printf("ERRO: Nenhum filme assistido\n");
        return;
    }
    for(int i=0; i<cont_film; i++)
        for(int j=0; j<cont_clt; j++)
            total += cont_freqfilm[j][i];

    for(int i=0; i<cont_film; i++)
    {
        if(cod_local == infos[i].film.cod)
        {
            for(int j=0; j<cont_clt; j++)
            {
                acum += cont_freqfilm[j][i];
            }
        printf("Frequencia: %.2f%%\n", acum / (total * 0.01));
        return;
        }
    }
    printf("ERRO: Codigo invalido\n");
    return;
}

void recomend_film(BANCO_DADOS* infos, HISTORICO hist_m[][30], int* cont_Histfilm, int cont_film, int cont_clt)
{
    printf("\n===============================================================================================\n");
    printf("\n\t RECOMENDAR FILME\n\n");
    CONTADOR cont_gen[6];
    CONTADOR aux;
    char cpf_local[50];
    int chave=0, repeticao=0;

    for(int i=0; i<6; i++)
    {
        cont_gen[i].cont = 0;
        cont_gen[i].total_cont = 0;
    }
    if(cont_clt <= 0)
    {
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    printf("Digite o CPF: ");
    scanf(" %[^\n]%*c", cpf_local);
    for(int i=0; i<cont_clt; i++)
    {
        if(strcmp(cpf_local, infos[i].clt.CPF) == 0)
        {
            if(infos[i].clt.status == 0)
            {
                printf("ERRO: Cliente nao ativo\n");
                return;
            }
            if (cont_Histfilm[i] <= 0)
            {
                printf("ERRO: Nenhum filme assistido\n");
                return;
            }
            for(int k=0; k<cont_Histfilm[i]; k++)
            {
                for(int j=0; j<cont_film; j++)
                {
                    if(hist_m[i][k].cod == infos[j].film.cod)
                    {
                        if(infos[j].film.gen == aventura)
                        {
                            cont_gen[aventura].cont++;
                            cont_gen[aventura].gen = aventura;
                        }
                        else if(infos[j].film.gen == comedia)
                        {
                            cont_gen[comedia].cont++;
                            cont_gen[comedia].gen = comedia;
                        }
                        else if(infos[j].film.gen == drama)
                        {
                            cont_gen[drama].cont++;
                            cont_gen[drama].gen = drama;
                        }
                        else if(infos[j].film.gen == terror)
                        {
                            cont_gen[terror].cont++;
                            cont_gen[terror].gen = terror;
                        }
                        else if(infos[j].film.gen == acao)
                        {
                           cont_gen[acao].cont++;
                           cont_gen[acao].gen = acao;
                        }
                        else if(infos[j].film.gen == romance)
                        {
                            cont_gen[romance].cont++;
                            cont_gen[romance].gen = romance;
                        }
                        break;
                    }
                }
            }
            for(int j=0; j<cont_film; j++)
            {
                if(infos[j].film.gen == aventura)
                    cont_gen[aventura].total_cont++;

                else if(infos[j].film.gen == comedia)
                    cont_gen[comedia].total_cont++;

                else if(infos[j].film.gen == drama)
                    cont_gen[drama].total_cont++;

                else if(infos[j].film.gen == terror)
                    cont_gen[terror].total_cont++;

                else if(infos[j].film.gen == acao)
                    cont_gen[acao].total_cont++;

                else if(infos[j].film.gen == romance)
                    cont_gen[romance].total_cont++;
            }
            for(int j=0; j<6; j++)
            {
                for(int k=0; k<5; k++)
                {
                    if(cont_gen[k].cont < cont_gen[k+1].cont)
                    {
                        aux = cont_gen[k];
                        cont_gen[k] = cont_gen[k+1];
                        cont_gen[k+1] = aux;
                    }
                }
            }
            if(cont_gen[0].cont >= cont_gen[0].total_cont)
            {
                printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
                return;
            }
            for(int j=1; j<6; j++)
            {
                if(cont_gen[0].cont == cont_gen[j].cont)
                {
                    repeticao++;
                }
            }
            for(int j=0; j<repeticao+1; j++)
            {
                for(int l=0; l<cont_film; l++)
                {
                    chave = 1;
                    for(int k=0; k<cont_Histfilm[i]; k++)
                    {
                        if(hist_m[i][k].cod == infos[l].film.cod)
                        {
                            chave=0;
                            break;
                        }
                    }
                    if(chave == 1 && infos[l].film.gen == cont_gen[j].gen)
                    {
                        printf("Codigo: %d\n", infos[l].film.cod);
                        printf("Nome: %s\n", infos[l].film.nome);
                        if(infos[l].film.gen == aventura)
                            printf("Genero: aventura\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[l].film.gen == comedia)
                            printf("Genero: comedia\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[l].film.gen == drama)
                            printf("Genero: drama\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[l].film.gen == terror)
                            printf("Genero: terror\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[l].film.gen == acao)
                            printf("Genero: acao\n");//escrito por extenso (exemplo: aventura, comedia, ...)
                        else if(infos[l].film.gen == romance)
                            printf("Genero: romance\n");//escrito por extenso (exemplo: aventura, comedia, ...)

                        if(infos[l].film.class == livre)
                            printf("Classificacao: livre\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[l].film.class == dez)
                            printf("Classificacao: +10\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[l].film.class == doze)
                            printf("Classificacao: +12\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[l].film.class == quatorze)
                            printf("Classificacao: +14\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[l].film.class == dezessei)
                            printf("Classificacao: +16\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18  
                        else if(infos[l].film.class == dezoito)
                            printf("Classificacao: +18\n"); //escrito da seguinte forma: livre, +10, +12, +14, +16 ou + 18
                    }
                }
            }
            return;
        }   
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}