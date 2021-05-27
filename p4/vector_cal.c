#include "vector_cal.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Vector* cubeta[102];
Vector *creaVector(int n){
   Vector *vec;
   int i;
   vec=(Vector *)malloc(sizeof(Vector));
   vec->n = n;	
   vec->vec = (double *)malloc(sizeof(double)*n);
   return vec;
}
void imprimeVector(Vector *v){
   int i; 
   printf ("[");
   for(i=0; i< v->n - 1; i++)
      printf("%f, ", v->vec[i]);
   printf("%lf]\n", v->vec[v->n - 1]);
}
void copiaVector(Vector *v,Vector *c){
   int i;
   c =creaVector(v->n);
   for(i = 0; i< v->n; i++)
      c->vec[i]=v->vec[i];	
   //return copy;	
}
Vector *sumaVector(Vector *a, Vector *b){
    Vector *c;
	int i;
	c = creaVector(a->n);
    for(i = 0; i < a->n; i++)
    	c->vec[i] = a->vec[i] + b->vec[i];
	return c;
}
Vector *restaVector(Vector *a, Vector *b){
	Vector *c;
	int i;
  	c = creaVector(a->n);
    for(i = 0; i < a->n; i++)
    	c->vec[i] = a->vec[i] - b->vec[i];
    return c;
}
Vector *escalarVector(double escalar, Vector *a){
	Vector *c;
	int i = 0;
	c = creaVector(a->n);
	for (i = 0; i < a->n; i++)
		c->vec[i] = escalar * a->vec[i];
	return c;
}
double productoPuntoVector(Vector *a, Vector *b){
	double c = 0.0;
	int i;
	for(i = 0; i < a->n; i++)
		c += a->vec[i] * b->vec[i];
	return c;
}
Vector *productoCruzVector(Vector *a, Vector *b){
	Vector *c;
	c = creaVector(a->n);
	if (a->n == 2){
		c->vec[0] = a->vec[0] * b->vec[1];
		c->vec[1] = -(b->vec[0] * a->vec[1]);
	}else if (a->n == 3){
		c->vec[0] = a->vec[1] * b->vec[2] - b->vec[1] * a->vec[2];
		c->vec[1] = b->vec[0] * a->vec[2] - a->vec[0] * b->vec[2];
		c->vec[2] = a->vec[0] * b->vec[1] - b->vec[0] * a->vec[1];
	}
	return c;
}
double magnitudVector(Vector *a){
	double c = 0.0;
	int i = 0;
	for (i = 0; i < a->n; i++)
		c += (a->vec[i] * a->vec[i]);
	c = sqrt(c);
	return c;
}
int obtenId(char var){
	if ('A' <= var && var <= 'Z')
	return (var - 'A');
	return (var - 'a' + 26);
}
Vector *obtenerValor(char var){
	int id = obtenId(var);
	Vector *c = cubeta[id];
	return c;
}
void actualizarValor(char var, Vector *a){
	int id = obtenId(var);
	cubeta[id] = a;
}
