#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int coeficiente;
  int expoente;
}TipoMonomio;

typedef struct{
  TipoMonomio *polinomio;
  int ultimo;
  int tamanho;
}TipoPolinomio;

int InicializaPolinomio(TipoPolinomio *, int);

int InsereMonomio(TipoPolinomio *, TipoMonomio);

// Fazer as operações e reduzir o vetor reduzir de tamanho.
void AtualizaPolinomio(TipoPolinomio *, int);

void ImprimePolinomio(TipoPolinomio *);

void OrganizaPolinomio(TipoPolinomio *, int);

int main(){

  int n; // número de monômios (grau)
  
  TipoMonomio monomio;
  
  TipoPolinomio polinomio;
  
  do{
    scanf("%d", &n);
  }while(n<1 || n>1023);

  if(InicializaPolinomio(&polinomio, n) == -1)
    printf("Sai fora, não deu certo!!");
  
  for(int i=0; i<n; i++){
    scanf("%d" "%d", &monomio.coeficiente, &monomio.expoente);
    if(InsereMonomio(&polinomio, monomio) == -1){
        printf("Lista Completa!!");
    }
  }

  OrganizaPolinomio(&polinomio, n);
  
  ImprimePolinomio(&polinomio);

  free(polinomio.polinomio);
  
  return 0;
}

int InicializaPolinomio(TipoPolinomio *polinomio, int n) {
    polinomio->ultimo = 0;
    polinomio->tamanho = n;
    polinomio->polinomio = malloc(n * sizeof(TipoMonomio));

    if (polinomio->polinomio == NULL) return -1;

    return 0;
}

int InsereMonomio(TipoPolinomio *lista, TipoMonomio monomio) {
    int posicao = lista->ultimo;

    if (posicao < lista->tamanho) {
        lista->polinomio[posicao] = monomio;
        lista->ultimo++;
    } else {
        return -1;
    }
    return 0;
}

void AtualizaPolinomio(TipoPolinomio *lista, int n){
  
  int count = 0; //repetições do expoente
  int e;
  
  for(int i=0; i<n; i++){
    e = lista->polinomio[i].expoente;
    count = 0;
    for(int j=0; j<n; j++){
      if(e == lista->polinomio[j].expoente){
        count++;
        if(count >= 2){
          lista->polinomio[i].coeficiente += lista->polinomio[j].coeficiente;
        }
      }
    }
  }
}

void ImprimePolinomio(TipoPolinomio *lista){
  for(int i=0; i<lista->ultimo; i++){
    printf("%d %d ",lista->polinomio[i].coeficiente, lista->polinomio[i].expoente);
  }
  if(lista->ultimo == 0)
    printf("nulo");
  
  printf("\n%d", lista->ultimo);
}

void OrganizaPolinomio(TipoPolinomio *lista, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (lista->polinomio[j].expoente < lista->polinomio[j + 1].expoente) {
        TipoMonomio temp = lista->polinomio[j];
        lista->polinomio[j] = lista->polinomio[j + 1];
        lista->polinomio[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < n - 1; i++) {
    if (lista->polinomio[i].expoente == lista->polinomio[i + 1].expoente) {
      lista->polinomio[i].coeficiente += lista->polinomio[i + 1].coeficiente;
      lista->polinomio[i + 1].coeficiente = 0;
    }
  }

  int novo_n = 0;
  for (int i = 0; i < n; i++) {
    if (lista->polinomio[i].coeficiente != 0) {
      lista->polinomio[novo_n] = lista->polinomio[i];
      novo_n++;
    }
  }

  lista->ultimo = novo_n;

}