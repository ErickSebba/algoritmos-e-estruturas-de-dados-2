#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[25];
    float preco;
    int quantidade;
}produtos;

void cadastro(int *a, produtos p[]){
    printf("digite o nome do produto ");
    scanf("%s",p[*a].nome);
    printf("\n");
    printf("digite o preco ");
    scanf("%f",&p[*a].preco);
    printf("\n");
    printf("digite a quantidade ");
    scanf("%d",&p[*a].quantidade);
    (*a)++;
    printf("\n");
}
void estoque(produtos p[]){
    int num, estoque;
    printf("digite o ID do produto");
    scanf("%d", num);
    printf("qual o novo estoque?");
    scanf("%d", estoque);
    p[num].quantidade=estoque;
}
void preco(produtos p[]){
    int num;
    float valor;
    printf("digite o ID do produto");
    scanf("%d", num);
    printf("qual o novo estoque?");
    scanf("%f", valor);
    p[num].preco=valor;
}
void listar(produtos p[], int *aux){

    for(int i=0;i<=*aux -1;i++){
        printf("\n%s\n",p[i].nome);
        printf("R$%.2f\n",p[i].preco);
        printf("%d unidades\n",p[i].quantidade);
        printf("id:%d\n",i);
        printf("----------------------------\n");
    }
}
void deletar(produtos p[], int *aux, int posdel){
    if(posdel<*aux){
        for(int i=posdel; i < *aux -1;i++){
            p[i]=p[i+1];
        }
        (*aux)--;
    }
    else{
        printf("posicao invalida");
    }


}

int main()
{
    produtos p[10];
    int aux=0, escolha, pos;
    do{
    printf("____________________\n");
    printf("o que voce gostaria de fazer?\n");
    printf("1\tcadastrar produto\n");
    printf("2\tatualizar estoque\n");
    printf("3\tatualizar preco\n");
    printf("4\tlistar os produtos\n");
    printf("5\texcluir produtos\n");
    printf("0\tfechar o programa\n");
    printf("____________________\n");
    scanf("%d",&escolha);



    switch(escolha)
    {
        case 1: 
        cadastro(&aux,p);
        break;

        case 2:
        estoque(p);
        break;

        case 3:
        preco(p);
        break;

        case 4:
        listar(p, &aux);
        break;

        case 5: printf("digite o id do produto:\n");
        scanf("%d", &pos);
        deletar(p, &aux, pos);
        break;
    }
    
    }while(escolha!=0);

    return 0;
}