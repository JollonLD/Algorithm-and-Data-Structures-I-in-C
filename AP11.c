#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo{
    int v;
    struct TipoNo *prox;
}TipoNo;

typedef struct TipoGrafo{
    int V, E;
    TipoNo **adj;
}TipoGrafo;

TipoGrafo *InicializaGrafo(TipoGrafo *grafo, int nV){
    grafo = (TipoGrafo*)malloc(sizeof(TipoGrafo));
    grafo->V = nV;
    grafo->E = 0;
    grafo->adj = (TipoNo*)malloc(nV*(sizeof(TipoNo)));

    for(int i=0; i<nV; i++){
        grafo->adj[i] = NULL;
    }

    return grafo;
}

void InsereAresta(TipoGrafo *grafo, int n, int m){
    TipoNo *p = malloc(sizeof(TipoNo));

    for(p = grafo->adj[n]; p != NULL; p = p->prox){
        if(p->v == m)
           return;
    }

    TipoNo *novoNo = malloc(sizeof(TipoNo));
    novoNo->v = m;
    novoNo->prox = NULL;

    p = grafo->adj[n];

    TipoNo *anterior = NULL;
    while (p != NULL && p->v < m) {
        anterior = p;
        p = p->prox;
    }

    if (anterior == NULL) {
        novoNo->prox = grafo->adj[n];
        grafo->adj[n] = novoNo;
    } else {
        novoNo->prox = anterior->prox;
        anterior->prox = novoNo;
    }

    grafo->E++;
}

void ImprimeListaADJ(TipoGrafo *grafo, int n){
    TipoNo *p = grafo->adj[n];

    while(p){
        printf("%d ", p->v);
        p = p->prox;
    }
}

void LiberaLA(TipoGrafo *grafo){
    TipoNo *p;

    for(int i=0; i<grafo->V; i++){
        while(p != NULL){
            p = grafo->adj[i];
            p = p->prox;
            free(grafo->adj[i]);
        }
        grafo->adj[i] = NULL;
    }
    free(grafo->adj);
    grafo->adj = NULL;
    free(grafo);
}

int main(){
    int busca, V, A, no1, no2;
    
    scanf("%d", &busca);
    scanf("%d %d", &V, &A);

    TipoGrafo *grafo = InicializaGrafo(&grafo, V);

    for(int i=0; i<A; i++){
        scanf("%d %d", &no1, &no2);
        InsereAresta(grafo, no1, no2);
    }

    ImprimeListaADJ(grafo, busca);
}
