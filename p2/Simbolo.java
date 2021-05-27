class Simbolo {
	String nombre;
	public short tipo;
	double val;
        Dibujable dibu;
	public String metodo;
	int defn;
	Simbolo sig;
        Simbolo(){
		nombre="";
		val=0.0;
	}
        Simbolo(/*String s,*/ short t, double d)
	{
		//nombre=s;
		tipo=t;
		val=d;
	}
	Simbolo(String s, short t, double d){
		nombre=s;
		tipo=t;
		val=d;
	}
        public void ponDibu(Dibujable  d){
		dibu=d;
	}
        public Dibujable obtenDibu(){
		return dibu;
	}
        public Simbolo obtenSig()
        {
		return sig;
	}
        public void ponSig(Simbolo s)
	{
		sig=s;
	}
        public String obtenNombre()
	{
		return nombre;
	}
}
