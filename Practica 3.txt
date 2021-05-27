%{
#include "vectores.h"

void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
void execerror(char *s, char *t);
void fpecatch();

%}

%union{
    Vector *vector;
    double numero;
    Symbol *sym;
}
%token <numero> NUMBER
%token <sym> VAR INDEF
%type <vector> exp vector component asgn
%type <numero> escalar
%right '='
%left '+' '-' ','
%left '*' 'X'
%left UNARYMINUS
%% 
list:   
	        | list'\n'
            | list exp '\n'  { imprimeVector($2); }
            | list asgn '\n'  { imprimeVector($2); }
            | list escalar '\n'  { printf("%.2f\n", $2); }
	        ;
asgn:	      VAR '=' exp {$$ = $1->u.val = $3; $1->type=VAR;}
escalar:      exp '*' exp {$$ = productoPunto($1, $3);}
            | '|'exp'|'   {$$ = magnitud($2);}
            | NUMBER	  {$$ = $1;}
            | '-'NUMBER %prec UNARYMINUS  {$$ = -$2;}
            ;
exp:          vector          { $$ = $1;  }
            | VAR             {  if($1->type == INDEF)execerror("Variable no definida, ", $1->name);
                                    $$=$1->u.val;
                              }
	          | asgn            { $$ = $1;  }
            | exp '+' exp     { $$ = sumaVector  ($1, $3);  }
            | exp '-' exp     { $$ = restaVector ($1, $3);  }
            | exp 'X' exp     { $$ = productoCruz($1, $3);  }
            | '['exp']'       { $$ = $2; }
            | escalar '*' exp { $$ = productoEscalar($1, $3);  }
            | exp '*' escalar { $$ = productoEscalar($3, $1);  }
	        ;

vector:       '['component']' { $$ = $2;}
        ;
component:    component','component { $$ = unirVectores($1, $3);}
            | NUMBER            { $$ = creaVector(1, $1); }
            ;

%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include<setjmp.h>

char *progname;
int lineno = 1;

jmp_buf begin;

void main (int argc, char *argv[]){
	progname=argv[0];
    //init();
    setjmp(begin);
    signal(SIGFPE, fpecatch);
  	yyparse ();
}

void execerror(char *s, char *t){
    warning(s, t);
    longjmp(begin, 0);
}

void fpecatch(){
    execerror("Excepcion de punto flotante", (char *)0);
}

int yylex (){
  	int c;

  	while ((c = getchar ()) == ' ' || c == '\t')  
  		;
 	if (c == EOF)                            
    		return 0;
  	if (c == '.' || isdigit (c)) {
      		ungetc (c, stdin);
      		scanf ("%lf", &(yylval.numero));
	      return NUMBER;
    	}
	if(isalpha(c) && c!='X'){
		Symbol *s;
		char sbuf[200], *p=sbuf;
		do {
			*p++=c;
		} while ((c=getchar())!=EOF && isalnum(c) && c!='X');
		ungetc(c, stdin);
		*p='\0';
		if((s=lookup(sbuf))==(Symbol *)NULL)
			s=install(sbuf, INDEF, (Vector *)NULL);
		yylval.sym=s;   
        if(s->type == INDEF){
			return VAR;
        } else {
 		//printf("func=(%s) tipo=(%d) \n", s->name, s->type);
                        return s->type;
        }
	}
  	if(c == '\n')
		lineno++;
  	return c;                                
}
void yyerror (char *s) {
	warning(s, (char *) 0);
}
void warning(char *s, char *t){
	fprintf (stderr, "%s: %s", progname, s);
	if(t)
		fprintf (stderr, " %s", t);
	fprintf (stderr, "cerca de la linea %d\n", lineno);
}


