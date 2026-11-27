#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCARACTERES 144

typedef struct {
    char texto[MAXCARACTERES + 1];
    int id;
    char usuario[20];
} REGISTRO;

typedef struct item {
    REGISTRO r;
    struct item* prox;
} ITEM;

typedef struct {
    ITEM* inicio;
    int qtde;
} LISTA;

void inicializar(LISTA* l) {
    l->inicio = NULL;
    l->qtde = 0;
}

ITEM* criarItem(REGISTRO r) {
    ITEM* novo = (ITEM*)malloc(sizeof(ITEM));
    if (novo) {
        novo->r = r;
        novo->prox = NULL;
        return novo;
    }
    return NULL;
}

void inserir(LISTA *l, REGISTRO r){
    ITEM *novo = criarItem(r);
    
    ITEM *pos = l->inicio;
    ITEM *ant = NULL;
    while (pos){
        ant = pos;
        pos = pos->prox;
    }
    if (!ant){
        l->inicio = novo;
    }
    else{
        ant->prox = novo;
    }
    l->qtde++;
}

void remover(LISTA* l, int id) {
    if (!l->inicio) {
        printf("erro\n");
        return;
    }

    ITEM* pos = l->inicio;
    ITEM* ant = NULL;

    while (pos && pos->r.id != id) {
        ant = pos;
        pos = pos->prox;
    }

    if (!pos) {
        printf("Erro\n", id);
        return;
    }

    if (!ant) {
        l->inicio = l->inicio->prox;
    } else {
        ant->prox = pos->prox;
    }

    free(pos);
    l->qtde--;
}

void imprimir(LISTA *l){
    ITEM *pos = l->inicio;
    while (pos){
        printf("%s /n", pos->r.texto);
        pos = pos->prox;
    }
}

int main() {
    LISTA publicacoes;
    inicializar(&publicacoes);
    REGISTRO novaPublicacao;
    int opcao;
    int id = 1;
    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova publicação\n");
        printf("2. Visualizar minhas publicações\n");
        printf("3. Excluir uma publicação\n");
        printf("4. Encerrar programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                printf("Digite seu nome de usuário: ");
                scanf(" %s", novaPublicacao.usuario);
                fflush(stdin); 
                printf("Digite o texto da publicação: ", MAXCARACTERES);
                scanf(" %s", novaPublicacao.texto);

                
  
                novaPublicacao.id = id++;


                inserir(&publicacoes, novaPublicacao);
                printf("Publicação adicionada com sucesso.\n");
                break;
            }
            case 2: {
                imprimir(&publicacoes);
                break;
            }
            case 3: {
                printf("Digite o ID da publicação que deseja excluir: ");
                scanf("%d", &id);
                remover(&publicacoes, id);
                printf("Publicação removida com sucesso.\n");
                break;
            }
            case 4:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    }while(opcao != 4);

    return 0;
}