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

