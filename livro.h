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
Livro* buscar_livro_por_id(Lista_livro* lista, int id);
int livro_ja_existe_na_lista(Lista_livro* lista, Livro* livro);
void remover_livro_da_lista(Lista_livro* lista, Livro* livro);
void descobrir_livros_em_comum(Lista_livro* lista_lidos1, Lista_livro* lista_lidos2, char* nome1, char* nome2);
void descobrir_livros_em_comum_para_saida(Lista_livro* lista_lidos1, Lista_livro* lista_lidos2, char* nome1, char* nome2, char* resultado);

// Funcionalidades de livros
char* obter_titulo_livro(Livro* livro);
Livro* inicializar_livro(int identificador, char titulo[], char autor[], char genero[], int ano);

// Funcoes para formatar listas como string (comando 8)
void formatar_lista_livros_como_string(Lista_livro* lista, char* resultado, int tamanho_max);

#endif