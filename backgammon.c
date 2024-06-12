#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"elemCircular.h"
#include"bicola.h"
#include"circular.h"

Circular inicializa();
void impTablero(Circular);
int tirarDados();
int decidirTurno();
int absoluto(int);
Circular completarRecorrido(Circular, int, char);
int recorrer(Circular, int,char);
int comprobarMov(Circular, int, int, char);
Circular recorrido(Circular, int, int, int, char, int[]);

int main(){
    int jugador = 0, puntaje_N = 0, puntaje_B = 0, movimiento = 0, band = 0, posicion = 0, resultado = 0, caso = 0, intentos = 0;
    Circular tablero = inicializa();
    Elem banca[2] = {0,0};
    srand(time(0));

    jugador = decidirTurno();

    impTablero(tablero);

    while((puntaje_B>-15)&&(puntaje_N<15)){
        resultado = tirarDados();
        printf("N: %d vs %d :B\n",puntaje_N,puntaje_B);
        if(jugador == 0){
            intentos = 0;
            printf("Jugador N\n");
            while((resultado>0)&&(intentos<3)&&(puntaje_N!=15)){
                printf("%d es el resultado de los dados\n",resultado);
                if(banca[0] != 0){
                    printf("Posicion = 0\n");
                    posicion = 0;
                }
                else{
                    printf("Ingrese la posicion de la ficha que desea mover: ");
                    do{
                        scanf("%d", &posicion);
                        band = recorrer(tablero, posicion, 'n');
                        if(!band)
                            printf("Casilla incorrecta, seleccionar otra: ");
                    }while(!band);
                }
                printf("Ingrese el numero de casillas que desea recorrer: ");
                do{
                    scanf("%d", &movimiento);
                    if(resultado - movimiento < 0)
                        printf("La cantidad que se desea recorrer es superior al resultado de los dados, ingrese otra cantidad: ");
                    else if(posicion + movimiento > 25)
                        printf("No puede recorrer tantas casillas, ya que quedaria fuera del tablero, ingrese otra cantidad: ");
                }while(resultado - movimiento < 0 || posicion + movimiento > 25);
                caso = comprobarMov(tablero, posicion, movimiento, 'n');
                if(caso){
                    resultado -= movimiento;
                    tablero = recorrido(tablero, posicion, movimiento, caso, 'n', banca);
                } else if(caso == 2){
                    resultado -= movimiento;
                    tablero = recorrido(tablero, posicion, movimiento, caso, 'n', banca);
                } else{
                    printf("No se puede realizar el movimiento, hay mas fichas en la posicion final, favor de escoger de nuevo. \n");
                    tablero = completarRecorrido(tablero,0,'n');
                    intentos ++;
                    printf("intento %d / 3\n",intentos);
                    if(intentos == 3){
                        printf("Omitiendo turno\n");
                        impTablero(tablero);
                        break;
                    }
                }
                impTablero(tablero);
                tablero = rotaDer(tablero);
                puntaje_N = primeroC(tablero);
                tablero =  rotaIzq(tablero);
            }
            tablero = rotaDer(tablero);
            puntaje_N = primeroC(tablero);
            jugador = 1;
        } else{
            intentos = 0;
            printf("Jugador B\n");
            while((resultado>0)&&(intentos<3)&&(puntaje_B!=-15)){
                printf("%d es el resultado de los dados\n",resultado);
                if(banca[1] != 0){
                    printf("Posicion = 0\n");
                    posicion = 0;
                } else{
                    printf("Ingrese la posicion de la ficha que desea mover: ");
                    do{
                        scanf("%d", &posicion);
                        band = recorrer(tablero, posicion, 'b');
                        if(!band)
                            printf("Casilla incorrecta, seleccionar otra: ");
                    }while(!band);
                }
                printf("Ingrese el numero de casillas que desea recorrer: ");
                do{
                    scanf("%d", &movimiento);
                    if(resultado - movimiento < 0)
                        printf("La cantidad que se desea recorrer es superior al resultado de los dados, ingrese otra cantidad: ");
                    else if(posicion + movimiento > 25)
                        printf("No puede recorrer tantas casillas, ya que quedaria fuera del tablero, ingrese otra cantidad: ");
                }while(resultado - movimiento < 0 || posicion + movimiento > 25);
                caso = comprobarMov(tablero, posicion, movimiento, 'b');
                if(caso){
                    resultado -= movimiento;
                    tablero = recorrido(tablero, posicion, movimiento, caso, 'b', banca);
                } else if(caso == 2){
                    resultado -= movimiento;
                    tablero = recorrido(tablero, posicion, movimiento, caso, 'b', banca);
                } else{
                    printf("No se puede realizar el movimiento, hay mas fichas en la posicion final, favor de escoger de nuevo. \n");
                    tablero = completarRecorrido(tablero,1,'b');
                    intentos ++;
                    printf("intento %d / 3\n",intentos);
                    if(intentos == 3){
                        printf("Omitiendo turno\n");
                        impTablero(tablero);
                        tablero = rotaDer(tablero);
                        break;
                    }
                }
                impTablero(tablero);
                puntaje_B = primeroC(tablero);
                tablero = rotaDer(tablero);
            }
            tablero = rotaIzq(tablero);
            puntaje_B = primeroC(tablero);
            jugador = 0;
        }
    }

    if(puntaje_N == 15)
        printf("Jugador N ganador\n");
    else
        printf("jugador B ganador\n");

    return 0;
}

Circular inicializa(){
    int i;
    Elem valores[26] = {0,-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2,0};
    Circular circular = nuevaC();
    for(i = 0; i<26; i++){
        circular = formarC(circular,valores[i]);
    }
    return circular;
}

void impTablero(Circular tablero){
    printf("\n\n\n");
    int i;
    printf("El tablero es: \n Jugador N\t");    
    for(i = 1; i<=26; i++){
        if(i<14)
            printf("%d \t",primeroC(tablero));
        tablero = rotaIzq(tablero);
    }
    printf("\n Jugador B\t");
    for(i = 1; i<=26; i++){
        tablero = rotaDer(tablero);
        if(i<14)
            printf("%d \t",primeroC(tablero));
    }
    printf("\n\n");
}

int tirarDados(){
    int dado1 = 0, dado2 = 0;
    dado1 = (rand() % 6) + 1;
    dado2 = (rand() % 6) + 1;
    return dado1+dado2;
};

int decidirTurno(){
    int jugadorN = 0, jugadorB = 0;
    jugadorN = tirarDados();
    jugadorB = tirarDados();

    printf("El jugador N obtuvo %d al tirar los dados\n",jugadorN);
    printf("El jugador B obtuvo %d al tirar los dados\n",jugadorB);
    if(jugadorN > jugadorB){
        printf("El jugador N inicia la partida\n");
        return 0;
    }else if(jugadorB > jugadorN){
        printf("El jugador B inicia la partida\n");
        return 1;
    }else{
        printf("Ambos obtuvieron el mismo resultado, van a  volver a tirar los dados\n");
        return decidirTurno();
    }
}

Elem absoluto(Elem n){
    if(n<0)
        return -n;
    else
        return n;
};

Circular completarRecorrido(Circular tablero, int pos, char jugador){
    int i, n = 26 - pos;
    if(jugador == 'n'){
        for(i = 0; i<n; i++)
            tablero = rotaIzq(tablero);
        return tablero;
    } else{
        for(i = 0; i<n; i++)
            tablero = rotaDer(tablero);
        return tablero;
    }
}

int recorrer(Circular tablero, int pos, char jugador){
    int i;
    Elem valor = 0;
    if(pos >= 25)
        return 0;
    else if(jugador == 'n'){
        for(i = 0; i<pos; i++){
            tablero = rotaIzq(tablero);
        }
        valor = primeroC(tablero);
        if(valor <= 0){
            tablero = completarRecorrido(tablero, pos,jugador);
            return 0;
        }
    }else if(jugador == 'b'){
        for(i = 0; i<pos; i++){
            tablero = rotaDer(tablero);
        }
        valor = primeroC(tablero);
        if(valor >= 0){
            tablero = completarRecorrido(tablero, pos,jugador);
            return 0;
        }
    }      
    if(valor == 0){
        return 0;
    }
    tablero = completarRecorrido(tablero, pos,jugador);
    return 1;
}

int comprobarMov(Circular tablero, int inicial, int final, char jugador){
    Elem valorMov = 0, valorPos = 0;
    int i;
    if(jugador == 'n'){
        valorMov = 1;
        for(i = 0; i<(inicial + final); i++){
            tablero = rotaIzq(tablero);
        }
    } else{
        valorMov = -1;
        for(i = 0; i<(inicial + final); i++){
            tablero = rotaDer(tablero);
        }
    }
    valorPos = primeroC(tablero);
    tablero = completarRecorrido(tablero, inicial+final, jugador);
    if(compararElem(absoluto(valorMov),absoluto(valorPos))&&(valorMov != valorPos))
        return 1;
    else if((valorMov > 0 && valorPos > 0)||(valorMov < 0 && valorPos < 0))
        return 2;
    return 0;
}

Circular recorrido(Circular tablero, int inicial, int final, int caso, char jugador, int banca[]){
    int i, n = 26-inicial-final; 
    Elem valorPos = 0;
    if(jugador == 'n'){
        for(i = 0; i<inicial; i++){
            tablero = rotaIzq(tablero);
        }

        if(banca[0] != 0)
            banca[0] = 0;
        else{
            tablero = formarC(tablero,primeroC(tablero)-1);
            tablero = desformarC(tablero);
            tablero = rotaDer(tablero);
        }

        for(i = 0; i<final; i++){
            tablero = rotaIzq(tablero);
        }
        valorPos = primeroC(tablero);

        if(caso == 2){
            tablero = formarC(tablero,1+valorPos);
            tablero = desformarC(tablero);
            tablero = rotaDer(tablero);
        }else{
            tablero = formarC(tablero,1);
            tablero = desformarC(tablero);
            tablero = rotaDer(tablero);
            banca[1] = valorPos; 
        }

        for(i = 0; i<n; i++){
            tablero = rotaIzq(tablero);
        }
        
    } else{
        for(i = 0; i<inicial; i++){
            tablero = rotaDer(tablero);
        }

        if(banca[1] != 0)
            banca[1] = 0;
        else{
            tablero = formarC(tablero,primeroC(tablero)+1);
            tablero = desformarC(tablero);
            tablero = rotaDer(tablero);
        }
        
        for(i = 0; i<final; i++){
            tablero = rotaDer(tablero);
        }
        valorPos = primeroC(tablero);
        
        if(caso == 2){
            tablero = formarC(tablero,-1+valorPos);
            tablero = desformarC(tablero);
            tablero = rotaDer(tablero);
        } else{
            tablero = formarC(tablero,-1);
            tablero = desformarC(tablero);
            tablero = rotaDer(tablero);
            banca[0] = valorPos;
        }
        
        for(i = 0; i<n-1; i++){
            tablero = rotaDer(tablero);
        }
    }
    return tablero;
}