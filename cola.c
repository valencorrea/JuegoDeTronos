#include <stdio.h>
#include <stdlib.h>
#include "cola.h"


#define CANTIDAD_NULA 0
#define EXITO 0
#define ERROR -1


cola_t* cola_crear(){
    cola_t* cola = malloc (sizeof(cola_t));
    
    if(!cola){
        return NULL;
    }
    else{
        cola->cantidad = CANTIDAD_NULA;
        cola->nodo_inicio = NULL;
        cola->nodo_fin = NULL;
    }
    return cola;
}

int cola_encolar(cola_t* cola, void* elemento){
    int estado = ERROR;
    nodo_t* nodo = malloc (sizeof(nodo_t));
    
    if(cola){
        if(nodo){
            if(cola->cantidad == CANTIDAD_NULA){
                cola->nodo_inicio = nodo;               
            }
            else{
                cola->nodo_fin->siguiente = nodo;
            }
            cola->nodo_fin = nodo;
            nodo->siguiente = NULL;
            nodo->elemento = elemento;
            cola->cantidad++;
            estado = EXITO;    
        }               
    }
    else{
        free(nodo);
    }
    return estado;
}

int cola_desencolar(cola_t* cola){
    int estado = ERROR;
    nodo_t* auxi;
    
    if(cola){
        if(cola->cantidad > CANTIDAD_NULA){
            if(cola->cantidad == 1){ 
                free(cola->nodo_inicio);
                cola->nodo_inicio = NULL;
                cola->nodo_fin = NULL;
            }
            else{
                auxi = cola->nodo_inicio;
                cola->nodo_inicio = auxi->siguiente; 
                free(auxi);
            }
            cola->cantidad--;
            estado = EXITO;
        }   
    }
    return estado;
}

bool cola_vacia(cola_t* cola){
    bool estado = false;
    if(!cola){
        estado = true;
    }
    else if(!cola->nodo_inicio){
        estado = true;
    }
    return estado;
}

int cola_cantidad(cola_t* cola){
    int cantidad = CANTIDAD_NULA;

    if(!cola){
        return cantidad;
    }
    else{
        cantidad = cola->cantidad;
    }
    return cantidad;
}

void* cola_primero(cola_t* cola){
    if(!cola){
        return NULL;
    }
    else if(cola->cantidad == CANTIDAD_NULA){
        return NULL;
    }
    return (cola->nodo_inicio->elemento);
}

void cola_destruir(cola_t* cola){
    if(!cola){
        return;
    }
    else{
        if(!cola_vacia(cola)){
            while(!cola_vacia(cola)){
                cola_desencolar(cola);
            }
        }    
        free(cola);
    }
}
