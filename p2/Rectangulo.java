import java.awt.*;


public class Rectangulo implements Dibujable {
	private int x=0;
	private int y=0;
	private int ancho=0;
	private int alto=0;

	public Rectangulo(int x, int y, int ancho, int alto)
	{
		this.x=x;
        this.y=y;
		this.ancho=ancho;
		this.alto=alto;
	}
	public void dibuja(Graphics g)
	{
		g.drawRect(x,y,ancho,alto);
	}
}
