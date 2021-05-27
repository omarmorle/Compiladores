#include "hoc.h" 
#include "y.tab.h"
#define NSTACK  256
static  Datum  stack[NSTACK];  /* la pila */
static  Datum   *stackp;       /* siguiente lugar libre en la pila */
#define NPROG   2000
Inst    prog[NPROG];    /* la máquina */
Inst    *progp;         /* siguiente lugar libre para la generación de código */
Inst    *pc;			/* contador de programa durante la ejecución */


void initcode()      /* inicialización para la generación de código */ 
{
	stackp = stack;
	progp = prog;
}

void push(d)		/*  meter d en la pila  */
Datum d; 
{
	if (stackp >= &stack[NSTACK])
	execerror("stack overflow", (char *) 0);
	*stackp++ = d;
}

Datum pop( )    	 /* sacar y retornar de la pila el elemento del tope */
{
	if (stackp <= stack)
	execerror("stack underflow", (char *) 0);
	return  *--stackp;
}


void constpush( )	/* meter una constante a la pila  */
{
	Datum d;
	d.val = ((Symbol  *)*pc++)->u.val;
	push(d);
}

void constpushd( )	/* meter una constante a la pila  */
{
	Datum d;
	d.num = ((Symbol  *)*pc++)->u.num;
	push(d);
}
void varpush()	/* meter una variable a la pila   */
{
	Datum d;
	d.sym  =  (Symbol   *)(*pc++);
	push(d);
}

void eval( )	/*  evaluar una variable en la pila   */
{
	Datum  d;
	d   =  pop();
	if   (d.sym->type   ==   INDEF)
	execerror("undefined variable",d.sym->name); 
	d.val   =  d.sym->u.val; 
	push(d);
}

void add( )		/*   sumar los dos elementos superiores de la pila   */
{
	Datum d1,   d2; 
	d2  =  pop(); 
	d1  =  pop(); 

	d1.val=  sumaVector(d1.val, d2.val); 
	push(d1); 
}

void sub()
{
	Datum d1,  d2; 
	d2  = pop(); 
	d1  = pop(); 
	d1.val=  restaVector(d1.val, d2.val); 
	push(d1);
}

void escalar()
{
	Datum d1, d2;
	d2 = pop(); 
	d1 = pop(); 
	d1.val = escalarVector(d1.num, d2.val);
	push(d1);
}


void productop( )
{
	Datum d1, d2;
	double d3;
	d2 = pop();

	d1 = pop();
	
	d3 = productoPuntoVector(d1.val, d2.val); 
	push((Datum)d3);
}

void productoc( )
{
	Datum d1, d2;
	d2 = pop();

	d1 = pop();
	
	d1.val = productoCruzVector(d1.val, d2.val); 
	push(d1);
}

void magnitud( )
{
	Datum d1;

	d1 = pop();
	
	d1.num = magnitudVector(d1.val); 
	push(d1);
}

void assign( )        /* asignar el valor superior al siguientevalor */ 
{
	Datum d1, d2;
	d1 = pop();
	d2 = pop();
	if (d1.sym->type != VAR && d1.sym->type != INDEF) 
	execerror("assignment to non-variable", d1.sym->name);
	d1.sym->u.val = d2.val;
	d1.sym->type = VAR;
	push(d2); 
} 

void print( )  /* sacar el valor superior de la pila e imprimirlo */ 
{
	Datum d;
	d = pop();
	imprimeVector(d.val);
}
void printd( )  /* sacar el valor superior de la pila e imprimirlo */ 
{
	Datum d;
	d = pop();
	printf("%lf",d.num);
}


Inst   *code(Inst f) /*   instalar una instrucción u operando   */
{
	Inst *oprogp = progp;
		if (progp >= &prog [ NPROG ])
			execerror("program too big", (char *) 0);
		*progp++ = f;
		return oprogp;
}

void execute(Inst p)	/*   ejecución con la máquina   */
{
	for  (pc  =  p;   *pc != STOP; ) 
		(*(*pc++))();
}

