#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "bibliotecas.h"

//Global var
int contador = 0;

int main(){/*funcao principal (main)*/

    int main_menu;
    produto *estoque;

    ler(&estoque);

    do{/*menu inicial*/
        printf("\n\t\tMENU PRINCIPAL:\n\t1 - PRODUTOS\n\t2 - VENDAS\n\t3 - SAIR\n\n");
        scanf("%i", &main_menu);//menu inicial
        getchar();

        switch(main_menu){
        case 1://chama a funcao produtos
            produtos(estoque);
            break;
        case 2://chama a funcao vendas
            vendas(estoque);
            break;
        case 3://fecha o programa apos salvar as informacoes em csv
            printf("\nSaindo...Obrigado pela preferencia!\n");
            break;
        default://erro caso informe opcao nao cadastrada no menu
            printf("\nOpaco invalida!\n");
            break;
        }
    }while (main_menu != 3);

    return 0;
}