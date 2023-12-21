#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int senha;
    int tempo;
    struct Item *prox;
} Item;

typedef struct {
    Item *inicio, *fim;
    int soma_tempo;
} Fila;

void inicializaFila(Fila *atendentes) {
    atendentes->inicio = NULL;
    atendentes->fim = NULL;
    atendentes->soma_tempo = 0;
}

void Insere(Fila *fila, Item item) {
    Item *novoitem = malloc(sizeof(Item));
    novoitem->senha = item.senha;
    novoitem->tempo = item.tempo;
    novoitem->prox = NULL;
    
    if (fila->fim == NULL)
        fila->inicio = novoitem;
    else {
        fila->fim->prox = novoitem;
    }
    
    fila->fim = novoitem;
}

int Retira(Fila *fila){
    Item* aux = fila->inicio;

    if(filavazia(fila) == 1){
        Item vazio;

        vazio.senha = -1;
        vazio.tempo = -1;
        vazio.prox = NULL;

        printf("Fila está vazia.");

        return vazio;
    }

    if(fila->fim == fila->inicio){
        fila->fim = NULL;
        fila->inicio = NULL;
        return *aux;
    }
    fila->inicio = fila->inicio->prox;

    return *aux;
}

void SeparaCliente(Fila *fila, Fila fila_espera, int caixas, int pessoas, Item item){
    int j, k, i;
    for(i=0; i<caixas; i++){
        fila[i].inicio = Retira(&fila_espera); 
    }

    for(i=0; i<pessoas; i++){
        for(j=0, k=1; k<caixas; j++, k++){
            if(fila[j].soma_tempo > fila[k].soma_tempo)
            j = k;
        }

        item = Retira(&fila);
        Insere(&fila[j], item);
        fila[j].soma_tempo += item.tempo;
    }

}

int main(){
    int caixas;
    int pessoas;
    Fila *atendentes, filaEspera;
    Item cliente;


    scanf("%d %d", &pessoas, &caixas);

    atendentes = malloc(caixas*(sizeof(Fila)));

    inicializaFila(&atendentes);

    for(int i = 0; i < pessoas; i++) {
        cliente.senha = i + 1;
        scanf("%d", &cliente.tempo);
        Insere(&filaEspera, cliente);
    }

    for (int i = 0; i < pessoas; i++) {
        printf("%d ", Retira(&atendentes));
    }

    free(atendentes->inicio);

    return 0;
}
