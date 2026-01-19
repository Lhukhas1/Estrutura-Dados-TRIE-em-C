#ifndef FilaD_H_INCLUDED
#define FilaD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Trie.h"


typedef struct nodo_Fila{
    Conteudo *conteudo;
    struct nodo_Fila *prox;
}Nodo_Fila;

typedef struct fila {
    Nodo_Fila *inicio, *final;
} Fila;

Fila* criaFila();

void push_Fila(Fila *fila, Conteudo *x);//coloca um conteudo na fila

Conteudo* pop_Fila(Fila *fila);//retira um conteudo da fila

int vazia_Fila(Fila *fila);//verifica se a fila esta vazia

void colocarLista(NodoTrie *raiz, Fila *fila);//percore a trie procurando os nodos terminais e coloca seus ponteiros na fila para serem salvos

void salvaArq(NodoTrie *raiz);//acha os nodos terminais e coloca no banco

#endif 