#ifndef LEITOR_H
#define LEITOR_H
#include <stdio.h>
#include <string.h>
#include "livro.h"

#define TAMANHO_MAXIMO 100
#define MAX_AFINIDADES 10

typedef struct Leitor Leitor;

typedef struct Celula Celula;

typedef struct Lista_leitores Lista_leitores; // Sentinela para a lista de leitores

Lista_leitores* criar_lista_leitores();
void inserir_leitor(Lista_leitores* lista, Leitor* leitor);
void imprimir_lista_leitores(Lista_leitores* lista);
Leitor* inicializa_leitor(int indentificador, char nome[TAMANHO_MAXIMO], int n_afinidades, char afinidades[][TAMANHO_MAXIMO]);
void imprime_leitor(Leitor* leitor);
void libera_lista_leitores(Lista_leitores*);
void adicionar_livro_lido(Leitor* leitor, Livro* livro);
void imprimir_livros_lidos(Leitor* leitor);
Leitor* buscar_leitor_por_id(Lista_leitores* lista, int id);
void adicionar_livro_desejado(Leitor* leitor, Livro* livro);
void imprimir_livros_desejados(Leitor* leitor);
#endif