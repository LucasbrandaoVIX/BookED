/*
 * Autor: Lucas Dantas Brandao
 * 
 * leitor.c
 */

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
    Recomendacao recomendacoes[100]; // Array para rastrear quem recomendou cada livro
    int num_recomendacoes;
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
    novo_leitor->num_recomendacoes = 0; // Inicializar contador de recomendações

    return novo_leitor; // Retornar o ponteiro para o novo leitor

}

int tem_afinidade_direta(Leitor* leitor1, Leitor* leitor2) {
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

int tem_afinidade_genero(Leitor* leitor1, Leitor* leitor2, Lista_leitores* lista_todos_leitores) {
    if (leitor1 == NULL || leitor2 == NULL || lista_todos_leitores == NULL) return 0;
    if (leitor1->indentificador == leitor2->indentificador) return 0; // Mesmo leitor
    
    // Array para marcar leitores visitados (assumindo IDs de 1 a 100)
    int visitados[101] = {0};
    
    // Fila para BFS (assumindo máximo 100 leitores)
    int fila[101];
    int inicio = 0, fim = 0;
    
    // Adicionar leitor inicial na fila
    fila[fim++] = leitor1->indentificador;
    visitados[leitor1->indentificador] = 1;
    
    // BFS para encontrar caminho até leitor2
    while (inicio < fim) {
        int id_atual = fila[inicio++];
        Leitor* leitor_atual = buscar_leitor_por_id(lista_todos_leitores, id_atual);
        
        if (leitor_atual == NULL) continue;
        
        // Verificar todos os leitores com afinidade direta
        Celula* aux = leitor_atual->lista_afinidades_com_leitores->primeiro;
        while (aux != NULL) {
            int id_vizinho = aux->leitor->indentificador;
            
            // Se chegou ao leitor destino
            if (id_vizinho == leitor2->indentificador) {
                return 1;
            }
            
            // Se não foi visitado, adicionar na fila
            if (!visitados[id_vizinho]) {
                visitados[id_vizinho] = 1;
                fila[fim++] = id_vizinho;
            }
            
            aux = aux->proximo;
        }
    }
    
    return 0; // Não encontrou caminho
}

void calcular_afinidades_leitor(Leitor* leitor, Lista_leitores* lista_todos_leitores) {
    if (leitor == NULL || lista_todos_leitores == NULL) return;
    
    Celula* aux = lista_todos_leitores->primeiro;
    while (aux != NULL) {
        if (tem_afinidade_direta(leitor, aux->leitor)) {
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
    
    /* //Imprimir afinidades encontradas
    aux = lista_leitores->primeiro;
    while (aux != NULL) {
        imprimir_afinidades_leitor(aux->leitor);
        aux = aux->proximo;
    }
    */
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

void adicionar_livro_desejado(Leitor* leitor, Livro* livro) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Leitor ou livro inválido.\n");
        return;
    }
    
    inserir_livro(leitor->livros_desejados, livro);
    printf("Livro adicionado à lista de desejados do leitor %s.\n", leitor->nome);
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

char* obter_nome_leitor(Leitor* leitor) {
    if (leitor == NULL) return NULL;
    return leitor->nome;
}

void recomendar_livro(Leitor* leitor_origem, Livro* livro, Leitor* leitor_destino) {
    if (leitor_origem == NULL || livro == NULL || leitor_destino == NULL) {
        printf("Erro: Parâmetros inválidos para recomendação.\n");
        return;
    }
    
    // Verificar se o leitor está tentando recomendar para si mesmo
    if (leitor_origem->indentificador == leitor_destino->indentificador) {
        printf("%s não pode recomendar livros para si mesmo.\n", leitor_origem->nome);
        return;
    }
    
    // Verificar se o leitor destino já leu o livro
    if (livro_ja_existe_na_lista(leitor_destino->livros_lidos, livro)) {
        printf("%s não precisa da recomendação de \"%s\" pois já leu este livro.\n", 
               leitor_destino->nome, obter_titulo_livro(livro));
        return;
    }
    
    // Verificar se o livro já está na lista de recomendados
    if (!livro_ja_existe_na_lista(leitor_destino->livros_recomendados, livro)) {
        inserir_livro(leitor_destino->livros_recomendados, livro);
        
        // Adicionar informação sobre quem recomendou
        if (leitor_destino->num_recomendacoes < 100) {
            leitor_destino->recomendacoes[leitor_destino->num_recomendacoes].livro = livro;
            leitor_destino->recomendacoes[leitor_destino->num_recomendacoes].id_recomendador = leitor_origem->indentificador;
            leitor_destino->num_recomendacoes++;
        }
    }
    
    printf("%s recomendou \"%s\" para %s.\n", 
           leitor_origem->nome, obter_titulo_livro(livro), leitor_destino->nome);
}

void aceitar_recomendacao(Leitor* leitor, Livro* livro, Lista_leitores* lista_leitores) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    
    // Verificar se o livro está na lista de recomendados
    if (!livro_ja_existe_na_lista(leitor->livros_recomendados, livro)) {
        printf("%s não possui recomendação do livro \"%s\".\n", leitor->nome, obter_titulo_livro(livro));
        return;
    }
    
    // Se o livro não está na lista de desejados, adicionar
    if (!livro_ja_existe_na_lista(leitor->livros_desejados, livro)) {
        inserir_livro(leitor->livros_desejados, livro);
    }
    
    // Remover da lista de recomendados e do array de recomendações
    remover_livro_da_lista(leitor->livros_recomendados, livro);
    
    // Remover do array de recomendações
    int id_livro = obter_id_livro(livro);
    for (int i = 0; i < leitor->num_recomendacoes; i++) {
        if (obter_id_livro(leitor->recomendacoes[i].livro) == id_livro) {
            // Mover todos os elementos seguintes uma posição para trás
            for (int j = i; j < leitor->num_recomendacoes - 1; j++) {
                leitor->recomendacoes[j] = leitor->recomendacoes[j + 1];
            }
            leitor->num_recomendacoes--;
            break;
        }
    }
    
    printf("%s aceitou a recomendação de \"%s\".\n", leitor->nome, obter_titulo_livro(livro));
}

void remover_recomendacao(Leitor* leitor, Livro* livro, Lista_leitores* lista_leitores) {
    if (leitor == NULL || livro == NULL) {
        printf("Erro: Parâmetros inválidos.\n");
        return;
    }
    
    // Verificar se o livro está na lista de recomendados
    if (!livro_ja_existe_na_lista(leitor->livros_recomendados, livro)) {
        printf("Erro: Livro não está na lista de recomendados.\n");
        return;
    }
    
    // Remover da lista de recomendados
    remover_livro_da_lista(leitor->livros_recomendados, livro);
    
    // Remover do array de recomendações
    int id_livro = obter_id_livro(livro);
    for (int i = 0; i < leitor->num_recomendacoes; i++) {
        if (obter_id_livro(leitor->recomendacoes[i].livro) == id_livro) {
            // Mover todos os elementos seguintes uma posição para trás
            for (int j = i; j < leitor->num_recomendacoes - 1; j++) {
                leitor->recomendacoes[j] = leitor->recomendacoes[j + 1];
            }
            leitor->num_recomendacoes--;
            break;
        }
    }
    
    printf("Recomendação de \"%s\" foi removida da lista de %s.\n", obter_titulo_livro(livro), leitor->nome);
}

int obter_id_recomendador(Leitor* leitor, Livro* livro) {
    if (leitor == NULL || livro == NULL) return -1;
    
    int id_livro = obter_id_livro(livro);
    for (int i = 0; i < leitor->num_recomendacoes; i++) {
        if (obter_id_livro(leitor->recomendacoes[i].livro) == id_livro) {
            return leitor->recomendacoes[i].id_recomendador;
        }
    }
    return -1; // Não encontrado
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

// ==================== FUNÇÕES DE IMPRESSÃO ====================
/*
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

void imprimir_lista_leitores(Lista_leitores* lista){
    Celula* aux;
    aux = lista->primeiro;
    while (aux!=NULL){
        imprime_leitor(aux->leitor);
        aux = aux->proximo;
    }
}

void imprimir_livros_desejados(Leitor* leitor) {
    if (leitor == NULL || leitor->livros_desejados == NULL) {
        printf("Nenhum livro desejado.\n");
        return;
    }
    
    imprimir_lista_livro(leitor->livros_desejados);
}

void imprimir_livros_recomendados(Leitor* leitor) {
    if (leitor == NULL || leitor->livros_recomendados == NULL) {
        printf("Nenhum livro recomendado.\n");
        return;
    }
    
    imprimir_lista_livro(leitor->livros_recomendados);
}

void imprimir_livros_lidos(Leitor* leitor) {
    if (leitor == NULL || leitor->livros_lidos == NULL) {
        printf("Nenhum livro lido.\n");
        return;
    }
    
    imprimir_lista_livro(leitor->livros_lidos);
}*/