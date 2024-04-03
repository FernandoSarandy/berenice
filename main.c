#include <stdlib.h>
#include <stdio.h>
#include "produtos.h" //responsavel por manipulação do estoque, tal como cadastro e atualização
#include "vendas.h" //responsavel pelos tramites de venda, tal como pagamento e salvamento de cupom

//Berenice ver - 4.0 - Dev Fernando, Gustavo, Carlos, Ana

//global var

int contador = 0;

//main
int main() {
    int menu;

    itens *iten = NULL;

    lerEstoque(&iten);

    printf("\t\t\tBem vinda berenice!\n");
    do {
        printf("1- Produto \n2- Vendas \n0- Sair\n");
        scanf("%d", & menu);
        getchar();
        switch (menu) {
        case 1:
            limparTela();
            menuProdutos(iten);
            break;
        case 2:
            limparTela();
            menuVendas(iten);
            break;
        case 0:
            limparTela();
            salvarEstoque(iten);    
            printf("\nSaindo. . .\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.");
            break;
        }
    } while (menu != 0);

    return 0;
}