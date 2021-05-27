#include <string.h>
struct complejo {
  double real, img;
};

typedef struct complejo Complejo;
typedef struct complejo *ComplejoAP;

/*  prototypes of the provided functions */ 
Complejo *creaComplejo(int real, int img);
Complejo *Complejo_add(Complejo *, Complejo *);
Complejo *Complejo_sub(Complejo *, Complejo *);
Complejo *Complejo_mul(Complejo *, Complejo *);
Complejo *Complejo_div(Complejo *, Complejo *);
void imprimirC(Complejo *c);

/*  prototypes of the provided functions */ 
/* define the return type of FLEX */
#define YYSTYPE ComplejoAP
