# Algoritmos e Estruturas de Dados 2

*Data structures coursework in C: a student enrollment system built on static linked lists, plus exercises on abstract data types, stacks, lists, sorting and files.*

Trabalhos da disciplina de Algoritmos e Estruturas de Dados 2 (UFMT, 2024), em C. O principal é o trabalho final, feito em grupo; os outros são exercícios de aula.

## Trabalho final: cadastro de alunos e matérias

[`trabalho-final/main.c`](trabalho-final/main.c) guarda alunos e matérias em **listas encadeadas estáticas** (vetor de itens com o índice do próximo e uma lista de posições livres). Pelo menu é possível:

- adicionar, remover e atualizar alunos (nome, RGA e curso) e matérias (nome, código, carga horária e horários na semana);
- matricular um aluno numa matéria, conferindo se o horário dele está livre;
- ordenar alunos e matérias por nome, em ordem crescente ou decrescente;
- mostrar a lista de presença de uma matéria e os horários livres de um aluno;
- salvar tudo em `dados.bin` ao sair e carregar de novo na próxima execução.

## Exercícios

| Pasta | Arquivo | O que é |
|---|---|---|
| `tipos-abstratos-de-dados/` | `estacionamento.c` | cadastro de carros, cálculo do valor a pagar, listagem e remoção |
| | `estoque.c` | cadastro de produtos, entrada no estoque, preço, listagem e remoção |
| `estruturas-de-dados/` | `album_de_fotos.c` | lista estática de fotos (código, avaliação e legenda) |
| | `garagem.c` | pilha de carros: entrar e sair da garagem |
| | `playlist.c` | pilha com desfazer e refazer |
| | `rede_social.c` | lista encadeada dinâmica (`malloc`/`free`) com menu |
| `algoritmos-de-ordenacao/` | `ordenacao_strings.c` | bubble sort de nomes |
| `manipulacao-de-arquivos/` | `lampada.c` | estado de lâmpadas e interruptores guardado num arquivo de texto |

## Como compilar

```bash
gcc trabalho-final/main.c -o cadastro
./cadastro
```

Os exercícios compilam do mesmo jeito (`gcc arquivo.c -o programa`). Todos foram conferidos com um compilador C recente. No `album_de_fotos.c`, a chamada `inicializarLista` foi trocada por `inicializar`, o nome da função definida no arquivo; antes ele não compilava.
