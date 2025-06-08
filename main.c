#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leitor.h"

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

int main() {

    Lista_leitores* lista = criar_lista_leitores();
    
    registrar_leitores_from_txt(lista);

    imprimir_lista_leitores(lista);
    return 0;
}
