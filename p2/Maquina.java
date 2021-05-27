import java.awt.*;
import java.awt.image.*;
import java.util.*;
import java.lang.reflect.*;

class  Maquina {
   Filtradora poste;
   HashMap<String, Simbolo> tabla;
   Stack pila;
   ArrayList prog;

   static int pc=0;
   int progbase=0;
   boolean returning=false;

   Method metodo;
   Method metodos[];
   Class c;
   Graphics g;
   double angulo;
   int x=0, y=0;
   Class parames[];
   Maquina(){ 
      poste= new Filtradora( ); 
   }
   public void setTabla(HashMap<String, Simbolo> t){ tabla = t; }
   public void setGraphics(Graphics g){ this.g=g; }
   Maquina(Graphics g){ this.g=g; }
   public ArrayList getProg(){ return prog; }
   void initcode(){
      pila=new Stack();
      prog=new ArrayList();
   }
   Object pop(){ return pila.pop(); }
   int code(Object f){
      System.out.println("Gen ("+f+") size="+prog.size());
      prog.add(f);
      return prog.size()-1;
   }
   void execute(int p){
      String inst;
      System.out.println("progsize="+prog.size());
      for(pc=0;pc < prog.size(); pc=pc+1){
         System.out.println("pc="+pc+" inst "+prog.get(pc));
      }
      for(pc=p; !(inst=(String)prog.get(pc)).equals("STOP") && !returning;){
	 //for(pc=p;pc < prog.size();){
         try {
	    //System.out.println("111 pc= "+pc);
	    inst=(String)prog.get(pc);
	    pc=pc+1;
	    System.out.println("222 pc= "+pc+" instr "+inst);
            c=this.getClass();
	    //System.out.println("clase "+c.getName());
            metodo=c.getDeclaredMethod(inst, null);
	    metodo.invoke(this, null);
	 } catch(NoSuchMethodException e){
				System.out.println("No metodo "+e);
         } catch(InvocationTargetException e){
				System.out.println(e);
         } catch(IllegalAccessException e){
				System.out.println(e);
         }
      }
   }
   public void constpush(){
      Simbolo s;
      Double d;
      s=(Simbolo)prog.get(pc);
      pc=pc+1;
      pila.push(new Double(s.val));
   }
   public void varpush(){
      Simbolo s;
      double d;
      //System.out.println("varpush ");
      s=(Simbolo)prog.get(pc);
      pc=pc+1;
      pila.push(s);
   }
   public void color(){
      Color colors[]={Color.red,Color.green,Color.blue};
      double d1;
      d1=((Double)pila.pop()).doubleValue();
      if(g!=null){
         g.setColor(colors[(int)d1]);
      }
   }

   public void line(){
      double x1, y1, x2, y2;
      y2=((Double)pila.pop()).doubleValue();
      x2=((Double)pila.pop()).doubleValue();
      y1=((Double)pila.pop()).doubleValue();
      x1=((Double)pila.pop()).doubleValue();
      if(g!=null){
         new Linea((int)x1,(int)y1,(int)x2,(int)y2).dibuja(g);
      }
      x=(int)(x1);
      y=(int)(y1);
      System.out.println("x = "+x+" y = "+y+" d1 = "+(x2-x1+y2-y1));
   }

   public void circulo(){
      double x, y, r;
      r=((Double)pila.pop()).doubleValue();
      y=((Double)pila.pop()).doubleValue();
      x=((Double)pila.pop()).doubleValue();
      if(g!=null){
         new Circulo((int)x, (int)y, (int)r).dibuja(g);
      }
   }
   public void rectangulo(){
      double ancho, alto, x, y;
      alto=((Double)pila.pop()).doubleValue();
      ancho=((Double)pila.pop()).doubleValue();
      y=((Double)pila.pop()).doubleValue();
      x=((Double)pila.pop()).doubleValue();
      if(g!=null){
         new Rectangulo((int)x,(int)y,(int)ancho,(int)alto).dibuja(g);
      }
   }
   public void draw(){      
      Simbolo s;
      Dibujable dibu;       
      s=(Simbolo)pila.pop();
      System.out.println("draw ( "+s.nombre+" )");
      dibu=s.obtenDibu();
      if(g!=null && dibu != null){
         System.out.println("draw DIBUJAR");
         dibu.dibuja(g);
         pila.push(dibu);
      }
   }
   public void filtro(){
      Simbolo s;
      Dibujable dibu;
      Imagen ima;
      System.err.println("FILTRO filtro");         
      s=(Simbolo)pila.pop();
      System.out.println("draw ( "+s.nombre+" )");
      dibu=s.obtenDibu(); 
      if(dibu != null){    
         System.out.println("if filtro");
         ima=(Imagen)dibu;
         //poste.set_Escala_de_Grises((BufferedImage)ima.ima);
         float[] kernel = new float[9];
         for (int i = 0; i < 9; i++) {
            kernel[i] = (float)(((Double)pila.pop()).doubleValue());
         }
         System.out.println("desp for filtro");
         poste.ponFiltro(new Kernel(3, 3, kernel));
         poste.procesa("User", (BufferedImage)ima.ima);
         new Imagen(poste.getFoto()).dibuja(g) ;
      }
      /*poste.set_Escala_de_Grises(leeImagen("Imagen.jpg"));
      System.err.println("antes dibujar ");
      new Imagen(poste.getFoto(), 100, 100, con).dibujar(g);*/        
   }
   public void print(){
      Double d;
      d=(Double)pila.pop();
      System.out.println(""+d.doubleValue());
   }
   public void prexpr(){
      Double d;
      d=(Double)pila.pop();
      System.out.print("["+d.doubleValue()+"]");
   }
}
