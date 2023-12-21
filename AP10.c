#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[30]; // informação do nó (nome com até 30 caracteres)
    int index;     // índice do nó no grafo
} TipoItem;

typedef struct{
    TipoItem l[1024]; // lista sequencial de nós
    int qtd; // lista linear de nós do grafo
}TipoLista;

typedef struct {
    TipoLista lista;
    int adj[1024][1024];   // matriz de adjacência N x N
} TipoGrafoMatrizAdj;


void inicializaGrafo(TipoGrafoMatrizAdj *grafo, int nV) {
    int i, j;
    grafo->lista.qtd = 0;
    
    for (i=0; i<nV; i++){
        for (j=0; j<nV; j++){
            grafo->adj[i][j] = 0;
        }
    }
}

int inserirNo(TipoLista *lista, char *nome, int nC) {
    if (lista->qtd == nC) {
        return -1;
    }

    strcpy(lista->l[lista->qtd].nome, nome);
    lista->l[lista->qtd].index = lista->qtd;
    lista->qtd++;

    return 1;
}

int buscaNo(TipoLista *lista, char *nome) {
    int i;

    for (i = 0; i < lista->qtd; i++) {
        if (strcmp(lista->l[i].nome, nome) == 0) {
            return lista->l[i].index;
        }
    }

    return -1;
}

int criarAresta(TipoGrafoMatrizAdj *grafo, char *no1, char *no2) {
    int i1 = buscaNo(&grafo->lista, no1);
    int i2 = buscaNo(&grafo->lista, no2);

    if (i1 < 0 || i2 < 0) {
        return -1;
    }

    grafo->adj[i1][i2] = 1;
    grafo->adj[i2][i1] = 1; // grafo não direcionado

    return 1;
}

int amigosSegundoGrau(TipoGrafoMatrizAdj *grafo, char *busca) {
    int no = buscaNo(&grafo->lista, busca);
    int amigosSegundoGrau = 0;
    int amigos[1024];
    int indice = 0;

    for (int i = 0; i < grafo->lista.qtd; i++){
        if (grafo->adj[no][i]){ //Verifica se existe conexão
            for (int j = 0; j < grafo->lista.qtd; j++){
                if(grafo->adj[i][j] && !grafo->adj[no][j] && j != no){
                    int amigoIndice = buscaNo(&grafo->lista, grafo->lista.l[j].nome);
                    int k;
                    for(k = 0; k < indice; k++) {
                        if(amigos[k] == amigoIndice){
                            break;
                        }
                    }
                    if(k == indice){
                        amigos[indice++] = amigoIndice;
                        amigosSegundoGrau++;
                    }
                }
            }
        }
    }

    return amigosSegundoGrau;
}





int main(){
    TipoGrafoMatrizAdj grafo;
    int nC, nV;
    char busca[17];

    scanf("%s", busca);

    scanf("%d %d", &nV, &nC);

    inicializaGrafo(&grafo, nV);
   
    for(int i=0; i<nC; i++){
        char no1[17], no2[17];

        scanf("%s", no1);
        if(buscaNo(&grafo.lista, no1) == -1)
            inserirNo(&grafo.lista, no1, nC);
        scanf("%s", no2);
        if(buscaNo(&grafo.lista, no2) == -1)
            inserirNo(&grafo.lista, no2, nC);
        criarAresta(&grafo, no1, no2);
    }

    //Para encontrar os amigos de segundo grau devemos ver os amigos de A e ver quais são os amigos desse amigo de A 
    //Posteriormente verificar se esse amigo do amigo é um amigo direto de A em um array de amigos que possui os índices dos amigos

    int qtdAmigos = amigosSegundoGrau(&grafo, busca);

    printf("%d", qtdAmigos);

    return 0;
}
