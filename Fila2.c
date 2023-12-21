#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {
    int id;
    int tempo;
    struct Cliente* proximo;
} Cliente;

typedef struct {
    Cliente* inicio;
    Cliente* fim;
    int SomaTempo;
} FilaClientes;

void inicializarFilaClientes(FilaClientes* fila);
int filaEstaVazia(FilaClientes* fila);
Cliente removerDaFila(FilaClientes* fila);
void inserirNaFila(FilaClientes* fila, Cliente novo);
void imprimirFilaClientes(FilaClientes* fila);

int buscaMenorFila(FilaClientes* filasAtendimento, int caixas);

int main() {
    FilaClientes* filasAtendimento, filaDeEspera;
    Cliente cliente;
    int quantClientes, caixas, i;

    scanf("%d %d", &quantClientes, &caixas);

    inicializarFilaClientes(&filaDeEspera);

    filasAtendimento = (FilaClientes*)malloc(caixas * sizeof(FilaClientes));

    for (i = 0; i < caixas; i++) {
        inicializarFilaClientes(&filasAtendimento[i]);
    }

    for (i = 0; i < quantClientes; i++) {
        scanf("%d", &cliente.tempo);
        cliente.id = i + 1;
        inserirNaFila(&filaDeEspera, cliente);

        int filaEscolhida = buscaMenorFila(filasAtendimento, caixas);
        cliente = removerDaFila(&filaDeEspera);
        inserirNaFila(&filasAtendimento[filaEscolhida], cliente);
        filasAtendimento[filaEscolhida].SomaTempo += cliente.tempo;
    }

    imprimirFilaClientes(&filaDeEspera);

    for (i = 0; i < caixas; i++) {
        printf("%d: ", i + 1);
        imprimirFilaClientes(&filasAtendimento[i]);
        printf("\n");
    }

    for (i = 0; i < caixas; i++) {
        free(filasAtendimento[i].inicio);
    }

    free(filasAtendimento);

    return 0;
}

void inserirNaFila(FilaClientes* fila, Cliente novo) {
    Cliente* aux = (Cliente*)malloc(sizeof(Cliente));
    aux->id = novo.id;
    aux->tempo = novo.tempo;
    aux->proximo = NULL;
    if (filaEstaVazia(fila) == 1) {
        fila->inicio = aux;
    } else {
        fila->fim->proximo = aux;
    }
    fila->fim = aux;
}

Cliente removerDaFila(FilaClientes* fila) {
    Cliente* aux = fila->inicio;

    if (filaEstaVazia(fila) == 1) {
        Cliente clienteVazio;

        clienteVazio.id = -1;
        clienteVazio.tempo = -1;
        clienteVazio.proximo = NULL;

        printf("Fila está vazia.");

        return clienteVazio;
    }

    if (fila->fim == fila->inicio) {
        fila->fim = NULL;
        fila->inicio = NULL;
        return *aux;
    }
    fila->inicio = fila->inicio->proximo;
    return *aux;
}

void inicializarFilaClientes(FilaClientes* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->SomaTempo = 0;
}

int filaEstaVazia(FilaClientes* fila) {
    if (fila->inicio == NULL && fila->fim == NULL) {
        return 1;
    }
    return 0;
}

void imprimirFilaClientes(FilaClientes* fila) {
    Cliente* aux = fila->inicio;
    while (aux != NULL) {
        printf("%d ", aux->id);
        aux = aux->proximo;
    }
}

int buscaMenorFila(FilaClientes* filasAtendimento, int caixas) {
    int menorFila = 0;
    for (int i = 1; i < caixas; i++) {
        if (filasAtendimento[i].SomaTempo < filasAtendimento[menorFila].SomaTempo) {
            menorFila = i;
        }
    }
    return menorFila;
}
