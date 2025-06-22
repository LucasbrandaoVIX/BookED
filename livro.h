#ifndef LIVRO_H
#define LIVRO_H
#include <stdio.h>
#include <string.h>

typedef struct Livro Livro;
typedef struct Celula Celula;
typedef struct Lista_livro Lista_livro;

Lista_livro* criar_lista_livro();
Livro* inicializar_livro(int identificador, char titulo[], char autor[], char genero[], int ano);
void inserir_livro(Lista_livro* lista, Livro* livro);
void imprimir_lista_livro(Lista_livro* lista_livro);
void imprime_livro(Livro* livro);
Livro* buscar_livro_por_id(Lista_livro* lista, int id);

#endif