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

// Funcionalidades da lista de leitores
Lista_leitores* criar_lista_leitores();
void inserir_leitor(Lista_leitores* lista, Leitor* leitor);
void imprimir_lista_leitores(Lista_leitores* lista);
void libera_lista_leitores(Lista_leitores*);

// Funcionalidades dos leitores
Leitor* inicializa_leitor(int indentificador, char nome[TAMANHO_MAXIMO], int n_afinidades, char afinidades[][TAMANHO_MAXIMO]);
void imprime_leitor(Leitor* leitor);
char* obter_nome_leitor(Leitor* leitor);
Leitor* buscar_leitor_por_id(Lista_leitores* lista, int id);

// Funcionalidades do comando 1
void adicionar_livro_lido(Leitor* leitor, Livro* livro);
void imprimir_livros_lidos(Leitor* leitor);

// Funcionalidades do comando 2
void adicionar_livro_desejado(Leitor* leitor, Livro* livro);
void imprimir_livros_desejados(Leitor* leitor);

// Funcionalidades do comando 3
void recomendar_livro(Leitor* leitor_origem, Livro* livro, Leitor* leitor_destino);
void imprimir_livros_recomendados(Leitor* leitor);

// Funcionalidades do comando 4
void aceitar_recomendacao(Leitor* leitor, Livro* livro);

// Funcionalidades do comando 5
void remover_recomendacao(Leitor* leitor, Livro* livro);

// Funcionalidade adicional
void descobrir_livros_em_comum_leitores(Leitor* leitor1, Leitor* leitor2);
void descobrir_livros_em_comum_leitores_para_saida(Leitor* leitor1, Leitor* leitor2, char* resultado);

// Funcionalidades de afinidades entre leitores
void calcular_afinidades_leitor(Leitor* leitor, Lista_leitores* lista_todos_leitores);
void construir_rede_afinidades(Lista_leitores* lista_leitores);
int tem_afinidade_genero(Leitor* leitor1, Leitor* leitor2);
void imprimir_afinidades_leitor(Leitor* leitor);

// Funcoes de acesso para dados opacos (comando 8)
Lista_livro* obter_livros_lidos(Leitor* leitor);
Lista_livro* obter_livros_desejados(Leitor* leitor);
Lista_livro* obter_livros_recomendados(Leitor* leitor);
Lista_leitores* obter_afinidades_leitor(Leitor* leitor);
int obter_id_leitor(Leitor* leitor);

#endif