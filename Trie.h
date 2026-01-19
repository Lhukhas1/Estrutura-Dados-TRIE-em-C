#ifndef Trie_H_INCLUDED
#define Trie_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conteudo{
    char nome[1000], id[30];
    unsigned int idade;
}Conteudo;

typedef struct nodoTrie{
    Conteudo *pessoa;
    struct nodoTrie *pai;
    struct nodoTrie *filhos[26];
}NodoTrie;

NodoTrie* criaNodo();

int calculaIndice(char letra);//calcula a posicao de uma letra no vetor de 26 posiçoes

void insere(NodoTrie *raiz, char *letra, Conteudo *conteudo);//insere o id na trie

int temFilhos(NodoTrie *nodo);//verifica se um nodo tem filhos

NodoTrie* busca(NodoTrie *raiz, char *letra);//busca um um id na trie

Conteudo* criaConteudo();//aloca memoria pra um cadastro

void destroiTrie(NodoTrie *raiz);//libera memoria de todos os nodos e por fim da raiz tmb

void imprimeArvore(NodoTrie *raiz);//imprime toda a arvore

void removeNodo(NodoTrie *raiz, char *palavra, int tamanho);//remove um id da trie

void retiraEspaco(char *nome);//remove o espaço do fim do nome

int contaNodosTerminais(NodoTrie *raiz);//percorre a lista e conta quantos sao terminais

void carregaArq(NodoTrie *raiz);//le o arquivo banco e carrega pra trie

#endif
