#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct TipoNo{
    int freq;
    char letra;
    struct TipoNo *esq, *dir;
}TipoNo;

typedef struct TipoArv{
    struct TipoNo *raiz;
}TipoArv;

void inicializaArv(TipoArv *);
TipoNo *CriaFolha(int, char);
void Insere(int, char, TipoArv *);
void emOrdem(TipoNo *);
TipoNo* removerNo(TipoNo*);
TipoNo* buscaremove(TipoNo *, char, char);
void ApagaArv(TipoNo *);


int main(){

    TipoArv arv;

    inicializaArv(&arv);

    char l1, l2;
    char string[1024];
    int str[26] = {0};

    scanf("%c %c", &l1, &l2);
    scanf("%s", string);

    for(int i=0; string[i] != '\0'; i++){
        int x = string[i];
        str[x-65]++;
    }

    for(int i=0; i<26; i++){
        if(str[i] != 0)
            Insere(str[i], i+65, &arv);
    }

    emOrdem(arv.raiz);
    printf("\n");

   arv.raiz = buscaremove(arv.raiz, l1, l2);

    emOrdem(arv.raiz);

    ApagaArv(arv.raiz);

    return 0;
}


void inicializaArv(TipoArv *arv){
    arv->raiz = NULL;
}

TipoNo *CriaFolha(int f, char c){
    TipoNo *novo = (TipoNo*) malloc(sizeof(TipoNo));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->freq = f;
    novo->letra = c;

    return novo;
}

void Insere(int f, char c, TipoArv *arv){
    
    TipoNo * novo = CriaFolha(f,c);
    
    TipoNo *aux1, *aux2;
    aux1 = NULL;
    aux2 = arv->raiz;
    
    while(aux2 != NULL){
        aux1 = aux2;
        if(f < aux2->freq){
            aux2 = aux2->esq;
        }
        else{
            aux2 = aux2->dir;
        }
    }
    
    if(aux1 == NULL){
        arv->raiz = novo;
    }
    else{
        if(f < aux1->freq){
            aux1->esq = novo;
        }
        else{
            aux1->dir = novo;
        }
    }

}

void emOrdem(TipoNo *no){
    if(no==NULL)
        return;
    emOrdem(no->esq);
    printf("%c",no->letra);
    emOrdem(no->dir);
}


TipoNo* removerNo(TipoNo* p) {
    if (p == NULL) {
        return NULL;
    }

    TipoNo* q;

    if (p->esq == NULL) {
        q = p->dir;
        free(p);
        return q;
    } else if (p->dir == NULL) {
        q = p->esq;
        free(p);
        return q;
    } else {
        q = p;
        TipoNo* r = p->esq;
        while (r->dir != NULL) {
            q = r;
            r = r->dir;
        }

        if (q != p) {
            q->dir = r->esq;
            r->esq = p->esq;
        }
        r->dir = p->dir;

        free(p);
        return r;
    }
}

TipoNo* buscaremove(TipoNo* no, char l1, char l2) {
    if (no == NULL) {
        return NULL;
    }

    no->esq = buscaremove(no->esq, l1, l2);
    no->dir = buscaremove(no->dir, l1, l2);

    if (no->letra == l1 || no->letra == l2) {
        TipoNo* aux = removerNo(no);
        no = aux;
    }

    return no;
}

void ApagaArv(TipoNo *no){
    if(no != NULL){
        ApagaArv(no->esq);
        ApagaArv(no->dir);
        free(no);
    }
}