#ifndef MOCHILA_H
#define MOCHILA_H

#include "item.h"

void inserirItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado, int max_slots, int capacidade_maxima);
void removerItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado);
void listarItens(const struct Item *mochila, int slotsUsados, int espacoOcupado, int capacidade_maxima);
void ordenarItensPorNome(struct Item *mochila, int slotsUsados);
void ordenarItensPorPrioridade(struct Item *mochila, int slotsUsados);
void ordenarItensPorTipo(struct Item *mochila, int slotsUsados);

/**
 * @param comparacoes Ponteiro para um int que será incrementado a cada 'strcmp'.
 * Retorna o índice do item se encontrado, ou -1 se não.
 */
int buscaBinariaRecursiva(const struct Item *mochila, int slotsUsados, const char* nomeItem, int* comparacoes);
/**
 * @param comparacoes Ponteiro para um int que será incrementado a cada 'strcmp'.
 * Retorna o índice do item se encontrado, ou -1 se não.
 */
int buscaSequencialIterativa(const struct Item *mochila, int slotsUsados, const char* nomeItem, int* comparacoes);

#endif // MOCHILA_H