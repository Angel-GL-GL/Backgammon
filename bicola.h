#ifndef bicola_h
#define bicola_h

typedef struct NodoBC{
    Elem dato;
    struct NodoBC *der;
    struct NodoBC *izq;
}*ApNodoBC;

typedef struct BCnodo{
    ApNodoBC izq;
    ApNodoBC der;
}*BiCola;


BiCola nuevaBC(){
    BiCola t = (BiCola)malloc(sizeof(struct BCnodo));
    t->izq=t->der=NULL;
    return t;
}

int esnuevaBC(BiCola q){return (q->izq == NULL)&&(q->der == NULL);};

BiCola formarIzqBC(Elem e, BiCola q){
    ApNodoBC t=(ApNodoBC)malloc(sizeof(struct NodoBC));
    t->dato = e; 
    t->izq=t->der=NULL;
    if(esnuevaBC(q)){
        q->izq=q->der=t;
    }else{
        q->izq->izq = t;
        t->der = q->izq;
        q->izq = t;
    }
    return q;
}

BiCola formarDerBC(BiCola q, Elem e){
    ApNodoBC t=(ApNodoBC)malloc(sizeof(struct NodoBC));
    t->dato = e; 
    t->der=t->izq=NULL;
    if(esnuevaBC(q)){
        q->der=q->izq=t;
    }else{
        q->der->der = t;
        t->izq = q->der;
        q->der = t;
    }
    return q;
}

Elem izquierdoBC(BiCola q){return q->izq->dato;};

Elem derechoBC(BiCola q){return q->der->dato;};

BiCola desformarIzqBC(BiCola q){
    if(q->izq==q->der){
        free(q->izq);
        free(q);
        return nuevaBC();
    } else{
        ApNodoBC t;
        t=q->izq;
        q->izq = q->izq->der;
        q->izq->izq = NULL;
        free(t);
        return q;
    }
}

BiCola desformarDerBC(BiCola q){
    if(q->der == q->izq){
        free(q->der);
        free(q);
        return nuevaBC();
    } else{
        ApNodoBC t;
        t=q->der;
        q->der = q->der->izq;
        q->der->der = NULL;
        free(t);
        return q;
    }
}

#endif