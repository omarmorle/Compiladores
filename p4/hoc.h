#include "vector_cal.h"
#include<string.h>
typedef struct Symbol { /* entrada de la tabla de símbolos */
	char   *name;
	short   type;   /* VAR, BLTIN, UNDEF */
	union {
		Vector *val;	       /* si es VAR */
        double num;
	} u;
	struct Symbol   *next;  /* para ligarse a otro */ 
} Symbol;

Symbol *install(char *s,int t, Vector *d), *lookup(char *s);

typedef union Datum {   /* tipo de la pila del intérprete */
Vector *val;
double num;
Symbol  *sym; } Datum; 

extern Datum pop();
typedef int (*Inst)();  /* instrucción de máquina */ 

#define STOP    (Inst) 0
extern	Inst prog[];
extern void assign(),varpush(), constpush(), print(),printd(), constpushd();
extern void  eval(), add(), sub(), productoc(), productop(), magnitud(),escalar();
