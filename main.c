#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACIDADE_MAXIMA 10 // O "peso" máximo que a mochila aguenta
#define MAX_SLOTS 10         // O número de tipos de itens diferentes que a mochila pode ter

struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

void definirItem(struct Item *item);
void inserirItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado);
void removerItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado);
void listarItens(struct Item *mochila, int slotsUsados, int espacoOcupado);
void limparBuffer();

int main() {
    struct Item *mochila = malloc(MAX_SLOTS * sizeof(struct Item));
    int slotsUsados = 0;    // Contador para os índices (0, 1, 2...)
    int espacoOcupado = 0;  // Contador para a soma das quantidades (o "peso")
    int opcao;

    printf("Sistema de Gerenciamento de Mochila\n");
    do {
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao) {
            case 1:
                inserirItem(mochila, &slotsUsados, &espacoOcupado);
                break;
            case 2:
                if (slotsUsados == 0) { // Checa se há slots em uso
                    printf("Mochila vazia! Nao ha itens para remover.\n");
                    break;
                }
                removerItem(mochila, &slotsUsados, &espacoOcupado);
                break;
            case 3:
                if (slotsUsados == 0) { // Checa se há slots em uso
                    printf("Mochila vazia! Nao ha itens para listar.\n");
                    break;
                }
                listarItens(mochila, slotsUsados, espacoOcupado);
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);
    free(mochila);
    return 0;
}

void definirItem(struct Item *item) {
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

void inserirItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado) {
    struct Item novoItem;
    definirItem(&novoItem); // Pega os dados do novo item

    // VERIFICA O PESO (ESPAÇO OCUPADO)
    if (*espacoOcupado + novoItem.quantidade > CAPACIDADE_MAXIMA) {
        printf("Mochila sem espaco suficiente! (%d/%d)\n", *espacoOcupado, CAPACIDADE_MAXIMA);
        printf("Item precisa de %d de espaco, mas so tem %d livre.\n", novoItem.quantidade, CAPACIDADE_MAXIMA - *espacoOcupado);
        return;
    }

    // TENTA EMPILHAR
    for (int i = 0; i < *slotsUsados; i++) {
        if (strcmp(mochila[i].nome, novoItem.nome) == 0) {
            mochila[i].quantidade += novoItem.quantidade; // Apenas soma a quantidade
            *espacoOcupado += novoItem.quantidade;        // Atualiza o peso total
            return; // Sai da função
        }
    }

    // VERIFICA OS SLOTS
    if (*slotsUsados >= MAX_SLOTS) {
        printf("Mochila cheia! Nao ha espaco para novos tipos de itens.\n");
        return;
    }

    // SE PASSOU TUDO, ADICIONA EM NOVO SLOT
    mochila[*slotsUsados] = novoItem;       // Adiciona o item no slot correto
    *espacoOcupado += novoItem.quantidade; // Atualiza o peso total
    (*slotsUsados)++;                     // Incrementa o contador de slots
    printf("Item inserido com sucesso!\n");
}

void removerItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado) {
    char buscaNome[30];
    printf("Nome do Item a ser removido: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    // usa 'slotsUsados', que é o número correto de itens
    for (int i = 0; i < *slotsUsados; i++) {
        if (strcmp(mochila[i].nome, buscaNome) == 0) {
            // Atualiza o peso total ANTES de remover
            *espacoOcupado -= mochila[i].quantidade; 
            
            // Move os itens restantes para preencher o espaço vazio
            for (int j = i; j < *slotsUsados - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            (*slotsUsados)--; // Decrementa o contador de slots
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado na mochila.\n");
}

void listarItens(struct Item *mochila, int slotsUsados, int espacoOcupado) {
    printf("Espaco na Mochila: %d/%d\n", espacoOcupado, CAPACIDADE_MAXIMA);
    printf("------------------------------\n");
    for (int i = 0; i < slotsUsados; i++) {
        printf("Slot %d:\tNome: %s\t|\tTipo: %s\t|\tQuantidade: %d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}