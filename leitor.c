#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leitor.h"

#define TAMANHO_MAXIMO 100
#define MAX_AFINIDADES 10

struct Leitor {
    int indentificador;
    char nome[TAMANHO_MAXIMO];
    int n_afinidades;
    char afinidades[MAX_AFINIDADES][TAMANHO_MAXIMO];
};

struct Celula {
    Leitor* leitor; // Ponteiro para o leitor
    Celula* proximo; // Ponteiro para a próxima célula
};

struct Lista_leitores{

    Celula* primeiro; // Ponteiro para a primeira célula
    Celula* ultimo; // Ponteiro para a última célula
    int tamanho; // Tamanho da lista de leitores
};

Lista_leitores* criar_lista_leitores(){

    Lista_leitores* nova_lista = (Lista_leitores*)malloc(sizeof(Lista_leitores)); // Alocar memória para a lista de leitores
    nova_lista->primeiro = NULL; // Inicializar o ponteiro para a primeira célula como NULL
    nova_lista->ultimo = NULL; // Inicializar o ponteiro para a última célula como NULL
    nova_lista->tamanho = 0; // Inicializar o tamanho da lista como 0
    return nova_lista; // Retornar o ponteiro para a nova lista de leitores
}           

void inserir_leitor(Lista_leitores* lista, Leitor* leitor){

    Celula* nova_celula = (Celula*)malloc(sizeof(Celula));
    
    if(lista->primeiro==NULL || lista->ultimo==NULL){ //lista vazia, primeira celula
        lista->primeiro = nova_celula;
        lista->ultimo = nova_celula;
    }else{
        lista->ultimo->proximo = nova_celula;
        lista->ultimo = lista->ultimo->proximo;
    }

    nova_celula->leitor = leitor;
    nova_celula->proximo = NULL;
}


Leitor* inicializa_leitor(int indentificador, char nome[TAMANHO_MAXIMO], int n_afinidades, char afinidades[][TAMANHO_MAXIMO]){

    // Alocar memória para o novo leitor
    Leitor* novo_leitor = (Leitor*)malloc(sizeof(Leitor));
    
    if (novo_leitor == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o leitor.\n");
        return NULL;
    }
    //Alocacao completa

    //Atribuir os atributos do leitor
    novo_leitor->indentificador = indentificador; // Atribuir o identificador
    
    strcpy(novo_leitor->nome, nome); // Atribuir o nome do leitor
    
    novo_leitor->n_afinidades = n_afinidades; // Atribuir o número de afinidades
    
    for(int i = 0; i < n_afinidades && i < MAX_AFINIDADES; i++) { // Atribuir as afinidades
        strcpy(novo_leitor->afinidades[i], afinidades[i]);
    }
    // Atribuição completa

    return novo_leitor; // Retornar o ponteiro para o novo leitor

}

void imprime_leitor(Leitor* leitor) {
    if (leitor == NULL) return;
    printf("ID: %d\n", leitor->indentificador);
    printf("Nome: %s\n", leitor->nome);
    printf("Afinidades (%d): ", leitor->n_afinidades);
    for (int i = 0; i < leitor->n_afinidades; i++) {
        printf("%s", leitor->afinidades[i]);
        if (i < leitor->n_afinidades - 1) printf(", ");
    }
    printf("\n");
}

void imprimir_lista_leitores(Lista_leitores* lista){
    Celula* aux;
    aux = lista->primeiro;
    while (aux!=NULL){
        imprime_leitor(aux->leitor);
        aux = aux->proximo;
    }
}

void libera_lista_leitores(Lista_leitores* lista){

    Celula* aux = lista->primeiro;

    while (aux != NULL){
        Celula* temp = aux;
        aux = aux->proximo;
        free(temp);
    }

}

