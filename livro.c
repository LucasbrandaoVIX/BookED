#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "livro.h"

#define TAMANHO_MAXIMO 100

struct Livro{

    int identificador;
    char titulo[TAMANHO_MAXIMO];
    char autor[TAMANHO_MAXIMO];
    char genero[TAMANHO_MAXIMO];
    int ano;
};

struct Celula{
    Livro* livro;
    Celula* proximo;
};

struct Lista_livro{
    Celula* primeiro;
    Celula* ultimo;
};

Livro* inicializar_livro(int identificador, char titulo[], char autor[], char genero[], int ano){

    Livro* novo_livro = (Livro*)malloc(sizeof(Livro));

    novo_livro->identificador = identificador;
    strcpy(novo_livro->titulo, titulo);
    strcpy(novo_livro->autor, autor);
    strcpy(novo_livro->genero, genero);
    novo_livro->ano = ano;
    
    return novo_livro;
}

Lista_livro* criar_lista_livro(){

    Lista_livro* nova_lista = (Lista_livro*)malloc(sizeof(Lista_livro));
    nova_lista->primeiro = nova_lista->ultimo = NULL;
    return nova_lista;

}

void inserir_livro(Lista_livro* lista, Livro* livro){

    Celula* nova_celula = (Celula*)malloc(sizeof(Celula));
    
    if (lista->primeiro == NULL || lista->ultimo ==NULL){
        lista->primeiro = lista->ultimo = nova_celula;
    }else{
        lista->ultimo->proximo = nova_celula;
        lista->ultimo = nova_celula;
    }
    
    nova_celula->proximo = NULL;
    nova_celula->livro = livro;
 
}

void imprime_livro(Livro* livro) {
    if (livro == NULL) return;
    printf("ID: %d\n", livro->identificador);
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Gênero: %s\n", livro->genero);
    printf("Ano: %d\n\n", livro->ano);
}

void imprimir_lista_livro(Lista_livro* lista_livro){
    Celula* aux = lista_livro->primeiro;
    while (aux != NULL) {
        imprime_livro(aux->livro);
        aux = aux->proximo;
    }
}

Livro* buscar_livro_por_id(Lista_livro* lista, int id) {
    if (lista == NULL) return NULL;
    
    Celula* aux = lista->primeiro;
    while (aux != NULL) {
        if (aux->livro->identificador == id) {
            return aux->livro;
        }
        aux = aux->proximo;
    }
    return NULL;
}

char* obter_titulo_livro(Livro* livro) {
    if (livro == NULL) return NULL;
    return livro->titulo;
}

int livro_ja_existe_na_lista(Lista_livro* lista, Livro* livro) {
    if (lista == NULL || livro == NULL) return 0;
    
    Celula* aux = lista->primeiro;
    while (aux != NULL) {
        if (aux->livro->identificador == livro->identificador) {
            return 1; // Livro encontrado
        }
        aux = aux->proximo;
    }
    return 0; // Livro não encontrado
}

void remover_livro_da_lista(Lista_livro* lista, Livro* livro) {
    if (lista == NULL || livro == NULL) return;
    
    Celula* aux = lista->primeiro;
    Celula* anterior = NULL;
    
    while (aux != NULL) {
        if (aux->livro->identificador == livro->identificador) {
            // Remover o nó
            if (anterior == NULL) {
                // Primeiro nó
                lista->primeiro = aux->proximo;
                if (lista->ultimo == aux) {
                    lista->ultimo = NULL;
                }
            } else {
                anterior->proximo = aux->proximo;
                if (lista->ultimo == aux) {
                    lista->ultimo = anterior;
                }
            }
            free(aux);
            return;
        }
        anterior = aux;
        aux = aux->proximo;
    }
}


