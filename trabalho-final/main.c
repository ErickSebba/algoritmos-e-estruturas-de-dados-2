#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATERIAS 10
#define TAM 15
#define INEXISTENTE -1
#define MAX_NOMES 50

typedef struct MAT{
    char nome[MAX_NOMES]; 
    int tempo; //9Carga horaria da materia
    int horariodisp[7];// cada posicao do vetor é um dia da semana    
    int codigo_materia;
} MATERIA;

typedef struct {
    char nome[MAX_NOMES]; 
    int rga; 
    char curso[MAX_NOMES];   
    MATERIA *materiascursando[MAX_MATERIAS];
} ALUNO;

typedef struct {  
    MATERIA m;
    ALUNO a;
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

void inserir_materia(LISTA *l, MATERIA m) {
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
        l->itens[novo].m = m;
        l->itens[novo].prox = INEXISTENTE;
    } else {
        printf("Erro: Lista cheia!\n");
    }
}

void inserir_aluno(LISTA *l, ALUNO a) {
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
        l->itens[novo].a = a;
        l->itens[novo].prox = INEXISTENTE;
    } else {
        printf("Erro: Lista cheia!\n");
    }
}

void remover_materia(LISTA *l, char nome[MAX_NOMES]) {
    int ant = INEXISTENTE;
    int pos = l->inicio;

    while (pos != INEXISTENTE && strcmp(l->itens[pos].m.nome, nome) != 0) {
        ant = pos;
        pos = l->itens[pos].prox;
    }
    if (pos == INEXISTENTE) return;

    if (ant == INEXISTENTE) {
        l->inicio = l->itens[pos].prox;
    } else {
        l->itens[ant].prox = l->itens[pos].prox;
    }

    l->itens[pos].prox = l->dispo;
    l->dispo = pos;
}

void remover_aluno(LISTA *l, char nome[MAX_NOMES]) {
    int ant = INEXISTENTE;
    int pos = l->inicio;

    while (pos != INEXISTENTE && strcmp(l->itens[pos].a.nome, nome) != 0) {
        ant = pos;
        pos = l->itens[pos].prox;
    }
    if (pos == INEXISTENTE) return;

    if (ant == INEXISTENTE) {
        l->inicio = l->itens[pos].prox;
    } else {
        l->itens[ant].prox = l->itens[pos].prox;
    }

    l->itens[pos].prox = l->dispo;
    l->dispo = pos;
}

void imprimir_lista_alunos(LISTA *l) {
    int pos = l->inicio;
    printf("Lista de Alunos Cadastrados:\n");
    printf("__________________________________________________\n");
    while (pos != INEXISTENTE) {
        printf("Nome: %s\n", l->itens[pos].a.nome);
        printf("RGA: %d\n", l->itens[pos].a.rga);
        printf("Curso: %s\n", l->itens[pos].a.curso);
        printf("Materias cursando:\n");
        if(l->itens[pos].a.materiascursando[0] == NULL) {
            printf("Nenhuma materia cursando.\n");
        } else {
            for (int i = 0; i < MAX_MATERIAS; i++) {
                if (l->itens[pos].a.materiascursando[i] != NULL) {
                    printf("%s\n", l->itens[pos].a.materiascursando[i]->nome);
                }
            }
        }
    
        pos = l->itens[pos].prox;
        printf("________________________________\n");
    }
    printf("__________________________________________________\n");
}

void imprimir_materia(LISTA *l){
    int pos = l->inicio;
    printf("Lista de Materias Cadastradas:\n");
    printf("______________________________________________________________\n");
    while(pos!=INEXISTENTE){
    printf("Nome:\t%s\n", l->itens[pos].m.nome);
	printf("Tempo da materia:\t%d\n", l->itens[pos].m.tempo);

    for(int i=0; i<7; i++){
        printf("____________________________\n");
        if(i==0) printf("segunda:\t");
        if(i==1) printf("terca:\t");
        if(i==2) printf("quarta:\t");
        if(i==3) printf("quinta:\t");
        if(i==4) printf("sexta:\t");
        if(i==5) printf("sabado:\t");
        if(i==6) printf("domingo:\t");

        if(l->itens[pos].m.horariodisp[i]==1) printf("7:30 as 9:30");
        if(l->itens[pos].m.horariodisp[i]==2) printf("9:30 as 11:30");
        if(l->itens[pos].m.horariodisp[i]==3) printf("13:30 as 15:30");
        if(l->itens[pos].m.horariodisp[i]==4) printf("15:30 as 17:30");
        if(l->itens[pos].m.horariodisp[i]==5) printf("7:30 as 11:30");
        if(l->itens[pos].m.horariodisp[i]==6) printf("13:30 as 17:30");
        
        printf("\n");
        printf("____________________________\n");
    }
    

	printf("Codigo da materia:\t%d\n", l->itens[pos].m.codigo_materia);
    printf("________________________________\n");
        pos = l->itens[pos].prox;
    }
    printf("\n");
    printf("______________________________________________________________\n");
}

int verifica_conflito_horario(MATERIA *materia1, MATERIA *materia2) {
    for (int i = 0; i < 7; i++) {
        // Verifica se há aula em ambos os horários para o dia i 
        if (materia1->horariodisp[i] == materia2->horariodisp[i]) {
            return 1; // Retorna 1 se houver conflito de horário
        }
        if ((materia1->horariodisp[i] == 1 || materia1->horariodisp[i] == 2) &&  materia2->horariodisp[i] == 5 ) {
            return 1; // Retorna 1 se houver conflito de horário
        }
        if ((materia1->horariodisp[i] == 3 || materia1->horariodisp[i] == 4) &&  materia2->horariodisp[i] == 6 ) {
            return 1; // Retorna 1 se houver conflito de horário
        }
        if ((materia2->horariodisp[i] == 1 || materia2->horariodisp[i] == 2) &&  materia1->horariodisp[i] == 5 ) {
            return 1; // Retorna 1 se houver conflito de horário
        }
        if ((materia2->horariodisp[i] == 3 || materia2->horariodisp[i] == 4) &&  materia1->horariodisp[i] == 6 ) {
            return 1; // Retorna 1 se houver conflito de horário
        }
    }
    return 0; // Retorna 0 se não houver conflito de horário
}

void pegarmateria(LISTA *a, LISTA *m, int rga_aluno, int codigo_materia) {
    int pos_aluno = a->inicio;
    int pos_materia = m->inicio;

    // Encontrar o aluno com o RGA especificado
    while (pos_aluno != INEXISTENTE) {
        if (a->itens[pos_aluno].a.rga == rga_aluno) {
            break;
        }
        pos_aluno = a->itens[pos_aluno].prox;
    }

    // Verificar se o aluno foi encontrado
    if (pos_aluno == INEXISTENTE) {
        printf("Aluno com RGA %d não encontrado.\n", rga_aluno);
        return;
    }

    while (pos_materia != INEXISTENTE) {
        if (m->itens[pos_materia].m.codigo_materia == codigo_materia) {
            break;
        }
        pos_materia = m->itens[pos_materia].prox;
    }
    if(pos_materia == INEXISTENTE){
        printf("Materia com codigo %d nao encontrada.\n", codigo_materia);
        return;
    }

    ALUNO *aluno = &a->itens[pos_aluno].a;
    MATERIA *materia = &m->itens[pos_materia].m;
    // Verificar se o aluno já está cursando a matéria
    for (int i = 0; i < MAX_MATERIAS; i++) {
        if (aluno->materiascursando[i] != NULL && aluno->materiascursando[i]->codigo_materia == materia->codigo_materia) {
            printf("O aluno ja esta cursando a materia %s.\n", materia->nome);
            return;
        }
    }

    // Verificar se há conflito de horário com outras matérias do aluno
    for (int i = 0; i < MAX_MATERIAS; i++) {
        if (aluno->materiascursando[i] != NULL && verifica_conflito_horario(aluno->materiascursando[i], materia)) {
            printf("Conflito de horario com a materia %s.\n", aluno->materiascursando[i]->nome);
            return;
        }
    }


    // Adicionar a matéria ao aluno
    for (int i = 0; i < MAX_MATERIAS; i++) {
        if (aluno->materiascursando[i] == NULL) {
            aluno->materiascursando[i] = materia;
            printf("Materia %s adicionada ao aluno %s.\n", materia->nome, aluno->nome);
            aluno->materiascursando[i+1] = NULL;
            return;
        }
    }

    printf("O aluno ja esta cursando o numero maximo de materias.\n");
}

void ordenar_alfabetico_aluno(LISTA *l) {
    int i, j, min;
    ITEM temp;

    for (i = l->inicio; i != INEXISTENTE; i = l->itens[i].prox) {
        min = i;
        for (j = l->itens[i].prox; j != INEXISTENTE; j = l->itens[j].prox) {
            if (strcmp(l->itens[j].a.nome, l->itens[min].a.nome) < 0) {
                min = j;
            }
        }
        // Trocar os itens da lista
        if (min != i) {
            temp = l->itens[i];
            l->itens[i] = l->itens[min];
            l->itens[min] = temp;

            // Trocar ponteiro 'prox' dos itens trocados
            int temp_prox = l->itens[i].prox;
            l->itens[i].prox = l->itens[min].prox;
            l->itens[min].prox = temp_prox;
        }
    }
    printf("Alunos ordenados por nome.\n");
}

void ordenar_alfabetico_aluno_decrescente(LISTA *l) {
    int i, j, max;
    ITEM temp;

    for (i = l->inicio; i != INEXISTENTE; i = l->itens[i].prox) {
        max = i;
        for (j = l->itens[i].prox; j != INEXISTENTE; j = l->itens[j].prox) {
            if (strcmp(l->itens[j].a.nome, l->itens[max].a.nome) > 0) {
                max = j;
            }
        }
        // Trocar os itens da lista
        if (max != i) {
            temp = l->itens[i];
            l->itens[i] = l->itens[max];
            l->itens[max] = temp;

            // Trocar ponteiro 'prox' dos itens trocados
            int temp_prox = l->itens[i].prox;
            l->itens[i].prox = l->itens[max].prox;
            l->itens[max].prox = temp_prox;
        }
    }
    printf("Alunos ordenados por nome em ordem decrescente.\n");
}

void ordenar_alfabetico_materia_decrescente(LISTA *l) {
    int i, j, max;
    ITEM temp;
    int temp_prox;

    for (i = l->inicio; i != INEXISTENTE; i = l->itens[i].prox) {
        max = i;
        for (j = l->itens[i].prox; j != INEXISTENTE; j = l->itens[j].prox) {
            if (strcmp(l->itens[j].m.nome, l->itens[max].m.nome) > 0) {
                max = j;
            }
        }
        
        if (max != i) {
            temp = l->itens[i];
            l->itens[i] = l->itens[max];
            l->itens[max] = temp;

            
            temp_prox = l->itens[i].prox;
            l->itens[i].prox = l->itens[max].prox;
            l->itens[max].prox = temp_prox;
        }
    }
    printf("Materias ordenadas por nome em ordem decrescente.\n");
}

void ordenar_alfabetico_materia(LISTA *l) {
    int i, j, min;
    ITEM temp;
    int temp_prox;

    for (i = l->inicio; i != INEXISTENTE; i = l->itens[i].prox) {
        min= i;
        for (j = l->itens[i].prox; j != INEXISTENTE; j = l->itens[j].prox) {
            if (strcmp(l->itens[j].m.nome, l->itens[min].m.nome) < 0) {
                min = j;
            }
        }
        
        if (min != i) {
            temp = l->itens[i];
            l->itens[i] = l->itens[min];
            l->itens[min] = temp;

            
            temp_prox = l->itens[i].prox;
            l->itens[i].prox = l->itens[min].prox;
            l->itens[min].prox = temp_prox;
        }
    }
    printf("Materias ordenadas por nome.\n");
}

void salvar_dados_arquivo(LISTA *a, LISTA *m) {
    FILE *arquivo = fopen("dados.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Salva os dados dos alunos no arquivo
    fwrite(a, sizeof(LISTA), 1, arquivo);

    // Salva os dados das matérias no arquivo
    fwrite(m, sizeof(LISTA), 1, arquivo);

    fclose(arquivo);
    printf("Dados salvos no arquivo dados.bin com sucesso.\n");
}

void carregar_dados_arquivo(LISTA *a, LISTA *m) {
    FILE *arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de dados não encontrado.\n");
        return;
    }

    // Lê os dados dos alunos do arquivo
    fread(a, sizeof(LISTA), 1, arquivo);

    // Lê os dados das matérias do arquivo
    fread(m, sizeof(LISTA), 1, arquivo);

    fclose(arquivo);
    printf("Dados lidos do arquivo dados.bin com sucesso.\n");
}


void atualizar_aluno(LISTA *l, char nome [MAX_NOMES], ALUNO anovo) {
    int ant = INEXISTENTE;
    int pos = l->inicio;

    while (pos != INEXISTENTE && strcmp(l->itens[pos].a.nome, nome) != 0) {
        ant = pos;
        pos = l->itens[pos].prox;
    }
    if (pos == INEXISTENTE) return;
    l->itens[ant].a = anovo;
    char nome_materia[MAX_NOMES];
    char confirmacao;
    
    do{
    printf("Voce deseja remover uma materia %s? (s/n): \n", nome_materia);
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        printf("Digite o nome da materia que deseja remover:\n");
            scanf("%s", nome_materia);
        for (int i = 0; i < MAX_MATERIAS; i++) {
            if (strcmp(l->itens[ant].a.materiascursando[i]->nome, nome_materia) == 0) {
                // Remover a matéria
                for (int j = i; j < MAX_MATERIAS - 1; j++) {
                    l->itens[ant].a.materiascursando[j] = l->itens[ant].a.materiascursando[j + 1];
                }
                l->itens[ant].a.materiascursando[MAX_MATERIAS - 1] = NULL;
                printf("Materia %s removida com sucesso!\n", nome_materia);
                return;
            }
        }
        printf("Materia %s nao encontrada!\n", nome_materia);
    } else {
        printf("Remocao cancelada.\n");
    }
    } while (confirmacao == 's' || confirmacao == 'S');
}
void atualizar_materia(LISTA *lista_materias, char nome[MAX_NOMES], MATERIA mnovo) {
    int pos = lista_materias->inicio;

    while (pos != INEXISTENTE) {
        if (strcmp(lista_materias->itens[pos].m.nome, nome) == 0) {
            lista_materias->itens[pos].m = mnovo;
            return;
        }
        pos = lista_materias->itens[pos].prox;
    }
}

void mostrar_disponibilidade_de_horario(LISTA *lista, int rga){
    int pos = lista->inicio;
    while (pos != INEXISTENTE && lista->itens[pos].a.rga != rga) { // Encontrar o aluno com o RGA especificado
        pos = lista->itens[pos].prox;
    }
    if (pos == INEXISTENTE) {
        printf("Aluno nao encontrado.\n");
        return;
    }
    ALUNO *aluno = &lista->itens[pos].a;
    int horarios_possiveis[7][7] = {0}; // Matriz para armazenar os horários possíveis do aluno
    for (int i = 0; aluno->materiascursando[i] != NULL; i++) {// Verificar os horários das matérias que o aluno está cursando
        for (int j = 0; j < 7; j++) {// Verificar os horários disponíveis para cada dia da semana
                if (aluno->materiascursando[i]->horariodisp[j] != 0) {// Se o horário não for livre, marcar como indisponível
                    horarios_possiveis[j][aluno->materiascursando[i]->horariodisp[j]] = 1; 
                }
            
        }
    }
    printf("Horarios disponiveis do aluno com RGA %d:\n", rga);
    char *dias_semana[7] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"};
    char *horarios[7] = {"Indisponível", "7:30 as 9:30", "9:30 as 11:30", "13:30 as 15:30", "15:30 as 17:30", "7:30 as 11:30", "13:30 as 17:30"};
    for (int i = 0; i < 7; i++) {
        printf("%s:\n", dias_semana[i]);
        for (int j = 0; j < 7; j++) {
            if (horarios_possiveis[i][j] == 1) {
                printf("Horário %s: Disponivel\n", horarios[j]);
            } else {
                printf("Horário %s: Indispoivel\n", horarios[j]);
            }
        }
    }
}

void imprimir_lista_presenca(LISTA *lista_alunos, char nome_materia[MAX_NOMES]) {
    int posicao_atual = lista_alunos->inicio;

    printf("Lista de Presenca para a Materia %s:\n", nome_materia);
    printf("-------------------------------------------------\n");
    printf("Alunos Presentes:\n");

    while (posicao_atual != INEXISTENTE) {
        ALUNO *aluno = &(lista_alunos->itens[posicao_atual].a);

        // Verificar se o aluno está cursando a matéria desejada
        for (int i = 0; i < MAX_MATERIAS; i++) {
            if (aluno->materiascursando[i] != NULL && strcmp(aluno->materiascursando[i]->nome, nome_materia) == 0) {
                // Se o aluno está cursando a matéria, imprimir seu nome
                printf("%s\n", aluno->nome);
                break;
            }
        }

        posicao_atual = lista_alunos->itens[posicao_atual].prox;
    }

    printf("-------------------------------------------------\n");
}

int main() {

    
    LISTA alunos, materias;
    ALUNO aluno;
    MATERIA materia;
    char nome_materia[MAX_NOMES];
    char nome_aluno[MAX_NOMES];
    int rga, opcao;

    inicializar(&alunos);
    inicializar(&materias);

    carregar_dados_arquivo(&alunos,&materias);
    

        //inserir_materia(&materias, (MATERIA){"AED2 VE1\n", 64, 1, 0, 0, 0, 1, 0, 0, 0004});

        //inserir_aluno(&alunos, (ALUNO){"Daniel Zamarioli\n", 1001, "EngComp", {NULL}});

    do {
        printf("______________________________________________________________\n");
        printf("************************************\n");
        printf("*                                  *\n");
        printf("*               MENU               *\n");
        printf("*                                  *\n");
        printf("************************************\n");
        printf("______________________________________________________________\n");
        printf("1. Adicionar um aluno\n");
        printf("2. Remover um aluno\n");
        printf("3. Adicionar uma materia\n");
        printf("4. Remover uma materia\n"); 
        printf("5. Atualizar dados de um aluno\n");
        printf("6. Atualizar dados de uma materia\n"); 
        printf("7. Tentar pegar uma materia\n");  
        printf("8. Ordenar alunos por nome(crescente ou decrescente)\n");
        printf("9. Ordenar materias por nome(crescente ou decrescente)\n");
        printf("10. Imprimir a lista de presenca de uma certa materia\n");
        printf("11. Imprimir alunos\n");
        printf("12. Imprimir materias\n");
        printf("13. Mostrar a disponibilidade de horario de um certo aluno\n");
        printf("14. Sair\n");
        printf("______________________________________________________________\n");
        printf("Escolha a opcao: ");

        fflush(stdin);
        scanf("%d", &opcao);
        getchar();
        switch (opcao) {
        case 1:

        printf("Digite o nome do aluno: ");
        fgets(aluno.nome, MAX_NOMES, stdin);
        printf("Digite o RGA do aluno: ");
            scanf("%d", &aluno.rga);
            getchar();
        printf("Digite o curso do aluno: ");
            fgets(aluno.curso, MAX_NOMES, stdin);
            getchar();
            for(int j=0;j<MAX_MATERIAS;j++){
                aluno.materiascursando[j] = NULL;
                }
            inserir_aluno(&alunos, aluno);
                break;

            case 2: 
                printf("Digite o nome do aluno a ser removido\n");
                fgets(nome_aluno, MAX_NOMES, stdin);
                getchar();
                remover_aluno(&alunos, nome_aluno);
                printf("\n");
                printf("aluno removido.\n");
                break;
            case 3: 
            printf("Digite o nome da materia: ");
            fgets(materia.nome, MAX_NOMES, stdin);
            getchar();

            printf("Digite o tempo de duracao da materia (em horas): ");
            scanf("%d", &materia.tempo);

              printf("Digite o codigo da materia: ");
              scanf("%d", &materia.codigo_materia);

             printf("Digite os horarios disponiveis para a materia (segunda a domingo):\n");
             printf("0. livre\n");
             printf("1. 7:30 as 9:30\n");
             printf("2. 9:30 as 11:30\n");
             printf("3. 13:30 as 15:30\n");
             printf("4. 15:30 as 17:30\n");
             printf("5. 7:30 as 11:30\n");
             printf("6. 13:30 as 17:30\n");
            for (int i = 0; i < 7; i++) {
                        if(i==0) printf("segunda\t");
                        if(i==1) printf("terca\t");
                        if(i==2) printf("quarta\t");
                        if(i==3) printf("quinta\t");
                        if(i==4) printf("sexta\t");
                        if(i==5) printf("sabado\t");
                        if(i==6) printf("domingo\t");
                scanf("%d", &materia.horariodisp[i]);
            }

            inserir_materia(&materias, materia);
            printf("materia adicionada.\n");

            break;
        
        case 4: 
            printf("Digite o nome da materia a ser removido\n");
            fgets(nome_materia, MAX_NOMES, stdin);
            getchar();
            remover_materia(&materias, nome_materia);
            printf("materia removida.\n");
            break;
        
        case 5:
            printf("Digite o nome do aluno a ser atualizado: ");
            fgets(nome_aluno, MAX_NOMES, stdin);
            getchar();
            printf("Digite o novo nome do aluno: ");
            fgets(aluno.nome, MAX_NOMES, stdin);
            getchar();
                printf("Digite o novo RGA do aluno: ");
                scanf("%d", &aluno.rga);
                printf("Digite o novo curso do aluno: ");
                fgets(aluno.curso, MAX_NOMES, stdin);
                getchar();
                
                 atualizar_aluno(&alunos, nome_aluno, aluno);
                 printf("aluno atualizado.\n");
                break;
            case 6: 

                printf("Digite o nome da materia a ser atualizado: ");
                fgets(nome_materia, MAX_NOMES, stdin);
                getchar();

                printf("Digite o novo nome da materia: ");
                fgets(materia.nome, MAX_NOMES, stdin);
                getchar();
                printf("Digite o novo tempo de duracao da materia (em horas): ");
                scanf("%d", &materia.tempo);
                printf("Digite o novo codigo da materia: ");
                scanf("%d", &materia.codigo_materia);
                printf("Digite os novos horarios disponiveis para a materia (segunda a domingo):\n");
                printf("0. livre\n");
                printf("1. 7:30 as 9:30\n");
                printf("2. 9:30 as 11:30\n");
                printf("3. 13:30 as 15:30\n");
                printf("4. 15:30 as 17:30\n");
                printf("5. 7:30 as 11:30\n");
                printf("6. 13:30 as 17:30\n");
                for (int i = 0; i < 7; i++) {
                        if(i==0) printf("segunda\t");
                        if(i==1) printf("terca\t");
                        if(i==2) printf("quarta\t");
                        if(i==3) printf("quinta\t");
                        if(i==4) printf("sexta\t");
                        if(i==5) printf("sabado\t");
                        if(i==6) printf("domingo\t");
                    scanf("%d", &materia.horariodisp[i]);
                }
                printf("TESTE\n");
                atualizar_materia(&materias, nome_materia, materia);
                printf("materia atualizada.\n");
                break;

            case 7:
            printf("Digite o rga do nome do aluno:\n ");
            scanf("%d", &rga);
            printf("Digite o codigo da materia:\n ");
            scanf("%d", &materia.codigo_materia);

            pegarmateria(&alunos, &materias, rga, materia.codigo_materia);
                break;
            case 8:
            printf("escolha o tipo de ordenacao:\n");
            printf("1. Crescente\n");
            printf("2. Decrescente\n");
            do{
                printf("Escolha a opcao: ");
                scanf("%d", &opcao);
                printf("%d", opcao);
            }while(opcao != 1 && opcao != 2);
            if(opcao == 1){
                ordenar_alfabetico_aluno(&alunos);
                printf("teste\n");
            } else {
                ordenar_alfabetico_aluno_decrescente(&alunos);
            }
                break;

            case 9:
            printf("escolha o tipo de ordenacao:\n");
            printf("1. Crescente\n");
            printf("2. Decrescente\n");
            do{
                printf("Escolha a opcao: ");
                scanf("%d", &opcao);
            }while(opcao != 1 && opcao != 2);
            if(opcao == 1){
                ordenar_alfabetico_materia(&materias);
                
            } else {
                ordenar_alfabetico_materia_decrescente(&materias);
                
            }
                break;

            case 10:
                printf("Digite o nome da materia: ");   
                fgets(nome_materia, MAX_NOMES, stdin);
                getchar();
                imprimir_lista_presenca(&alunos, nome_materia);   
                break;

            case 11:
                imprimir_lista_alunos(&alunos);
                break;

            case 12:
                imprimir_materia(&materias);
                break;
            case 13:
                printf("Digite o RGA do aluno: ");  
                scanf("%d", &rga);
                mostrar_disponibilidade_de_horario(&alunos, rga);
                break;

            case 14:
                salvar_dados_arquivo(&alunos,&materias);
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 14);//while para encerrar o programa
    return 0;
}
//AUTORES DO CODIGO: ERICK SEBBA, TEO MATOS, DANIEL ZAMARIOLI