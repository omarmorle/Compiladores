//### This file created by BYACC 1.8(/Java extension  1.15)
//### Java capabilities added 7 Jan 97, Bob Jamison
//### Updated : 27 Nov 97  -- Bob Jamison, Joe Nieten
//###           01 Jan 98  -- Bob Jamison -- fixed generic semantic constructor
//###           01 Jun 99  -- Bob Jamison -- added Runnable support
//###           06 Aug 00  -- Bob Jamison -- made state variables class-global
//###           03 Jan 01  -- Bob Jamison -- improved flags, tracing
//###           16 May 01  -- Bob Jamison -- added custom stack sizing
//###           04 Mar 02  -- Yuval Oren  -- improved java performance, added options
//###           14 Mar 02  -- Tomas Hurka -- -d support, static initializer workaround
//### Please send bug reports to tom@hukatronic.cz
//### static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";



package modelo.compilador;



//#line 2 "P2.y"
	import java.lang.Math;
	import java.io.*;
	import java.util.StringTokenizer;
	import modelo.Configuracion;
//#line 22 "Parser.java"




public class Parser
{

boolean yydebug;        //do I want debug output?
int yynerrs;            //number of errors so far
int yyerrflag;          //was there an error?
int yychar;             //the current working character

//########## MESSAGES ##########
//###############################################################
// method: debug
//###############################################################
void debug(String msg)
{
  if (yydebug)
    System.out.println(msg);
}

//########## STATE STACK ##########
final static int YYSTACKSIZE = 500;  //maximum stack size
int statestk[] = new int[YYSTACKSIZE]; //state stack
int stateptr;
int stateptrmax;                     //highest index of stackptr
int statemax;                        //state when highest index reached
//###############################################################
// methods: state stack push,pop,drop,peek
//###############################################################
final void state_push(int state)
{
  try {
		stateptr++;
		statestk[stateptr]=state;
	 }
	 catch (ArrayIndexOutOfBoundsException e) {
     int oldsize = statestk.length;
     int newsize = oldsize * 2;
     int[] newstack = new int[newsize];
     System.arraycopy(statestk,0,newstack,0,oldsize);
     statestk = newstack;
     statestk[stateptr]=state;
  }
}
final int state_pop()
{
  return statestk[stateptr--];
}
final void state_drop(int cnt)
{
  stateptr -= cnt; 
}
final int state_peek(int relative)
{
  return statestk[stateptr-relative];
}
//###############################################################
// method: init_stacks : allocate and prepare stacks
//###############################################################
final boolean init_stacks()
{
  stateptr = -1;
  val_init();
  return true;
}
//###############################################################
// method: dump_stacks : show n levels of the stacks
//###############################################################
void dump_stacks(int count)
{
int i;
  System.out.println("=index==state====value=     s:"+stateptr+"  v:"+valptr);
  for (i=0;i<count;i++)
    System.out.println(" "+i+"    "+statestk[i]+"      "+valstk[i]);
  System.out.println("======================");
}


//########## SEMANTIC VALUES ##########
//public class ParserVal is defined in ParserVal.java


String   yytext;//user variable to return contextual strings
ParserVal yyval; //used to return semantic vals from action routines
ParserVal yylval;//the 'lval' (result) I got from yylex()
ParserVal valstk[];
int valptr;
//###############################################################
// methods: value stack push,pop,drop,peek.
//###############################################################
void val_init()
{
  valstk=new ParserVal[YYSTACKSIZE];
  yyval=new ParserVal();
  yylval=new ParserVal();
  valptr=-1;
}
void val_push(ParserVal val)
{
  if (valptr>=YYSTACKSIZE)
    return;
  valstk[++valptr]=val;
}
ParserVal val_pop()
{
  if (valptr<0)
    return new ParserVal();
  return valstk[valptr--];
}
void val_drop(int cnt)
{
int ptr;
  ptr=valptr-cnt;
  if (ptr<0)
    return;
  valptr = ptr;
}
ParserVal val_peek(int relative)
{
int ptr;
  ptr=valptr-relative;
  if (ptr<0)
    return new ParserVal();
  return valstk[ptr];
}
final ParserVal dup_yyval(ParserVal val)
{
  ParserVal dup = new ParserVal();
  dup.ival = val.ival;
  dup.dval = val.dval;
  dup.sval = val.sval;
  dup.obj = val.obj;
  return dup;
}
//#### end semantic value section ####
public final static short IF=257;
public final static short ELSE=258;
public final static short WHILE=259;
public final static short FOR=260;
public final static short COMP=261;
public final static short DIFERENTES=262;
public final static short MAY=263;
public final static short MEN=264;
public final static short MAYI=265;
public final static short MENI=266;
public final static short FNCT=267;
public final static short NUMBER=268;
public final static short VAR=269;
public final static short AND=270;
public final static short OR=271;
public final static short FUNC=272;
public final static short RETURN=273;
public final static short PARAMETRO=274;
public final static short PROC=275;
public final static short YYERRCODE=256;
final static short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    1,    1,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    5,    5,    5,
    6,    3,    3,    3,    3,    3,    3,    3,   15,   14,
   12,    4,   13,    8,    7,    9,   10,   11,   11,   11,
};
final static short yylen[] = {                            2,
    0,    2,    3,    2,    1,    3,    2,    1,    2,    1,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    2,    2,    1,    4,    0,    1,    3,
    0,   14,   11,   10,   16,    8,    8,    5,    1,    1,
    1,    1,    0,    0,    1,    1,    1,    0,    1,    3,
};
final static short yydefred[] = {                         1,
    0,   45,   46,   47,   39,   10,    0,   41,    0,   26,
   40,    0,    0,    2,    0,    0,    0,    5,    0,    0,
    0,    0,    0,    0,    0,    0,   25,    0,    0,    0,
    3,    0,    7,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    4,    0,    0,    0,    0,   42,
    0,    0,    0,    0,   15,    6,    0,    0,    0,    0,
    0,    0,    0,   23,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   27,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   38,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   36,   37,    0,   44,
    0,    0,   44,   34,    0,    0,   33,    0,    0,    0,
    0,    0,   32,    0,   44,   35,
};
final static short yydgoto[] = {                          1,
   16,   17,   18,   19,   69,  113,   20,   79,   21,   22,
   73,   23,  102,   24,   25,
};
final static short yysindex[] = {                         0,
    9,    0,    0,    0,    0,    0,  -49,    0,  -13,    0,
    0,  -13,  -13,    0,  -13,   28,   75,    0,  -24,   -9,
   -4,   10, -255, -255,  -48,  -13,    0,  108, -242,   54,
    0,   86,    0,  -13,  -13,  -13,  -13,  -13,  -13,  -13,
  -13,  -13,  -13,  -13,    0,  -13,  -13,  -13,  -13,    0,
   17,   19,  -13,   97,    0,    0,  217,  152,  190, -194,
 -225, -242, -190,    0,  108,  108,  -57,   97,    3,   97,
   97,   97,   45,   49,   57,  -35,    0,  -13,   70,   71,
  -13,   62,   14,   15,   73,   97,   18,   20,   97,  -13,
  -32,  -32,    0,  -32,  -32,   97,  -32,  -32,  -32,  -32,
   76,   23,   24,   27,   29,  -13,    0,    0, -114,    0,
   45,   32,    0,    0,  105,  -32,    0,   33,  -32,  -32,
   40,  -32,    0,   52,    0,    0,
};
final static short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -19,  119,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   38,    0,    0,  -42,    0,
    0,    0,  -33,  -26,    0,    0,  -38,  158,  151,  131,
  138,  125,   65,    0,   60,  230,   21,    7,    0,  116,
  116,   -7,  100,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   34,    0,    0,   12,    0,
    0,    0,    0,    0,    0,  100,   61,   61,   63,   63,
    0,    0,    0,    0,    0,   89,    0,    0,  -10,    0,
  116,    0,    0,    0,    0,    0,    0,    0,   63,    0,
    0,   63,    0,    0,    0,    0,
};
final static short yygindex[] = {                         0,
   31,  395,   -6,   46,  118,    0,    0,  353,    0,    0,
   79,    0,   91,    0,    0,
};
final static int YYTABLESIZE=517;
static short yytable[];
static { yytable();}
static void yytable(){
yytable = new short[]{                         31,
   13,   48,   16,   16,   16,   16,   16,   15,   78,   33,
   28,   26,   12,   50,   11,   46,   48,   11,   14,   13,
   16,    9,   31,    9,    9,    9,   15,   40,   41,   31,
   47,   12,   11,   49,   31,   48,   49,   31,   37,    9,
   39,   13,   53,   77,   40,   41,   78,   29,   15,   49,
   29,   49,   50,   12,   16,   50,   74,   85,   75,   28,
   13,   12,   12,   12,   12,   12,   11,   15,   51,   52,
   50,   39,   12,    9,   30,   40,   41,   30,   28,   12,
   41,   28,   42,    8,    8,    8,    8,    8,   81,   83,
   33,   33,   33,   33,   55,   44,   42,   84,   43,   29,
   13,    8,   13,   13,   13,   22,   22,   22,   22,   22,
   87,   88,   33,   12,   31,   33,   44,   42,   13,   43,
   90,   97,   98,   22,   99,  100,   30,   44,   42,   48,
   43,   93,   48,   45,  106,    8,   91,   92,   44,   42,
   94,   43,   95,  112,   56,  118,  119,  107,  108,   44,
  122,  109,   13,  110,  116,  120,   44,   22,   44,   24,
   24,   24,   24,   24,  123,   19,   19,   19,   19,   19,
   76,   18,   18,   18,   18,   18,  125,   24,   21,   21,
   21,   21,   21,   19,  111,   43,    0,   44,  103,   18,
    0,   20,   20,   20,   20,   20,   21,    0,   17,   17,
   17,   17,   17,   34,   35,   36,   37,   38,   39,   20,
    0,   24,   40,   41,    0,    0,   17,   19,    0,    0,
    0,    0,   16,   18,    2,    0,    3,    4,    0,    0,
   21,    0,    0,    0,    5,    6,    7,    0,    0,    8,
    9,   10,   11,   20,    0,    0,   31,    0,   31,   31,
   17,    0,    0,    0,    6,    7,   31,   31,   31,    9,
   10,   31,   31,   31,   31,    2,    0,    3,    4,    0,
   14,    0,   14,   14,   14,    5,    6,    7,    0,    0,
    8,    9,   10,   11,    2,    0,    3,    4,   14,    0,
    0,    0,    0,    0,    5,    6,    7,    0,    0,    8,
    9,   10,   11,    8,    8,    8,    8,    8,    8,    0,
    0,    0,    8,    8,   34,   35,   36,   37,   38,   39,
    0,    0,   14,   40,   41,   22,   22,   22,   22,   22,
   22,    0,    0,    0,   22,   34,   35,   36,   37,   38,
   39,    0,    0,    0,   40,   41,   34,   35,   36,   37,
   38,   39,    0,    0,    0,   40,   41,   34,   35,   36,
   37,   38,   39,    0,    0,    0,   40,   41,   34,   35,
   36,   37,   38,   39,    0,    0,    0,   40,   41,   24,
   24,   24,   24,   24,   24,   19,   19,   19,   19,   19,
   19,   18,   18,   18,   18,   18,    0,    0,   21,   21,
   21,    0,   21,   27,    0,    0,   28,   29,    0,   30,
   32,   20,   20,   20,   36,   37,   38,   39,   17,   17,
   54,   40,   41,   80,    0,   82,    0,    0,   57,   58,
   59,   60,   61,   62,   63,   64,   65,   66,   67,    0,
   68,   70,   71,   72,    0,    0,    0,   68,  101,    0,
    0,  104,  105,   37,   38,   39,    0,    0,    0,   40,
   41,    0,  114,  115,    0,  117,    0,    0,    0,    0,
    0,  121,   86,    0,  124,   89,    0,  126,   35,   36,
   37,   38,   39,    0,   96,    0,   40,   41,    0,    0,
    0,   32,   32,   32,   32,    0,    0,    0,    0,    0,
   72,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   32,    0,    0,   32,
};
}
static short yycheck[];
static { yycheck(); }
static void yycheck() {
yycheck = new short[] {                         10,
   33,   44,   41,   42,   43,   44,   45,   40,   44,   16,
   44,   61,   45,  269,   41,   40,   59,   44,   10,   33,
   59,   41,   33,   43,   44,   45,   40,  270,  271,   40,
   40,   45,   59,   41,   45,   40,   44,   10,  264,   59,
  266,   33,   91,   41,  270,  271,   44,   41,   40,   40,
   44,   59,   41,   45,   93,   44,   40,   93,   40,   93,
   33,   41,   42,   43,   44,   45,   93,   40,   23,   24,
   59,  266,   45,   93,   41,  270,  271,   44,   41,   59,
  271,   44,   40,   41,   42,   43,   44,   45,   44,   41,
   97,   98,   99,  100,   41,   42,   43,   41,   45,   93,
   41,   59,   43,   44,   45,   41,   42,   43,   44,   45,
   41,   41,  119,   93,  125,  122,   42,   43,   59,   45,
   59,   91,   92,   59,   94,   95,   93,   42,   43,   41,
   45,   59,   44,   59,   59,   93,  123,  123,   42,   43,
  123,   45,  123,  258,   59,   41,  116,  125,  125,   42,
  120,  125,   93,  125,  123,  123,   41,   93,   59,   41,
   42,   43,   44,   45,  125,   41,   42,   43,   44,   45,
   53,   41,   42,   43,   44,   45,  125,   59,   41,   42,
   43,   44,   45,   59,  106,  125,   -1,  125,   98,   59,
   -1,   41,   42,   43,   44,   45,   59,   -1,   41,   42,
   43,   44,   45,  261,  262,  263,  264,  265,  266,   59,
   -1,   93,  270,  271,   -1,   -1,   59,   93,   -1,   -1,
   -1,   -1,  261,   93,  257,   -1,  259,  260,   -1,   -1,
   93,   -1,   -1,   -1,  267,  268,  269,   -1,   -1,  272,
  273,  274,  275,   93,   -1,   -1,  257,   -1,  259,  260,
   93,   -1,   -1,   -1,  268,  269,  267,  268,  269,  273,
  274,  272,  273,  274,  275,  257,   -1,  259,  260,   -1,
   41,   -1,   43,   44,   45,  267,  268,  269,   -1,   -1,
  272,  273,  274,  275,  257,   -1,  259,  260,   59,   -1,
   -1,   -1,   -1,   -1,  267,  268,  269,   -1,   -1,  272,
  273,  274,  275,  261,  262,  263,  264,  265,  266,   -1,
   -1,   -1,  270,  271,  261,  262,  263,  264,  265,  266,
   -1,   -1,   93,  270,  271,  261,  262,  263,  264,  265,
  266,   -1,   -1,   -1,  270,  261,  262,  263,  264,  265,
  266,   -1,   -1,   -1,  270,  271,  261,  262,  263,  264,
  265,  266,   -1,   -1,   -1,  270,  271,  261,  262,  263,
  264,  265,  266,   -1,   -1,   -1,  270,  271,  261,  262,
  263,  264,  265,  266,   -1,   -1,   -1,  270,  271,  261,
  262,  263,  264,  265,  266,  261,  262,  263,  264,  265,
  266,  261,  262,  263,  264,  265,   -1,   -1,  261,  262,
  263,   -1,  265,    9,   -1,   -1,   12,   13,   -1,   15,
   16,  261,  262,  263,  263,  264,  265,  266,  261,  262,
   26,  270,  271,   71,   -1,   73,   -1,   -1,   34,   35,
   36,   37,   38,   39,   40,   41,   42,   43,   44,   -1,
   46,   47,   48,   49,   -1,   -1,   -1,   53,   96,   -1,
   -1,   99,  100,  264,  265,  266,   -1,   -1,   -1,  270,
  271,   -1,  110,  111,   -1,  113,   -1,   -1,   -1,   -1,
   -1,  119,   78,   -1,  122,   81,   -1,  125,  262,  263,
  264,  265,  266,   -1,   90,   -1,  270,  271,   -1,   -1,
   -1,   97,   98,   99,  100,   -1,   -1,   -1,   -1,   -1,
  106,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  119,   -1,   -1,  122,
};
}
final static short YYFINAL=1;
final static short YYMAXTOKEN=275;
final static String yyname[] = {
"end-of-file",null,null,null,null,null,null,null,null,null,"'\\n'",null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,"'!'",null,null,null,null,null,null,"'('","')'","'*'","'+'",
"','","'-'",null,null,null,null,null,null,null,null,null,null,null,null,null,
"';'",null,"'='",null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,"'['",null,"']'",null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,"'{'",null,"'}'",null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,"IF","ELSE","WHILE","FOR","COMP",
"DIFERENTES","MAY","MEN","MAYI","MENI","FNCT","NUMBER","VAR","AND","OR","FUNC",
"RETURN","PARAMETRO","PROC",
};
final static String yyrule[] = {
"$accept : list",
"list :",
"list : list '\\n'",
"list : list linea '\\n'",
"linea : exp ';'",
"linea : stmt",
"linea : linea exp ';'",
"linea : linea stmt",
"exp : VAR",
"exp : '-' exp",
"exp : NUMBER",
"exp : VAR '=' exp",
"exp : exp '*' exp",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : '(' exp ')'",
"exp : exp COMP exp",
"exp : exp DIFERENTES exp",
"exp : exp MEN exp",
"exp : exp MENI exp",
"exp : exp MAY exp",
"exp : exp MAYI exp",
"exp : exp AND exp",
"exp : exp OR exp",
"exp : '!' exp",
"exp : RETURN exp",
"exp : PARAMETRO",
"exp : nombreProc '(' arglist ')'",
"arglist :",
"arglist : exp",
"arglist : arglist ',' exp",
"nop :",
"stmt : if_ '(' exp stop_ ')' '{' linea stop_ '}' ELSE '{' linea stop_ '}'",
"stmt : if_ '(' exp stop_ ')' '{' linea stop_ '}' nop stop_",
"stmt : while_ '(' exp stop_ ')' '{' linea stop_ '}' stop_",
"stmt : for_ '(' instrucciones stop_ ';' exp stop_ ';' instrucciones stop_ ')' '{' linea stop_ '}' stop_",
"stmt : funcion nombreProc '(' ')' '{' linea null_ '}'",
"stmt : procedimiento nombreProc '(' ')' '{' linea null_ '}'",
"stmt : instruccion '[' arglist ']' ';'",
"instruccion : FNCT",
"procedimiento : PROC",
"funcion : FUNC",
"nombreProc : VAR",
"null_ :",
"stop_ :",
"if_ : IF",
"while_ : WHILE",
"for_ : FOR",
"instrucciones :",
"instrucciones : exp",
"instrucciones : instrucciones ',' exp",
};

//#line 221 "P2.y"



TablaDeSimbolos tablaDeSimbolos = new TablaDeSimbolos();
MaquinaDePila maquina = new MaquinaDePila(tablaDeSimbolos);
int i = 0;
int j = 0;
double[][] auxiliar;
Funcion funcionAux;
boolean huboError;

String ins;
StringTokenizer st;

void yyerror(String s){
	huboError = true;
	System.out.println("error:"+s);
}

boolean newline;
int yylex(){
	String s;
	int tok = 0;
	Double d;
	if (!st.hasMoreTokens()){
		if (!newline){
			newline=true;
			return '\n'; //So we look like classic YACC example
		}
		else
			return 0;
	}
	s = st.nextToken();
	try{
		d = Double.valueOf(s);/*this may fail*/
		yylval = new ParserVal(d.doubleValue()); //SEE BELOW
		return NUMBER;
	}
	catch (Exception e){}
	if(esVariable(s)){
		if(s.equals("proc")){
			return PROC;
		}
		if(s.charAt(0) == '$'){
			yylval = new ParserVal((int)Integer.parseInt(s.substring(1)));
			return PARAMETRO;
		}
		if(s.equals("return")){
			return RETURN;
		}
		if(s.equals("func")){
			return FUNC;
		}
		if(s.equals("if")){
			return IF;
		}
		if(s.equals("else")){
			return ELSE;
		}
		if(s.equals("while")){
			return WHILE;
		}
		if(s.equals("for")){
			return FOR;
		}
		boolean esFuncion = false;
		Object objeto = tablaDeSimbolos.encontrar(s);
		if(objeto instanceof Funcion){
			funcionAux = (Funcion)objeto;
			yylval = new ParserVal(objeto);			
			esFuncion = true;
			return FNCT;
		}
		if(!esFuncion){
			yylval = new ParserVal(s);
			return VAR;
		}
	}
	else{
            if(s.equals("==")){
                return COMP;
            }
            if(s.equals("!=")){
                    return DIFERENTES;
            }
            if(s.equals("<")){
                    return MEN;
            }
            if(s.equals("<=")){
                    return MENI;
            }
            if(s.equals(">")){
                    return MAY;
            }
            if(s.equals(">=")){
                    return MAYI;
            }
            if(s.equals("&&")){
                    return AND;
            }
            if(s.equals("||")){
                    return OR;
            }
            tok = s.charAt(0);
	}
	//System.out.println("Token: " + tok);
	return tok;
}

String reservados[] = {">=", "&&", "||", "<=","==", "!=", "=", "{", "}", ",", "*", "+", "-", "(", ")", "|", "[", "]", ";", "!", "<", ">"};
public String ajustarCadena(String cadena){
    String nueva = "";
    boolean encontrado = false;
    for(int i = 0; i < cadena.length() - 1; i++){
        encontrado = false;
        for(int j = 0; j < reservados.length; j++){
            if(cadena.substring(i, i + reservados[j].length()).equals(reservados[j])){
                i += reservados[j].length()-1;
                nueva += " " + reservados[j] + " ";
                encontrado = true;
                break;
            }
        }
        if(!encontrado)
            nueva += cadena.charAt(i);
    }
    if(cadena.length() > 0){
        char ultimo = cadena.charAt(cadena.length()-1);
        if(ultimo == ';' || ultimo == '}')
            nueva += " " + ultimo + " ";
        else
            nueva += cadena.charAt(cadena.length()-1);
    }
    //System.out.println(nueva);
    return nueva;
}

boolean esVariable(String s){
	boolean cumple = true;
	for(int i = 0; i < reservados.length; i++)
		if(s.equals(reservados[i]))
			cumple = false;
	return cumple;
}
public void insertarInstrucciones(){
	tablaDeSimbolos.insertar("Girar", new MaquinaDePila.Girar());
	tablaDeSimbolos.insertar("Avanzar", new MaquinaDePila.Avanzar());
	tablaDeSimbolos.insertar("CambiarColor", new MaquinaDePila.CambiarColor());
}


public Configuracion ejecutarCodigo(String codigo){
    st = new StringTokenizer(ajustarCadena(codigo));
    newline=false;
    yyparse();
    if(!huboError)
            maquina.ejecutar();
    return maquina.getConfiguracion();
} 

public Configuracion ejecutar(){
    maquina.ejecutar();
    return maquina.getConfiguracion();
}

//AGREGAR AL .y
public boolean compilar(String codigo){
    st = new StringTokenizer(ajustarCadena(codigo));
    newline=false;
    yyparse();
    return !huboError;
}

public boolean ejecutarSiguiente(){
    return maquina.ejecutarSiguiente();
}

public Configuracion getConfiguracion(){
    return maquina.getConfiguracion();
}

public void limpiar(){
    tablaDeSimbolos = new TablaDeSimbolos();
    insertarInstrucciones();
    maquina = new MaquinaDePila(tablaDeSimbolos);
}


void dotest() throws Exception{
	insertarInstrucciones();
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	while (true){
		huboError = false;
		try{
			ins = ajustarCadena(in.readLine());
		}
		catch (Exception e){}
		st = new StringTokenizer(ins);
		newline=false;
		//maquina = new MaquinaDePila(tablaDeSimbolos);
		yyparse();
		if(!huboError)
			maquina.ejecutar();
	}
}

public static void main(String args[]) throws Exception{
	Parser par = new Parser(false);
	par.dotest();
}
//#line 551 "Parser.java"
//###############################################################
// method: yylexdebug : check lexer state
//###############################################################
void yylexdebug(int state,int ch)
{
String s=null;
  if (ch < 0) ch=0;
  if (ch <= YYMAXTOKEN) //check index bounds
     s = yyname[ch];    //now get it
  if (s==null)
    s = "illegal-symbol";
  debug("state "+state+", reading "+ch+" ("+s+")");
}





//The following are now global, to aid in error reporting
int yyn;       //next next thing to do
int yym;       //
int yystate;   //current parsing state from state table
String yys;    //current token string


//###############################################################
// method: yyparse : parse input and execute indicated items
//###############################################################
int yyparse()
{
boolean doaction;
  init_stacks();
  yynerrs = 0;
  yyerrflag = 0;
  yychar = -1;          //impossible char forces a read
  yystate=0;            //initial state
  state_push(yystate);  //save it
  val_push(yylval);     //save empty value
  while (true) //until parsing is done, either correctly, or w/error
    {
    doaction=true;
    if (yydebug) debug("loop"); 
    //#### NEXT ACTION (from reduction table)
    for (yyn=yydefred[yystate];yyn==0;yyn=yydefred[yystate])
      {
      if (yydebug) debug("yyn:"+yyn+"  state:"+yystate+"  yychar:"+yychar);
      if (yychar < 0)      //we want a char?
        {
        yychar = yylex();  //get next token
        if (yydebug) debug(" next yychar:"+yychar);
        //#### ERROR CHECK ####
        if (yychar < 0)    //it it didn't work/error
          {
          yychar = 0;      //change it to default string (no -1!)
          if (yydebug)
            yylexdebug(yystate,yychar);
          }
        }//yychar<0
      yyn = yysindex[yystate];  //get amount to shift by (shift index)
      if ((yyn != 0) && (yyn += yychar) >= 0 &&
          yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
        {
        if (yydebug)
          debug("state "+yystate+", shifting to state "+yytable[yyn]);
        //#### NEXT STATE ####
        yystate = yytable[yyn];//we are in a new state
        state_push(yystate);   //save it
        val_push(yylval);      //push our lval as the input for next rule
        yychar = -1;           //since we have 'eaten' a token, say we need another
        if (yyerrflag > 0)     //have we recovered an error?
           --yyerrflag;        //give ourselves credit
        doaction=false;        //but don't process yet
        break;   //quit the yyn=0 loop
        }

    yyn = yyrindex[yystate];  //reduce
    if ((yyn !=0 ) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
      {   //we reduced!
      if (yydebug) debug("reduce");
      yyn = yytable[yyn];
      doaction=true; //get ready to execute
      break;         //drop down to actions
      }
    else //ERROR RECOVERY
      {
      if (yyerrflag==0)
        {
        yyerror("syntax error");
        yynerrs++;
        }
      if (yyerrflag < 3) //low error count?
        {
        yyerrflag = 3;
        while (true)   //do until break
          {
          if (stateptr<0)   //check for under & overflow here
            {
            yyerror("stack underflow. aborting...");  //note lower case 's'
            return 1;
            }
          yyn = yysindex[state_peek(0)];
          if ((yyn != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
            if (yydebug)
              debug("state "+state_peek(0)+", error recovery shifting to state "+yytable[yyn]+" ");
            yystate = yytable[yyn];
            state_push(yystate);
            val_push(yylval);
            doaction=false;
            break;
            }
          else
            {
            if (yydebug)
              debug("error recovery discarding state "+state_peek(0)+" ");
            if (stateptr<0)   //check for under & overflow here
              {
              yyerror("Stack underflow. aborting...");  //capital 'S'
              return 1;
              }
            state_pop();
            val_pop();
            }
          }
        }
      else            //discard this token
        {
        if (yychar == 0)
          return 1; //yyabort
        if (yydebug)
          {
          yys = null;
          if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
          if (yys == null) yys = "illegal-symbol";
          debug("state "+yystate+", error recovery discards token "+yychar+" ("+yys+")");
          }
        yychar = -1;  //read another
        }
      }//end error recovery
    }//yyn=0 loop
    if (!doaction)   //any reason not to proceed?
      continue;      //skip action
    yym = yylen[yyn];          //get count of terminals on rhs
    if (yydebug)
      debug("state "+yystate+", reducing "+yym+" by rule "+yyn+" ("+yyrule[yyn]+")");
    if (yym>0)                 //if count of rhs not 'nil'
      yyval = val_peek(yym-1); //get current semantic value
    yyval = dup_yyval(yyval); //duplicate yyval if ParserVal is used as semantic value
    switch(yyn)
      {
//########## USER-SUPPLIED ACTIONS ##########
case 4:
//#line 49 "P2.y"
{yyval = val_peek(1);}
break;
case 5:
//#line 50 "P2.y"
{yyval = val_peek(0);}
break;
case 6:
//#line 51 "P2.y"
{yyval = val_peek(2);}
break;
case 7:
//#line 52 "P2.y"
{yyval = val_peek(1);}
break;
case 8:
//#line 55 "P2.y"
{				
				yyval = new ParserVal(maquina.agregarOperacion("varPush_Eval")); 
				maquina.agregar(val_peek(0).sval);
			}
break;
case 9:
//#line 59 "P2.y"
{
                                System.out.println("NEGATIVO");
				yyval = new ParserVal(maquina.agregarOperacion("negativo"));
			}
break;
case 10:
//#line 62 "P2.y"
{
				yyval = new ParserVal(maquina.agregarOperacion("constPush"));
				maquina.agregar(val_peek(0).dval);
			}
break;
case 11:
//#line 66 "P2.y"
{
				yyval = new ParserVal(val_peek(0).ival);
				maquina.agregarOperacion("varPush");
		        maquina.agregar(val_peek(2).sval);
		        maquina.agregarOperacion("asignar");
		        maquina.agregarOperacion("varPush_Eval"); 
				maquina.agregar(val_peek(2).sval);
			}
break;
case 12:
//#line 74 "P2.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("multiplicar");
			}
break;
case 13:
//#line 78 "P2.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("sumar");
			}
break;
case 14:
//#line 82 "P2.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("restar");
			}
break;
case 15:
//#line 86 "P2.y"
{
				yyval = new ParserVal(val_peek(1).ival);
			}
break;
case 16:
//#line 89 "P2.y"
{
				 maquina.agregarOperacion("comparar");
				 yyval = val_peek(2);
			}
break;
case 17:
//#line 93 "P2.y"
{
				 maquina.agregarOperacion("compararNot");
				 yyval = val_peek(2);
			}
break;
case 18:
//#line 97 "P2.y"
{
				 maquina.agregarOperacion("menor");
				 yyval = val_peek(2);
			}
break;
case 19:
//#line 101 "P2.y"
{
				 maquina.agregarOperacion("menorIgual");
				 yyval = val_peek(2);
			}
break;
case 20:
//#line 105 "P2.y"
{
				 maquina.agregarOperacion("mayor");
				 yyval = val_peek(2);
			}
break;
case 21:
//#line 109 "P2.y"
{
				 maquina.agregarOperacion("mayorIgual");
				 yyval = val_peek(2);
			}
break;
case 22:
//#line 113 "P2.y"
{
				maquina.agregarOperacion("and");
				 yyval = val_peek(2);
			}
break;
case 23:
//#line 117 "P2.y"
{
				maquina.agregarOperacion("or");
				 yyval = val_peek(2);
			}
break;
case 24:
//#line 121 "P2.y"
{
				maquina.agregarOperacion("negar");
				yyval = val_peek(0);
			}
break;
case 25:
//#line 125 "P2.y"
{ yyval = val_peek(0); maquina.agregarOperacion("_return"); }
break;
case 26:
//#line 127 "P2.y"
{ yyval = new ParserVal(maquina.agregarOperacion("push_parametro")); maquina.agregar((int)val_peek(0).ival); }
break;
case 27:
//#line 129 "P2.y"
{ yyval = new ParserVal(maquina.agregarOperacionEn("invocar",(val_peek(3).ival))); maquina.agregar(null); }
break;
case 29:
//#line 133 "P2.y"
{yyval = val_peek(0); maquina.agregar("Limite");}
break;
case 30:
//#line 134 "P2.y"
{yyval = val_peek(2); maquina.agregar("Limite");}
break;
case 31:
//#line 137 "P2.y"
{yyval = new ParserVal(maquina.agregarOperacion("nop"));}
break;
case 32:
//#line 140 "P2.y"
{
				yyval = val_peek(13);
				maquina.agregar(val_peek(7).ival, val_peek(13).ival + 1);
				maquina.agregar(val_peek(2).ival, val_peek(13).ival + 2);
				maquina.agregar(maquina.numeroDeElementos() - 1, val_peek(13).ival + 3);
			}
break;
case 33:
//#line 146 "P2.y"
{
				yyval = val_peek(10);
				maquina.agregar(val_peek(4).ival, val_peek(10).ival + 1);
				maquina.agregar(val_peek(1).ival, val_peek(10).ival + 2);
				maquina.agregar(maquina.numeroDeElementos() - 1, val_peek(10).ival + 3);
			}
break;
case 34:
//#line 152 "P2.y"
{
				yyval = val_peek(9);
				maquina.agregar(val_peek(3).ival, val_peek(9).ival + 1);
				maquina.agregar(val_peek(0).ival, val_peek(9).ival + 2);
			}
break;
case 35:
//#line 157 "P2.y"
{
				yyval = val_peek(15);
				maquina.agregar(val_peek(10).ival, val_peek(15).ival + 1);
				maquina.agregar(val_peek(7).ival, val_peek(15).ival + 2);
				maquina.agregar(val_peek(3).ival, val_peek(15).ival + 3);
				maquina.agregar(val_peek(0).ival, val_peek(15).ival + 4);
			}
break;
case 38:
//#line 166 "P2.y"
{ 
				yyval = new ParserVal(val_peek(4).ival);
				maquina.agregar(null);
			}
break;
case 39:
//#line 171 "P2.y"
{
			yyval = new ParserVal(maquina.agregar((Funcion)(val_peek(0).obj)));
			}
break;
case 40:
//#line 176 "P2.y"
{ maquina.agregarOperacion("declaracion"); }
break;
case 41:
//#line 178 "P2.y"
{ maquina.agregarOperacion("declaracion"); }
break;
case 42:
//#line 181 "P2.y"
{yyval = new ParserVal(maquina.agregar(val_peek(0).sval));}
break;
case 43:
//#line 184 "P2.y"
{maquina.agregar(null);}
break;
case 44:
//#line 187 "P2.y"
{yyval = new ParserVal(maquina.agregarOperacion("stop"));}
break;
case 45:
//#line 190 "P2.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_if_then_else"));
	        maquina.agregarOperacion("stop");/*then*/
	        maquina.agregarOperacion("stop");/*else*/
	        maquina.agregarOperacion("stop");/*siguiente comando*/
		}
break;
case 46:
//#line 198 "P2.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_while"));
	        maquina.agregarOperacion("stop");/*cuerpo*/
	        maquina.agregarOperacion("stop");/*final*/
		}
break;
case 47:
//#line 205 "P2.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_for"));
	        maquina.agregarOperacion("stop");/*condicion*/
	        maquina.agregarOperacion("stop");/*instrucción final*/
	        maquina.agregarOperacion("stop");/*cuerpo*/
	        maquina.agregarOperacion("stop");/*final*/
		}
break;
case 48:
//#line 213 "P2.y"
{ yyval = new ParserVal(maquina.agregarOperacion("nop"));}
break;
case 49:
//#line 214 "P2.y"
{yyval = val_peek(0);}
break;
case 50:
//#line 215 "P2.y"
{yyval = val_peek(2);}
break;
//#line 969 "Parser.java"
//########## END OF USER-SUPPLIED ACTIONS ##########
    }//switch
    //#### Now let's reduce... ####
    if (yydebug) debug("reduce");
    state_drop(yym);             //we just reduced yylen states
    yystate = state_peek(0);     //get new state
    val_drop(yym);               //corresponding value drop
    yym = yylhs[yyn];            //select next TERMINAL(on lhs)
    if (yystate == 0 && yym == 0)//done? 'rest' state and at first TERMINAL
      {
      if (yydebug) debug("After reduction, shifting from state 0 to state "+YYFINAL+"");
      yystate = YYFINAL;         //explicitly say we're done
      state_push(YYFINAL);       //and save it
      val_push(yyval);           //also save the semantic value of parsing
      if (yychar < 0)            //we want another character?
        {
        yychar = yylex();        //get next character
        if (yychar<0) yychar=0;  //clean, if necessary
        if (yydebug)
          yylexdebug(yystate,yychar);
        }
      if (yychar == 0)          //Good exit (if lex returns 0 ;-)
         break;                 //quit the loop--all DONE
      }//if yystate
    else                        //else not done yet
      {                         //get next state and push, for next yydefred[]
      yyn = yygindex[yym];      //find out where to go
      if ((yyn != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn]; //get new state
      else
        yystate = yydgoto[yym]; //else go to new defred
      if (yydebug) debug("after reduction, shifting from state "+state_peek(0)+" to state "+yystate+"");
      state_push(yystate);     //going again, so push state & val...
      val_push(yyval);         //for next action
      }
    }//main loop
  return 0;//yyaccept!!
}
//## end of method parse() ######################################



//## run() --- for Thread #######################################
/**
 * A default run method, used for operating this parser
 * object in the background.  It is intended for extending Thread
 * or implementing Runnable.  Turn off with -Jnorun .
 */
public void run()
{
  yyparse();
}
//## end of method run() ########################################



//## Constructors ###############################################
/**
 * Default constructor.  Turn off with -Jnoconstruct .

 */
public Parser()
{
  //nothing to do
}


/**
 * Create a parser, setting the debug to true or false.
 * @param debugMe true for debugging, false for no debug.
 */
public Parser(boolean debugMe)
{
  yydebug=debugMe;
}
//###############################################################



}
//################### END OF CLASS ##############################
