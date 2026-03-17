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
    free((*p)->coeficientes);
    free(*p);
    *p = NULL;

    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente
    if (exp < 0 || exp > p->grau) {
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
    if (exp > p->grau || exp < 0 || (p->coeficientes[exp] == 0)) {
        return 0;
    }

    *coef = p->coeficientes[exp];    

    return 1;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)
    int resultado = 0;
    int potencia = 1;
    for (int i = 0; i <= p->grau; i++) {
        resultado += p->coeficientes[i]*potencia;
        potencia *= x;
    }
    
    return resultado;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro
    int maior_grau = (p->grau >= q->grau) ? p->grau : q->grau;
    polinomio *r = poli_create(maior_grau);

    for (int i = 0; i <= maior_grau; i++) {
        int coef_p = (i <= p->grau) ? p->coeficientes[i] : 0;
        int coef_q = (i <= q->grau) ? q->coeficientes[i] : 0;
        int soma = coef_p + coef_q;

        poli_ins_termo(r, i, soma);
    }

    return r;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro
    int maior_grau = p->grau + q->grau;
    polinomio *r = poli_create(maior_grau);

    for (int i = 0; i <= p->grau; i++) {
        for (int j = 0; j <= q->grau; j++) {
            r->coeficientes[i+j] += p->coeficientes[i]*(q->coeficientes[j]);
        }
    }

    return r;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}


