#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
    char *nome;
    float imc;
    struct Lista *prox;
    struct Lista *ant;
} lista;

typedef struct _Cab {
    struct Lista *head;
    int qtd;
} Cab;

void adicionar(Cab *cab);
void remover(Cab *cab);
void imprimir(Cab *cab);
void imprime_maior_menor(Cab *cab);
void desalocar(Cab *cab);

int main() {
    int menu = -1;
    Cab *cab = (Cab*) malloc(sizeof(Cab));
    cab->head = NULL;
    cab->qtd = 0;

    do {
        printf("\n1- Registrar\n2- Remover\n3- Mostrar lista\n");
        printf("4- Mostrar maior e menor imc\n5- Finalizar\nOpção: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                adicionar(cab);
                break;
            case 2:
                remover(cab);
                break;
            case 3:
                imprimir(cab);
                break;
            case 4:
                imprime_maior_menor(cab);
                break;
            case 5:
                desalocar(cab);
                break;
            default:
                printf("\nOpção inválida.\n");
                break;
        } 
    } while(menu != 5);

    return 0;
}

void adicionar(Cab *cab) {
    char nome[50];
    int peso;
    float altura;
    lista *novo = (lista*) malloc(sizeof(lista));
    lista *aux;

    printf("Nome: ");
    scanf("%s", nome);
    printf("Peso: ");
    scanf("%d", &peso);
    printf("Altura: ");
    scanf("%f", &altura);

    novo->nome = (char*) malloc(sizeof(char)*strlen(nome));
    strcpy(novo->nome, nome);
    novo->imc = (float) peso / (altura * altura);

    if(cab->head == NULL) {
        /* Primeiro elemento */
        novo->prox = novo;
        novo->ant = novo;
        cab->head = novo;
        cab->qtd++;
    } else if(strcmp(novo->nome, cab->head->nome) < 0) {
        /* Adicionar no início */
        novo->prox = cab->head;
        novo->ant = cab->head->ant;
        cab->head->ant = novo;
        novo->ant->prox = novo;
        cab->head = novo;
        cab->qtd++;
    } else if(strcmp(novo->nome, cab->head->ant->nome) > 0) {
        /* Adicionar no fim */
        novo->prox = cab->head;
        novo->ant = cab->head->ant;
        novo->ant->prox = novo;
        cab->head->ant = novo;
        cab->qtd++;
    } else {
        /* Insere no meio */
        aux = cab->head->prox;
        while(1) {
            if(strcmp(novo->nome, aux->nome)<=0) {
                novo->prox = aux;
                novo->ant = aux->ant;
                aux->ant = novo;
                novo->ant->prox = novo;
                cab->qtd++;
                break;
            }
            aux = aux->prox;
        }
    }
}

void remover(Cab *cab) {
    char nome[50];
    lista *aux = cab->head;
    int i;

    if(cab->head == NULL) {
        printf("\nLista vazia!\n");
    } else {
        printf("Nome para remover: ");
        scanf("%s", nome);
        if(strcmp(nome, aux->nome) == 0) {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            cab->head = aux->prox;
            cab->qtd--;
            free(aux->nome);
            free(aux);
        } else if(strcmp(nome, aux->ant->nome) == 0) {
            aux = aux->ant;
            aux->ant->prox = cab->head;
            cab->head->ant = aux->ant;
            cab->qtd--;
            free(aux->nome);
            free(aux);
        } else {
            aux = aux->prox;
            
            for(i=0; i<(cab->qtd-2); i++) {
                if(strcmp(nome, aux->nome) == 0) {
                    aux->ant->prox = aux->prox;
                    aux->prox->ant = aux->ant;
                    cab->qtd--;
                    free(aux->nome);
                    free(aux);
                    break;
                }
                aux = aux->prox;
            }
        }
    }
}

void imprimir(Cab *cab) {
    int i = 0;
    lista *aux = cab->head;
    
    if(cab->qtd == 0) {
        printf("\nLista vazia!");
    }
    printf("\n");
    for(i=0; i<cab->qtd; i++) {
        printf("Nome: %s - IMC: %0.2f\n", aux->nome, aux->imc);
        aux = aux->prox;
    }
    printf("\n");
}

void imprime_maior_menor(Cab *cab) {
    float maior = 0.0, menor = 99999.9;
    int i;
    lista *aux = cab->head, *pmaior, *pmenor;

    if(cab->head == NULL) {
        printf("\nLista Vazia!\n");
    } else {
        for(i=0; i<cab->qtd; i++) {
            if(aux->imc > maior) {
                pmaior = aux;
                maior = aux->imc;
            }
            if(aux->imc < menor) {
                pmenor = aux;
                menor = aux->imc;
            }

            aux = aux->prox;
        }

        printf("\nMaior imc: %s - IMC %.2f\n", pmaior->nome, pmaior->imc);
        printf("Menor imc: %s - IMC %.2f\n", pmenor->nome, pmenor->imc);
    }
}

void desalocar(Cab *cab) {
    int i;
    lista *aux = cab->head, *desaloca;

    for(i=0; i<cab->qtd; i++) {
        desaloca = aux;
        aux = aux->prox;
        free(desaloca->nome);
        free(desaloca);
    }

    free(cab);
}