#include <stdio.h>
#include <stdlib.h>
#include "leitor.h"
#include "livro.h"
#include "arquivo.h"

int main() {
    Lista_leitores* lista_leitores = criar_lista_leitores();
    Lista_livro* lista_livros = criar_lista_livro();
    
    // Abrir arquivo de saída
    abrir_arquivo_saida();
    
    printf("=== CARREGANDO DADOS ===\n");
    registrar_leitores_from_txt(lista_leitores);
    registrar_livros_from_txt(lista_livros);
    
    printf("=== PROCESSANDO COMANDOS ===\n");
    processar_comandos(lista_leitores, lista_livros);
    
    printf("\n=== LISTA FINAL DE LEITORES ===\n");
    imprimir_lista_leitores(lista_leitores);
    
    // Fechar arquivo de saída
    fechar_arquivo_saida();
    
    printf("\n=== RELATÓRIO GERADO ===\n");
    printf("Arquivo saida.txt criado com sucesso!\n");
    
    libera_lista_leitores(lista_leitores);
    return 0;
}