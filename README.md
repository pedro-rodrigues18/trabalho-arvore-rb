# Trabalho utilizando Árvore Rubro Negra

## Descrição
Trabalho proposto na disciplina de Algoritmos e Estrutura de Dados II, CEFET-MG campus Divinópolis, no qual foi implementado uma Árvore Vermelho-Preto (Rubro Negra)
onde é armazenado o código (número) de um ônibus e a rota deste õnibus de um ponto hipotético A a B.

## Um pouco sobre Árvores Vermelho e Preto
A árvore rubro negra (também conhecida como vermelho-preto ou red-black) é um tipo de árvore binária balanceada. A árvore rubro negra utiliza-se de um esquema de coloração 
de seus nós para manter o balancemanto da árvore.

A árvore foi originalmente criada por Rudolf Bayer em 1972, chamadas árvores binárias simétricas. Posteriormente, ela adiquiriu seu nome atual. A árvore rubro negra possui esse
nome porque cada um de seus nós podem ser <b><i>vermelho</i></b> ou <b><i>preto</i></b>.

Ela é complexa, mas tem um bom pior-caso de tempo de execução para suas operações e é eficiente na prática: pode-se buscar, inserir, e remover em tempo O(log n), onde n é o 
número total de elementos da árvore.

Além disso, a árvore deve satisfazer o seguinte conjunto
de propriedades:

1. Todo nó da árvore é <b>VERMELHO</b> ou <b>PRETO</b>.
2. A raiz é sempre <b>PRETA</b>.
3. Todo nó folha <b>(NULL)</b> é <b>preto</b>.
4. Se um nó é <b>VERMELHO</b> então os seus filhos são <b>PRETO</b>.
5. Para cada nó, todos os os caminhos deste nó para os nós folhas descendentes contêm o mesmo número de nós <b>PRETO</b>.

## Rotação
Uma rotação é uma operação realizada na árvore para garantir seu balanceamento. Na rubro-negra pode ser feita a direita e a esquerda, onde são alterados os nodos rotacionados.

## Inserções
Ao inserir-se um elemento em uma árvore rubro-negra, esta é comparada com os elementos e alocada em sua posição conforme a regra de que a cada novo nodo inserido na árvore 
obedecerá o esquema de menor para o lado esquerdo e maior para o lado direito. Ao inserir um elemento ele é sempre da cor vermelha (exceto se for o nodo raiz). A seguir a árvore
analisa se o antecessor da folha. Se este for vermelho será necessário alterar as cores para garantir a regra 5.

## Inserção implementada em C
```
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
```
## Remoção
Com as operações de rotação e alteração de cor, remove-se o nó e estabelece-se as propriedades da árvore. Caso a remoção efetiva seja de um nó vermelho, esta é realizada sem 
problemas, pois todas as propriedades da árvore se manterão intactas. Se o nó a ser removido for preto, a quantidade de nós pretos em pelo menos um dos caminhos da árvore foi 
alterado, o que implica que algumas operações de rotação e/ou alteração de cor sejam feitas para manter o balanceamento da árvore.

## Remoção implementada em C
```
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
```


## Baixando o repositório
```bash
# Clone este repositório
$ git clone https://github.com/pedro-rodrigues18/trabalho-arvore-rb.git
```

## Compilando o código
É necessário ter o compilador de C (gcc) instalado na máquina.

Com os três arquivos (arvoreLLRB.c, arvoreLLRB.h main.c) dentro de uma pasta, abra o terminal dentro da pasta dos arquivos e execute:
```
$ gcc arvoreLLRB.c main.c -o run
$ ./run
```
## Referência
[Algoritmos - Teoria e Prática 3ªed - Capítulo 13](https://www.amazon.com.br/Algoritmos-Teoria-Pr%C3%A1tica-Thomas-Cormen/dp/8535236996).

[Estrutura de Dados descomplicada em linguagem C](https://www.amazon.com.br/Estrutura-Dados-Descomplicada-Linguagem-Backes/dp/8535285237).

[Wikpédia: Árvore rubro-negra](https://pt.wikipedia.org/wiki/%C3%81rvore_rubro-negra).

[Red-Black Tree](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/).
