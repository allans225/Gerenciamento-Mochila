#ifndef MOCHILA_H
#define MOCHILA_H

#include "item.h"

#define CAPACIDADE_MAXIMA 10
#define MAX_SLOTS 10

struct No {
    struct Item dados;      // Os dados do item
    struct No* proximo;     // O ponteiro para o próximo nó
};

// Passa 'struct No**' (ponteiro para ponteiro) para modificar a cabeça da lista
void inserirItem(struct No **p_mochila, int *slotsUsados, int *espacoOcupado);

// Também usa 'struct No**' para o caso de removermos o primeiro item
void removerItem(struct No **p_mochila, int *slotsUsados, int *espacoOcupado);

// 'const struct No*' (ponteiro simples) pois apenas lê a lista
void listarItens(const struct No *mochila, int slotsUsados, int espacoOcupado);

// Busca um item e retorna um ponteiro para os dados dele
struct Item* buscarItem(struct No *mochila, const char* nomeBusca);

// Libera toda a memória da lista no final
void liberarMochila(struct No *mochila);

#endif // MOCHILA_H