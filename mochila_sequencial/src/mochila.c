#include <stdio.h>
#include <string.h>
#include "mochila.h"
#include "utils.h" // Usa a função limparBuffer

// Esta função é um "detalhe de implementação" da inserção.
// 'static' para que seja PRIVADA a este arquivo.
static void definirItem(struct Item *item) {
    printf("Nome do Item: ");
    fgets(item->nome, sizeof(item->nome), stdin);
    item->nome[strcspn(item->nome, "\n")] = 0;

    printf("Tipo do Item: ");
    fgets(item->tipo, sizeof(item->tipo), stdin);
    item->tipo[strcspn(item->tipo, "\n")] = 0;

    printf("Quantidade do Item: ");
    scanf("%d", &item->quantidade);

    printf("Prioridade do Item (0-10): ");
    scanf("%d", &item->prioridade);
    limparBuffer();
}

void inserirItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado, int max_slots, int capacidade_maxima) {
    struct Item novoItem;
    definirItem(&novoItem);

    // Verifica se há espaço suficiente na mochila
    if (*espacoOcupado + novoItem.quantidade > capacidade_maxima) {
        printf("Mochila sem espaco suficiente! (%d/%d)\n", *espacoOcupado, capacidade_maxima);
        return;
    }

    // Verifica se o item já existe para empilhar
    for (int i = 0; i < *slotsUsados; i++) {
        if (strcmp(mochila[i].nome, novoItem.nome) == 0) {
            mochila[i].quantidade += novoItem.quantidade;
            *espacoOcupado += novoItem.quantidade;
            return;
        }
    }

    // Verifica se há slots disponíveis para um novo tipo de item
    if (*slotsUsados >= max_slots) {
        printf("Mochila cheia! Nao ha espaco para novos tipos de itens.\n");
        return;
    }

    // Insere o novo item na mochila
    mochila[*slotsUsados] = novoItem;
    // Atualiza o espaço ocupado
    *espacoOcupado += novoItem.quantidade;
    // Incrementa o número de slots usados
    (*slotsUsados)++;
    printf("Item inserido com sucesso!\n");
}

void removerItem(struct Item *mochila, int *slotsUsados, int *espacoOcupado) {
    char buscaNome[30];
    printf("Nome do Item a ser removido: ");
    fgets(buscaNome, sizeof(buscaNome), stdin);
    buscaNome[strcspn(buscaNome, "\n")] = 0;

    // Procura o item por nome
    for (int i = 0; i < *slotsUsados; i++) {
        // Compara os nomes dos itens
        if (strcmp(mochila[i].nome, buscaNome) == 0) {
            // Item encontrado, remove o espaço ocupado
            *espacoOcupado -= mochila[i].quantidade;
            // Move os itens restantes para preencher o espaço
            for (int j = i; j < *slotsUsados - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*slotsUsados)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item nao encontrado na mochila.\n");
}

void listarItens(const struct Item *mochila, int slotsUsados, int espacoOcupado, int capacidade_maxima) {
    printf("\n--- Conteudo da Mochila ---\n");
    printf("Espaco Ocupado: %d/%d\n", espacoOcupado, capacidade_maxima);
    
    if (slotsUsados == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    
    for (int i = 0; i < slotsUsados; i++) {
        printf("Slot %d. Nome: %s\t|\tTipo: %s\t|\tQuantidade: %d\t|\tPrioridade: %d\n",
            i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("---------------------------\n");
}

// Selection Sort para ordenar itens por nome (alfabético)
void ordenarItensPorNome(struct Item *mochila, int slotsUsados) {
    // Se não há itens ou há apenas 1, não precisa ordenar
    if (slotsUsados < 2) {
        return;
    }
    struct Item temp; // Variável temporária para a troca (swap)

    // Passa por cada posição que precisa ser preenchida
    for (int i = 0; i < slotsUsados - 1; i++) {
        // Encontra o índice do menor item restante
        int indiceDoMenor = i;

        // Compara o item 'i' com todos os seguintes
        for (int j = i + 1; j < slotsUsados; j++) {
            
            // strcmp() compara duas strings
            // (alfabéticamente: A (vem ANTES) = MENOR, Z (vem DEPOIS) = MAIOR)
            //   < 0: se a string 'j' vem ANTES da string 'indiceDoMenor' (então 'j' é menor)
            //   > 0: se a string 'j' vem DEPOIS da string 'indiceDoMenor' (então 'j' é maior)
            //   = 0: se são iguais
            
            // "Se o nome do item 'j' vem antes do nome do 'menor' atual..."
            if (strcmp(mochila[j].nome, mochila[indiceDoMenor].nome) < 0) {
                indiceDoMenor = j; // "então o 'j' é o novo menor."
            }
        }

        // Se o menor item encontrado não for o 'i' com o qual começamos,
        // nós os trocamos de lugar.
        if (indiceDoMenor != i) {
            temp = mochila[i];
            mochila[i] = mochila[indiceDoMenor];
            mochila[indiceDoMenor] = temp;
        }
    }
}

// Bubble Sort para ordenar itens por prioridade (decrescente)
void ordenarItensPorPrioridade(struct Item *mochila, int slotsUsados) {
    int i, j;
    struct Item temp; // Var temporária para auxiliar na troca

    // Laço Externo: controla o número de passadas
    // Vai até slotsUsados - 1 pois o último elemento já estará ordenado

    for (i = 0; i < slotsUsados - 1; i++) {
        // Laço Interno: compara os elementos adjacentes
        // O "- i" serve para não verificar novamente os itens que já foram 
        // ordenados e colocados no final nas passadas anteriores

        for (j = 0; j < slotsUsados - i - 1; j++) {
            // CONDIÇÃO DE ORDENAÇÃO DECRESCENTE (MAIOR -> MENOR)
            if (mochila[j].prioridade < mochila[j + 1].prioridade) {
                // Realiza a troca de estruturas inteiras
                temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort para ordenar itens por tipo (alfabético)
void ordenarItensPorTipo(struct Item *mochila, int slotsUsados) {
    int i, j;
    struct Item chave; // Var para guardar o item que estamos movendo

    // Começa do segundo item (índice 1) até o final
    for (i = 1; i < slotsUsados; i++) {
        
        chave = mochila[i]; // Pega o item na posição i da mochila
        j = i - 1;

        // O Loop while faz duas coisas:
        // não passa do início do array (j >= 0).
        // Verifica se o item anterior (mochila[j]) é "maior" alfabeticamente que a nossa chave
        //    strcmp > 0 significa que mochila[j].tipo vem DEPOIS da chave.tipo no alfabeto.
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            // Se o item anterior for maior, empurra ele para a direita
            mochila[j + 1] = mochila[j];
            j = j - 1; // Recua para comparar com o próximo anterior
        }
        // Encontra a posiçao correta e coloca a chave lá.
        mochila[j + 1] = chave;
    }
}

// Função auxiliar (privada) recursiva
static int buscaBinariaRecursiva_aux(const struct Item *mochila, const char* nomeItem, int inicio, int fim, int* comparacoes) {
    if (inicio > fim) {
        return -1; 
    }

    int meio = inicio + (fim - inicio) / 2;

    (*comparacoes)++; // Incrementa o contador ANTES de cada 'strcmp'
    int cmp = strcmp(mochila[meio].nome, nomeItem);

    if (cmp == 0) {
        return meio; 
    } 
    else if (cmp < 0) {
        // Passa o ponteiro 'comparacoes' para a próxima chamada recursiva
        return buscaBinariaRecursiva_aux(mochila, nomeItem, meio + 1, fim, comparacoes);
    } 
    else {
        // Passa o ponteiro 'comparacoes' para a próxima chamada recursiva
        return buscaBinariaRecursiva_aux(mochila, nomeItem, inicio, meio - 1, comparacoes);
    }
}

//Função principal (wrapper) que inicia a busca binária
int buscaBinariaRecursiva(const struct Item *mochila, int slotsUsados, const char* nomeItem, int* comparacoes) {
    *comparacoes = 0; // Inicializa o contador ANTES de chamar a auxiliar
    return buscaBinariaRecursiva_aux(mochila, nomeItem, 0, slotsUsados - 1, comparacoes);
}

// Busca sequencial iterativa
int buscaSequencialIterativa(const struct Item *mochila, int slotsUsados, const char* nomeItem, int* comparacoes    ) {
    *comparacoes = 0; // Inicializa o contador
    for (int i = 0; i < slotsUsados; i++) {
        (*comparacoes)++; // Incrementa o contador ANTES de cada 'strcmp'
        if (strcmp(mochila[i].nome, nomeItem) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}