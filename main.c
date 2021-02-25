/* Árvore Left Leaning Red Black Tree (Árvore Vermelho Preto Caída para Esquerda)
** Aluno: Pedro Henrique Rodrigues Pereira
*/
#include "arvoreLLRB.h"

#define N 5 // Quantidade de Onibus cadastrado

void menu(){
    printf("\n------- SISTEMA DE CADASTRO E CONSULTA DAS ROTAS DOS ÔNIBUS DA CIDADE -------\n\n");
    printf("[1] - Pesquisar rota de um ônibus.\n");
    printf("[2] - Deletar rota de um ônibus.\n");
    printf("[3] - Imprimir em Pos Ordem os ônibus cadastrados\n");
    printf("[4] - Imprimir em Ordem Central os ônibus cadastrados\n");
    printf("[5] - Imprimir em Pré Ordem os ônibus cadastrados\n");
    printf("[0] - Sair do programa.\n");
    printf(">> ");
}


int main(){
    
    No *raiz = criarArvoreLLRB();
	No *aux = criarArvoreLLRB();
    Registro r;
    //Número do õnibus
	int numeroOnibus[] = {2, 13, 23, 3, 11};
    char *rotas[] = {"Danilo Passos - Bela Vista", "Vila Romana - Belvedere", "Danilo Passos - Cacoco", "Santa Tereza - Jardim das Acacias", "Tiete - Vila das Roseiras"};// Rotas dos ônibus
    int op = 0;
    int numeroDoOnibus = 0;
    No *onibus;

    for(int i=0; i<N; i++){
        r.chave = numeroOnibus[i];
        r.valor = rotas[i];
        insereArvoreLLRB(&raiz, r);
    }

    do{
        menu();
        scanf("%d", &op);
        printf("\n");
        switch(op){
            case 1:
                printf("Pesquisar rota de um ônibus.\n");
                printf("Insira o número do ônibus: ");
                scanf("%d", &numeroDoOnibus);
                onibus = buscarNo(&raiz, numeroDoOnibus);
                if(onibus != NULL)
                    printf("Rota do ônibus %d: %s\n", onibus->reg.chave, onibus->reg.valor);
                else
                    printf("Ônibus não cadastrado.\n");
                break;
            case 2:
                printf("Deletar ônibus do cadastro.\n");
                printf("Insira o número do ônibus que deseja deletar: ");
                scanf("%d", &numeroDoOnibus);
                onibus = buscarNo(&raiz, numeroDoOnibus);
                if(onibus != NULL){
                    r.chave = onibus->reg.chave;
                    r.valor = onibus->reg.valor;
                    removerArvoreLLRB(&raiz, r);
                    printf("Ônibus %d removido com sucesso!\n", onibus->reg.chave);
                }
                else
                    printf("Ônibus não está cadastrado.\n");
                break;
            case 3:
                printf("Imprimir em pos ordem os ônibus cadastrados.\n");
                imprimirPosOrdem(raiz);
                printf("\n");
                break;
            case 4:
                printf("Imprimir em ordem central os ônibus cadastrados.\n");
                imprimirOrdemCentral(raiz);
                printf("\n");
                break;
            case 5:
                printf("Imprimir em pré ordem os ônibus cadastrados.\n");
                imprimirPreOrdem(raiz);
                printf("\n");
                break;
            case 0:
                printf("Saindo... Programa encerrado com sucesso!\n");
                return 0;
                break;
            default:
                printf("[ERRO] - Opção inválida.\n");
                break;
        }
    }while(true);

    return 0;
}

