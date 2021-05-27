import java.awt.*;
import java.awt.image.*;
import java.util.*;

class Filtradora {
   private BufferedImage foto;    
   private Hashtable mOps;
   public Filtradora(){ mOps = new Hashtable(); }  
   void procesa(String key, BufferedImage fSrcImage){
      BufferedImageOp op = (BufferedImageOp)mOps.get(key);
      this.foto = op.filter(fSrcImage, null);
   }
   public void ponFiltro(Kernel kernel){
      mOps.put("User", new ConvolveOp(kernel) );
   }
   public BufferedImage getFoto(){  return foto; }  
}

