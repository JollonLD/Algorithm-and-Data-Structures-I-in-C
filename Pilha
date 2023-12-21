#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

typedef struct {
    int data;
    struct TipoItem* proximo;
} TipoItem;

typedef struct {
    TipoItem* topo;
} TipoPilha;

int pilhaVazia(TipoPilha*);

void inicializaPilha(TipoPilha*);

void Push(TipoPilha*, int);

int Pop(TipoPilha*);

int CalcularRPN(char[], TipoPilha*);

int main() {
    TipoPilha pilha;
    char string[MAX];

    scanf("%s", string);

    inicializaPilha(&pilha);

    int resultado = CalcularRPN(string, &pilha);

    if (resultado == -1) {
        printf("Invalid Expression\n");
        return 1;
    }

    printf("%d\n", resultado);

    return 0;
}

void inicializaPilha(TipoPilha* pilha) {
    pilha->topo = NULL;
}

int pilhaVazia(TipoPilha* pilha) {
    return (pilha->topo == NULL);
}

void Push(TipoPilha* pilha, int valor) {
    TipoItem* novo = (TipoItem*)malloc(sizeof(TipoItem));
    novo->data = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

int Pop(TipoPilha* pilha) {
    if (pilhaVazia(pilha)) {
        return -1;
    }
    TipoItem* aux = pilha->topo;
    int valor = aux->data;
    pilha->topo = pilha->topo->proximo;
    free(aux);
    return valor;
}

int CalcularRPN(char string[], TipoPilha* pilha) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            Push(pilha, string[i] - '0');
        } else if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/') {
            int num2 = Pop(pilha);
            int num1 = Pop(pilha);
            if (num1 == -1 || num2 == -1) {
                return -1;
            }
            if (string[i] == '+') {
                Push(pilha, num1 + num2);
            } else if (string[i] == '-') {
                Push(pilha, num1 - num2);
            } else if (string[i] == '*') {
                Push(pilha, num1 * num2);
            } else if (string[i] == '/') {
                if (num2 == 0) {
                    return -1;
                }
                Push(pilha, num1 / num2);
            }
        }
    }

    if (pilhaVazia(pilha) || pilha->topo->proximo != NULL) {
        return -1;
    }

    return Pop(pilha);
}
