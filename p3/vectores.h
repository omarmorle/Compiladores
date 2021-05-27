#ifndef __VECTORES_H__
#define __VECTORES_H__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct vector {
     char name;
     int n;
     double *vec;
};
typedef struct vector Vector;

typedef struct Symbol { /* entrada de la tabla de símbolos */
	char   *name;
	short   type;   /* VAR, BLTIN, UNDEF */
	union {
		Vector *val;	       /* si es VAR */
		double  (*ptr)();      /* sí es BLTIN */
	} u;
	struct Symbol   *next;  /* para ligarse a otro */ 
} Symbol;

Symbol *install(char *,int, Vector *); 
Symbol *lookup(char *s);
Vector *creaVector(int n, double dato);
void imprimeVector(Vector *a);
Vector *unirVectores(Vector *a, Vector *b);
Vector *copiaVector(Vector *a);
Vector *sumaVector(Vector *a, Vector *b);
Vector *restaVector(Vector *a, Vector *b);
double productoPunto(Vector *a, Vector *b);
Vector *productoCruz(Vector *a, Vector *b);
Vector *productoEscalar(double a, Vector *b);
double magnitud(Vector *a);

#endif
