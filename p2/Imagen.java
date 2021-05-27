import java.awt.Image.* ;
import java.awt.Toolkit.* ;
import java.awt.*;
import java.io.Serializable;
import javax.swing.*;
public class Imagen implements Dibujable {
	private int x=0, y=0,r=0;
	//String cade ;
	 ImageIcon imagen ;
         public Image ima ;
	 transient Container con ;
	public Imagen(Image ima){
                this.ima=ima ;
	}
	public Imagen(/*String cade,*/ImageIcon imagen, int x, int y, Container con){
		this.y=y;
		this.con=con;
		this.x=x ;
                this.imagen=imagen ;	
		//this.cade=cade ;
	}
        public Imagen(Image ima, int x, int y, Container con){
		this.y=y;
		this.con=con;
		this.x=x ;
                this.ima=ima ;
		//this.cade=cade ;
	}
        public void transladar(int dx,int dy) {
        	this.x+=dx; this.y+=dy;
                //this.x2+=dx; this.y2+=dy;
    	}
        public void escalar(int dx, int dy){}
        public void dibuja(Graphics g){
		//g.drawImage (imagen.getImage(), x, y, con);
                g.drawImage (ima, x, y, con);
	}
}
