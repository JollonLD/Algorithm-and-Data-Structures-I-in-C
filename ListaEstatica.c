#include <stdio.h>

#define MAX 1000

typedef struct{
	int chave;
	char nome[50];
}TipoItem;

typedef struct{
	TipoItem itens[MAX];
	int ultimo;
}ListaLinearSE;

void inicializaListaLLSE(ListaLinearSE *);

void imprimeListaLLSE(ListaLinearSE *);

int insereNoFinalLLSE(ListaLinearSE *, TipoItem );

int main() {
    int i,n;
    ListaLinearSE lista;
    TipoItem item;
    inicializaListaLLSE(&lista);
    scanf("%d",&n);
    for(i=0; i<n; i++) {
        scanf("%d %s",&item.chave,item.nome);
        if(insereNoFinalLLSE(&lista,item) < 0){
	       printf("ERRO! Tam.limite excedido.\n");
	       break;
	       }
        }
    imprimeListaLLSE(&lista);
    return 0;
}

void inicializaListaLLSE(ListaLinearSE *lista){
    lista->ultimo= 0;
}

void imprimeListaLLSE(ListaLinearSE *lista){
  int i=0;
  for(i=0; i < lista->ultimo; i++)
    printf("%d %s\n", lista->itens[i].chave,  
                      lista->itens[i].nome);
}

int insereNoFinalLLSE(ListaLinearSE *lista, 
                      TipoItem novoItem){
	int pos = lista->ultimo;
	if(pos < MAX){
		lista->itens[pos] = novoItem;
		lista->ultimo++;
	}
	else return -1;
	return 0;
}
