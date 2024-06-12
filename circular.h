#ifndef circular_h
#define circular_h

#include"BiCola.h"

typedef BiCola Circular;

Circular nuevaC(){return nuevaBC();}

Circular formarC(Circular c, Elem e){ return formarDerBC(c,e);}

int esnuevaC(Circular c){return esnuevaBC(c);}

Elem primeroC(Circular c){return izquierdoBC(c);}

Circular desformarC(Circular c){return desformarIzqBC(c);}

Circular rotaIzq(Circular c){
    return desformarIzqBC(formarDerBC(c,izquierdoBC(c)));}

Circular rotaDer(Circular c){
    return desformarDerBC(formarIzqBC(derechoBC(c),c));}

#endif