#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leitor.h"
#include "livro.h"

#define TAMANHO_MAXIMO 100
#define MAX_AFINIDADES 10

void registrar_leitores_from_txt(Lista_leitores* lista) {
    FILE* arq_leitores;
    arq_leitores = fopen("leitores.txt", "r");
    if (arq_leitores == NULL) {
        printf("Error opening file\n");
    }

    char linha[256];
    fgets(linha, sizeof(linha), arq_leitores); // Pular o cabeçalho

    while (fgets(linha, sizeof(linha), arq_leitores)) {
        int id, n_afinidades;
        char nome[TAMANHO_MAXIMO];
        char afinidades[MAX_AFINIDADES][TAMANHO_MAXIMO];

        // Separar os campos usando strtok
        char* token = strtok(linha, ";");
        if (token == NULL) continue;
        id = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(nome, token, TAMANHO_MAXIMO);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        n_afinidades = atoi(token);

        // Afinidades
        int i = 0;
        while ((token = strtok(NULL, ";")) != NULL && i < MAX_AFINIDADES) {
            // Remover espaços em branco do início
            while (*token == ' ') token++;
            strncpy(afinidades[i], token, TAMANHO_MAXIMO);
            i++;
        }

        Leitor* leitor = inicializa_leitor(id, nome, n_afinidades, afinidades);
        //imprime_leitor(leitor);
        inserir_leitor(lista, leitor);
    }

    fclose(arq_leitores);
}

void registrar_livros_from_txt(Lista_livro* lista) {
    FILE* arq_livros;
    arq_livros = fopen("livros.txt", "r");
    if (arq_livros == NULL) {
        printf("Error opening livros.txt file\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arq_livros); // Pular o cabeçalho

    while (fgets(linha, sizeof(linha), arq_livros)) {
        int id, ano;
        char titulo[TAMANHO_MAXIMO];
        char autor[TAMANHO_MAXIMO];
        char genero[TAMANHO_MAXIMO];

        char* token = strtok(linha, ";");
        if (token == NULL) continue;
        id = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(titulo, token, TAMANHO_MAXIMO);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(autor, token, TAMANHO_MAXIMO);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(genero, token, TAMANHO_MAXIMO);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        ano = atoi(token);

        Livro* livro = inicializar_livro(id, titulo, autor, genero, ano);
        inserir_livro(lista, livro);
    }

    fclose(arq_livros);
}

int main() {

    Lista_leitores* lista_leitores = criar_lista_leitores();
    Lista_livro* lista_livros = criar_lista_livro();
    
    registrar_leitores_from_txt(lista_leitores);
    registrar_livros_from_txt(lista_livros);

    // Exemplo de uso: adicionar livro lido para um leitor
    Leitor* alice = buscar_leitor_por_id(lista_leitores, 1);
    Livro* livro_terror = buscar_livro_por_id(lista_livros, 1); // O Iluminado
    
    if (alice != NULL && livro_terror != NULL) {
        adicionar_livro_lido(alice, livro_terror);
    }

    printf("=== LISTA DE LEITORES ===\n");
    imprimir_lista_leitores(lista_leitores);
    
    libera_lista_leitores(lista_leitores);
    return 0;
}
