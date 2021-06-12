package vista;

import java.awt.Color;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;
import modelo.Configuracion;
import modelo.Linea;
import modelo.compilador.Parser;

public class VentanaPrincipal extends JFrame {

    JTextArea areaDeCodigo;
    JScrollPane scrollCodigo;
    PanelDeDibujo panelDeDibujo;
    JButton ejecutar;
    JButton debug;
    JButton siguiente;
    Parser parser;
    boolean modoDebug;
    
    public VentanaPrincipal(){
        
        super("Mini Logo");
        
        modoDebug = false;
        
        parser = new Parser();
        parser.insertarInstrucciones();
        
        areaDeCodigo = new JTextArea(20,20);
        scrollCodigo = new JScrollPane (areaDeCodigo);
        scrollCodigo.setBounds(10,10,250,550);
        add(scrollCodigo);
        
        panelDeDibujo = new PanelDeDibujo();
        panelDeDibujo.setBounds(270,10,Propiedades.PANEL_DE_DIBUJO_ANCHO,Propiedades.PANEL_DE_DIBUJO_LARGO);
        
        add(panelDeDibujo);
        
        ejecutar = new JButton(new ImageIcon(System.getProperty("user.dir") + "/Play.png"));
        ejecutar.setBounds(10,570,100,90);
        ejecutar.addActionListener(new ActionListener(){

            @Override
            public void actionPerformed(ActionEvent ae) {
                parser.limpiar();
                if(parser.compilar(areaDeCodigo.getText()))
                    panelDeDibujo.setConfiguracion(parser.ejecutar());
                else{
                    parser = new Parser();
                    parser.insertarInstrucciones();
                    panelDeDibujo.setConfiguracion(parser.getConfiguracion());
                }
                panelDeDibujo.repaint();
            }
        });
        add(ejecutar);
        
        debug = new JButton(new ImageIcon(System.getProperty("user.dir") + "/Debug.png"));
        debug.setBounds(110,570,100,90);
        debug.addActionListener(new ActionListener(){

            @Override
            public void actionPerformed(ActionEvent ae) {
                parser.limpiar();
                if(!modoDebug){
                    if(parser.compilar(areaDeCodigo.getText())){
                        panelDeDibujo.setConfiguracion(parser.getConfiguracion());
                        cambiarDebug();
                    }
                    else{
                        parser = new Parser();
                        parser.insertarInstrucciones();
                        panelDeDibujo.setConfiguracion(parser.getConfiguracion());
                    }
                }
                else{
                    cambiarDebug();
                }
                panelDeDibujo.repaint();
            }
        });
        add(debug);
        
        siguiente = new JButton(new ImageIcon(System.getProperty("user.dir") + "/Next.png"));
        siguiente.setBounds(210,570,50,90);
        siguiente.addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent ae) {
                parser.ejecutarSiguiente();
                panelDeDibujo.setConfiguracion(parser.getConfiguracion());
                panelDeDibujo.repaint();
            }
        });
        siguiente.setEnabled(false);
        add(siguiente); 
        setLayout(null);
        setBounds(50,50,1000,700);
        setVisible(true);
        setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
        
    }
    
    private void cambiarDebug(){
        if(!modoDebug){
            areaDeCodigo.setEnabled(false);
            ejecutar.setEnabled(false);
            siguiente.setEnabled(true);
        }
        else{
           areaDeCodigo.setEnabled(true);
            ejecutar.setEnabled(true);
            siguiente.setEnabled(false); 
        }
        modoDebug = !modoDebug;
    }
}
