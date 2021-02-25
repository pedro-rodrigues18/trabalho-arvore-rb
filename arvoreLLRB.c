#include "arvoreLLRB.h"

// Implementação dos métodos da Árvore Left Leaning Red Black Tree (Árvore Vermelho Preto Caída para Esquerda)
No* criarArvoreLLRB(){
    return NULL;
}
// Nó Vermelho é: True
// Nó Preto é   : False

// TODO ponteiro NULL é considerado Preto
bool retornaCorDoNo(No **no){
    if(*no == NULL)
        return false;
    else
        return (*no)->cor;
}

void trocaCorDoNo(No **no){
    (*no)->cor = !(*no)->cor;
    if((*no)->esq != NULL)
        (*no)->esq->cor = !(*no)->esq->cor;
    if((*no)->dir != NULL)
        (*no)->dir->cor = !(*no)->dir->cor;
}

No* rotacaoEsquerda(No **no){
    No *pai;
    pai = (*no)->dir;
    (*no)->dir = pai->esq;
    pai->esq = *no;
    pai->cor = (*no)->cor;
    (*no)->cor = true;
    
    return pai;
}

No* rotacaoDireita(No **no){
    No *pai;
    pai = (*no)->esq;
    (*no)->esq = pai->dir;
    pai->dir = *no;
    pai->cor = (*no)->cor;
    (*no)->cor = true;
    
    return pai;
}

No* move2EsqRed(No **no){
    trocaCorDoNo(no);
    if( retornaCorDoNo(&(*no)->esq->dir) == true){
        (*no)->dir = rotacaoDireita(&(*no)->dir);
        *no = rotacaoEsquerda(no);
        trocaCorDoNo(no);
    }
    return *no;
}

No* move2DirRed(No **no){
    trocaCorDoNo(no);
    if( retornaCorDoNo(&(*no)->esq->esq) == true){
        *no = rotacaoDireita(no);
        trocaCorDoNo(no);
    }
    return *no;
}

No* balacear(No **no){
    // Nó VERMELHO é sempre filho a ESQUERDA
    if(retornaCorDoNo(&(*no)->dir) == true)
        *no = rotacaoEsquerda(no);

    // Filho da direita e neto da esquerda são vermelhos
    if((*no)->esq != NULL && retornaCorDoNo(&(*no)->esq) == true && retornaCorDoNo(&(*no)->esq->esq) == true)
        *no = rotacaoDireita(no);

    //2 Filhos vermelhos: troca cor!
    if(retornaCorDoNo(&(*no)->esq) == true && retornaCorDoNo(&(*no)->dir) == true)
        trocaCorDoNo(no);
    
    return *no;
}

No* inserirNo(No **no, Registro r, int *resp){
    if(*no == NULL){
        No *novo;
        novo = (No*)malloc(sizeof(No));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->reg = r;
        novo->cor = true; // Todo No novo é vermelho
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    
    if(r.chave == (*no)->reg.chave)
        *resp = 0; // Valor duplicado
    else{
        if(r.chave < (*no)->reg.chave)
            (*no)->esq = inserirNo(&(*no)->esq, r, resp);
        else
            (*no)->dir = inserirNo(&(*no)->dir, r, resp);
    }

    if(retornaCorDoNo(&(*no)->dir) == true && retornaCorDoNo(&(*no)->esq) == false)
        *no = rotacaoEsquerda(no);
    
    if(retornaCorDoNo(&(*no)->esq) == true && retornaCorDoNo(&(*no)->esq->esq) == true)
        *no = rotacaoDireita(no);
    
    if(retornaCorDoNo(&(*no)->esq) == true && retornaCorDoNo(&(*no)->dir) == true)
        trocaCorDoNo(no);
    
    return *no;
}

int insereArvoreLLRB(No **raiz, Registro r){
    int resp;
    *raiz = inserirNo(raiz, r, &resp);

    if(raiz != NULL)
        (*raiz)->cor = false;
    
    return resp; 
}

No* procurarMenor(No **atual){
    No *no1 = *atual;
    No *no2 = (*atual)->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

No* removerMenor(No **aux){
    if((*aux)->esq == NULL){
        free(aux);
        return NULL;
    }
    if(retornaCorDoNo(&(*aux)->esq) == false && retornaCorDoNo(&(*aux)->esq->esq) == false){
        *aux = move2EsqRed(aux);
    }
    (*aux)->esq = removerMenor(&(*aux)->esq);
    return balacear(aux);
}

No* removerNo(No **no, Registro r){
    if(r.chave < (*no)->reg.chave){
        if(retornaCorDoNo(&(*no)->esq) == false && retornaCorDoNo(&(*no)->esq->esq) == false){
            (*no) = move2EsqRed(no);
        }
        (*no)->esq = removerNo(&(*no)->esq, r);
    }
    else{
        if(retornaCorDoNo(&(*no)->esq) == true){
            (*no) = rotacaoDireita(no);
        }
        if((r.chave == (*no)->reg.chave) && (&(*no)->dir == NULL)){
            free(no);
            return NULL;
        }
        if(retornaCorDoNo(&(*no)->dir) == false && retornaCorDoNo(&(*no)->dir->esq) == false){
            (*no) = move2DirRed(no);
        }
        if(r.chave == (*no)->reg.chave){
            No *x = procurarMenor(&(*no)->dir);
            (*no)->reg.chave = x->reg.chave;
            (*no)->dir = removerMenor(&(*no)->dir);
        }
        else{
            (*no)->dir = removerNo(&(*no)->dir, r);
        }
    }
    return balacear(no);
}

bool consulta(No **no, No **raiz, Registro r){
    bool aux = true;
    if(*no == NULL){
        printf("[ERROR]: Registro não encontrado!\n");
        return false;
    }
    if((*no)->reg.chave > r.chave){
        aux = consulta(&(*no)->esq, raiz, r);
        return aux;
    }
    if((*no)->reg.chave < r.chave)
    {
        aux = consulta(&(*no)->dir, raiz, r);
        return aux;
    }
    *raiz = *no;
    return aux;
}

int removerArvoreLLRB(No **no, Registro r){
    No *aux = criarArvoreLLRB();
    if(consulta(no, &aux, r)){
        No *no2 = *no;
        *no = removerNo(&no2, r);
        if(*no != NULL)
            (*no)->cor = false;
        return 1;
    }
    else
        return 0;
}

No* buscarNo(No **no, int chave){
    if(*no == NULL || (*no)->reg.chave == chave)
        return *no;

    if(chave > (*no)->reg.chave)
        return buscarNo(&(*no)->dir, chave);
    else
        return buscarNo(&(*no)->esq, chave);
}

void imprimirPreOrdem(No *no){
    if(!(no == NULL)){
        printf("%d ", no->reg.chave);
        imprimirPreOrdem(no->esq);
        imprimirPreOrdem(no->dir);
    }
}

void imprimirOrdemCentral(No *no){
    if(!(no == NULL)){
        imprimirPreOrdem(no->esq);
        printf("%d ", no->reg.chave);
        imprimirPreOrdem(no->dir);
    }
}

void imprimirPosOrdem(No *no){
    if(!(no == NULL)){
        imprimirPreOrdem(no->esq);
        imprimirPreOrdem(no->dir);
        printf("%d ", no->reg.chave);
    }
}