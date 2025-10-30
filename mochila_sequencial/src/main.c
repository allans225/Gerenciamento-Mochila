#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mochila.h" // Inclui funcoes mochila
#include "utils.h"   // Inclui o limpador buffer

#define CAPACIDADE_MAXIMA 50 // O "peso" máximo que a mochila aguenta
#define MAX_SLOTS 10         // O número de tipos de itens diferentes

int main() {
    struct Item *mochila = malloc(MAX_SLOTS * sizeof(struct Item));
    if (mochila == NULL) {
        printf("Erro fatal: Falha ao alocar memoria para a mochila.\n");
        return 1;
    }
    
    int slotsUsados = 0;    // Contador para número de slots para itens diferentes na mochila
    int espacoOcupado = 0;  // Contador para o "peso" total dos itens na mochila
    int opcao;

    printf("Sistema de Gerenciamento de Mochila (Sequencial)\n");
    do {
        printf("\n1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Busca Binaria Recursiva)\n");
        printf("5. Buscar Item (Busca Sequencial Iterativa)\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                inserirItem(mochila, &slotsUsados, &espacoOcupado, MAX_SLOTS, CAPACIDADE_MAXIMA);
                ordenarItensPorNome(mochila, slotsUsados);
                break;
            case 2:
                if (slotsUsados == 0) {
                    printf("Mochila vazia! Nao ha itens para remover.\n");
                } else {
                    removerItem(mochila, &slotsUsados, &espacoOcupado);
                }
                break;
            case 3:
                listarItens(mochila, slotsUsados, espacoOcupado, CAPACIDADE_MAXIMA);
                break;
            case 4: {
                if (slotsUsados == 0) {
                    printf("Mochila vazia! Nao ha itens para buscar.\n");
                    break;
                }
                char nomeBusca[30];
                printf("Digite o nome exato do item a buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remove o newline
                int comparacoes = 0; // Contador de comparações para buscas
                int indice = buscaBinariaRecursiva(mochila, slotsUsados, nomeBusca, &comparacoes);

                if (indice != -1) {
                    printf("--> Item ENCONTRADO!\n");
                    // Mostra os detalhes do item encontrado
                    printf("Slot %d. Nome: %s\t|\tTipo: %s\t|\tQuantidade: %d\n",
                           indice + 1, 
                           mochila[indice].nome, 
                           mochila[indice].tipo, 
                           mochila[indice].quantidade);
                } else {
                    printf("--> Item '%s' NAO encontrado. <<<\n", nomeBusca);
                }
                printf(">>> Numero de comparacoes (Binaria): %d\n", comparacoes);
                break;
            }
            case 5: {
                if (slotsUsados == 0) {
                    printf("Mochila vazia! Nao ha itens para buscar.\n");
                    break;
                }
                char nomeBuscaSeq[30];
                printf("Digite o nome exato do item a buscar: ");
                fgets(nomeBuscaSeq, sizeof(nomeBuscaSeq), stdin);
                nomeBuscaSeq[strcspn(nomeBuscaSeq, "\n")] = 0; // Remove o newline
                int comparacoes = 0; // Contador de comparações para buscas
                int indiceSeq = buscaSequencialIterativa(mochila, slotsUsados, nomeBuscaSeq, &comparacoes);

                if (indiceSeq != -1) {
                    printf("--> Item ENCONTRADO!\n");
                    // Mostra os detalhes do item encontrado
                    printf("Slot %d. Nome: %s\t|\tTipo: %s\t|\tQuantidade: %d\n",
                           indiceSeq + 1, 
                           mochila[indiceSeq].nome, 
                           mochila[indiceSeq].tipo, 
                           mochila[indiceSeq].quantidade);
                } else {
                    printf("--> Item '%s' NAO encontrado. <<<\n", nomeBuscaSeq);
                }
                printf(">>> Numero de comparacoes (Sequencial) %d\n", comparacoes);
                break;
            }
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);
    free(mochila);
    return 0;
}