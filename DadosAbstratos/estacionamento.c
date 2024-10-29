#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char placa[10];
    char marca[15];
    char modelo[15];
    char cor[10];
    float horas;
}carros;

void cadastro(carros p[], int *a ){
    printf("digite a placa:");
    scanf("%s",p[*a].placa);
    printf("\n");
    getchar();
    printf("digite a marca:");
    scanf("%s",p[*a].marca);
    printf("\n");
    getchar();
    printf("digite o modelo:");
    scanf("%s",p[*a].modelo);
    printf("\n");
    getchar();
    printf("digite a cor:");
    scanf("%s",p[*a].cor);
    printf("\n");
    getchar();
    printf("digite as quantidade de horas que o carro ficou");
    scanf("%d",&p[*a].horas);
    (*a)++;
    printf("\n");
}
void calcular(carros p[], int pos){
    int total;
    total= p[pos].horas * 7.5;
    printf("o valor total ficou em %d",total);
}

void listar(carros p[], int *aux){

    for(int i=0;i<=*aux -1;i++){
        printf("\n%s\n",p[i].placa);
        printf("\n%s\n",p[i].marca);
        printf("\n%s\n",p[i].modelo);
        printf("\n%s\n",p[i].cor);
        printf("%d\n",p[i].horas);
        printf("id:%d\n",i);
        printf("----------------------------\n");
    }
}
void deletar(carros p[], int *aux, int posdel){
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
    carros c[10];
    int aux=0, escolha, pos;
    do{
    printf("____________________\n");
    printf("o que voce gostaria de fazer?\n");
    printf("1\tentrada de veiculos\n");
    printf("2\tcalcular tarifas\n");
    printf("3\tsaida veiculos\n");
    printf("4\tlistar os produtos\n");;
    printf("0\tfechar o programa\n");
    printf("____________________\n");
    scanf("%d",&escolha);



    switch(escolha)
    {
        case 1: 
        cadastro(c, &aux);
        break;

        case 2:
        printf("digite o id do carro:\n");
        scanf("%d", &pos);
        calcular(c,pos);
        break;

        case 3:
        printf("digite o id do carro:\n");
        scanf("%d", &pos);
        deletar(c, &aux, pos);
        break;


        case 4: 
        listar(c, &aux);
        break;
    }
    
    }while(escolha!=0);

    return 0;
}
