#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "produtos.h"
#include "vendas.h"

//funcoes

void menuProdutos(itens * iten) {
    int menu, loop;

    do {
        printf("\n\n\t\t\tProdutos\n");
        printf("1- Exibir \n2- Cadastrar \n3- Atualizar\n4- Excluir \n5- Salvar \n6- Ler\n7- Salvar Binario \n8- Ler Binario\n0- Sair\n");
        scanf("%d", & menu);
        getchar();
        switch (menu) {
        case 1:
            limparTela();
            exibirProdutos(iten);
            break;
        case 2:
            limparTela();
            cadastrarProdutos(&iten);
            break;
        case 3:
            limparTela();
            atualizarProdutos(iten);
            break;
        case 4:
            limparTela();
            excluirProdutos(iten);
            break;
        case 5:
            limparTela();
            gerarHTML(&iten);
            salvarEstoque(iten);
            break;
        case 6:
            limparTela();
            lerEstoque( & iten);
            break;
        case 7:
            limparTela();
            salvarBinario(iten);
            break;
        case 8:
            limparTela();
            lerBinario( & iten);
            break;
        case 0:
            limparTela();
            printf("\nVoltando. . .\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.");
            break;
        }
    } while (menu != 0);

}

void cadastrarProdutos(itens ** iten) {
    int continuar, codigo, valida, qtdCadastros;

    do {
        printf("\nInforme a quantidade de itens a serem cadastrados: ");
        scanf("%d", & qtdCadastros);
        getchar();
        if (qtdCadastros == 0) {
            return;
        } //simples validação para quantia de cadastro, sendo 0 para cancelar cadastro
    } while (qtdCadastros < 0);

    for (int i = 0; i < qtdCadastros; i++) { //loop para cadastrar a quantia de itens inserida pela usuario
        limparTela();
        do {
            do {
                printf("\nDigite o codigo para o novo item de numero %d ou aperte 0 para cancelar:  ", i+1);
                scanf("%d", & codigo);
                getchar();
                if (codigo == 0){
                    return;
                }
                valida = pesquisaLinear(codigo, *iten);
                if (valida > -1 || codigo < 1) {
                    printf("\nCodigo invalido ou ja cadastrado. Tente novamente.");
                }
            } while (codigo < 1);
        } while (valida > -1); //validacao do codigo, utilizando do retorno da função de pesquisa
        *iten = (itens * ) realloc(*iten, (contador + 1) * sizeof(itens)); //alocação de memória para comportar um novo item na struct
        (*iten)[contador].codigo = codigo; //finalmente salva a informaçã do codigo em seu devido lugar na struct, somente depois que ela conseguir comportar nova info
        printf("\nDigite o nome para o novo item:  ");
        gets((*iten)[contador].nomeItem);
        fflush(stdin);
        do {
            printf("\nDigite o preco para o novo item:  ");
            scanf("%f", & (*iten)[contador].preco);
            getchar();
            if ((*iten)[contador].preco <= 0) {
                printf("\nPreco invalido, tente novamente. . .\n");
            }
        } while ((*iten)[contador].preco <= 0);
        do {
            printf("\nDigite a quantidade do novo item no estoque:  ");
            scanf("%d", & (*iten)[contador].estoque);
            getchar();
            if ((*iten)[contador].estoque < 0) {
                printf("\nQuantidade invalida, tente novamente. . .");
            }
        } while ((*iten)[contador].estoque < 0);

        contador++; //incrementa o contador, apontando para nova linha da struct e apontando a quantidade de itens ja cadastrados
    }
}

void exibirProdutos(itens * iten) { //simples função para exibição dos produtos na tela do usário
    bubbleSort_exibir( & iten);
    printf("\n\t\t\tItens\n");
    printf("\n%8s - %-25s - %-15s  - %10s\n", "CODIGO", "NOME", "PRECO", "ESTOQUE");
    for (int i = 0; i < contador; i++) {
        printf("\n%8d - %-25s - R$%-13.2f - %10d", iten[i].codigo, iten[i].nomeItem, iten[i].preco, iten[i].estoque);
    }
}

int pesquisaLinear(int codigo, itens * iten) { //algoritimo de pesquisa, retorna ou indice do item ou -1
    for (int i = 0; i < contador; i++) {
        if (codigo == iten[i].codigo) {
            return i;
        }
    }
    return -1; //só retorna -1 quando nenhum item foi encontrado
}

void atualizarProdutos(itens * iten) { //função para atualizar info de itens, utilizando de var temporárias para validar as mudanças
    int codigo, index, qtdAtualizar, confirma;
    float precoAtualizar;

    exibirProdutos(iten);
    printf("\n\nInforme o codigo do item que deseja atualizar:  ");
    scanf("%d", & codigo);
    getchar();
    index = pesquisaLinear(codigo, iten);
    if (index == -1) {
        printf("\nProduto nao cadastrado.\n");
    } else {
        printf("\n%s Selecionado.", iten[index].nomeItem);
        printf("\nDigite a quantia atualizada do item:  ");
        scanf("%d", & qtdAtualizar);
        getchar();
        printf("\nDigite o preco atualizado do item:  ");
        scanf("%f", & precoAtualizar);
        getchar();
        printf("\nItem atualizado! Verifique a baixo\n");

        printf("\n \tO Item %s era: R$%.2f - %d", iten[index].nomeItem, iten[index].preco, iten[index].estoque);
        printf("\n \tO Item %s sera: R$%.2f - %d", iten[index].nomeItem, precoAtualizar, qtdAtualizar);
        do {
            printf("\nDeseja confirmar as mudancas? 1- Sim 0- Nao\n");
            scanf("%d", & confirma);
            getchar();
            if (confirma == 1) {
                iten[index].estoque = qtdAtualizar;
                iten[index].preco = precoAtualizar;
                printf("\nItem atualizado com sucesso!\n");
            } else if (confirma == 0) {
                printf("\nAtualização descartada!\n");
            } else {
                printf("\nOpcao invalida! digite 1 ou 0. . .\n");
            }
        } while (confirma != 1 && confirma != 0);
    }
}

void excluirProdutos(itens * iten) {
    int index, codigo, confirma;

    exibirProdutos(iten);
    printf("\nDigite o codigo do item que deseja deletar:  ");
    scanf("%d", & codigo);
    getchar();
    index = pesquisaLinear(codigo, iten);
    if (index > -1) {
        do {
            printf("\nQuer mesmo deletar o item?\n1- Sim\n0- Nao\n");
            scanf("%d", & confirma);
            getchar();
            if (confirma == 1) {
                for (int i = index; i < contador; i++) { //algoritimo para excluir, copiando as informações da próxima linha para a anterior
                    iten[i] = iten[i + 1];
                }
                contador--; //muda o contador global, alterando a quantidade de itens cadastrados
                iten = (itens * ) realloc(iten, (contador) * sizeof(itens)); //realoca a memória dinicamente alocada, reacomodando a quantia a menos do item
            } else if (confirma == 0) {
                printf("\nRetornando. . .\n");
            } else {
                printf("\nOpcao invalida.\n");
            }
        } while (confirma < 0 || confirma > 1);
    } else {
        printf("\nCodigo invalido ou nao cadastrado. . .");
    }

}

void bubbleSort_exibir(itens ** iten) {
    itens temp;

    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - 1 - i; j++) {
            if (( * iten)[j].codigo > ( * iten)[j + 1].codigo) {
                temp = ( * iten)[j];
                ( * iten)[j] = ( * iten)[j + 1];
                ( * iten)[j + 1] = temp;
            }
        }
    }
}

void salvarEstoque(itens * iten) { //função para salvamento em arquivo texto
    FILE * pEstoque = fopen("estoque.csv", "w"); //abertura do arquivo em modo write

    if (pEstoque == NULL) {
        printf("\n Erro ao abrir o arquivo! \n");
        exit(1); //sai do programa com o codigo de erro (1)
    } //validação se o arquivo foi aberto corretamente

    fprintf(pEstoque, "%i\n", contador); //imprime no arquivo o contador
    for (int i = 0; i < contador; i++) { //em seguida o restante do estoque
        fprintf(pEstoque, "%d,%s,R$%.2f,%d\n", iten[i].codigo, iten[i].nomeItem, iten[i].preco, iten[i].estoque);
    }

    fclose(pEstoque); //fecha o arquivo

    printf("\nEstoque salvo com sucesso!");

}

void lerEstoque(itens ** iten) { //função de leitura de arquivo texto
    FILE * pEstoque = fopen("estoque.csv", "r"); //abri o arquivo texto em modo de leitura

    if (pEstoque == NULL) {
        printf("\n Erro ao abrir o arquivo! Ou arquivo inexistente, crie um novo estoque! \n");
        return;
    } //validação se o arquivo foi aberto corretamente, informando ao usuário se algo deu errado

    fscanf(pEstoque, "%d\n", & contador); //le a primeira linha, onde contem o contador
    if (contador > 0) { //valida a precença do contador para ser feita a devida alocação de memória
        * iten = (itens * ) calloc(contador, sizeof(itens));
        if (iten == NULL) {
            printf("Erro de alocação de memória.\n");
            exit(1);
        } //validação da alocação de memória

        for (int i = 0; i < contador; i++) { //leitura do conteudo do estoque, lendo os itens linha por linha após o contador
            fscanf(pEstoque, "%d,%25[^,],R$%f,%d\n", 
            & ( * iten)[i].codigo, ( * iten)[i].nomeItem, & ( * iten)[i].preco, & ( * iten)[i].estoque);
        }
    } else { //valida a precença do contador para ser feita a devida alocação de memória
        * iten = (itens * ) calloc(contador + 1, sizeof(itens));
        if (iten == NULL) {
            printf("Erro de alocação de memória.\n");
            exit(1);
        }
    }

    fclose(pEstoque); //fecha o arquivo
    printf("\nEstoque importado com sucesso.\n");
}

void salvarBinario(itens * iten) { //função para salvamento em binário, funciona de forma parecida com o salvamento de arquivo texto
    FILE * pEstoqueb = fopen("estoque.bin", "wb");

    if (pEstoqueb == NULL) {
        printf("\n Erro ao abrir o arquivo! \n");
        exit(1);
    }

    fwrite( & contador, sizeof(int), 1, pEstoqueb); //função de salvamento, de acordo com a documentação
    printf("\nescreveu o contador"); //print p/ debug
    fwrite(iten, sizeof(itens), contador, pEstoqueb);
    printf("\nescreveu a struct"); //print p/ debug

    fclose(pEstoqueb); //fecha o arquivo
}

void lerBinario(itens ** iten) { //função para leitura em binário
    FILE * pEstoqueb = fopen("estoque.bin", "rb");

    if (pEstoqueb == NULL) {
        printf("\n Erro ao abrir o arquivo! \n");
        exit(1);
    }

    fread( & contador, sizeof(int), 1, pEstoqueb); //função de leitura, de acordo com a documentação
    printf("\nleu o contador %d", contador); //print p/ debug
    * iten = (itens * ) calloc(contador, sizeof(itens)); //faz a aloção de memoria de acordo com a leitura do contador
    if (iten == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    fread(&iten, sizeof(itens), 1, pEstoqueb); //função de leitura, de acordo com a documentação
    printf("\nleu a struct\n"); //print p/ debug

    fclose(pEstoqueb); //fecha o arquivo texto
}

void limparTela() {
    #ifdef _WIN32
        system("cls");  // for Windows
    #elif __APPLE__
        system("clear");  // for macOS
    #else
        system("clear");  // for Linux/Unix
    #endif
}

void gerarHTML(itens ** iten) {
    FILE * arquivo;
    char nomeArquivo[] = "produtos.html"; // Nome do arquivo HTML de saída

    // Abre o arquivo no modo de escrita ("w")
    arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo HTML.\n");
        exit(1);
    }

    // Escreve o cabeçalho do arquivo HTML
    fprintf(arquivo, "<!DOCTYPE html>\n");
    fprintf(arquivo, "<html>\n");
    fprintf(arquivo, "<head>\n");
    fprintf(arquivo, "<title>Lista de Produtos</title>\n");
    fprintf(arquivo, "</head>\n");
    fprintf(arquivo, "<body>\n");

    // Escreve a tabela com os dados dos produtos
    fprintf(arquivo, "<h1>Lista de Produtos</h1>\n");
    fprintf(arquivo, "<table border='1'>\n");
    fprintf(arquivo, "<tr><th>Codigo</th><th>Nome</th><th>Quantidade</th><th>Preco</th><th>Vendido</th></tr>\n");

    for (int i = 0; i < contador; i++) {
        fprintf(arquivo, "<tr><td>%d</td><td>%s</td><td>%d</td><td>%.2f</td><td>%d</td></tr>\n",
            (*iten)[i].codigo, (*iten)[i].nomeItem, (*iten)[i].estoque, (*iten)[i].preco, (*iten)[i].vendidos);
    }

    fprintf(arquivo, "</table>\n");

    // Fecha as tags HTML
    fprintf(arquivo, "</body>\n");
    fprintf(arquivo, "</html>\n");

    // Fecha o arquivo após a escrita
    fclose(arquivo);

    printf("Arquivo HTML gerado com sucesso!\n");
}

void lerHtml(itens ** iten) {

    FILE * arquivo;
    char nomeArquivo[] = "exemplo.html"; // Nome do arquivo HTML

    // Abre o arquivo no modo de leitura ("r")
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Lê e exibe o conteúdo do arquivo linha por linha
    char linha[1000]; // Tamanho máximo da linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);
}