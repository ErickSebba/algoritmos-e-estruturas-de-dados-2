#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char musica[20];
} REGISTRO;

typedef struct item {
    REGISTRO r;
    struct item *ant;
} ITEM;

typedef struct {
    ITEM *topo;
    int tam;
} PILHA;

void inicializarPilha(PILHA *p) {
    p->topo = NULL;
    p->tam = 0;
}

ITEM* criarItem(REGISTRO r) {
    ITEM* novo = (ITEM*) malloc(sizeof(ITEM));
    if (novo) {
        novo->r = r;
        novo->ant = NULL;
        return novo;
    }
    return NULL;
}

void empilhar(PILHA *p, REGISTRO r) {
    ITEM* novo = criarItem(r);
    if (novo) {
        novo->ant = p->topo;
        p->topo = novo;
        p->tam++;
    } else {
        printf("Erro\n");
    }
}

void desempilhar(PILHA *p) {
    if (p->topo) {
        ITEM* temp = p->topo;
        p->topo = p->topo->ant;
        free(temp);
        p->tam--;
    } else {
        printf("Pilha vazia.\n");
    }
}

void refazer(PILHA *p, PILHA *p2) {
    if (p2->topo) {
        empilhar(p, p2->topo->r);
        desempilhar(p2);
    } else {
        printf("Erro\n");
    }
}

void desfazer(PILHA *p, PILHA *p2) {
    if (p->topo) {
        empilhar(p2, p->topo->r);
        desempilhar(p);
    } else {
        printf("Erro\n");
    }
}

void imprimir(PILHA *p) {
    ITEM* pos = p->topo;
    while (pos) {
        printf("%s\n", pos->r.musica);
        pos = pos->ant;
    }
}

int main() {
    PILHA p, p2;
    inicializarPilha(&p);
    inicializarPilha(&p2);

    empilhar(&p, (REGISTRO){"mus1"});
    empilhar(&p, (REGISTRO){"mus2"});
    empilhar(&p, (REGISTRO){"mus3"});
    empilhar(&p, (REGISTRO){"mus4"});

    printf("Playlist original:\n");
    imprimir(&p);

    printf("\n_____________________________\n");
    desfazer(&p, &p2);
    printf("Após desfazer\n");
    imprimir(&p);

    printf("\n_____________________________\n");
    refazer(&p, &p2);
    printf("Após refazer\n");
    imprimir(&p);

    return 0;
}