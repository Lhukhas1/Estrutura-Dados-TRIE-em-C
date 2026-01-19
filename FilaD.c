#include "FilaD.h"

Fila* criaFila(){
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->final = fila->inicio = NULL;

    return fila;
}
void push_Fila(Fila *fila, Conteudo *x){//coloca um conteudo na fila
    Nodo_Fila *novo = (Nodo_Fila*)malloc(sizeof(Nodo_Fila));

    novo->conteudo = x;
    novo->prox = NULL;

    if(fila->final == NULL)
        fila->inicio = novo;
    else
        fila->final->prox = novo;

    fila->final = novo;
}

Conteudo* pop_Fila(Fila *fila) {//retira um conteudo da fila
    Conteudo *aux = fila->inicio->conteudo;
    Nodo_Fila *prox = fila->inicio->prox;

    if (fila->inicio == fila->final)
        fila->final = NULL;

    free(fila->inicio);
    fila->inicio = prox;

    return aux;
}

int vazia_Fila(Fila *fila){//verifica se a fila esta vazia
    return fila->final == NULL ? 1 : 0;
}

void colocarLista(NodoTrie *raiz, Fila *fila){// Percorre a lista ate achar os nodos teminais
    for(int i = 0; i < 26; i++){
        if(raiz->filhos[i] != NULL)
            colocarLista(raiz->filhos[i], fila);
    }
    if (raiz->pessoa != NULL)
        push_Fila(fila, raiz->pessoa);//quando acha um teminal coloca um ponteiro pro conteudo na fila
}

void salvaArq(NodoTrie *raiz){//Salva todos os cadastros da trie no arquivo
    FILE *arquivo = fopen("banco.txt", "w");
    Fila *fila = criaFila();

    fprintf(arquivo, "%d\n", contaNodosTerminais(raiz));

    colocarLista(raiz, fila);

    while (!vazia_Fila(fila)) {
        Conteudo *conteudo = pop_Fila(fila);
        fprintf(arquivo, "%s %s %d\n", conteudo->id, conteudo->nome, conteudo->idade);
    }
    free(fila);
    fclose(arquivo);
}