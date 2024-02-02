#include <stdio.h>
#include <stdlib.h>
typedef struct no{
    int valor;
    struct no *esquerdo, *direito;
    short altura;
}No;

No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo ->valor = x;
        novo ->esquerdo = 0;
        novo ->direito = 0;
        novo ->altura = 0;
    }
    else
    printf("\nERRO ao alocar nó em novoNo!\n");
    return novo;
}

short maior(short a,short b){
    return (a>b)? a: b;

}

short fatorDeBalanceamento(No *no){
    if(no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r ->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo),alturaDoNo(y->direito)) + 1;

    return y;

}

No* rotacaoDireita(No *r){
    No *y, *f;

    y = r ->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r ->altura = maior(alturaDoNo(r->esquerdo),alturaDoNo(r->direito)) + 1;
    y ->altura = maior(alturaDoNo(y ->esquerdo), alturaDoNo(y->direito)) + 1;
    
    return y;
}

No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);

}

No*rotacaoEsquerdaDireita(No *r) {
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);

}

No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);

    if(fb < -1 && fatorDeBalanceamento(raiz ->direito) <=0)
        raiz = rotacaoEsquerda(raiz);

    else if (fb >1 && fatorDeBalanceamento (raiz ->esquerdo) >=0)
        raiz = rotacaoDireita(raiz);
    
    else if(fb>1 && fatorDeBalanceamento(raiz ->esquerdo) >=0)
        raiz = rotacaoEsquerdaDireita(raiz);
    
    else if(fb< -1 && fatorDeBalanceamento(raiz ->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);
    
    return raiz;


}



No* inserir(No *raiz, int x){
    if(raiz == 0)
        return novoNo(x);
    else{
        if(x<raiz ->valor)
            raiz ->esquerdo = inserir(raiz ->esquerdo, x);
        else if(x > raiz ->valor)
            raiz ->direito = inserir(raiz ->direito, x);
        else
        printf("\nInserção não realizada!\n O elemento %d já existe");
        }


raiz ->altura = maior(alturaDoNo(raiz ->esquerdo), alturaDoNo(raiz->direito)) +1;

raiz =balancear(raiz);
return raiz;
}

void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz ->direito, nivel + 1);
        printf("\n\n");

        for (i=0; i < nivel; i++)
        printf("\t");
        printf("%d", raiz ->valor);
        imprimir(raiz->esquerdo,nivel +1);

    }
}

int main(){

    int opcao,valor;
    No *raiz = 0;
    do{
        printf("\t0 - Sair\n");
        printf("\t1 - inserir\n");
        printf("\t2 - Imprimir\n");
        scanf("d%",&opcao);
        switch(opcao){
            case 0:
                printf("Saindo...");
                break;
            case 1:
                printf("\tDigite o valor a ser inserido: "); 
                scanf("%d",&valor);
                raiz = inserir(raiz,valor);
                break;
            case 2:
                imprimir(raiz,1);
                break;
            default:
                printf("Opção inválida");
        }
    }while(opcao!=0);
        return 0;
}