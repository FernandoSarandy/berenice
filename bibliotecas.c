#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "bibliotecas.h"

//funcoes:
void produtos(produto *estoque){

    int menu_produtos;

    do{/*menu de produtos*/
        printf("\n\t\tMENU DE PRODUTOS:\n\n\t1 - EXIBIR\n\t2 - CADASTRAR\n\t3 - ATUALIZAR\n\t4 - EXCLUIR\n\t5 - SALVAR\n\t6 - LER\n\t7 - VOLTAR\t\n\t8 - SALVAR BIN\n\n");
        scanf("%i", &menu_produtos);//menu de produtos
        getchar();

        switch(menu_produtos){
        case 1://chama a funcao exibir
            exibir(estoque);
            break;
        case 2://chama a funcao cadastrar
            cadastrar(estoque);
            salvar(estoque);
            salvar_bin(estoque);
            //gerarHTML(estoque);
            break;
        case 3://chama a funcao atualizar
            atualizar(estoque);
            break;
        case 4://chama a funcao excluir
            excluir(estoque);
            salvar(estoque);
            salvar_bin(estoque);
            //gerarHTML(estoque);
            break;
        case 5://chama a funcao salvar
            salvar(estoque);
            salvar_bin(estoque);
            gerarHTML(&estoque);
            break;
        case 6://chama a funcao ler
            ler(&estoque);
            lerHtml(&estoque);
            break;
        case 7://volta ao menu anterior
            printf("Voltando. . .\n");
            break;
        case 8:
            salvar_bin(estoque);
            break;
        default://erro caso informe a opcao nao cadastrada no menu
            printf("\nOpcao invalida!\n");
            break;
        }
    }while(menu_produtos != 7);//loop ate usuario desejar sai
}

void vendas(produto *estoque){

    int menu_vendas, loop;

    do{
        printf("\n\t\tMENU VENDAS:\n\t1 - REALIZAR VENDAS\n\t2 - RELATORIO VENDAS\n\t3 - VOLTAR\n\n");
        scanf("%i", &menu_vendas);//menu de vendas
        getchar();

        switch(menu_vendas){
        case 1:
            do{
                loop = realizar_venda(estoque);
            }while(loop == 1);
            salvar(estoque);
            break;
        case 2:
            relatorio_vendas(estoque);
            salvar(estoque);
            break;
        case 3:
            printf("\nVoltando. . .\n");
            break;
        default:
            printf("\nOpcao invalida!\n");//opcao inexistente do menu
            break;
        }
    }while(menu_vendas != 3);//continua no menu ate selecionar opcao valida
}

void exibir(produto *estoque){
    //void limparTela();
    printf("\n\t\t\tPRODUTOS CADASTRADOS:\n\n");
    printf("\nCODIGO\t\tNOME DO ITEM\t\t\tVALOR(UNIDADE)\t\tESTOQUE\n\n");

    for(int i = 0; i < contador; i++){
        printf("%-15i %-26s %15.2f %20i\n", estoque[i].codigo, estoque[i].nome, estoque[i].preco, estoque[i].quantidade);
    }
}

int cadastrar(produto *estoque){

    int validacao, loop = 1, cod;

    do{
        printf("\nDigite o codigo do produto: \n");
        scanf("%i", &cod);//solicita que insira um codigo para ser cadastrado
        getchar();

        if(cod > 0){
            estoque = (produto *)realloc(estoque, (contador + 1) * sizeof(produto)); // separa espaco no arquivo para cadastro de nova struct e altera o valor do contador

            do{
                validacao = pesquisa(cod, estoque);

                if(validacao < 0){
                    printf("\nCodigo cadastrado com sucesso!\n");
                    estoque[contador].codigo = cod;
                    printf("\n%i", estoque[contador].codigo);//cadastra o codigo do produto
                }else{
                    printf("\nCodigo ja cadastrado, digite outro codigo para cadastro!\n");
                    printf("\nDigite o codigo para cadastro: \n");//recusa cadastro de codigos repetidos/invalidos
                    scanf("%i", &cod);
                    getchar();
                }
            }while(validacao >= 0);

            printf("\nDigite o nome do produto: \n");
            gets(estoque[contador].nome);//cadastra o nome do produto
            fflush(stdin);
            printf("\nDigite o valor do produto: \n");
            scanf("%f", &estoque[contador].preco);//cadastra o preco do produto
            getchar();
            printf("\nDigite a quantidade para o estoque: \n");
            scanf("%i", &estoque[contador].quantidade);//cadastra a quantidade de estoque
            getchar();
            printf("\nProduto cadastrado com sucesso!");

            contador++;

            do{
                printf("\nGostaria de cadastrar mais produtos? \n1 - SIM\n2 - NAO\n"); // mini menu para continuar cadastrando ou nao
                scanf("%i", &loop);
                getchar();
            }while(loop != 1 && loop != 2);
        }else{
            printf("\nNumero para codigo invalido! Confira o numero e tente novamente.\n"); // codigo deve ser maior que 0 e nao ter sido cadastrado antes
            loop = 1;
        }
    }while(loop == 1);
    return loop;
}

int pesquisa(int cod, produto *estoque){/*pesquisa o produto pelo codigo*/

    for(int i = 0; i < contador; i++){
        if(estoque[i].codigo == cod){
            return i;//retorna o codigo do produto
        }
    }
    return -1;//retorna quando nao foi encontrado
}

void atualizar(produto *estoque){

    int cod, indice, menu, continuar;
    char nome[MAX_NAME_STR];

    exibir(estoque);

    do{
        printf("\nDigite o codigo do produto: \n");//buscar codigo do produto
        scanf("%i", &cod);
        getchar();
        indice = pesquisa(cod, estoque);
        if(indice < 0){
            printf("\nCodigo nao cadastrado, confira o numero e tente novamente.\n"); // para codigo nao existente
        }
    }while(indice < 0);

    do{
        printf("\nO codigo %i foi selecionado!", estoque[indice].codigo);
        printf("\nO que deseja alterar:\n1 - NOME\n2 - PRECO\n3 - QUANTIDADE\n"); // opcao para alterar atraves do codigo do produto
        scanf("%i", &menu);
        getchar();

        switch(menu){
            case 1:
                printf("\nDigite o novo nome para o produto:\n");
                gets(estoque[indice].nome);//alterando o nome do produto
                fflush(stdin);
                printf("\nNome cadastrado com sucesso.");
                
                continuar = miniM_atualizar();
                break;
            case 2:
                printf("\nDigite o novo valor para o produto:\n");
                scanf("%f", &estoque[indice].preco);//alterando o valor do produtos
                getchar();

                continuar = miniM_atualizar();
                break;
            case 3:
                printf("\nDigite a nova quantidade do produto:\n");
                scanf("%i", &estoque[indice].quantidade);//alterando a quantidade do produto
                getchar();
                
                continuar = miniM_atualizar();
                break;
            default:
                printf("\nOpcao invalido, tente novamente: \n");
                continuar = 1;
                break;
        }
    }while(continuar != 2);
}

void excluir(produto *estoque){

    int cod, indice, continuar, menu;

    exibir(estoque);

    do{
        printf("\nDigite o codigo do produto: \n");//escolha do produto a ser excluido
        scanf("%i", &cod);
        getchar();
        indice = pesquisa(cod, estoque);
        if(indice < 0){/*verificar se codigo cadastrado*/
            printf("\nCodigo nao cadastrado, confira o numero e tente novamente.\n");
        }
    }while(indice < 0);

    do{
        printf("\nO codigo %i foi selecionado!", estoque[indice].codigo);
        printf("\nDeseja mesmo deletar o produto?\n1 - SIM\n2 - NAO\n");//menu para confirmar exclusao
        scanf("%i", &continuar);
        getchar();

        if(continuar == 1){
            for(int i = indice; i < contador; i++){
                estoque[i] = estoque[i + 1];
            }
            contador--;
            estoque = (produto *)realloc(estoque, (contador) * sizeof(produto));//realoca todos os itens do arquivo txt para uma posicao anterior
        }else if(continuar == 2){
            printf("\n Retornando . . . \n");//retorna ao menu anterior
            menu = -1;
        }else{
            printf("\n Opcao invalida! Tente novamente! \n");//escolha errada no menu de exclusao
        }
    }while(continuar != 1 && continuar != 2);//mantem o menu de exclusao ate a opcao valida ser digitada

    printf("\n Alteracao feita com sucesso! Confira a baixo: \n");//confirmacao do item excluido
    printf("\nCodigo - %i \nNome - %s \nPreco - %.2f \nQuantidade - %i", estoque[indice].codigo, estoque[indice].nome, estoque[indice].preco, estoque[indice].quantidade);
}

int salvar(produto *estoque){/*salva em csv*/

    FILE *pont_arq = fopen("produtos.csv", "w");

    if(pont_arq == NULL){
        printf("\n Erro ao abrir o arquivo! \n");//quando arquivo nao localizado/inexistente/com erros
        return 1;
    }

    fprintf(pont_arq, "Quantidade de itens; %i\n", contador);//salvamento dentro do csv
    fprintf(pont_arq, "Codigo; Nome; Preco; Quantidade\n");
    for(int i = 0; i < contador; i++){
        fprintf(pont_arq, "%i,%s,%.2f,%i,%i\n", estoque[i].codigo, estoque[i].nome, estoque[i].preco, estoque[i].quantidade, estoque[i].vendido);
    }

    ordenar(&estoque);

    fclose(pont_arq);//fecha o arquivo csv

    return -1;
}

int ler(produto **estoque){

    FILE *pont_arq = fopen("produtos.csv", "r");

    if(pont_arq == NULL){
        printf("\n Erro ao abrir o arquivo! \n");//quando arquivo nao localizado/inexistente/com erros
        return 1;
    }

    fscanf(pont_arq, "Quantidade de itens; %i\n", &contador);//salvamento dentro do txt

    //alocacao de memoria
    *estoque = (produto *)calloc((contador + 1), sizeof(produto));//verifica alocacao da memoria
    if(estoque == NULL){
        printf("Erro de alocação de memória.\n");
        fclose(pont_arq);
        return 1;
    }

    fscanf(pont_arq, "Codigo; Nome; Preco; Quantidade\n");
    for(int i = 0; i < contador; i++){
        fscanf(pont_arq, "%i,%25[^,],%f,%i,%i\n", &(*estoque)[i].codigo, (*estoque)[i].nome, &(*estoque)[i].preco, &(*estoque)[i].quantidade, &(*estoque)[i].vendido);
    }

    fclose(pont_arq);//fecha o arquivo csv

    return -1;
}

int realizar_venda(produto *estoque){
    //carrinho struct;
    produto * carrinho;
    int indice, quant, cod, indcarro, contcarro = 0, validacarro, continua;

    carrinho = (produto *) calloc (1, sizeof(produto));//inicializa a alocação do carrinho
    //vendas
    //perguntar qual item comprar/validar se existe o código;
    do{
        exibir(estoque);
        do{
            printf("\nDigite o codigo do produto: \n");//escolha do produto a ser excluido atraves do codigo
            scanf("%i", & cod);
            getchar();
            indice = pesquisa(cod, estoque);
            if(indice < 0){/*verificar se o codigo esta cadastrado*/
                printf("\nCodigo nao cadastrado, confira o numero e tente novamente: \n");
            }
        }
        while(indice < 0);
        //qual quantidade;
        do{
            printf("\nDigite a quantidade desejada: \n");//cadastra a quantidade de estoque
            scanf("%i", & quant);
            getchar();
            if(quant > estoque[indice].quantidade){//validar quantidade existente;
                printf("Quantidade invalida, tente de novo:");
            }
        }
        while(quant > estoque[indice].quantidade);

        //item já existe no carrinho(se sim:modificar item carrinho/se não: adicionar o novo item ao carrinho);
        validacarro = 0;
        for(int i = 0; i < contcarro; i++){
            if(estoque[indice].codigo == carrinho[i].codigo){
                indcarro = i;
                validacarro = 1; //indica que o item já existe no carrinho
                break;//para de percorrer o carrinho
            }
        }
        if(validacarro == 1){//item já existe dentro do carrinho
            carrinho[indcarro].vendido += quant;
            estoque[indice].quantidade -= quant;
            estoque[indice].vendido += quant;
        }else{
            carrinho[contcarro] = estoque[indice];
            carrinho[contcarro].vendido = quant;
            estoque[indice].quantidade -= quant;
            estoque[indice].vendido += quant;
            contcarro++; //adiciona nova posicao ao carrinho indicando quantos itens tem dentro
        }
        carrinho = (produto *)realloc(carrinho,(contcarro + 1) * sizeof(produto)); //realocação para o carrinho p/ novo item

        do{//perguntar se deseja adicionar mais itens;
            printf("\nDeseja adicionar mais produtos?\n1 - SIM\n2 - NAO\n");
            scanf("%i", &continua);
            getchar();
            if(continua < 1 || continua > 2){
                printf("\nOpacao invalida, tente novamente: \n");
            }
        }
        while(continua < 1 || continua > 2);
    }
    while(continua == 1);//loop

    pagamento(carrinho, contcarro);

    do{//perguntar se deseja realizar outra venda;
        printf("\nDeseja realizar outra venda?\n1 - SIM\n2 - NAO\n");
        scanf("%i", & continua);
        getchar();
        if(continua == 1){
            return 1; //retorna pra funcao anterior com valor de 1
        }else if (continua == 2){
            return 2; //retorna para funcao anterior(vendas)
        }else{
            printf("\nOpcao invalida, tente novamente: \n");
        }
    }while(continua != 1 && continua != 2);
}

void pagamento(produto * carrinho, int contcarro){

    int menu_pagamento;
    float subtotal = 0;
    //percorrer carrinho;
    //calcular quantidade de cada item vendido pelo preço;
    printf("\nCODIGO\tNOME DO ITEM\tQUANTIDADE\tVALOR(UNIDADE)\tESTOQUE\tSUBTOTAL\n\n");
    for(int i = 0; i < contcarro; i++){
        subtotal += (carrinho[i].preco * carrinho[i].vendido);
        //mostrar carrinho;
        printf("\n%-6i %-20s %-10i %-10.2f %-10.2f\n", carrinho[i].codigo, carrinho[i].nome, carrinho[i].vendido, carrinho[i].preco, (carrinho[i].vendido * carrinho[i].preco));
    }//adquirir o total da compra final;
    printf("TOTAL DA COMPRA:\t\t%.2f", subtotal);
    //perguntar forma de pagamento;
    do{
        printf("\nO valor total da compra foi de %.2f\n", subtotal);
        printf("\nQual a forma de pagamento deseja realizar?\n1 - A vista\n2 - A prazo\n");
        scanf("%i", & menu_pagamento);
        getchar();

        switch(menu_pagamento){
        case 1:
            printf("\nVoce escolheu pagamento a vista!\n");
            pagamento_a_vista(subtotal);
            break;
        case 2:
            printf("\nVoce escolheu pagamento a prazo!\n");
            pagamento_a_prazo(subtotal);
            break;
        default:
            printf("\nOpcao invalida, tente novamente:\n");
            break;
        }
    }while(menu_pagamento != 1 && menu_pagamento != 2);
    
    cupom(contcarro, carrinho);
    printf("\nexecutou cupom\n");
    salvar_cupom(contcarro, carrinho);
}

void pagamento_a_vista(float subtotal){

    float valpago, total;
    //calcular quando a vista os descontos(perguntar valor pago pelo cliente e validar/calcular troco);
    if(subtotal <= 50){ //desconto de 5%
        total = subtotal * 0.95;
    }else if(subtotal > 50 && subtotal < 100){//desconto de 10%
        total = subtotal * 0.90;
    }else{ //desconto de 18%
        total = subtotal * 0.82;
    }
    printf("\nO valor final da compra será de R$ %.2f já com o desconto!\n", total);
    printf("\nInforme o valor recebido do cliente: \n");
    scanf("%f", & valpago);
    if(valpago == total){
        printf("\nValor pago nao gerou troco!\n");
        printf("\nObrigado pela preferencia!\n");
    }else if(valpago > total){
        printf("\nO valor pago gerou troco de R$%.2f\n", valpago - total);
        printf("\nObrigado pela preferencia!\n");
    }else{
        printf("\nO valor pago nao foi suficiente! Necessário para pagamento R$%.2f a mais\n", total - valpago);
        printf("\nInforme o valor recebido do cliente: \n");
        scanf("%f", & valpago);
        if(valpago == total){
            printf("\nValor pago nao gerou troco!\n");
            printf("\nObrigado pela preferencia!\n");
        }else if(valpago > total){
            printf("\nO valor pago gerou troco de R$%.2f\n", valpago - total);
            printf("\nObrigado pela preferencia!\n");
        }else{
            printf("\nO valor pago nao foi suficiente!\n");
            printf("\nObrigado pela preferencia!\n");
        }
    }
}

void pagamento_a_prazo(float subtotal){
    //calcular os juros quando a prazo;
    float total, mensalidade;
    int parcelas;

    do{
        printf("\nInforme o numero de parcelas: \n");
        scanf("%i", & parcelas);
        getchar();
        if(parcelas <= 1){
            printf("\nNumero de parcelas invalido, informe a quantidade de parcelas desejadas acima de 1.\n");
        }
    }while(parcelas <= 1);
    if(parcelas <= 3){
        total = subtotal * 1.05;//juros de 5%
    }else{
        total = subtotal * 1.08;//juros de 8%
    }
    mensalidade = total / parcelas;

    printf("\nO valor total da compra sera de R$%.2f, com %i parcelas no valor de R$%.2f cada mes.\n", total, parcelas, mensalidade);
    printf("\nObrigado pela preferencia!\n");
}

void cupom(int contcarro, produto * carrinho){

    produto aux;
    float subtotal = 0;

     for(int i = 0; i < contcarro; i++){
        for(int j = 0; j < contcarro - i - 1; j++){
            if((carrinho[j].vendido * carrinho[j].preco) < (carrinho[j + 1].vendido * carrinho[j+1].preco)){
                aux = carrinho[j];
                carrinho[j] = carrinho[j + 1];
                carrinho[j + 1] = aux;
            }
        }
    }
    //mostrar cupom(maior valor pro menor);
    printf("\nCODIGO\tNOME DO ITEM\tQUANTIDADE\tVALOR(UNIDADE)\tSUBTOTAL\n\n");
    for(int i = 0; i < contcarro; i++){
        subtotal += (carrinho[i].preco * carrinho[i].vendido);
        printf("\n%-6i %-20s %-10i %-10.2f %-10.2f\n", carrinho[i].codigo, carrinho[i].nome, carrinho[i].vendido, carrinho[i].preco, (carrinho[i].vendido * carrinho[i].preco));
    }
    printf("TOTAL DA COMPRA:\t\t%.2f", subtotal);
}

void relatorio_vendas(produto *estoque){

    produto aux;

    for(int i = 0; i < contador; i++){
        for(int j = 0; j < contador - i - 1; j++){
            if((estoque[j].vendido * estoque[j].preco) < (estoque[j + 1].vendido * estoque[j+1].preco)){
                aux = estoque[j];
                estoque[j] = estoque[j + 1];
                estoque[j + 1] = aux;
            }
        }
    }//mostrar os itens vendidos(maior valor pro menor);
    printf("\n\t\t\t\t\tPRODUTOS CADASTRADOS:\n");
    printf("\nCODIGO\tNOME DO ITEM\tVALOR(UNIDADE)\tQUANTIDADE\n\n");

    for(int i = 0; i < contador; i++){
        printf("%-6i %-20s %-10.2f %-10i\n", estoque[i].codigo, estoque[i].nome, estoque[i].preco, estoque[i].vendido);
    }
    //informa o produto que menos vendeu;
    //printf("\nO item menos vendido foi o:\n");
    //printf("\n%s,\tcodigo: %i\n", estoque[contador - 1].nome, estoque[contador - 1].codigo);
}

int salvar_cupom(int contcarro, produto *carrinho){//salvar txt

    time_t tempo_atual;
    struct tm *info_tempo;
    char cupomTime[50];
    //pega informação da data e hora local
    time(&tempo_atual);
    info_tempo = localtime(&tempo_atual);
    //Formatar a data e a hora
    strftime(cupomTime,sizeof(cupomTime), "venda do %d-%m-%Y - %H-%M-%S.txt", info_tempo);

    FILE * pont_arq = fopen(cupomTime, "w");

    if(pont_arq == NULL){
        printf("\n Erro ao abrir o arquivo! \n");//quando arquivo nao localizado/inexistente/com erros
        return 1;
    }
    //salvamento dentro do txt
    fprintf(pont_arq, "\nCODIGO\tNOME DO ITEM\tQUANTIDADE\tVALOR(UNIDADE)\tSUBTOTAL\n\n");
    for(int i = 0; i < contcarro; i++){
        fprintf(pont_arq, "%-6i,%-20s,%-10i,%-10.2f,%-10.2f\n", carrinho[i].codigo, carrinho[i].nome, carrinho[i].vendido, carrinho[i].preco, (carrinho[i].vendido * carrinho[i].preco));
    }
    fclose(pont_arq);//fecha o arquivo txt

    return -1;
}

void salvar_bin(produto *estoque){//salva arquivo formato binario

    FILE *estoquebin = fopen("estoque.bin", "wb");

    if(estoquebin == NULL){
        printf("\nErro na abertura do arquivo.\n");
        exit(1);
    }
    fwrite(&contador, sizeof(int), 1, estoquebin);
    printf("\nContador ok.\n");
    fwrite(estoque, sizeof(produto), contador, estoquebin);

    fclose(estoquebin);//fechamento do arquivo binario
}

void ler_bin(produto **estoque){

    FILE *estoquebin = fopen("estoque.bin", "rb");

    if(estoquebin == NULL){
        printf("\nErro na abertura do arquivo.\n");
        exit(1);
    }
    fread(&contador, sizeof(int), 1, estoquebin);
    printf("\nContador ok.\n");

    *estoque = (produto *)calloc((contador + 1), sizeof(produto));//verifica alocacao da memoria

    if(estoque == NULL){
        printf("Erro de alocação de memória.\n");
        fclose(estoquebin);
        exit(1);
    }
    fread(estoque, sizeof(produto), contador, estoquebin);

    fclose(estoquebin);//fechamento do arquivo binario
}

/*void limparTela(){//funcao de limpeza de tela para facilitar leitura do programa
    printf("\e[1;1H\e[2J");
    //e provides an escape. and e [1;1H] place your cursor in the upper right corner of the console screen. and e [2J adds a space to the top of all existing screen characters.}
    //limpa no tela no linux
}*/

void ordenar(produto **estoque){

    produto aux;

    for(int i = 0; i < contador; i++){
        for(int j = 0; j < contador - i - 1; j++){
            if((*estoque)[j].codigo > (*estoque)[j + 1].codigo){
                aux = (*estoque)[j];
                (*estoque)[j] = (*estoque)[j + 1];
                (*estoque)[j + 1] = aux;
            }
        }
    }
}

int lerHtml(produto **estoque){
    //Comando para abrir o arquivo HTML no navegador
    #ifdef _WIN32
        system("start produtos.html");
    #else 
    #ifdef __APPLE__
        system("open produtos.html");
    #else
        system("xdg-open produtos.html");
    #endif
    #endif

    return 0;
}

void gerarHTML(produto **estoque){

    FILE *arquivo;
    char ArquivoHtml[] = "produtos.html";//Nome do arquivo HTML de saída
    arquivo = fopen(ArquivoHtml, "w");//Abre o arquivo no modo de escrita

    if(arquivo == NULL){
        printf("Erro ao criar o arquivo HTML.\n");
        return;
    }
    //Escreve o cabeçalho do arquivo HTML
    fprintf(arquivo, "<!DOCTYPE html>\n");
    fprintf(arquivo, "<html>\n");
    fprintf(arquivo, "<head>\n");
    fprintf(arquivo, "<title>Vendinha da Berenice</title>\n");
    fprintf(arquivo, "<style>\n");
    fprintf(arquivo, "body {\n");
    fprintf(arquivo, "    font-family: 'Bradley Hand', cursive;\n"); //Fonte do texto
    fprintf(arquivo, "    color: #8b4513;\n");                       //Cor para o restante do texto
    fprintf(arquivo, "    background-color: #FFE4E1;\n");            //Cor de fundo
    fprintf(arquivo, "    text-align: center;\n");                   //Alinha o texto no centro
    fprintf(arquivo, "}\n");
    fprintf(arquivo, "h1 {\n");
    fprintf(arquivo, "    color: #DC143C;\n");     //Cor do título
    fprintf(arquivo, "    text-align: center;\n"); //Alinha o título no centro
    fprintf(arquivo, "}\n");
    fprintf(arquivo, "table {\n");
    fprintf(arquivo, "    border-collapse: collapse;\n");
    fprintf(arquivo, "    width: 80%%;\n");
    fprintf(arquivo, "    margin: 20px auto;\n");
    fprintf(arquivo, "}\n");
    fprintf(arquivo, "th, td {\n");
    fprintf(arquivo, "    border: 1px solid #c71585;\n");
    fprintf(arquivo, "    text-align: left;\n");
    fprintf(arquivo, "    padding: 8px;\n");
    fprintf(arquivo, "}\n");
    fprintf(arquivo, "th {\n");
    fprintf(arquivo, "    background-color: #e6e6fa;\n");
    fprintf(arquivo, "}\n");
    fprintf(arquivo, ".nome-produto {\n");
    fprintf(arquivo, "    color: #000000;\n");//Cor do nome dos produtos
    fprintf(arquivo, "}\n");
    fprintf(arquivo, ".valor {\n");
    fprintf(arquivo, "    color: #000080;\n");//Cor dos valores
    fprintf(arquivo, "}\n");
    fprintf(arquivo, ".quantidade {\n");
    fprintf(arquivo, "    color: #008000;\n");//Cor das quantidades
    fprintf(arquivo, "}\n");
    fprintf(arquivo, "</style>\n");
    fprintf(arquivo, "</head>\n");
    fprintf(arquivo, "<body>\n");
    //Escreve a tabela com os dados dos produtos
    fprintf(arquivo, "<h1>Vendinha da Berenice</h1>\n");
    fprintf(arquivo, "<table>\n");
    fprintf(arquivo, "<tr><th>Código</th><th class='nome-produto'>Nome</th><th class='quantidade'>Quantidade</th><th class='valor'>Preço</th><th>Vendido</th></tr>\n");

    for(int i = 0; i < contador; i++){
        fprintf(arquivo, "<tr><td>%i</td><td class='nome-produto'>%s</td><td class='quantidade'>%i</td><td class='valor'>%.2f</td><td>%i</td></tr>\n",
                (*estoque)[i].codigo, (*estoque)[i].nome, (*estoque)[i].quantidade, (*estoque)[i].preco, (*estoque)[i].vendido);
    }
    fprintf(arquivo, "</table>\n");
    //Fecha as tags HTML
    fprintf(arquivo, "</body>\n");
    fprintf(arquivo, "</html>\n");
    //Fecha o arquivo após a escrita
    fclose(arquivo);

    printf("Arquivo HTML gerado com sucesso!\n");
}

int miniM_atualizar(){//menu para loop na função atualizar
           
    int continua, menu;

    do{
        printf("\nDeseja continuar editando?\n1 - SIM\n2 - NAO\n"); //mini menu para saber se havera novas alteracoes
        scanf("%i", &continua);
        getchar();

        if(continua == 1){//volta no menu de atualizar
            return 1;
        }else if(continua == 2){
            printf("\nRetornando. . .\n"); //retorna ao menu anterior
            return 2;
        }else{
            printf("\nOpcao invalida! Tente novamente:\n"); //selecao de opcao nao existente
        }
    }while (continua != 1 && continua != 2);
}