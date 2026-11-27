#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 12
#define INEXISTENTE -1

typedef struct {
    char fotocod[50]; 
    int avaliacao;    
    char legenda[50]; 
} REGISTRO;

typedef struct {
    REGISTRO r;
    int prox;
} ITEM;

typedef struct {
    ITEM itens[TAM];
    int inicio;
    int dispo;
} LISTA;

void inicializar(LISTA *l){

    l->inicio = INEXISTENTE;
    l->dispo = 0;

    for (int i = 0; i < TAM - 1; i++){
        l->itens[i].prox = i + 1;
    }
    l->itens[TAM - 1].prox = INEXISTENTE;
}

void inserir(LISTA *l, REGISTRO r) {
    if (l->dispo != INEXISTENTE) {
        int novo = l->dispo;
        l->dispo = l->itens[l->dispo].prox;

        if (l->inicio == INEXISTENTE) {
            l->inicio = novo;
        } else {
            int pos = l->inicio;
            int ant = INEXISTENTE;
            while (pos != INEXISTENTE) {
                ant = pos;
                pos = l->itens[pos].prox;
            }
            l->itens[ant].prox = novo;
        }
        l->itens[novo].r = r;
        l->itens[novo].prox = INEXISTENTE;
    } else {
        printf("Erro: Lista cheia!\n");
    }
}

void remover(LISTA *l, char fotocod[]) {
    int ant = INEXISTENTE;
    int pos = l->inicio;

    while (pos != INEXISTENTE && strcmp(l->itens[pos].r.fotocod, fotocod) != 0) {
        ant = pos;
        pos = l->itens[pos].prox;
    }
    if (pos == INEXISTENTE) return;

    if (ant == INEXISTENTE) {
        l->inicio = l->itens[pos].prox;
    } else {
        l->itens[ant].prox = l->itens[pos].prox;
    }

    // Adicionar à lista de disponíveis
    l->itens[pos].prox = l->dispo;
    l->dispo = pos;
}

void imprimir(LISTA *l){
    int pos = l->inicio;
    while(pos!=INEXISTENTE){
        printf("%s\n", l->itens[pos].r.fotocod);
	printf("%d\n", l->itens[pos].r.avaliacao);
	printf("%d\n", l->itens[pos].r.legenda);
        pos = l->itens[pos].prox;
    }
}

int main() {
    LISTA album;
    REGISTRO novaFoto;
    inicializar(&album);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar foto\n");
        printf("2. Remover foto\n");
        printf("3. Visualizar álbum\n");
        printf("4. Encerrar programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                if (album.dispo != INEXISTENTE) {
                    
                    printf("Digite o caminho da imagem: ");
                    scanf(" %s", novaFoto.fotocod);
                    printf("Digite a avaliação (de 0 a 5 estrelas): ");
                    scanf("%d", &novaFoto.avaliacao);
                    printf("Digite a legenda da foto: ");
                    scanf(" %s", novaFoto.legenda);
                    inserir(&album, novaFoto);
                    printf("Foto adicionada ao álbum.\n");
                } else {
                    printf("Erro: O álbum está cheio, não é possível adicionar mais fotos.\n");
                }
                break;
            }
            case 2: {
                char caminho[50];
                printf("Digite o caminho da imagem a ser removida: ");
                scanf(" %s", caminho);
                remover(&album, caminho);
                printf("Foto removida do álbum.\n");
                break;
            }
            case 3:
                imprimir(&album);
                break;
            case 4:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 4);

    return 0;
}