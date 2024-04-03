#ifndef BIBLIOTECAS_H
#define BIBLIOTACAS_H

#define MAX_NAME_STR 26//forma utilizada para dizer quanto de espaco cabe na variavel nome de dentro da struct

//Struct
typedef struct{
    int codigo;
    char nome[MAX_NAME_STR];//utilizado para facilitar o manuseio do codigo caso queira mudar a quantidade guardada no char nome
    int quantidade;
    float preco;
    int vendido;
}produto;

extern int contador;

//funcoes
void produtos(produto *estoque);
void vendas(produto *estoque);
void exibir(produto *estoque);
int cadastrar(produto *estoque);
void atualizar(produto *estoque);
void excluir(produto *estoque);
int salvar(produto *estoque);
int ler(produto **estoque);
int realizar_venda(produto *estoque);
void pagamento (produto * carrinho, int contcarro);
void pagamento_a_vista(float subtotal);
void pagamento_a_prazo(float subtotal);
void cupom(int contcarro, produto * carrinho);
void relatorio_vendas(produto * estoque);
int salvar_cupom(int contcarro, produto *carrinho);
int pesquisa(int cod, produto *estoque);
void salvar_bin(produto *estoque);
void ler_bin(produto **estoque);
//void limparTela();
void ordenar(produto **estoque);
void gerarHTML(produto **estoque);
int lerHtml(produto **estoque);
int miniM_atualizar();

#endif // BIBLIOTECAS_H
