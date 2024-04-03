#ifndef VENDAS_H
#define VENDAS_H
#include "produtos.h"

void menuVendas(itens * iten);
void realizarVenda(itens * iten); // função principal de vendas
void bubbleSort_cupom(itens carrinho[], int tamanho); // função para ordenar o cupom fiscal em ordem de gasto
void pgtoDinheiro(float * totalCompra);
void pgtoCartao(float * totalCompra);
void printCarrinho(int tamanho, itens carrinho[], float * totalCompra); // função para imprimir as informações do carrinho na tela do usuário
void relatorioVendas(itens * iten);
void salvarCupom(int tamanho, itens carrinho[], float * totalCompra); // função para salvar o cupom fiscal em arquivo texto, com data e hora

#endif // VENDAS_H