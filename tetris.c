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
