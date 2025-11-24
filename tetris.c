#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

//----------------------------------------------
// STRUCT DA PEÇA
//----------------------------------------------
typedef struct {
    char nome;   // Tipo da peça: I, O, T, L
    int id;      // Identificador único da peça
} Peca;

//----------------------------------------------
// VARIÁVEIS GLOBAIS PARA GERAR IDs
//----------------------------------------------
int proximoID = 0;


//----------------------------------------------
// GERA UMA NOVA PEÇA COM ID ÚNICO
//----------------------------------------------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];  // tipo aleatório
    nova.id = proximoID++;          // id único

    return nova;
}

//----------------------------------------------
// EXIBE O ESTADO ATUAL DA FILA E PILHA
//----------------------------------------------
void exibirEstado(Peca fila[], int inicio, int fim, int qtdFila,
                  Peca pilha[], int topo) {

    printf("\n========================================\n");
    printf("Estado atual:\n\n");

    printf("Fila de peças:\t");
    if (qtdFila == 0) {
        printf("(vazia)");
    } else {
        int i = inicio;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
    }
    printf("\n");

    printf("Pilha de reserva\t(Topo -> Base): ");
    if (topo == -1) {
        printf("(vazia)");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }

    printf("\n========================================\n");
}

//----------------------------------------------
// INSERE NO FINAL DA FILA (FILA CIRCULAR)
//----------------------------------------------
void enfileirar(Peca fila[], int *fim, int *qtd, Peca nova) {
    fila[*fim] = nova;
    *fim = (*fim + 1) % TAM_FILA;
    (*qtd)++;
}


//----------------------------------------------
// REMOVE DO INÍCIO DA FILA (DEQUEUE)
//----------------------------------------------
Peca desenfileirar(Peca fila[], int *inicio, int *qtd) {
    Peca retirada = fila[*inicio];
    *inicio = (*inicio + 1) % TAM_FILA;
    (*qtd)--;
    return retirada;
}


//----------------------------------------------
// INSERE NA PILHA (PUSH)
//----------------------------------------------
int push(Peca pilha[], int *topo, Peca nova) {
    if (*topo == TAM_PILHA - 1) {
        return 0; // pilha cheia
    }
    pilha[++(*topo)] = nova;
    return 1;
}


//----------------------------------------------
// REMOVE DA PILHA (POP)
//----------------------------------------------
int pop(Peca pilha[], int *topo, Peca *removida) {
    if (*topo == -1) {
        return 0; // pilha vazia
    }
    *removida = pilha[(*topo)--];
    return 1;
}

//----------------------------------------------
// PROGRAMA PRINCIPAL
//----------------------------------------------
int main() {
    srand(time(NULL));

    // FILA CIRCULAR
    Peca fila[TAM_FILA];
    int inicio = 0, fim = 0, qtdFila = 0;

    // PILHA
    Peca pilha[TAM_PILHA];
    int topo = -1;

    // Inicializar a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(fila, &fim, &qtdFila, gerarPeca());
    }

    int opcao;

    do {
        exibirEstado(fila, inicio, fim, qtdFila, pilha, topo);

        printf("\nOpções de Ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Reservar peça (fila -> pilha)\n");
        printf("3 - Usar peça reservada (pop)\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        printf("\n");

        switch(opcao) {
            case 1: {
                // JOGAR PEÇA
                Peca jogada = desenfileirar(fila, &inicio, &qtdFila);
                printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);

                // Repor a fila imediatamente
                enfileirar(fila, &fim, &qtdFila, gerarPeca());
                break;
            }

            case 2: {
                // RESERVAR PEÇA
                if (topo == TAM_PILHA - 1) {
                    printf("Pilha de reserva está cheia! Não é possível reservar.\n");
                } else {
                    Peca reservada = desenfileirar(fila, &inicio, &qtdFila);
                    push(pilha, &topo, reservada);
                    printf("Peça reservada: [%c %d]\n", reservada.nome, reservada.id);

                    // Repor a fila
                    enfileirar(fila, &fim, &qtdFila, gerarPeca());
                }
                break;
            }

            case 3: {
                // USAR PEÇA DA RESERVA
                Peca usada;
                if (pop(pilha, &topo, &usada)) {
                    printf("Peça usada da reserva: [%c %d]\n", usada.nome, usada.id);
                } else {
                    printf("Pilha de reserva vazia! Nada a usar.\n");
                }
                break;
            }

            case 0:
                printf("Encerrando jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}