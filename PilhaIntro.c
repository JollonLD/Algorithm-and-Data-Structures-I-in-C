#include <stdio.h>


#define MAX 10
typedef struct {
    int chave;
    char nome[51];
}TipoItem;

typedef struct{
    TipoItem itens[MAX];
    int tam;
    int topo;
}TipoPilha;

void inicializarPilha(TipoPilha *pilha){
    pilha->topo = -1; // pilha vazia
    pilha->tam  = MAX;
}

int pilhaVazia(TipoPilha *pilha){
    if(pilha->topo == -1)
        return 1;
    return 0;
}

int pilhaCheia(TipoPilha *pilha){
    if(pilha->topo == pilha->tam-1)
        return 1;
    return 0;
}

int push(TipoPilha *pilha, TipoItem item){
    if(pilha->topo == MAX-1){
        pilha[pilha->topo] = item;
            return 1;
    }
    else
        return 0;
}

TipoItem pop(TipoPilha *pilha){
    if(pilha->topo == -1)
        return &itens.chave = -1;
    else{
        return pilha[pilha->topo];
    }
}

int main(){
    TipoPilha pilha;
    TipoItem item;
    int i,N;
    inicializarPilha(&pilha);
    scanf("%d",&N);
    //inserindo N itens na pilha
    for(i=0; i<N; i++){
        scanf("%d %s",&item.chave,item.nome);
        if(!push(&pilha,item)){
                break;
        }
    }
    //desempilhando
    while(!pilhaVazia(&pilha)){
        item = pop(&pilha);
        printf("Desempilha %d %s\n",item.chave,item.nome);
    }
    return 0;
}
