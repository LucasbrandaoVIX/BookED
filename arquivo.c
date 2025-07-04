/*
 * Autor: Lucas Dantas Brandao
 * 
 * arquivo.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arquivo.h"
#include "leitor.h"
#include "livro.h"

#define TAMANHO_MAXIMO 100
#define MAX_AFINIDADES 10

// Global file pointer for output
FILE* arquivo_saida = NULL;

void abrir_arquivo_saida() {
    arquivo_saida = fopen("saida.txt", "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao abrir arquivo saida.txt para escrita.\n");
    }
}

void fechar_arquivo_saida() {
    if (arquivo_saida != NULL) {
        fclose(arquivo_saida);
    }
}

void escrever_saida(const char* mensagem) {
    if (arquivo_saida != NULL) {
        fprintf(arquivo_saida, "%s\n", mensagem);
        fflush(arquivo_saida); // Força a escrita imediata
    }
}

void registrar_leitores_from_txt(Lista_leitores* lista) {
    FILE* arq_leitores;
    arq_leitores = fopen("leitores.txt", "r");
    if (arq_leitores == NULL) {
        printf("Error opening leitores.txt file\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arq_leitores); // Pular o cabeçalho

    while (fgets(linha, sizeof(linha), arq_leitores)) {
        int id, n_afinidades;
        char nome[TAMANHO_MAXIMO];
        char afinidades[MAX_AFINIDADES][TAMANHO_MAXIMO];

        // Remove newline character
        linha[strcspn(linha, "\n")] = 0;

        // Separar os campos usando strtok
        char* token = strtok(linha, ";");
        if (token == NULL) continue;
        id = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(nome, token, TAMANHO_MAXIMO - 1);
        nome[TAMANHO_MAXIMO - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        n_afinidades = atoi(token);

        // Afinidades
        int i = 0;
        while ((token = strtok(NULL, ";")) != NULL && i < MAX_AFINIDADES && i < n_afinidades) {
            // Remover espaços em branco do início
            while (*token == ' ') token++;
            // Remove newline at the end
            char* newline = strchr(token, '\n');
            if (newline) *newline = '\0';
            strncpy(afinidades[i], token, TAMANHO_MAXIMO - 1);
            afinidades[i][TAMANHO_MAXIMO - 1] = '\0';
            i++;
        }

        Leitor* leitor = inicializa_leitor(id, nome, n_afinidades, afinidades);
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

        // Remove newline character
        linha[strcspn(linha, "\n")] = 0;

        char* token = strtok(linha, ";");
        if (token == NULL) continue;
        id = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(titulo, token, TAMANHO_MAXIMO - 1);
        titulo[TAMANHO_MAXIMO - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(autor, token, TAMANHO_MAXIMO - 1);
        autor[TAMANHO_MAXIMO - 1] = '\0';

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        strncpy(genero, token, TAMANHO_MAXIMO - 1);
        genero[TAMANHO_MAXIMO - 1] = '\0';

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
    
    // Escrever no arquivo de saída
    char mensagem[256];
    sprintf(mensagem, "%s leu \"%s\"", obter_nome_leitor(leitor), obter_titulo_livro(livro));
    escrever_saida(mensagem);
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
    
    // Escrever no arquivo de saída
    char mensagem[256];
    sprintf(mensagem, "%s deseja ler \"%s\"", obter_nome_leitor(leitor), obter_titulo_livro(livro));
    escrever_saida(mensagem);
}

void executar_comando_recomendar_livro(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor_origem, int id_livro, int id_leitor_destino) {
    Leitor* leitor_origem = buscar_leitor_por_id(lista_leitores, id_leitor_origem);
    Livro* livro = buscar_livro_por_id(lista_livros, id_livro);
    Leitor* leitor_destino = buscar_leitor_por_id(lista_leitores, id_leitor_destino);
    
    if (leitor_origem == NULL) {
        printf("Erro: Leitor origem com ID %d não encontrado.\n", id_leitor_origem);
        return;
    }
    
    if (livro == NULL) {
        printf("Erro: Livro com ID %d não encontrado.\n", id_livro);
        return;
    }
    
    if (leitor_destino == NULL) {
        printf("Erro: Leitor destino com ID %d não encontrado.\n", id_leitor_destino);
        return;
    }
    
    recomendar_livro(leitor_origem, livro, leitor_destino);
    
    // Escrever no arquivo de saída
    char mensagem[256];
    sprintf(mensagem, "%s recomendou \"%s\" para %s", 
            obter_nome_leitor(leitor_origem), 
            obter_titulo_livro(livro), 
            obter_nome_leitor(leitor_destino));
    escrever_saida(mensagem);
}

void executar_comando_aceitar_recomendacao(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor, int id_livro) {
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
    
    aceitar_recomendacao(leitor, livro);
    
    // Escrever no arquivo de saída
    char mensagem[256];
    sprintf(mensagem, "%s aceita recomendação de \"%s\"", 
            obter_nome_leitor(leitor), 
            obter_titulo_livro(livro));
    escrever_saida(mensagem);
}

void executar_comando_remover_recomendacao(Lista_leitores* lista_leitores, Lista_livro* lista_livros, int id_leitor, int id_livro) {
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
    
    remover_recomendacao(leitor, livro);
    
    // Escrever no arquivo de saída
    char mensagem[256];
    sprintf(mensagem, "%s rejeita recomendação de \"%s\"", 
            obter_nome_leitor(leitor), 
            obter_titulo_livro(livro));
    escrever_saida(mensagem);
}

void executar_comando_descobrir_livros_em_comum(Lista_leitores* lista_leitores, int id_leitor1, int id_leitor2) {
    Leitor* leitor1 = buscar_leitor_por_id(lista_leitores, id_leitor1);
    Leitor* leitor2 = buscar_leitor_por_id(lista_leitores, id_leitor2);
    
    if (leitor1 == NULL) {
        printf("Erro: Leitor com ID %d não encontrado.\n", id_leitor1);
        return;
    }
    
    if (leitor2 == NULL) {
        printf("Erro: Leitor com ID %d não encontrado.\n", id_leitor2);
        return;
    }
    
    // Exibir no console
    descobrir_livros_em_comum_leitores(leitor1, leitor2);
    
    // Escrever no arquivo de saída
    char resultado[512];
    descobrir_livros_em_comum_leitores_para_saida(leitor1, leitor2, resultado);
    escrever_saida(resultado);
}

void executar_comando_verificar_afinidade(Lista_leitores* lista_leitores, int id_leitor_origem, int id_leitor_destino) {
    Leitor* leitor_origem = buscar_leitor_por_id(lista_leitores, id_leitor_origem);
    Leitor* leitor_destino = buscar_leitor_por_id(lista_leitores, id_leitor_destino);
    
    if (leitor_origem == NULL) {
        printf("Erro: Leitor origem com ID %d não encontrado.\n", id_leitor_origem);
        return;
    }
    
    if (leitor_destino == NULL) {
        printf("Erro: Leitor destino com ID %d não encontrado.\n", id_leitor_destino);
        return;
    }
    
    int tem_afinidade = tem_afinidade_genero(leitor_origem, leitor_destino, lista_leitores);
    
    // Exibir no console
    if (tem_afinidade) {
        printf("%s e %s têm afinidades em comum.\n", 
               obter_nome_leitor(leitor_origem), 
               obter_nome_leitor(leitor_destino));
    } else {
        printf("%s e %s não têm afinidades em comum.\n", 
               obter_nome_leitor(leitor_origem), 
               obter_nome_leitor(leitor_destino));
    }
    
    // Escrever no arquivo de saída
    char mensagem[256];
    if (tem_afinidade) {
        sprintf(mensagem, "Existe afinidade entre %s e %s", 
                obter_nome_leitor(leitor_origem), 
                obter_nome_leitor(leitor_destino));
    } else {
        sprintf(mensagem, "%s e %s não têm afinidades em comum", 
                obter_nome_leitor(leitor_origem), 
                obter_nome_leitor(leitor_destino));
    }
    escrever_saida(mensagem);
}

void executar_comando_imprimir_booked(Lista_leitores* lista_leitores) {
    if (lista_leitores == NULL) {
        printf("Erro: Lista de leitores inválida.\n");
        return;
    }
    
    printf("Imprimindo toda a BookED...\n");
    
    // Escrever cabeçalho no arquivo de saída
    escrever_saida("Imprime toda a BookED\n");
    
    // Percorrer todos os leitores
    Lista_leitores* aux_lista = lista_leitores;
    Leitor* aux_leitor = NULL;
    
    // Precisamos acessar a estrutura interna da lista de leitores
    // Como é opaca, vamos iterar através dos leitores usando busca por ID
    for (int id = 1; id <= 10; id++) { // Assumindo IDs de 1 a 10
        aux_leitor = buscar_leitor_por_id(lista_leitores, id);
        if (aux_leitor == NULL) continue;
        
        char linha_leitor[512];
        sprintf(linha_leitor, "Leitor: %s", obter_nome_leitor(aux_leitor));
        escrever_saida(linha_leitor);
        
        // Livros lidos
        char lidos[512];
        formatar_lista_livros_como_string(obter_livros_lidos(aux_leitor), lidos, sizeof(lidos));
        char linha_lidos[1024];
        sprintf(linha_lidos, "Lidos: %s", strlen(lidos) > 0 ? lidos : "");
        escrever_saida(linha_lidos);
        
        // Livros desejados
        char desejados[512];
        formatar_lista_livros_como_string(obter_livros_desejados(aux_leitor), desejados, sizeof(desejados));
        char linha_desejados[1024];
        sprintf(linha_desejados, "Desejados: %s", strlen(desejados) > 0 ? desejados : "");
        escrever_saida(linha_desejados);
        
        // Livros recomendados
        char recomendados[512];
        formatar_lista_livros_como_string(obter_livros_recomendados(aux_leitor), recomendados, sizeof(recomendados));
        char linha_recomendados[1024];
        sprintf(linha_recomendados, "Recomendacoes: %s", strlen(recomendados) > 0 ? recomendados : "");
        escrever_saida(linha_recomendados);
        
        // Afinidades
        char afinidades[512] = "";
        Lista_leitores* lista_afinidades = obter_afinidades_leitor(aux_leitor);
        if (lista_afinidades != NULL) {
            int primeiro = 1;
            // Iterar através dos leitores com afinidade
            for (int aff_id = 1; aff_id <= 10; aff_id++) {
                Leitor* leitor_afinidade = buscar_leitor_por_id(lista_afinidades, aff_id);
                if (leitor_afinidade != NULL) {
                    if (!primeiro) {
                        strcat(afinidades, ", ");
                    }
                    strcat(afinidades, obter_nome_leitor(leitor_afinidade));
                    primeiro = 0;
                }
            }
        }
        
        char linha_afinidades[1024];
        sprintf(linha_afinidades, "Afinidades: %s", strlen(afinidades) > 0 ? afinidades : "");
        escrever_saida(linha_afinidades);
        
        // Linha em branco entre leitores
        escrever_saida("");
    }
}

void processar_comandos(Lista_leitores* lista_leitores, Lista_livro* lista_livros) {
    // Construir rede de afinidades antes de processar comandos
    construir_rede_afinidades(lista_leitores);
    
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
        
        // Skip empty lines
        if (strlen(linha) == 0) continue;
        
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
            case 3: { // Recomendar Livro
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor_origem = atoi(token);
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_livro = atoi(token);
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor_destino = atoi(token);
                
                // Execute command
                executar_comando_recomendar_livro(lista_leitores, lista_livros, id_leitor_origem, id_livro, id_leitor_destino);
                break;
            }
            case 4: { // Aceitar Recomendação
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor = atoi(token);
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_livro = atoi(token);
                
                // Execute command
                executar_comando_aceitar_recomendacao(lista_leitores, lista_livros, id_leitor, id_livro);
                break;
            }
            case 5: { // Remover Recomendação
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor = atoi(token);
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_livro = atoi(token);
                
                // Execute command
                executar_comando_remover_recomendacao(lista_leitores, lista_livros, id_leitor, id_livro);
                break;
            }
            case 6: { // Descobrir Livros em Comum
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor1 = atoi(token);
                
                token = strtok(NULL, ";"); // Skip param2 (not used)
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor2 = atoi(token);
                
                // Execute command
                executar_comando_descobrir_livros_em_comum(lista_leitores, id_leitor1, id_leitor2);
                break;
            }
            case 7: { // Verificar Afinidade
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor_origem = atoi(token);
                
                token = strtok(NULL, ";"); // Skip param2 (not used)
                
                token = strtok(NULL, ";");
                if (token == NULL) continue;
                int id_leitor_destino = atoi(token);
                
                // Execute command
                executar_comando_verificar_afinidade(lista_leitores, id_leitor_origem, id_leitor_destino);
                break;
            }
            case 8: { // Imprimir toda a BookED
                executar_comando_imprimir_booked(lista_leitores);
                break;
            }
            default:
                printf("Comando %d não implementado ainda.\n", comando);
                break;
        }
    }

    fclose(arq_comandos);
}
