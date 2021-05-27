%{
import java.util.*;
import java.lang.Math;
import java.io.*;
import java.util.StringTokenizer;
import java.awt.*;
import java.awt.event.*;
import javax.imageio.*;
import java.awt.image.*;
import javax.swing.*;
import java.lang.reflect.*;
%}
%token NUMBER LINE CIRCULO RECTANGULO COLOR PRINT IMAGEN FILTRO
%start list
%%
list :
     | list ';'
     | list inst ';'   { 
             maq.code("print"); maq.code("STOP"); return 1 ;
     }   
     ;
inst:  NUMBER  { ((Algo)$$.obj).inst=maq.code("constpush");
                maq.code(((Algo)$1.obj).simb); }
      | RECTANGULO NUMBER NUMBER NUMBER NUMBER{
         maq.code("constpush");
         maq.code(((Algo)$2.obj).simb);
         maq.code("constpush");
         maq.code(((Algo)$3.obj).simb);
         maq.code("constpush");
         maq.code(((Algo)$4.obj).simb);
         maq.code("constpush");
         maq.code(((Algo)$5.obj).simb);
         maq.code("rectangulo");
         }
      | LINE NUMBER NUMBER NUMBER NUMBER{
               maq.code("constpush");
               maq.code(((Algo)$2.obj).simb);
               maq.code("constpush");
               maq.code(((Algo)$3.obj).simb);
               maq.code("constpush");
               maq.code(((Algo)$4.obj).simb);
               maq.code("constpush");
               maq.code(((Algo)$5.obj).simb);
               maq.code("line");}
      | CIRCULO NUMBER NUMBER NUMBER{
               maq.code("constpush");
               maq.code(((Algo)$2.obj).simb);
               maq.code("constpush");
               maq.code(((Algo)$3.obj).simb);
               maq.code("constpush");
               maq.code(((Algo)$4.obj).simb);
               maq.code("circulo");}
      | COLOR NUMBER { maq.code("constpush");
                maq.code(((Algo)$2.obj).simb); maq.code("color");}
      | IMAGEN NUMBER NUMBER {
              Simbolo s=new Simbolo();
              s.ponDibu(new Imagen(leeImagen("dalmata.jpg"), 
                (int)((Algo)$2.obj).simb.val, 
                (int)((Algo)$3.obj).simb.val, jf));
              maq.code("varpush");
              maq.code(s);  
              maq.code("draw");      
      }
      | FILTRO NUMBER NUMBER NUMBER NUMBER NUMBER NUMBER 
        NUMBER NUMBER NUMBER  {  
                      maq.code("constpush");
                      maq.code(((Algo)$2.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$3.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$4.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$5.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$6.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$7.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$8.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$9.obj).simb);
                      maq.code("constpush");
                      maq.code(((Algo)$10.obj).simb);
                     
                      Simbolo s=new Simbolo();
                      s.ponDibu(new Imagen(leeImagen("dalmata.jpg"), 
                100, 
                100, jf));
                      maq.code("varpush");
                      maq.code(s);  
                      maq.code("filtro");
}
      ;
%%
public BufferedImage leeImagen(String nombre){
   BufferedImage imagen;
   try {
      imagen = ImageIO.read(new File(nombre));     
   } catch (IOException e){
        System.err.println("no cargo "+nombre);
        return null;
   }
   return imagen;
   }
class Algo {
	Simbolo simb;
	int inst;
        Dibujable dibu;
	public Algo(int i){ inst=i; }
        public Algo(Dibujable d){ dibu=d; }
	public Algo(Simbolo s, int i){
		simb=s; inst=i;
	}
}
public void setTokenizer(StringTokenizer st){
 	this.st= st;
}
public void setNewline(boolean newline){
 	this.newline= newline;
}
//Tabla tabla;
HashMap<String, Simbolo> tabla=new HashMap<String, Simbolo>();
Maquina maq;

StringTokenizer st;
boolean newline;
int yylex(){
String s;
int tok;
Double d;
Simbolo simbo;
   if (!st.hasMoreTokens())
      if (!newline) {
         newline=true; 
	 return ';';  
      }
   else
      return 0;
   s = st.nextToken();
   try {
      d = Double.valueOf(s);
      simbo=new Simbolo(NUMBER, d.doubleValue());
      yylval = new ParserVal(new Algo(simbo, 0) );
      tok = NUMBER;
   } catch (Exception e){
   if(Character.isLetter(s.charAt(0))){
	if((simbo=tabla.get(s))!=null){
           yylval = new ParserVal(new Algo(simbo, 0));  
        }	
         tok= simbo.tipo;
    } else {
    	tok = s.charAt(0);
    }
   /*if(Character.isLetter(s.charAt(0))){
      System.out.println("s es = ("+s+")");
      if((simbo=tabla.lookup(s))==null)
         yylval = new ParserVal(new Algo(simbo, 0));
	 tok= simbo.tipo;	
      }*/ 
   }
   return tok;
}
void yyerror(String s){
   System.out.println("parser error: "+s);
}
static Parser par = new Parser(0);
static JFrame jf;
static JLabel lmuestra=new JLabel("                                 ");
static Canvas canv;
static Graphics g;
Parser(int foo){
   maq=new Maquina();
   //tabla=new Tabla();
 try {
   Method[] ma = ((Maquina)maq).getClass().getMethods();
   for (Method m : ma) {  
            Class[] parameters = m.getParameterTypes();
            if( m.getReturnType().equals(Void.TYPE) && 
                m.getParameterTypes().length==0){
                System.out.println( m.getName()  + " returns void ");
            }  
   } 
  } catch (Exception e) {
       e.printStackTrace();
  }
   tabla.put("line", new Simbolo(LINE, 0.0));
   tabla.put("circulo", new Simbolo(CIRCULO, 0.0));
   tabla.put("rectangulo", new Simbolo(RECTANGULO, 0.0));
   tabla.put("color", new Simbolo(COLOR, 0.0));
   tabla.put("print", new Simbolo( PRINT, 0.0));
   tabla.put("ima", new Simbolo(IMAGEN, 0.0));
   tabla.put("fil", new Simbolo(FILTRO, 0.0));
   maq.setTabla(tabla);
   jf=new JFrame("Calcula");
   canv=new Canvas();
   canv.setSize(600,600);
   jf.add("North", new PanelEjecuta(maq, this));
   jf.add("Center", canv);
   jf.setSize( 600, 700);
   jf.setVisible(true);
   g=canv.getGraphics();
   maq.setGraphics(g);
   jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);  
}
public static void main(String args[]){ new Parser(); }
