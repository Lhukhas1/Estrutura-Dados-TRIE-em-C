#include "Trie.h"

NodoTrie* criaNodo(){ // cria um nodo vazio com todos os ponterios NULL
    NodoTrie *novo = (NodoTrie*)malloc(sizeof(NodoTrie));
    novo->pai = NULL;
    novo->pessoa = NULL;

    for(int i = 0; i < 26; i++)
        novo->filhos[i] = NULL;
    
    return novo;
}

void insere(NodoTrie *raiz, char *letra, Conteudo *conteudo){//insere o nodo na trie
    int indice = calculaIndice(*letra);

    if(*letra == '\0'){//vai ate o fim da palavra
        raiz->pessoa = conteudo;
        return;
    }
    else if(raiz->filhos[indice] == NULL){
        raiz->filhos[indice] = criaNodo();
        raiz->filhos[indice]->pai = raiz;//coloca o pai do novo nodo criado 
    }

    insere(raiz->filhos[indice], letra + 1, conteudo);
}

int temFilhos(NodoTrie *nodo){//Busca linear para saber se um no tem filhos
    for(int i = 0; i < 26; i++)
        if(nodo->filhos[i] != NULL)//Retorna 1 se tiver filhos e 0 se nao tiver
            return 1;

    return 0;
}

NodoTrie* busca(NodoTrie *raiz, char *letra){//desce ate o fim da palavra, se for terminal retorna um ponteiro pra ele
    int indice = calculaIndice(*letra);

    if(*letra == '\0')
        return raiz->pessoa == NULL? NULL : raiz;

    if(raiz->filhos[indice] == NULL)
        return NULL;

    return busca(raiz->filhos[indice], letra + 1);
}


Conteudo* criaConteudo(){//Apenas aloca memoria 
    Conteudo *aux = (Conteudo*)malloc(sizeof(Conteudo));
    return aux;
}

void destroiTrie(NodoTrie *raiz){//da free em todos os nodos e seus conteudos caso houver 
    for(int i = 0; i < 26; i++)
        if(raiz->filhos[i] != NULL)
            destroiTrie(raiz->filhos[i]);
        
    if(raiz->pessoa != NULL)
        free(raiz->pessoa); 
    
    free(raiz);//da free no nodo atual e no fim da o free da raiz
}

int calculaIndice(char letra){//Calcula o indice da letra no vetor
    return letra - 'a';
}

void imprimeArvore(NodoTrie *raiz){//percore a trie procurando nodos terminais imprimindo os conteudos quando achar
    for(int i = 0; i < 26; i++){
        if(raiz->filhos[i] != NULL)
            imprimeArvore(raiz->filhos[i]);
    }
    if(raiz->pessoa != NULL)
        printf("(%s|%s|%d)\n", raiz->pessoa->id, raiz->pessoa->nome, raiz->pessoa->idade);
}

void removeNodo(NodoTrie *raiz, char *palavra, int tamanho){
    NodoTrie *aux;
    int indice;
    raiz->pessoa = NULL;// desmarca 

    while(!raiz->pessoa && raiz->pai){ //enquanto nao for um nodo terminal e o pai nao for NULL
        if(temFilhos(raiz))//se o nodo tiver filhos nao precisa fazer nada
            break;

        aux = raiz->pai;

        indice = calculaIndice(palavra[tamanho - 1]);

        raiz->pai->filhos[indice] = NULL;//acessamos o pai e mudamos o endereço do vetor pra Null pois nao tem mais o nodo filho
        tamanho--;//como estamos voltando do terminal pro inicio e precisamos atualizar os ponteiros vamos usando a palavra pra saber a letra q estamos e calcular o indice q ele esta no pai

        free(raiz);
        raiz = aux;
    }
}

void retiraEspaco(char *nome){//retira o espaço do fim do nome
    int tam = strlen(nome);
    nome[tam - 1] = '\0';
}

int contaNodosTerminais(NodoTrie *raiz){//Conta todos os nodos teminais
    int tam = 0;

    if(raiz->pessoa != NULL) 
        tam++;

    for(int i = 0; i < 26; i++) 
        if(raiz->filhos[i] != NULL) 
            tam += contaNodosTerminais(raiz->filhos[i]);

    return tam;
}

void carregaArq(NodoTrie *raiz){//Abre o arquivo e carrega eles pra trie
    int Ncadastros;
    FILE *arquivo = fopen("banco.txt", "r");
    
    fscanf(arquivo, "%d", &Ncadastros);

    for(int i = 0; i < Ncadastros; i++){    
        Conteudo *cadastro = criaConteudo();

        fscanf(arquivo," %s %[^0-9] %d", cadastro->id, cadastro->nome, &cadastro->idade);   
        retiraEspaco(cadastro->nome);

        insere(raiz, cadastro->id, cadastro);
    }

    fclose(arquivo);
} 

