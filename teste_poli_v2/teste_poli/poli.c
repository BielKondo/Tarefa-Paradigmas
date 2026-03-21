// 10436238 - Gabriel Hideaquy Kondo
// 10440034 - João Pedro Sinzato Bocchini

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
    // printf("p->grau: %d, q->grau: %d\n", p->grau, q->grau);
    // printf("coeficientes de p: ");
    // for (int i = 0; i <= p->grau; i++) {
    //     printf("%d ", p->coeficientes[i]);
    // }
    // printf("\n");
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro
    polinomio *r = poli_create(p->grau - q->grau);

    poli_ins_termo(r, p->grau - q->grau, p->coeficientes[p->grau] / q->coeficientes[q->grau]);
    //r->coeficientes[p->grau - q->grau] = p->coeficientes[p->grau] / q->coeficientes[q->grau];
    //int primeiro_coef_grau = p->grau - q->grau;

    int grau_s = (p->grau - q->grau) + q->grau;  
    polinomio *s = poli_create(grau_s); 

    int coef = 0;

    for (int i = 0; i <= q->grau; i++) {
        int coef_r;
        poli_get_termo(r, p->grau - q->grau, &coef_r);
        //coef = r->coeficientes[p->grau - q->grau] * q->coeficientes[i];
        coef = coef_r * q->coeficientes[i];
        poli_ins_termo(s, r->grau + i, coef);
    }

    // polinomio *t = poli_create(grau_t);
    polinomio *t = poli_create(p->grau); // grau do resto nunca pode ser maior que o grau de p
    	
    for (int k = 0; k <= p->grau; k++) {
        int coef_p = (k<=p->grau) ? p->coeficientes[k] : 0;
        int coef_s = (k<=s->grau) ? s->coeficientes[k] : 0;
        int subtrair = coef_p - coef_s;

        poli_ins_termo(t, k, subtrair); 
    }

    t->grau = 0;
    for (int j = p->grau; j >= 0; j--) {
        if (t->coeficientes[j] != 0) {
            t->grau = j;
            break;
        }
    }

    // printf("coeficientes de t: ");
    // for (int i = 0; i <= t->grau; i++) {
    //     printf("%d ", t->coeficientes[i]);
    // }
    // printf("\n");

    // for (int l = 0; l < (p->grau - q->grau); l++) {
    //     poli_ins_termo(r, l, r->coeficientes[p->grau - q->grau]); // vai montando o polinomio final
    // }
    poli_destroy(&s);
    if (t->grau >= q->grau) {
        polinomio *div_resultado = poli_div(t, q);
        polinomio *final = poli_soma(r, div_resultado);
        poli_destroy(&div_resultado);
        poli_destroy(&r);
        poli_destroy(&t);
        return final;
    }

    poli_destroy(&t);
    return r;
}


