#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    polinomio *pol = (polinomio*)malloc(sizeof(polinomio)); // aloco espaço para o polinomio
    // o número de termos é o grau + 1
    pol->coeficientes = calloc(grau +  1, sizeof(int)); // aloco espaço e inicializo todos os termos em 0 com calloc
    pol->grau = grau;
    pol->termos = 0;

    return pol;
}

void poli_destroy(polinomio **p){
    free(*p->coeficientes);
    free(*p);

    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente
    if (exp < 0 || exp > grau) {
        return 0;
    }
    if (p->coeficientes[exp] != 0 && coef == 0) {
        p->coeficientes[exp] = coef;
        p->termos -= 1;
    } else if (p->coeficientes[exp] == 0 && coef != 0) {
        p->coeficientes[exp] = coef;
        p->termos += 1;
    }

    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // TODO: Implemente aqui a solucao para operacao get coeficiente

    return 0;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)     
    
    return 0;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}


