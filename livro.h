#ifndef LIVRO_H
#define LIVRO_H
#include <stdio.h>
#include <string.h>

typedef struct Livro Livro;
typedef struct Celula Celula;
typedef struct Lista_livro Lista_livro;

// Funcionalidades da lista de livros
Lista_livro* criar_lista_livro();
void inserir_livro(Lista_livro* lista, Livro* livro);
void imprimir_lista_livro(Lista_livro* lista_livro);
Livro* buscar_livro_por_id(Lista_livro* lista, int id);
int livro_ja_existe_na_lista(Lista_livro* lista, Livro* livro);
void remover_livro_da_lista(Lista_livro* lista, Livro* livro);

// Funcionalidades de livros
char* obter_titulo_livro(Livro* livro);
void imprime_livro(Livro* livro);
Livro* inicializar_livro(int identificador, char titulo[], char autor[], char genero[], int ano);

#endif