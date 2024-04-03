#ifndef PRODUTOS_H
#define PRODUTOS_H

//struct

typedef struct {
    int codigo;
    char nomeItem[26];
    float preco;
    int estoque;
    int vendidos;

}
itens;

extern int contador;

// header
int pesquisaLinear(int codigo, itens * iten); // função que busca e retorna índice de algum item da struct, ou -1 caso não encontrado
void menuProdutos(itens * iten);
void cadastrarProdutos(itens ** iten);
void exibirProdutos(itens * iten);
void atualizarProdutos(itens * iten); // função para atualizar as informações do produto, mostrando antes e depois
void excluirProdutos(itens * iten);
void bubbleSort_exibir(itens ** iten);
void salvarEstoque(itens * iten); // função para salvamento em arquivo texto
void lerEstoque(itens ** iten); // função para leitura de estoque, excluindo o estoque já em memória
void salvarBinario(itens * iten); // função para salvamento em arquivo binário
void lerBinario(itens ** iten); // função para leitura de estoque em binário, excluindo o estoque já em memória
void limparTela(); // função para limpeza de tela
void gerarHTML(itens ** iten);

#endif // PRODUTOS_H