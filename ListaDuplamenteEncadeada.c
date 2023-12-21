/*
Caso o ruído encontrado esteja localizado no meio da lista e ambas as substrings vizinhas
possuem tamanho maior ou igual a 2 caracteres.
 
Caso o ruído seja encontrado na primeira posição da string de entrada, deve-se considerar
apenas o substring vizinho da direita.
 
Caso o ruído seja encontrado na última posição da string de entrada, deve-se considerar
apenas o substring vizinho da esquerda.
*/
 
#include <stdio.h>
#include <stdlib.h>
 
typedef struct TipoItem{
  char letra;
  int tamanho;
  struct TipoItem *ant, *prox;
}TipoItem;
 
typedef struct{
  TipoItem *inicio, *fim;
}ListaDE;
 
void inicializarListaDE(ListaDE *lista){
    lista->inicio = NULL;
    lista->fim    = NULL;
}
 
int ListaVazia(ListaDE *lista){
  if(lista->inicio == NULL && lista->fim == NULL)
    return 1;
  return 0;
}
 
void Insere(ListaDE *lista, TipoItem *novo){
  
  TipoItem *novoNo = malloc(sizeof(TipoItem));
  novoNo->letra = novo->letra;
  novoNo->tamanho = novo->tamanho;
  
  if(ListaVazia(lista)){
    lista->inicio = novoNo;
    lista->fim = novoNo;
    novoNo->ant = NULL;
    novoNo->prox = NULL;
  }
  else{
    lista->fim->prox = novoNo;
    novoNo->ant = lista->fim;
    novoNo->prox = NULL;
    lista->fim = novoNo;
  }
}
 
int Contagem(ListaDE *lista) {
  int size = 0;
  TipoItem *temp = lista->inicio;
 
  while(temp != NULL){
    if(temp->tamanho / 10 < 1){
      size += 2;
    } 
    else{
      if(temp->tamanho / 10 < 10){
        size += 3;
      }
      else{
        size += 4;
      }
    }
    temp = temp->prox;
  }
  return size;
}
 
void ImprimeString(ListaDE *lista) {
  TipoItem *temp = lista->inicio;
  while(temp != NULL){
    printf("%d%c", temp->tamanho, temp->letra);
    temp = temp->prox;
  }
}
 
void RemoverRuido(ListaDE* lista){
  TipoItem *temp = lista->inicio;
  
  while(temp != NULL){
    if(temp->tamanho == 1){
      if(temp->ant == NULL){
        if(temp->prox->tamanho > 1){
          temp->prox->tamanho++;
          lista->inicio = temp->prox;
          temp->prox->ant = NULL;
        }
      }
      else{
        if(temp->prox == NULL){
          if(temp->ant->tamanho > 1){
            temp->ant->tamanho++;
            lista->fim = temp->ant;
            temp->ant->prox = NULL;
          }
        }
        else{
          if(temp->ant->tamanho > 1 && temp->prox->tamanho > 1){
            temp->ant->prox = temp->prox;
            temp->prox->ant = temp->ant;
            if(temp->ant->tamanho == temp->prox->tamanho){
              temp->ant->tamanho++;   
            }
            else{
              if(temp->ant->tamanho > temp->prox->tamanho){
                temp->ant->tamanho++;
              }
              else{
                temp->prox->tamanho++;
              }
            }
          }
        }
      }
    }
    temp = temp->prox;
  }
}
 
 
 
int main(){
  ListaDE lista;
  TipoItem item;
  char string[1024];
  
  scanf("%s", string);
  
  inicializarListaDE(&lista);
 
  int count = 1;
 
  for(int i=0; string[i] != '\0'; i++){
    if(string[i] == string[i+1]){
      count++;
    }
    else{
      item.tamanho = count;
      item.letra = string[i];
      Insere(&lista, &item);
      count = 1;
    }
  }
 
  printf("%d\n", Contagem(&lista));
  ImprimeString(&lista);
  printf("\n");
 
  RemoverRuido(&lista);
  printf("%d\n", Contagem(&lista));
  ImprimeString(&lista);
  
  TipoItem *current = lista.inicio; 
  
  while(current != NULL){
    TipoItem *temp = current;
    current = current->prox;
    free(temp);
  }
  
  return 0;
}
