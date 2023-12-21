#include <stdio.h>
#include <stdlib.h>

typedef struct TipoNo{
    int numero;
    struct TipoNo *esq, *dir;
}TipoNo;

typedef struct TipoArv{
    struct TipoNo *raiz;
}TipoArv;

void inicializaArv(TipoArv *);
TipoNo *CriaFolha(int);
void Insere(int, TipoArv *, int *);
void preOrdem(TipoNo *);
void emOrdem(TipoNo *);
void posOrdem(TipoNo *);
void Busca(TipoArv *, int);


int main(){

    int valor, tamanho;
    int elemento;
    int altura = 0;
    int buscaexiste = 0;

    TipoArv arvore;

    inicializaArv(&arvore);

    scanf("%d", &tamanho);
    scanf("%d", &valor);

    for(int i=0; i<tamanho; i++){
        scanf("%d", &elemento);
        Insere(elemento, &arvore, &altura);
        if(elemento == valor){
            buscaexiste = 1;
        }
    }

    preOrdem(arvore.raiz);
    printf("\n");
    emOrdem(arvore.raiz);
    printf("\n");
    posOrdem(arvore.raiz);
    printf("\n");
    if(buscaexiste){
        Busca(&arvore, valor);
    }
    else{
        printf("-1");
    }
    printf("\n");
    printf("%d", altura);
    return 0;
}


void inicializaArv(TipoArv *arv){
    arv->raiz = NULL;
}

TipoNo *CriaFolha(int elemento){
    TipoNo *novo = (TipoNo*) malloc(sizeof(TipoNo));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->numero = elemento;

    return novo;
}

void Insere(int elemento, TipoArv *arv, int *altura){
    
    TipoNo * novo = CriaFolha(elemento);
    
    int tamanho = 0;
    TipoNo *aux1, *aux2;
    aux1 = NULL;
    aux2 = arv->raiz;
    
    while(aux2 != NULL){
        aux1 = aux2;
        if(elemento < aux2->numero){
            aux2 = aux2->esq;
        }
        else{
            aux2 = aux2->dir;
        }
        tamanho ++;
    }

    if(tamanho > *altura){
        *altura = tamanho;
    }
    
    if(aux1 == NULL){
        arv->raiz = novo;
    }
    else{
        if(elemento < aux1->numero){
            aux1->esq = novo;
        }
        else{
            aux1->dir = novo;
        }
    }

}

void preOrdem(TipoNo *no){
    if(no==NULL)
        return;
    printf("%d ",no->numero); 
    preOrdem(no->esq);    
    preOrdem(no->dir);
}

void emOrdem(TipoNo *no){
    if(no==NULL)
        return;
    emOrdem(no->esq);
    printf("%d ",no->numero);
    emOrdem(no->dir);
}

void posOrdem(TipoNo *no){
    if(no==NULL)
        return;
    posOrdem(no->esq);    
    posOrdem(no->dir);
    printf("%d ",no->numero);
}

void Busca(TipoArv *arv, int elemento){
    TipoNo *aux = arv->raiz;
    while(aux != NULL && elemento != aux->numero){
        if(elemento < aux->numero){
            printf("%d ", aux->numero);
            aux = aux->esq;
        }
        else{
            printf("%d ", aux->numero);
            aux = aux->dir;
        }
    }
    printf("%d", elemento);
}

