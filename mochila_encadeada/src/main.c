#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mochila.h" // Inclui o motor da mochila
#include "utils.h"   // Inclui o limpador de buffer

int main() {
    // A mochila começa como uma lista vazia (NULL)
    struct No *mochila = NULL;
    
    int slotsUsados = 0;
    int espacoOcupado = 0;
    int opcao;

    printf("Sistema de Gerenciamento de Mochila (Lista Encadeada)\n");
    do {
        printf("\n1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                // Passa o ENDEREÇO da mochila (&mochila)
                inserirItem(&mochila, &slotsUsados, &espacoOcupado);
                break;
            case 2:
                if (slotsUsados == 0) {
                    printf("Mochila vazia! Nao ha itens para remover.\n");
                } else {
                    // Passa o ENDEREÇO da mochila (&mochila)
                    removerItem(&mochila, &slotsUsados, &espacoOcupado);
                }
                break;
            case 3:
                // Passa o ponteiro da mochila (mochila)
                listarItens(mochila, slotsUsados, espacoOcupado);
                break;
            case 4: {
                if (slotsUsados == 0) {
                    printf("Mochila vazia! Nao ha itens para buscar.\n");
                    break;
                }
                char nomeBusca[30];
                printf("Digite o nome exato do item a buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = 0;

                struct Item* itemEncontrado = buscarItem(mochila, nomeBusca);
                if (itemEncontrado != NULL) {
                    printf("--> Item ENCONTRADO! <<<\n");
                    printf(" - Nome: %s, Tipo: %s, Qtd: %d\n",
                           itemEncontrado->nome, itemEncontrado->tipo, itemEncontrado->quantidade);
                } else {
                    printf(">>> Item '%s' NAO encontrado. <<<\n", nomeBusca);
                }
                break;
            }
            case 5:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);
    
    liberarMochila(mochila);
    return 0;
}