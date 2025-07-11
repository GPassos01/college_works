#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PUZZLE_SIZE 9

typedef struct Estado {
    int blocos[PUZZLE_SIZE];
} Estado;

typedef struct No {
    Estado estado;
    struct No* pai;
    int custo;
    int hlocal; // Heurística local (distância de Manhattan)
    int hfora;  // Heurística fora-de-linha (blocos fora do lugar)
    int f; // Total cost (f = g + h)
} No;

Estado* criarEstado(int blocos[PUZZLE_SIZE]) {
    Estado* estado = malloc(sizeof(Estado));
    if (estado == NULL) {
        printf("Erro ao alocar memória para o estado.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        estado->blocos[i] = blocos[i];
    }
    return estado;
}

void destruirEstado(Estado* estado) {
    free(estado);
}

Estado* copiarEstado(Estado* estado) {
    Estado* novoEstado = malloc(sizeof(Estado));
    if (novoEstado == NULL) {
        printf("Erro ao alocar memória para o novo estado.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        novoEstado->blocos[i] = estado->blocos[i];
    }
    return novoEstado;
}

int findBlank(Estado* estado) {
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (estado->blocos[i] == 0) {
            return i;
        }
    }
    return -1; // Erro: espaço em branco não encontrado
}

bool isObjetivo(Estado* estado) {
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (estado->blocos[i] != (i) % PUZZLE_SIZE) {
            return false;
        }
    }
    return true;
}

int distanciaManhattan(int bloco, int posicaoFinal) {
    int linhaAtual = bloco / 3;
    int colunaAtual = bloco % 3;
    int linhaFinal = posicaoFinal / 3;
    int colunaFinal = posicaoFinal % 3;
    return abs(linhaAtual - linhaFinal) + abs(colunaAtual - colunaFinal);
}

int heuristicaLocal(Estado* estado) {
    int total = 0;
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        total += distanciaManhattan(estado->blocos[i], i);
    }
    return total;
}

int heuristicaFora(Estado* estado) {
    int fora = 0;
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (estado->blocos[i] != (i) % PUZZLE_SIZE && estado->blocos[i] != 0) {
            fora++;
        }
    }
    return fora;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

No** gerarFilhos(Estado* estado, int* numFilhos) {
    int blankPos = findBlank(estado);
    if (blankPos == -1) {
        return NULL; // Erro: espaço em branco não encontrado
    }

    *numFilhos = 0;
    No** filhos = malloc(4 * sizeof(No*));
    if (filhos == NULL) {
        printf("Erro ao alocar memória para os filhos.\n");
        exit(EXIT_FAILURE);
    }

    int movimentos[4] = {-3, 3, -1, 1};
    for (int i = 0; i < 4; i++) {
        int newPos = blankPos + movimentos[i];
        if (newPos >= 0 && newPos < PUZZLE_SIZE && !(blankPos % 3 == 0 && i == 2) && !(blankPos % 3 == 2 && i == 3)) {
            filhos[*numFilhos] = malloc(sizeof(No));
            if (filhos[*numFilhos] == NULL) {
                printf("Erro ao alocar memória para o filho.\n");
                exit(EXIT_FAILURE);
            }
            filhos[*numFilhos]->estado = *copiarEstado(estado);
            swap(&filhos[*numFilhos]->estado.blocos[blankPos], &filhos[*numFilhos]->estado.blocos[newPos]);
            (*numFilhos)++;
        }
    }
    return filhos;
}

void liberarNos(No** nos, int numNos) {
    for (int i = 0; i < numNos; i++) {
        free(nos[i]);
    }
    free(nos);
}

bool jaVisitado(Estado* estado, No** nosVisitados, int numNosVisitados) {
    for (int i = 0; i < numNosVisitados; i++) {
        bool igual = true;
        for (int j = 0; j < PUZZLE_SIZE; j++) {
            if (estado->blocos[j] != nosVisitados[i]->estado.blocos[j]) {
                igual = false;
                break;
            }
        }
        if (igual) {
            return true;
        }
    }
    return false;
}

bool aEstrela(Estado* estadoInicial) {
    No* noInicial = malloc(sizeof(No));
    if (noInicial == NULL) {
        printf("Erro ao alocar memória para o nó inicial.\n");
        exit(EXIT_FAILURE);
    }
    noInicial->estado = *estadoInicial;
    noInicial->pai = NULL;
    noInicial->custo = 0;
    noInicial->hlocal = heuristicaLocal(estadoInicial);
    noInicial->hfora = heuristicaFora(estadoInicial);
    noInicial->f = noInicial->custo + noInicial->hlocal + noInicial->hfora;

    No** abertos = malloc(sizeof(No*));
    if (abertos == NULL) {
        printf("Erro ao alocar memória para a lista aberta.\n");
        exit(EXIT_FAILURE);
    }
    No** fechados = malloc(sizeof(No*));
    if (fechados == NULL) {
        printf("Erro ao alocar memória para a lista fechada.\n");
        exit(EXIT_FAILURE);
    }

    int numAbertos = 1;
    int numFechados = 0;

    abertos[0] = noInicial;

    while (numAbertos > 0) {
        int indiceMinF = 0;
        for (int i = 1; i < numAbertos; i++) {
            if (abertos[i]->f < abertos[indiceMinF]->f) {
                indiceMinF = i;
            }
        }

        No* noAtual = abertos[indiceMinF];
        abertos[indiceMinF] = abertos[numAbertos - 1];
        numAbertos--;

        if (isObjetivo(&noAtual->estado)) {
            // Encontrou a solução, exibe os passos
            No* temp = noAtual;
            int numPassos = 0;
            while (temp != NULL) {
                numPassos++;
                temp = temp->pai;
            }

            printf("Solução encontrada em %d passos:\n", numPassos);

            // Exibe os passos reversamente
            while (noAtual != NULL) {
                for (int i = 0; i < PUZZLE_SIZE; i++) {
                    printf("%d ", noAtual->estado.blocos[i]);
                    if ((i + 1) % 3 == 0) {
                        printf("\n");
                    }
                }
                printf("\n");
                noAtual = noAtual->pai;
            }

            liberarNos(abertos, numAbertos);
            liberarNos(fechados, numFechados);
            return true;
        }

        int numFilhos = 0;
        No** filhos = gerarFilhos(&noAtual->estado, &numFilhos);

        for (int i = 0; i < numFilhos; i++) {
            No* filho = filhos[i];
            filho->pai = noAtual;
            filho->custo = noAtual->custo + 1;
            filho->hlocal = heuristicaLocal(&filho->estado);
            filho->hfora = heuristicaFora(&filho->estado);
            filho->f = filho->custo + filho->hlocal + filho->hfora;

            if (!jaVisitado(&filho->estado, fechados, numFechados) && !jaVisitado(&filho->estado, abertos, numAbertos)) {
                abertos = realloc(abertos, (numAbertos + 1) * sizeof(No*));
                if (abertos == NULL) {
                    printf("Erro ao realocar memória para a lista aberta.\n");
                    exit(EXIT_FAILURE);
                }
                abertos[numAbertos] = filho;
                numAbertos++;
            } else {
                free(filho);
            }
        }

        fechados = realloc(fechados, (numFechados + 1) * sizeof(No*));
        if (fechados == NULL) {
            printf("Erro ao realocar memória para a lista fechada.\n");
            exit(EXIT_FAILURE);
        }
        fechados[numFechados] = noAtual;
        numFechados++;
    }

    liberarNos(abertos, numAbertos);
    liberarNos(fechados, numFechados);
    return false;
}

int main() {
    int estadoInicial[PUZZLE_SIZE] = {5, 2, 0,
                                      6, 1, 4,
                                      8, 7, 3};
    Estado* estado = criarEstado(estadoInicial);

    bool solucionavel = aEstrela(estado);

    if (!solucionavel) {
        printf("O jogo não é solucionável!\n");
    }

    destruirEstado(estado);
    return 0;
}