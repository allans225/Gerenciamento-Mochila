#include <stdio.h>
#include "utils.h"

// Função de buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}