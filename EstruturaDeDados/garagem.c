#include<stdio.h>
#include<stdlib.h>

#define TAM 10

typedef struct{
    int apartamento;
    char placa[5];
} REGISTRO;

typedef struct{
    REGISTRO registros[TAM];
    int topo;
} PILHA;

void inicializarp(PILHA *p){
    p->topo = 0;
}
void empilhar(PILHA *p, REGISTRO r){
    if(p->topo < TAM){
        p->registros[p->topo] = r;
        p->topo++;
    }
    else{
        printf("pilha cheia");
    }
}
void desempilhar(PILHA *p){
    if(p->topo > 0){
        p->topo--;
    }
}
void imprimircarros(PILHA p, int pos){
    for(int i = p.topo - 1; i >= pos; i--){
        printf("%s\n", p.registros[i].placa);
        printf("%d\n", p.registros[i].apartamento);
    }
}
int main(){
    PILHA p;
    REGISTRO r;
    int escolha, pos;
    inicializarp(&p);
    do{
        printf("____________________________________\n");
        printf("1\tinserir carro\n");
        printf("2\tremover o ultimo carro\n");
        printf("3\timprimir carros\n");
        printf("____________________________________\n");
        printf("o que voce deseja fazer?\n");
        scanf("%d", &escolha);
        printf("\n");
        
        if(escolha ==1){
        printf("digite a placa do carro:\n");
        scanf("%s", &r.placa);
        printf("\n");
        printf("digite o apartamento:\n");
        scanf("%d", &r.apartamento);
        printf("\n");
        empilhar(&p, r);
        }
        else if(escolha==2){
            desempilhar(&p);
        }
        else if(escolha==3){
        printf("a posicao do carro:\n");
        scanf("%d", &pos);
        printf("\n");
            imprimircarros(p,pos);
        }
    }while(escolha != 0);
    
    
    return 0;
}
