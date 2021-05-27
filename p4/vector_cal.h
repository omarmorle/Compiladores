#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct vector {
	char name;
	int n;
	double *vec;
};

typedef struct vector Vector;

Vector *creaVector(int n);
void imprimeVector(Vector *a);
void copiaVector(Vector *v,Vector *c);
Vector *sumaVector(Vector *a, Vector *b);
Vector *restaVector(Vector *a, Vector *b);
Vector *escalarVector(double escalar, Vector *a);
double productoPuntoVector(Vector *a, Vector *b);
Vector *productoCruzVector(Vector *a, Vector *b);
double magnitudVector(Vector *a);
void actualizarValor(char var, Vector *a);
Vector *obtenerValor(char var);
int obtenId(char var);
