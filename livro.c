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

void descobrir_livros_em_comum(Lista_livro* lista_lidos1, Lista_livro* lista_lidos2, char* nome1, char* nome2) {
    if (lista_lidos1 == NULL || lista_lidos2 == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    
    printf("Livros em comum entre %s e %s:\n", nome1, nome2);
    
    int livros_encontrados = 0;
    
    Celula* aux1 = lista_lidos1->primeiro;
    while (aux1 != NULL) {
        if (livro_ja_existe_na_lista(lista_lidos2, aux1->livro)) {
            printf("- %s\n", obter_titulo_livro(aux1->livro));
            livros_encontrados++;
        }
        aux1 = aux1->proximo;
    }
    
    if (livros_encontrados == 0) {
        printf("Nenhum livro em comum encontrado.\n");
    } else {
        printf("Total: %d livro(s) em comum.\n", livros_encontrados);
    }
}

void descobrir_livros_em_comum_para_saida(Lista_livro* lista_lidos1, Lista_livro* lista_lidos2, char* nome1, char* nome2, char* resultado) {
    if (lista_lidos1 == NULL || lista_lidos2 == NULL || resultado == NULL) {
        strcpy(resultado, "Erro: Parâmetros inválidos");
        return;
    }
    
    char livros_comuns[512] = "";
    int livros_encontrados = 0;
    
    Celula* aux1 = lista_lidos1->primeiro;
    while (aux1 != NULL) {
        if (livro_ja_existe_na_lista(lista_lidos2, aux1->livro)) {
            if (livros_encontrados > 0) {
                strcat(livros_comuns, ", ");
            }
            strcat(livros_comuns, obter_titulo_livro(aux1->livro));
            livros_encontrados++;
        }
        aux1 = aux1->proximo;
    }
    
    if (livros_encontrados == 0) {
        sprintf(resultado, "Livros em comum entre %s e %s: Nenhum", nome1, nome2);
    } else {
        sprintf(resultado, "Livros em comum entre %s e %s: %s", nome1, nome2, livros_comuns);
    }
}

void formatar_lista_livros_como_string(Lista_livro* lista, char* resultado, int tamanho_max) {
    if (lista == NULL || resultado == NULL) {
        strcpy(resultado, "");
        return;
    }
    
    resultado[0] = '\0';
    int primeiro = 1;
    
    Celula* aux = lista->primeiro;
    while (aux != NULL) {
        if (!primeiro) {
            strncat(resultado, ", ", tamanho_max - strlen(resultado) - 1);
        }
        strncat(resultado, obter_titulo_livro(aux->livro), tamanho_max - strlen(resultado) - 1);
        primeiro = 0;
        aux = aux->proximo;
    }
    
    if (strlen(resultado) == 0) {
        strcpy(resultado, "");
    }
}


