#include <stdio.h>
#include <string.h>
#define TAMi 5
#define TAMj 13

void trocar( char a[], char b[]){
    char aux[TAMj];
    strcpy(aux, a);
    strcpy(a, b);
    strcpy(b, aux);
}
void bubbleSort(char v[][TAMj], int tam){
    for (int i = 0; i < tam - 1; i++){
        for (int j = 0; j < tam - i - 1; j++){
            if (strcmp(v[j], v[j+1]) > 0){
                trocar(v[j], v[j+1]);
            }
        }
    }
}

int main()
{
    char a[TAMi][TAMj]={"RONDONOPOLIS", "CUIABA","AMORINOPOLIS", "DIORAMA","BARRA"};

    bubbleSort(a, TAMi);

    for(int i=0;i<TAMi;i++){
        printf("%s \n", a[i]);
    }
    return 0;
}
