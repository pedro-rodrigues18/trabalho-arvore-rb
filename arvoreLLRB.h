#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Registro Registro;
typedef struct No No;

struct Registro{
    int chave;
    char *valor;
};

struct No{
    Registro reg;
    No *esq, *dir;
    bool cor; // cor = true Vermelhor | cor = false Preto
};

// Definição do métodos para manipular a Árvore Left Leaning Red Black Tree
No* criarArvoreLLRB();
void pesquisarNaArvoreLLRB(No **no, No **aux, Registro r);
bool retornaCorDoNo(No **no);
void trocaCorDoNo(No **no);
No* rotacaoEsquerda(No **no);
No* rotacaoDireita(No **no);
No* move2EsqRed(No **no);
No* move2DirRed(No **no);
No* balacear(No **no);
No* inserirNo(No **no, Registro r, int *resp);
int insereArvoreLLRB(No **raiz, Registro r);
No* removerNo(No **no, Registro r);
No* removerMenor(No **aux);
int removerArvoreLLRB(No **no, Registro r);
No* procurarMenor(No **aux);
bool consulta(No **aux, No **raiz, Registro r);
No* buscarNo(No **no, int chave);
void imprimirPreOrdem(No *no);
void imprimirOrdemCentral(No *no);
void imprimirPosOrdem(No *no);