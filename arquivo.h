#ifndef ARQUIVO_H
#define ARQUIVO_H
#include <stdio.h>
#include "leitor.h"
#include "livro.h"

// Funções para leitura de arquivos
void registrar_leitores_from_txt(Lista_leitores* lista);
void registrar_livros_from_txt(Lista_livro* lista);
void processar_comandos(Lista_leitores* lista_leitores, Lista_livro* lista_livros);

// Funções para arquivo de saída
void abrir_arquivo_saida();
void fechar_arquivo_saida();
void escrever_saida(const char* mensagem);

// Funções para execução de comandos
void executar_comando_adicionar_livro_lido(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor, int id_livro);
void executar_comando_adicionar_livro_desejado(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor, int id_livro);
void executar_comando_recomendar_livro(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor_origem, int id_livro, int id_leitor_destino);

#endif
