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

void executar_comando_adicionar_livro_lido(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor, int id_livro) {
    Leitor* leitor = buscar_leitor_por_id(lista_leitores, id_leitor);
    Livro* livro = buscar_livro_por_id(lista_livros, id_livro);
    
    if (leitor == NULL) {
        printf("Erro: Leitor com ID %d não encontrado.\n", id_leitor);
        return;
    }
    
    if (livro == NULL) {
        printf("Erro: Livro com ID %d não encontrado.\n", id_livro);
        return;
    }
    
    adicionar_livro_lido(leitor, livro);
}

void executar_comando_adicionar_livro_desejado(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor, int id_livro) {
    Leitor* leitor = buscar_leitor_por_id(lista_leitores, id_leitor);
    Livro* livro = buscar_livro_por_id(lista_livros, id_livro);
    
    if (leitor == NULL) {
        printf("Erro: Leitor com ID %d não encontrado.\n", id_leitor);
        return;
    }
    
    if (livro == NULL) {
        printf("Erro: Livro com ID %d não encontrado.\n", id_livro);
        return;
    }
    
    adicionar_livro_desejado(leitor, livro);
}

void processar_comandos(Lista_leitores* lista_leitores, Lista_livro* lista_livros) {
    FILE* arq_comandos;
    arq_comandos = fopen("comandos.txt", "r");
    if (arq_comandos == NULL) {
        printf("Error opening comandos.txt file\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arq_comandos); // Pular o cabeçalho

    while (fgets(linha, sizeof(linha), arq_comandos)) {
        // Remove newline character
        linha[strcspn(linha, "\n")] = 0;
        
        // Skip comment lines
        if (linha[0] == '/' && linha[1] == '/') continue;
        
        // Parse command
        char* token = strtok(linha, ";");
        if (token == NULL) continue;
        
        int comando = atoi(token);
        
        switch (comando) {
            case 1: { // Adicionar Livro Lido
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor = atoi(token);
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_livro = atoi(token);
                
                // Execute command
                executar_comando_adicionar_livro_lido(lista_leitores, lista_livros, id_leitor, id_livro);
                break;
            }
            case 2: { // Adicionar Livro Desejado
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor = atoi(token);
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_livro = atoi(token);
                
                // Execute command
                executar_comando_adicionar_livro_desejado(lista_leitores, lista_livros, id_leitor, id_livro);
                break;
            }
            default:
                printf("Comando %d não implementado ainda.\n", comando);
                break;
        }
    }

    fclose(arq_comandos);
}



int main() {

    Lista_leitores* lista_leitores = criar_lista_leitores();
    Lista_livro* lista_livros = criar_lista_livro();
    
    printf("=== CARREGANDO DADOS ===\n");
    registrar_leitores_from_txt(lista_leitores);
    registrar_livros_from_txt(lista_livros);
    
    printf("=== PROCESSANDO COMANDOS ===\n");
    processar_comandos(lista_leitores, lista_livros);
    
    printf("\n=== LISTA FINAL DE LEITORES ===\n");
    imprimir_lista_leitores(lista_leitores);
    
    libera_lista_leitores(lista_leitores);
    return 0;
}
