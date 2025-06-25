#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leitor.h"

#define TAMANHO_MAXIMO 100
#define MAX_AFINIDADES 10

struct Leitor {
    int indentificador;
    char nome[TAMANHO_MAXIMO];
    int n_afinidades;
    char afinidades[MAX_AFINIDADES][TAMANHO_MAXIMO];
    Lista_livro* livros_lidos; // Lista de livros lidos pelo leitor
    Lista_livro* livros_desejados; // Lista de livros desejados pelo leitor
    Lista_livro* livros_recomendados; // Lista de livros recomendados para o leitor
    Lista_leitores* lista_afinidades_com_leitores;
};

struct Celula {
    Leitor* leitor; // Ponteiro para o leitor
    Celula* proximo; // Ponteiro para a próxima célula
};

struct Lista_leitores{

    Celula* primeiro; // Ponteiro para a primeira célula
    Celula* ultimo; // Ponteiro para a última célula
    int tamanho; // Tamanho da lista de leitores
};

Lista_leitores* criar_lista_leitores(){

    Lista_leitores* nova_lista = (Lista_leitores*)malloc(sizeof(Lista_leitores)); // Alocar memória para a lista de leitores
    nova_lista->primeiro = NULL; // Inicializar o ponteiro para a primeira célula como NULL
    nova_lista->ultimo = NULL; // Inicializar o ponteiro para a última célula como NULL
    nova_lista->tamanho = 0; // Inicializar o tamanho da lista como 0
    return nova_lista; // Retornar o ponteiro para a nova lista de leitores
}           

void inserir_leitor(Lista_leitores* lista, Leitor* leitor){

    Celula* nova_celula = (Celula*)malloc(sizeof(Celula));
    
    if(lista->primeiro==NULL || lista->ultimo==NULL){ //lista vazia, primeira celula
        lista->primeiro = nova_celula;
        lista->ultimo = nova_celula;
    }else{
        lista->ultimo->proximo = nova_celula;
        lista->ultimo = lista->ultimo->proximo;
    }

    nova_celula->leitor = leitor;
    nova_celula->proximo = NULL;
}


Leitor* inicializa_leitor(int indentificador, char nome[TAMANHO_MAXIMO], int n_afinidades, char afinidades[][TAMANHO_MAXIMO]){

    // Alocar memória para o novo leitor
    Leitor* novo_leitor = (Leitor*)malloc(sizeof(Leitor));
    
    if (novo_leitor == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o leitor.\n");
        return NULL;
    }
    //Alocacao completa

    //Atribuir os atributos do leitor
    novo_leitor->indentificador = indentificador; // Atribuir o identificador
    
    strcpy(novo_leitor->nome, nome); // Atribuir o nome do leitor
    
    novo_leitor->n_afinidades = n_afinidades; // Atribuir o número de afinidades
    
    for(int i = 0; i < n_afinidades && i < MAX_AFINIDADES; i++) { // Atribuir as afinidades
        strcpy(novo_leitor->afinidades[i], afinidades[i]);
    }
    // Atribuição completa

    novo_leitor->livros_lidos = criar_lista_livro(); // Inicializar lista de livros lidos
    novo_leitor->livros_desejados = criar_lista_livro(); // Inicializar lista de livros desejados
    novo_leitor->livros_recomendados = criar_lista_livro(); // Inicializar lista de livros recomendados
    novo_leitor->lista_afinidades_com_leitores = criar_lista_leitores(); // Inicializar lista de afinidades

    return novo_leitor; // Retornar o ponteiro para o novo leitor

}

int tem_afinidade_genero(Leitor* leitor1, Leitor* leitor2) {
    if (leitor1 == NULL || leitor2 == NULL) return 0;
    if (leitor1->indentificador == leitor2->indentificador) return 0; // Mesmo leitor
    
    // Verificar se há gêneros em comum
    for (int i = 0; i < leitor1->n_afinidades; i++) {
        for (int j = 0; j < leitor2->n_afinidades; j++) {
            if (strcmp(leitor1->afinidades[i], leitor2->afinidades[j]) == 0) {
                return 1; // Encontrou afinidade
            }
        }
    }
    return 0; // Não há afinidade
}

void calcular_afinidades_leitor(Leitor* leitor, Lista_leitores* lista_todos_leitores) {
    if (leitor == NULL || lista_todos_leitores == NULL) return;
    
    Celula* aux = lista_todos_leitores->primeiro;
    while (aux != NULL) {
        if (tem_afinidade_genero(leitor, aux->leitor)) {
            // Verificar se já não está na lista de afinidades
            Celula* aux_afinidade = leitor->lista_afinidades_com_leitores->primeiro;
            int ja_existe = 0;
            while (aux_afinidade != NULL) {
                if (aux_afinidade->leitor->indentificador == aux->leitor->indentificador) {
                    ja_existe = 1;
                    break;
                }
                aux_afinidade = aux_afinidade->proximo;
            }
            
            if (!ja_existe) {
                inserir_leitor(leitor->lista_afinidades_com_leitores, aux->leitor);
            }
        }
        aux = aux->proximo;
    }
}

void construir_rede_afinidades(Lista_leitores* lista_leitores) {
    if (lista_leitores == NULL) return;
    
    printf("=== CONSTRUINDO REDE DE AFINIDADES ===\n");
    
    Celula* aux = lista_leitores->primeiro;
    while (aux != NULL) {
        calcular_afinidades_leitor(aux->leitor, lista_leitores);
        aux = aux->proximo;
    }
    
    // Imprimir afinidades encontradas
    aux = lista_leitores->primeiro;
    while (aux != NULL) {
        imprimir_afinidades_leitor(aux->leitor);
        aux = aux->proximo;
    }
}

void imprimir_afinidades_leitor(Leitor* leitor) {
    if (leitor == NULL) return;
    
    printf("Afinidades de %s: ", leitor->nome);
    
    if (leitor->lista_afinidades_com_leitores->primeiro == NULL) {
        printf("Nenhuma afinidade encontrada.\n");
        return;
    }
    
    Celula* aux = leitor->lista_afinidades_com_leitores->primeiro;
    int primeiro = 1;
    while (aux != NULL) {
        if (!primeiro) printf(", ");
        printf("%s", aux->leitor->nome);
        primeiro = 0;
        aux = aux->proximo;
    }
    printf("\n");
}

void imprime_leitor(Leitor* leitor) {
    if (leitor == NULL) return;
    printf("ID: %d\n", leitor->indentificador);
    printf("Nome: %s\n", leitor->nome);
    printf("Afinidades (%d): ", leitor->n_afinidades);
    for (int i = 0; i < leitor->n_afinidades; i++) {
        printf("%s", leitor->afinidades[i]);
        if (i < leitor->n_afinidades - 1) printf(", ");
    }
    printf("\n");
    printf("Leitores com afinidades: ");
    if (leitor->lista_afinidades_com_leitores->primeiro == NULL) {
        printf("Nenhum");
    } else {
        Celula* aux = leitor->lista_afinidades_com_leitores->primeiro;
        int primeiro = 1;
        while (aux != NULL) {
            if (!primeiro) printf(", ");
            printf("%s", aux->leitor->nome);
            primeiro = 0;
            aux = aux->proximo;
        }
    }
    printf("\n");
    printf("Livros lidos:\n");
    imprimir_livros_lidos(leitor);
    printf("Livros desejados:\n");
    imprimir_livros_desejados(leitor);
    printf("Livros recomendados:\n");
    imprimir_livros_recomendados(leitor);
    printf("---\n");
}

void libera_lista_leitores(Lista_leitores* lista){

    Celula* aux = lista->primeiro;

    while (aux != NULL){
        Celula* temp = aux;
        aux = aux->proximo;
        free(temp);
    }

}

void adicionar_livro_lido(Leitor* leitor, Livro* livro) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Leitor ou livro inválido.\n");
        return;
    }
    
    inserir_livro(leitor->livros_lidos, livro);
    printf("Livro adicionado à lista de lidos do leitor %s.\n", leitor->nome);
}

void imprimir_livros_lidos(Leitor* leitor) {
    if (leitor == NULL || leitor->livros_lidos == NULL) {
        printf("Nenhum livro lido.\n");
        return;
    }
    
    imprimir_lista_livro(leitor->livros_lidos);
}

void adicionar_livro_desejado(Leitor* leitor, Livro* livro) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Leitor ou livro inválido.\n");
        return;
    }
    
    inserir_livro(leitor->livros_desejados, livro);
    printf("Livro adicionado à lista de desejados do leitor %s.\n", leitor->nome);
}

void imprimir_livros_desejados(Leitor* leitor) {
    if (leitor == NULL || leitor->livros_desejados == NULL) {
        printf("Nenhum livro desejado.\n");
        return;
    }
    
    imprimir_lista_livro(leitor->livros_desejados);
}

Leitor* buscar_leitor_por_id(Lista_leitores* lista, int id) {
    if (lista == NULL) return NULL;
    
    Celula* aux = lista->primeiro;
    while (aux != NULL) {
        if (aux->leitor->indentificador == id) {
            return aux->leitor;
        }
        aux = aux->proximo;
    }
    return NULL;
}

void imprimir_lista_leitores(Lista_leitores* lista){
    Celula* aux;
    aux = lista->primeiro;
    while (aux!=NULL){
        imprime_leitor(aux->leitor);
        aux = aux->proximo;
    }
}

char* obter_nome_leitor(Leitor* leitor) {
    if (leitor == NULL) return NULL;
    return leitor->nome;
}

void recomendar_livro(Leitor* leitor_origem, Livro* livro, Leitor* leitor_destino) {
    if (leitor_origem == NULL || livro == NULL || leitor_destino == NULL) {
        printf("Erro: Parâmetros inválidos para recomendação.\n");
        return;
    }
    
    // Verificar se o livro já está na lista de recomendados usando função do livro.c
    if (!livro_ja_existe_na_lista(leitor_destino->livros_recomendados, livro)) {
        inserir_livro(leitor_destino->livros_recomendados, livro);
    }
    
    printf("%s recomendou \"%s\" para %s.\n", 
           leitor_origem->nome, obter_titulo_livro(livro), leitor_destino->nome);
}

void imprimir_livros_recomendados(Leitor* leitor) {
    if (leitor == NULL || leitor->livros_recomendados == NULL) {
        printf("Nenhum livro recomendado.\n");
        return;
    }
    
    imprimir_lista_livro(leitor->livros_recomendados);
}

void aceitar_recomendacao(Leitor* leitor, Livro* livro) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    
    // Verificar se o livro está na lista de recomendados usando função do livro.c
    if (!livro_ja_existe_na_lista(leitor->livros_recomendados, livro)) {
        printf("Erro: Livro não está na lista de recomendados.\n");
        return;
    }
    
    // Se o livro não está na lista de desejados, adicionar usando função do livro.c
    if (!livro_ja_existe_na_lista(leitor->livros_desejados, livro)) {
        inserir_livro(leitor->livros_desejados, livro);
    }
    
    // Remover da lista de recomendados usando função do livro.c
    remover_livro_da_lista(leitor->livros_recomendados, livro);
    
    printf("%s aceitou a recomendação de \"%s\".\n", leitor->nome, obter_titulo_livro(livro));
}

void remover_recomendacao(Leitor* leitor, Livro* livro) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    
    // Verificar se o livro está na lista de recomendados usando função do livro.c
    if (!livro_ja_existe_na_lista(leitor->livros_recomendados, livro)) {
        printf("Erro: Livro não está na lista de recomendados.\n");
        return;
    }
    
    // Remover da lista de recomendados usando função do livro.c
    remover_livro_da_lista(leitor->livros_recomendados, livro);
    
    printf("Recomendação de \"%s\" foi removida da lista de %s.\n", obter_titulo_livro(livro), leitor->nome);
}

void descobrir_livros_em_comum_leitores(Leitor* leitor1, Leitor* leitor2) {
    if (leitor1 == NULL || leitor2 == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    
    descobrir_livros_em_comum(leitor1->livros_lidos, leitor2->livros_lidos, leitor1->nome, leitor2->nome);
}

void descobrir_livros_em_comum_leitores_para_saida(Leitor* leitor1, Leitor* leitor2, char* resultado) {
    if (leitor1 == NULL || leitor2 == NULL || resultado == NULL) {
        strcpy(resultado, "Erro: Parâmetros inválidos");
        return;
    }
    
    descobrir_livros_em_comum_para_saida(leitor1->livros_lidos, leitor2->livros_lidos, leitor1->nome, leitor2->nome, resultado);
}

// Funcoes de acesso para dados opacos (comando 8)
Lista_livro* obter_livros_lidos(Leitor* leitor) {
    if (leitor == NULL) return NULL;
    return leitor->livros_lidos;
}

Lista_livro* obter_livros_desejados(Leitor* leitor) {
    if (leitor == NULL) return NULL;
    return leitor->livros_desejados;
}

Lista_livro* obter_livros_recomendados(Leitor* leitor) {
    if (leitor == NULL) return NULL;
    return leitor->livros_recomendados;
}

Lista_leitores* obter_afinidades_leitor(Leitor* leitor) {
    if (leitor == NULL) return NULL;
    return leitor->lista_afinidades_com_leitores;
}

int obter_id_leitor(Leitor* leitor) {
    if (leitor == NULL) return -1;
    return leitor->indentificador;
}