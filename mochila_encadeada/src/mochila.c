#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mochila.h" // Inclui as definições e protótipos
#include "utils.h"   // Inclui o 'limparBuffer'

/**
 * Função privada (static) para preencher os dados de um item.
 */
static void definirItem(struct Item *item) {
    printf("Nome do Item: ");
    fgets(item->nome, sizeof(item->nome), stdin);
    item->nome[strcspn(item->nome, "\n")] = 0;

    printf("Tipo do Item: ");
    fgets(item->tipo, sizeof(item->tipo), stdin);
    item->tipo[strcspn(item->tipo, "\n")] = 0;

    printf("Quantidade do Item: ");
    scanf("%d", &item->quantidade);
    limparBuffer();
}

/**
 * Insere um item na lista encadeada.
 */
void inserirItem(struct No **p_mochila, int *slotsUsados, int *espacoOcupado) {
    struct Item novoItem;
    definirItem(&novoItem); // Pega os dados

    // VERIFICA O PESO
    if (*espacoOcupado + novoItem.quantidade > CAPACIDADE_MAXIMA) {
        printf("Mochila sem espaco suficiente! (%d/%d)\n", *espacoOcupado, CAPACIDADE_MAXIMA);
        return;
    }

    // TENTA EMPILHAR
    struct No *atual = *p_mochila;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, novoItem.nome) == 0) {
            atual->dados.quantidade += novoItem.quantidade;
            *espacoOcupado += novoItem.quantidade;
            printf("Item '%s' empilhado!\n", novoItem.nome);
            return;
        }
        atual = atual->proximo;
    }

    // VERIFICA OS SLOTS
    if (*slotsUsados >= MAX_SLOTS) {
        printf("Mochila cheia! Nao ha espaco para novos tipos de itens.\n");
        return;
    }

    // ADICIONA NOVO NÓ (Insere no início da lista)
    struct No *novoNo = (struct No*) malloc(sizeof(struct No));
    if (novoNo == NULL) { return; } // Falha de memória

    novoNo->dados = novoItem;
    novoNo->proximo = *p_mochila;   // O novo nó aponta para a antiga cabeça
    *p_mochila = novoNo;            // A cabeça da lista agora é o novo nó

    *espacoOcupado += novoItem.quantidade;
    (*slotsUsados)++;
    printf("Item inserido com sucesso!\n");
}

/**
 * Remove um item da lista encadeada.
 */
void removerItem(struct No **p_mochila, int *slotsUsados, int *espacoOcupado) {
    char buscaNome[30];
    printf("Nome do Item a ser removido: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    struct No* atual = *p_mochila;
    struct No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, buscaNome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado na mochila.\n");
        return;
    }

    *espacoOcupado -= atual->dados.quantidade;

    if (anterior == NULL) {
        *p_mochila = atual->proximo; // Remove da cabeça
    } else {
        anterior->proximo = atual->proximo; // "Pula" o nó atual
    }
    
    free(atual); // Libera o nó removido
    (*slotsUsados)--;
    printf("Item removido com sucesso!\n");
}

/**
 * Lista todos os itens da lista encadeada.
 */
void listarItens(const struct No *mochila, int slotsUsados, int espacoOcupado) {
    printf("\n--- Conteudo da Mochila ---\n");
    printf("Espaco Ocupado: %d/%d\n", espacoOcupado, CAPACIDADE_MAXIMA);
    printf("Slots de Itens: %d/%d\n", slotsUsados, MAX_SLOTS);
    printf("------------------------------\n");

    const struct No* atual = mochila; // 'const' pois apenas lemos
    while (atual != NULL) {
        printf(" - Nome: %s (%s) | Quantidade: %d\n", 
               atual->dados.nome, 
               atual->dados.tipo, 
               atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("---------------------------\n");
}

/**
 * Busca um item na lista (busca sequencial iterativa).
 */
struct Item* buscarItem(struct No *mochila, const char* nomeBusca) {
    struct No* atual = mochila;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            return &(atual->dados); // Retorna o endereço dos dados
        }
        atual = atual->proximo;
    }
    return NULL; // Não encontrado
}

/**
 * Libera toda a memória alocada para a lista.
 */
void liberarMochila(struct No *mochila) {
    struct No* atual = mochila;
    struct No* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
}