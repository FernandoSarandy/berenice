#include <stdlib.h>
#include <stdio.h>
#include <string.h>
///Berenice ver.2.3 - 18/09/2023 - Dev Fernando Feques Sarandy, Gustavo Kafica, Ana Beatriz e Carlos Gabriel.
///global var
int estoque[5]= {0};
float preco []= {7.5, 8.69, 5, 4.5, 3.25};
char itens[][25]= {"PAO DE FORMA", "PAO DE CENTEIO", "BROA DE MILHO", "SONHO   ","TUBAINA"};
float relatorio_vendas[5]={0};
///header
void display_nome (int cod); //mostra o item selecionado enquanto valida o codigo inserido pelo usuario
void display_itens (); //faz o display dos itens disponiveis
void cadastro_estoque();
void pgto_dinheiro(float total_compra);
void pgto_cartao(float total_compra);
int vendas();
///functions
int main ()
{
    //local var
    int main_menu, continuar_vendas;
    //processo
    printf("BEM-VINDA BERENICE!\n\n");
    do{
        printf("\nMENU PRINCIPAL:\n1 - CADASTRO ESTOQUE\n2 - VISUALIZAR ESTOQUE\n3 - MENU VENDA\n0 - SAIR\n\n");
        scanf("%i",&main_menu);
        getchar();
        switch (main_menu){
        case 1:
            cadastro_estoque();
            break;
        case 2:
            display_itens();
            break;
        case 3:
            do{
                continuar_vendas=vendas();
            }
            while (continuar_vendas==1);
            break;
        case 0:
            printf("\n\nSaindo...");
            break;
        default:
            printf("OPCAO INVALIDA!!\n");
            break;
        }
    }
    while (main_menu!=0);
    return 0;
}
int vendas ()
{
    int codigo, qtd, sub_qtd[5]= {0}, pgto, loop=1, continuar=0;
    float total=0, subt, subt_un[5], maior_gasto=0;
    while(1){ //loop principal da funcao de vendas, permitindo que mais de um item seja selecionado na mesma compra
        display_itens();
        printf("\nDIGITE O CODIGO DO ITEM PARA CONTINUAR:\nDIGITE 0 PARA SAIR DA SELECAO DE ITENS:\n");
        scanf("%i", &codigo);
        getchar();
        while (codigo < 0 || codigo > 5){
            printf("\nCODIGO INVALIDO!!\nSELECIONE UM CODIGO VALIDO!!\n");
            display_itens();
            printf("\nDIGITE O CODIGO DO ITEM PARA CONTINUAR:\nDIGITE 0 PARA SAIR DA SELECAO DE ITENS:\n");
            scanf("%i", &codigo);
            getchar();
        }
        display_nome(codigo); //chamada da funcao de display, recebendo a var codigo, inserida pelo usuario logo acima
        if (codigo == 0){ //verificacao do codigo para permanecer no loop ou para sair dele, dando continuidade a compra
            break;
        }
        printf("\nDIGITE A QUANTIDADE DE ITENS:\n");
        scanf("%i", &qtd);
        getchar();
        while (qtd>estoque[codigo-1] || qtd < 0){ //rapida verificacao de qtd, se foi invalida ou se foi inserida uma quantia valida porem maior que o estoque atual do item em questao
            if (qtd>estoque[codigo-1]){
                printf("ESTOQUE INSUFICIENTE!!\nTENTE NOVAMENTE!!\nDIGITE 0 PARA SELECIONAR OUTRO ITEN:\n");
                display_nome(codigo);
                scanf("%i", &qtd);
                getchar();
            }else{
                printf("QUANTIDADE INVALIDA!!\nTENTE NOVAMENTE!!\nDIGITE 0 PARA SELECIONAR OUTRO ITEN:\n");
                display_nome(codigo);
                scanf("%i",&qtd);
                getchar();
            }
        }
        sub_qtd[codigo-1] += qtd;
        estoque[codigo-1] -= qtd;
        total=0;
        for (int i=0; i<5; i++){ //aqui vai os calculos para atribuicao de valores dos subtotais da compra
            subt = sub_qtd[i]*preco[i]; //essa linha faz a atribuicao do subtotal da compra a um var auxiliar para que entao seja somada na linha mais a baixo
            subt_un[i]=subt; //calculo para ser usado no cupom fiscal mais em baixo, atribuindo um valor a sua correspondente poscicao no vetor.
            total+=subt; // pega a var auxiliar para fazer o calculo do subtotal
        }
    }
    if (total!=0){
        //Cupom fiscal, nao consegui achar um jeito de fazer uma funcao para o cupom, já que eu usei um vetor para algumas funcionalidades
        printf("\n\n************************RESUMO DE VENDA**************************\n\n");
        for (int i=0, j=1; i<5; i++){
            if (subt_un[i]>=maior_gasto){ //repeticao feita, caso o loop ache um valor maior que o atual, só entao ele atribuirá um valor novo.
                maior_gasto=subt_un[i]; //calculo usado para determinar o item com maior gasto
            }
            if (sub_qtd[i]>0 && subt_un[i]>0){ //verificacao se a algum item chamado nessa compra, ignorando-o caso nao.
                printf("\n|%i|\t\t|%s|\t\t|%i un|\t\t|R$%.2f|", j, itens[i], sub_qtd[i], subt_un[i]); //printagem das linhas do cupom, chamando as respectivas vars
                j++; // var temporaria para servir como numeracao da lista do cupom
            }
        }
        printf("\n\n\nO TOTAL COMPRA:\nR$ %.2f", total);
        for (int i=0; i<5; i++){
            if (subt_un[i]==maior_gasto){
                printf("\nO ITEM COM MAIS GASTO:\n%s COM O SUBTOTAL DE R$ %.2f\n\n", itens[i],subt_un[i]);
                break;
            }
        }
        printf("\n\n\n****************************************************************\n\n\n");
        //chamada das funcoes de pgto
        printf("\nINFORME A FORMA DE PAGAMENTO.\n1 - DINHEIRO\n2 - CARTAO\n");
        scanf("%i",&pgto);
        getchar();
        while (loop==1){
            switch (pgto){
            case 1:
                loop=0;
                pgto_dinheiro(total);
                break;
            case 2:
                loop=0;
                pgto_cartao(total);
                break;
            default:
                printf("\nFORMA DE PAGAMENTO INVALIDA!!\nTENTE NOVAMENTE...\n");
                scanf("%i",&pgto);
                getchar();
                loop=1;
                break;
            }
        }
        printf("\nDESEJA REALIZAR UMA NOVA VENDA:\n0 - NAO\n1 - SIM\n\n");
        scanf("%i", &continuar);
        getchar();
        while (continuar<0 || continuar>1){
            printf("\nOPCAO INVALIDA, TENTE NOVAMENTE\nDESEJA REALIZAR UMA NOVA VENDA:\n0 - NAO\n1 - SIM\n\n");
            scanf("%i", &continuar);
            getchar();
        }
    }
    return continuar;
}
void display_nome (int cod) //funcao para chamada de algum item em especifico, quando selecionado
{
    switch (cod){
    case 0:
        printf("\n\n\nSAINDO...\n\n");
        break;
    default:
        printf("\n\n%s SELECIONADO, %i un RESTANTES\n",itens[cod-1], estoque[cod-1]);
        break;
    }
    return;
}
void display_itens () //funcao para chamada da tabela de itens
{
    printf("\n|COD| \t|     ITEN      |\t|ESTOQUE|       | PRECO |\n----------------------------------------------------------");
    for (int i=0; i<5; i++){
        printf("\n| %i |\t|%s\t|\t| %i un |\t|R$ %.2f|\n----------------------------------------------------------", i+1, itens[i], estoque[i], preco[i]);
    }//print das linhas dos itens dos vetores de itens, estoque e preco
    printf("\n");
}
void cadastro_estoque() //funcao de cadastro do estoque
{
    int codigo, qtd;
    while (1){
        display_itens();
        printf ("SELECIONE O PRODUTO:\nDIGITE 0 PARA SAIR:\n");
        scanf("%i", &codigo);
        getchar();
        while (codigo < 0 || codigo > 5){
            printf("\nCODIGO INVALIDO!!\nSELECIONE UM CODIGO VALIDO!!\n");
            display_itens();
            printf("\n\nDIGITE O CODIGO DO ITEM PARA CONTINUAR:\nDIGITE 0 PARA SAIR:\n");
            scanf("%i", &codigo);
            getchar();
        }
        if (codigo == 0){
            break;
        }
        display_nome (codigo);
        printf ("\nINFORME A QUANTIDADE ATUALIZADA:\n");
        scanf("%i",&qtd);
        getchar();
        while (qtd<0){
            printf("\nQUANTIDADE INVALIDA!!\n");
            display_nome(codigo);
            printf ("\nINFORME A QUANTIDADE ATUALIZADA:\n");
            scanf("%i",&qtd);
            getchar();
        }
        estoque[codigo-1]=qtd;
    }
    return;
}
void pgto_dinheiro(float total_compra) //funcao de pgto do dinheiro, ela é void pq ela nao retorna nada enquanto recebe uma var float, o total da compra
{
    float recalculo, pgto, troco;
    printf("\nFORMA DE PAGAMENTO SELECIONADA:\nDINHEIRO.\n\n");
    if (total_compra<=50){
        recalculo = (total_compra-(total_compra*0.05));
    }
    if (total_compra<100){
        recalculo = (total_compra-(total_compra*0.10));
    }else{
        recalculo = (total_compra-(total_compra*0.18));
    }
    printf("\nTOTAL COM DESCONTO:\nR$ %.2f\n", recalculo);
    printf("\nVALOR RECEBIDO:\n");
    scanf("%f", &pgto);
    getchar();
    while (pgto<recalculo){
        printf("\nPAGAMENTO INVALIDO!!\nTENTE NOVAMENTE:\n");
        scanf("%f", &pgto);
        getchar();
    }
    troco=(pgto-recalculo);
    printf("\nTROCO A DEVOLVER:\nR$ %.2f\n", troco);
    return;
}
void pgto_cartao(float total_compra) //funcao de pgto do cartao, ela é void pq ela nao retorna nada enquanto recebe uma var float, o total da compra
{
    int nparcelas;
    float recalculo, parcela;

    printf("\nFORMA DE PAGAMENTO SELECIONADA:\nCARTAO.\n\n");
    printf("\nINFORME A QUANTIDADE DE PARCELAS:\n");
    scanf("%i", &nparcelas);
    getchar();
    while(nparcelas<=0){
        printf("\nQUANTIDADE DE PARCELAS INVALIDA!!\nTENTE NOVAMENTE:\n");
        scanf("%i", &nparcelas);
        getchar();
    }
    if (nparcelas<=3){
        recalculo=(total_compra+(total_compra*0.05));
    }else{
        recalculo=(total_compra+(total_compra*0.08));
    }
    parcela=recalculo/nparcelas;
    printf("\nTOTAL COM JUROS:\nR$ %.2f\n",recalculo);
    if (recalculo!=parcela){
        printf("O VALOR DE CADA PARCELA:\nR$ %.2f\n", parcela);
    }
    return;
}
