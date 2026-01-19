#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaD.h"
#include "Trie.h"

int main(){
    NodoTrie *raiz = criaNodo();//Cria a raiz da arvore
    NodoTrie *aux; 
    Conteudo *cadastro;
    char opcao, ids[30];

    carregaArq(raiz);//carrega os dados do txt pra Trie
   
    do{
        scanf(" %c", &opcao);

        if(opcao == '?'){
            scanf(" %s", ids);
            
            aux = busca(raiz, ids);//retorna o indereço do nodo termina da palavra se houver

            if(aux)//Se a palavra existir
                printf("(%s|%s|%d)\n", aux->pessoa->id, aux->pessoa->nome, aux->pessoa->idade);
            else
                printf("ID %s nao encontrado.\n", ids);
        }

        else if(opcao == '+'){ 
            cadastro = criaConteudo();//Cria um nodo para o cadastro

            scanf(" %s %[^0-9] %d", cadastro->id, cadastro->nome, &cadastro->idade);
            retiraEspaco(cadastro->nome);//retira o espaço que foi lido do fim do nome

            insere(raiz, cadastro->id, cadastro);//Faz a inserçao na trie
            printf("Inserido (%s|%s|%d)\n", cadastro->id, cadastro->nome, cadastro->idade);
        }

        else if(opcao == '-'){ 
            scanf(" %s", ids);
                
            aux = busca(raiz, ids);//retorna o indereço do nodo termina da palavra se houver
            

            if(aux){
                cadastro = aux->pessoa;//Salvando o conteudo pois a funçao remove nao da free no conteudo apenas no nodo

                removeNodo(aux, ids, strlen(ids));//Faz a remoçao da letras do id 
                
                printf("Removido (%s|%s|%d)\n", cadastro->id, cadastro->nome, cadastro->idade);
                free(cadastro);
            }
            else
                printf("ID %s nao encontrado.\n", ids); 
             
        }
        else if(opcao == 'P'){
            if(temFilhos(raiz))
                imprimeArvore(raiz);//imprime a toda a arvore
        }
        
        else if(opcao == 'S'){
            salvaArq(raiz);//Salva todos os cadastros no txt
            printf("banco.txt salvo.\n");
        }
    }while(opcao != 'F');

    destroiTrie(raiz);//libera toda a memoria da trie junto com a raiz
    return 0;
}