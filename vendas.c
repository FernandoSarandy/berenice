#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "produtos.h"
#include "vendas.h"

void menuVendas(itens * iten) {
    int menu, loop;

    do {
        printf("\n\t\t\tVenda\n");
        printf("1- Realizar venda \n2- Relatorio de venda \n0- Sair\n");
        scanf("%d", & menu);
        getchar();
        switch (menu) {
        case 1:
            if (contador == 0) {
                printf("\nEstoque vazio!");
            } else {
                realizarVenda(iten);
            }
            break;
        case 2:
            relatorioVendas(iten);
            break;
        case 0:
            printf("\nVoltando. . .\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.");
            break;
        }
    } while (menu != 0);

}
void realizarVenda(itens * iten) {
    itens * carrinho; //struct local para armazenamento de itens do carrinho
    int index, codigo, tamanhoCarrinho = 0, qtd, indexCarrinho;
    short int loop = 1, validaCarrinho = 0, continuar = 1;
    float totalCompra = 0; //var para pgto, sendo manipuladas via ponteiro

    carrinho = (itens * ) calloc(1, sizeof(itens)); //alocação inicial do carrinho, liberando o uso da realocação mais a fundo na função

    do {
        limparTela();
        do {
            exibirProdutos(iten);
            printf("\n\nDigite o codigo do item para continuar ou digite 0 para sair da selecao de itens\n");
            scanf("%d", & codigo);
            getchar();
            if (codigo == 0) { //garante o avanço da compra somente quando 0 solicitado pelo usuário
                continuar = 0;
                break;
            }
            index = pesquisaLinear(codigo, iten); //função achando o indice do item
            if (index < 0) {
                limparTela();
                printf("\nItem invalido ou nao cadastrado, tente novamente\n");
            } else {
                printf("\n%s selecionado", iten[index].nomeItem);
            }
        } while (index < 0);
        if (continuar != 0) { //garantia que o codigo não irá rodar quando não necessário
            while (loop == 1) { //loop de validação de quanttidade
                printf("\nDigite a quantidade de itens que gostaria:  ");
                scanf("%d", & qtd);
                getchar();
                if (qtd > iten[index].estoque || qtd < 0) { //validção de quantidade no estoque
                    printf("\nQuantidade de itens insuficiente ou invalida, tente novamente.\n");
                    loop = 1;
                } else if (qtd != 0) {
                    loop = 0;
                    for (int i = 0; i < tamanhoCarrinho; i++) { //algoritimo de pesquisa linear para o carrinho
                        if (iten[index].codigo == carrinho[i].codigo) {
                            validaCarrinho = 1; //valida a existencia do item no carrinho ou não
                            indexCarrinho = i; //associação do index do item, tal como na função pesquia linear
                        }
                    }
                    if (validaCarrinho != 1) {
                        carrinho = (itens * ) realloc(carrinho, (tamanhoCarrinho + 1) * sizeof(itens)); //realocação dinamica do carrinho, p/ comportar mais um item
                        //manipulação do carrinho, copiando item da struct de esttoque para struct do carrinho, facilitando a exibição e printagem do cupom fiscal
                        carrinho[tamanhoCarrinho] = iten[index];
                        carrinho[tamanhoCarrinho].vendidos = qtd;
                        iten[index].estoque -= qtd;
                        iten[index].vendidos += qtd;
                        tamanhoCarrinho++; //incrementa o tamanho do carrinho tal como o contador global para manipular o tamanho do carrinho
                    } else {
                        carrinho[indexCarrinho].vendidos += qtd;
                        iten[index].estoque -= qtd;
                        iten[index].vendidos += qtd;
                        validaCarrinho = 0; //reseta a validação do carrinho ao seu valor original.
                    }
                } else {
                    loop = 0; //var interagindo com o loop de validação de quantidade
                }
            }
            loop = 1; //reseta para o valor original, garantindo que se pergunte devidamente a quantidade de itens desejados
        }
    } while (continuar == 1); //validacao do loop principal
    if (tamanhoCarrinho != 0) { //garante que o trecho a seguir só será exibido se houver itens no carrinho
        printf("\n\t\t**Resumo venda**\n");
        printCarrinho(tamanhoCarrinho, carrinho, & totalCompra); //chamada de função, apontado o endereço do total da compra
        printf("\n\t O total da compra foi de: R$%.2f\n", totalCompra); //printa o total da compra após calculo feito dentro da função anterior via ponteiro
        do {
            printf("\n\nSelecine a forma de pgto:\n 1 - Dinheiro\n 2 - Cartao\n");
            scanf("%hd", & continuar);
            getchar();
            if (continuar != 1 && continuar != 2) { //validação
                printf("\nOpcao invalida, tente novamente.");
            } else if (continuar == 1) {
                pgtoDinheiro( & totalCompra); //função de pgto, enviando o total da compra via ponteiro
                bubbleSort_cupom(carrinho, tamanhoCarrinho); //bubble sort para ordernar o copum em ordem de gasto
                printf("\n\t\t**Cupom Fiscal**\n\n");
                printCarrinho(tamanhoCarrinho, carrinho, & totalCompra);

            } else {
                pgtoCartao( & totalCompra); //função de pgto, enviando o total da compra via ponteiro
                bubbleSort_cupom(carrinho, tamanhoCarrinho); //bubble sort para ordernar o copum em ordem de gasto
                printf("\n\t\t**Cupom Fiscal**\n\n");
                printCarrinho(tamanhoCarrinho, carrinho, & totalCompra);
            }
            salvarCupom(tamanhoCarrinho, carrinho, & totalCompra);
        } while (continuar != 1 && continuar != 2);
    }

    free(carrinho); //libera a memoria alocada para o carrinho, uma vez que não mais necessário
}

void bubbleSort_cupom(itens carrinho[], int tamanho) {
    itens temp; //var auxiliar para manipulação do bubble sort, segurando as infos da struct principal para fazer a ordenação
    int validaTroca; //var para validar a troca e funcionamento do algoritimo de ordenação

    for (int i = 0; i < tamanho - 1; i++) {
        validaTroca = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if ((carrinho[j].preco * carrinho[j].vendidos) < (carrinho[j + 1].preco * carrinho[j + 1].vendidos)) {
                // Troca carrinho[j] e carrinho[j + 1]
                temp = carrinho[j]; //salva as informações na var auxiliar
                carrinho[j] = carrinho[j + 1]; //faz a troca
                carrinho[j + 1] = temp; //repocisiona as informações da var auxiliar ao seu devido lugar
                validaTroca = 1; //valida para continuar a ordenação
            }
        }
        // Se nenhum elemento foi trocado nesta iteração, o array está ordenado
        if (validaTroca == 0) {
            break;
        }
    }
}
void pgtoDinheiro(float * totalCompra) { //função de pagamento utilizando ponteiro
    float pgto;

    printf("\nPgto dinheiro selecionado.\n");
    if ( * totalCompra <= 50) {
        printf("\nAplicando 5%% de desconto!\n");
        * totalCompra = ( * totalCompra - ( * totalCompra * 0.05));
    } else if ( * totalCompra < 100) {
        printf("\nAplicando 10%% de desconto!\n");
        * totalCompra = ( * totalCompra - ( * totalCompra * 0.10));
    } else {
        printf("\nAplicando 18%% de desconto!\n");
        * totalCompra = ( * totalCompra - ( * totalCompra * 0.18));
    }
    printf("\nO novo total eh: R$%.2f", * totalCompra);
    do {
        printf("\nInforme a quantia paga: \nR$");
        scanf("%f", & pgto);
        getchar();
        if (pgto < * totalCompra) {
            printf("\nPagamento invalido! Tente novamente.\n");
        } else {
            printf("\nO total da compra foi: R$%.2f", * totalCompra);
            printf("\nO troco a ser devolvido eh: R$%.2f", pgto - * totalCompra);
        }
    } while (pgto < * totalCompra);
}

void pgtoCartao(float * totalCompra) { //função de pagamento utilizando ponteiro
    int qtdParcelas;

    do {
        printf("\nPgto dinheiro selecionado.\n");
        printf("\nInforme a quantidade de parcelas\n");
        scanf("%d", & qtdParcelas);
        getchar();
        if (qtdParcelas < 1) {
            printf("\nQuantia de parcelas invalida. Tente novamente.");
        }
    } while (qtdParcelas < 1);
    printf("\nO total da compra eh: R$%.2f parcelado em %d vezes", * totalCompra, qtdParcelas);
    if (qtdParcelas <= 3) {
        printf("\nAplicando 5%% de juros!\n");
        * totalCompra = ( * totalCompra + ( * totalCompra * 0.05));
    } else {
        printf("\nAplicando 8%% de juros!\n");
        * totalCompra = ( * totalCompra + ( * totalCompra * 0.08));
    }
    printf("\nE o valor total com acrescimo eh de R$%.2f", * totalCompra);
    if (qtdParcelas > 1) {
        printf("\nO valor da parcela eh de: R$%.2f", ( * totalCompra / qtdParcelas));
    }
}

void printCarrinho(int tamanho, itens carrinho[], float * totalCompra) {
    printf("#  %-15s  %-15s  %-15s  %-15s\n", "ITEM", "PRECO UN", "QUANTIA", "SUBTOTAL");
    for (int i = 0; i < tamanho; i++) {
        printf("%-2d %-15s  R$%-13.2f  %-15d  R$%.2f\n", i + 1, carrinho[i].nomeItem, carrinho[i].preco, carrinho[i].vendidos, (carrinho[i].preco * carrinho[i].vendidos));
        * totalCompra += (carrinho[i].preco * carrinho[i].vendidos);
    }
}

void relatorioVendas(itens * iten) {
    printf("\n\t\t\tRelatorio de vendas\n");
    printf("\n%8s - %-25s - R$%-15s - %8s - %12s\n", "Codigo", "Nome", "Preco", "Estoque", "Vendidos");
    for (int i = 0; i < contador; i++) {
        if (iten[i].vendidos > 0) {
            printf("%8d - %-25s - R$%-15.2f - %8d - %10d\n", iten[i].codigo, iten[i].nomeItem, iten[i].preco, iten[i].estoque, iten[i].vendidos);
        }
    }
}

void salvarCupom(int tamanho, itens carrinho[], float * totalCompra) { //função para salvamento de arquivo texto do cupom fiscal
    //var utilizadas paras funções da biblioteca time.h
    time_t rawtime;
    struct tm * timeinfo; //struct da biblioteca time.h
    char arquivoVenda[50]; //nome do arquivo

    time( & rawtime); //função da biblioteca time.h
    timeinfo = localtime( & rawtime);

    strftime(arquivoVenda, sizeof(arquivoVenda), "venda_%d.%m.%Y._%H.%M.%S.txt", timeinfo);
    //função para salvamento do nome do arquivo, nome do aqruivo, tamanho do titulo, formato do titulo, informações da sturct do time.h
    FILE * arquivo = fopen(arquivoVenda, "w"); //abertura do arquivo texto em modo write, enviado var arquivo venda como nome, recebendo, assim, a data e hora

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo\n");
        return;
    } // validação se abriu o arquivo ou não
    fprintf(arquivo, "#  %-12s  %-12s  %-12s  %-12s\n", "ITEM", "PRECO UN", "QUANTIA", "SUBTOTAL"); //print do cabeçalho
    * totalCompra = 0;
    for (int i = 0; i < tamanho; i++) { //print do cupom fiscal
        fprintf(arquivo, "%-2d - %-12s - R$%-11.2f - %-12d - R$%.2f\n", i + 1, carrinho[i].nomeItem, carrinho[i].preco, carrinho[i].vendidos, (carrinho[i].preco * carrinho[i].vendidos));
        * totalCompra += (carrinho[i].preco * carrinho[i].vendidos);
    }
    fprintf(arquivo, "\nO total da compra foi: R$%.2f\n", * totalCompra); // print do total da compra

    fclose(arquivo); //fecha o arquivo
}