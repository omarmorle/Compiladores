#include "vectores.h"
#include  "y.tab.h"

static Symbol *symlist=0;    /* tabla de simbolos: lista ligada */

Vector *creaVector(int n, double dato){
    Vector *vec;
    int i;
    vec=(Vector *)malloc(sizeof(Vector));
    vec->n = n;
    vec->vec = (double *)malloc(sizeof(double)*n);
    vec->vec[0] = dato;
    return vec;
}
void imprimeVector(Vector *v){
    int i;
    for(i=0; i< v->n; i++)
        printf("%.2f ", v->vec[i]);
    printf("\n");
}
Vector *copiaVector(Vector *v){
    int i;
    Vector *copy=creaVector(v->n, 0);
    for(i = 0; i< v->n; i++)
        copy->vec[i]=v->vec[i];
    return copy;
}
Vector *sumaVector(Vector *a, Vector *b){
    Vector *c;
    int i;
    c=creaVector(a->n, 0);
    for(i=0; i< a->n;i++)
        c->vec[i]=a->vec[i]+b->vec[i];
    return c;
}
Vector *restaVector(Vector *a, Vector *b){
    Vector *c;
    int i;
    c=creaVector(a->n, 0);
    for(i=0; i< a->n;i++)
        c->vec[i]=a->vec[i]-b->vec[i];
    return c;
}
Vector *unirVectores(Vector *a, Vector *b){
    Vector *c;
    int i, j;
    int len = a->n + b->n;
    c = creaVector(len, 0);
    for(i = 0; i < a->n; i++){
        c->vec[i] = a->vec[i];
    }
    for(j = i;j < len; j++){
        c->vec[j] = b->vec[j - i];
    }
    return c;
}

double productoPunto(Vector *a, Vector *b){
    int i, len;
    double res = 0;
    len = a->n > b->n ? b->n : a->n;
    for(i = 0; i < len; i++){
        res += a->vec[i] * b->vec[i];
    }
    return res;
}
Vector *productoCruz(Vector *a, Vector *b){
    Vector *c;
    c = creaVector(3, 0);
    c->vec[0] = a->vec[1] * b->vec[2] - b->vec[1] * a->vec[2];
    c->vec[1] = a->vec[2] * b->vec[0] - b->vec[2] * a->vec[0];
    c->vec[2] = a->vec[0] * b->vec[1] - b->vec[0] * a->vec[1];
    return c;
}
Vector *productoEscalar(double a, Vector *b){
    Vector *c;
    int i;
    c = creaVector(b->n, 0);
    for(i = 0; i < b->n; i++){
        c->vec[i] = a*b->vec[i];
    }
    return c;
}
double magnitud(Vector *a){
    double res = 0;
    int i;
    for(i = 0; i < a->n; i++){
        res += a->vec[i] * a->vec[i];
    }
    return sqrt(res);
}

Symbol *lookup(char *s)    /* encontrar s en la tabla de símbolos */
{
  Symbol  *sp;
	for (sp = symlist; sp != (Symbol *)0; sp = sp->next)
		if (strcmp(sp->name, s)== 0)
			return sp;
	return 0;      /* 0 ==> no se encontró */
}

Symbol *install(char *s,int t, Vector *d) /* instalar s en la tabla de símbolos */
{
	Symbol *sp;
	sp = (Symbol *)malloc(sizeof(Symbol));
	sp->name = (char *)malloc(strlen(s)+ 1) ; /* +1 para '\0' */
	strcpy(sp->name, s);
	sp->type = t;
	sp->u.val = d;
	sp->next  =  symlist;   /*  poner al frente de la lista   */
	symlist =  sp;
  return sp;
}
