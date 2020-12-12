#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define EXITO 0
#define ERROR -1
#define PRIMER_ELEMENTO 0
#define SEGUNDO_ELEMENTO 1
#define UNICO_ELEMENTO 1
#define LISTA_VACIA 0
#define INICIO_ITERACION 0
#define CANTIDAD_INICIAL 0

typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}nodo_t;

struct lista{
    nodo_t* nodo_inicio;
    nodo_t* nodo_fin;
    int cantidad_elem;
};

struct lista_iterador{
    nodo_t* corriente;
    lista_t* lista;
    bool pos_inicial;
};


/*
 * Procedimiento que recibe una lista e inicializa todos sus campos.
 */
void inicializar_lista(lista_t* lista);

/*
 * Procedimiento que renueva los valores de la lista luego de la insercion de un nuevo 
 * elemento. La lista tiene al menos un elemento.
 */
void actualizar_luego_de_insertar(lista_t* lista, void* elemento, nodo_t* nodo_nuevo);

/*
 * Procedimiento que se fija la posicion recibida y ubica al elemento en la misma, teniendo en 
 * cuenta la cantidad actual de la lista.
 */
void ubicar_elemento(lista_t* lista, void* elemento, size_t posicion, nodo_t* nodo_nuevo);

/*
 * Procedimiento que borra el unico elemento almacenado en la lista dejandola vacia.
 */
void borrar_unico_elemento(lista_t* lista);

/*
 * Procedimiento que elimina un elemento de la lista cuando esta tiene mas de un elemento.
 */
void borrar_un_elemento(lista_t* lista);

/*
 * Procedimiento que busca una posicion recibida dentro de la lista y elimina aquel elemento.
 * Este elemento no sera ni el de la posicion 0 ni el de la ultima.
 */
void borrar_elemento_seleccionado(lista_t* lista, size_t posicion);


lista_t* lista_crear(){
    lista_t* lista = (lista_t*) malloc (sizeof(lista_t));

    if(!lista){
        return NULL;
    }
    inicializar_lista(lista);
    return lista;
}

void inicializar_lista(lista_t* lista){
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    lista->cantidad_elem = LISTA_VACIA;
}

int lista_insertar(lista_t* lista, void* elemento){
    int estado = ERROR;    
    
    if(lista){
        nodo_t* nodo_nuevo = (nodo_t*) malloc (sizeof(nodo_t));
        if(nodo_nuevo){
            if(lista->cantidad_elem == CANTIDAD_INICIAL){
                lista->nodo_inicio = nodo_nuevo;
            }
            else{
                lista->nodo_fin->siguiente = nodo_nuevo;
            }      
            actualizar_luego_de_insertar(lista, elemento, nodo_nuevo);
            estado = EXITO;
        }
    }    
    return estado;
}

void actualizar_luego_de_insertar(lista_t* lista, void* elemento, nodo_t* nodo_nuevo){
    nodo_nuevo->siguiente = NULL;
    nodo_nuevo->elemento = elemento;
    lista->nodo_fin = nodo_nuevo;
    lista->cantidad_elem++;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    int estado = ERROR;

    if(lista){
        if(posicion >= lista->cantidad_elem){
            estado = lista_insertar(lista, elemento);
        }
        else{
            nodo_t* nodo_nuevo = (nodo_t*) malloc (sizeof(nodo_t));
            if(nodo_nuevo){
                ubicar_elemento(lista, elemento, posicion, nodo_nuevo);
                estado = EXITO;
            }
        }
    }    
    return estado;
}

void ubicar_elemento(lista_t* lista, void* elemento, size_t posicion, nodo_t* nodo_nuevo){
    nodo_t* nodo_auxi;
    
    if(posicion == PRIMER_ELEMENTO){
        nodo_nuevo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nodo_nuevo;
    }
    else if(posicion == SEGUNDO_ELEMENTO){
        nodo_nuevo->siguiente = lista->nodo_inicio->siguiente;
        lista->nodo_inicio->siguiente = nodo_nuevo;
    }
    else{
        nodo_auxi = lista->nodo_inicio;
        for(int i=INICIO_ITERACION; i<(posicion-1); i++){
            nodo_auxi = nodo_auxi->siguiente;
        }      
        nodo_nuevo->siguiente = nodo_auxi->siguiente;
        nodo_auxi->siguiente = nodo_nuevo;
    }
    nodo_nuevo->elemento = elemento;
    lista->cantidad_elem++;
}

int lista_borrar(lista_t* lista){
    int estado = ERROR;
    
    if(lista){
        if(lista->cantidad_elem != CANTIDAD_INICIAL){
            if(lista->cantidad_elem == UNICO_ELEMENTO){
                borrar_unico_elemento(lista);
            }
            else if(lista->cantidad_elem > UNICO_ELEMENTO){
                borrar_un_elemento(lista);
            }
            lista->cantidad_elem--;
            estado = EXITO; 
        }
    }
    return estado;
}

void borrar_unico_elemento(lista_t* lista){
    free(lista->nodo_inicio);
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
}

void borrar_un_elemento(lista_t* lista){
    nodo_t* nodo_iterador = NULL;
    nodo_t* nodo_liberador = NULL;

    nodo_iterador = lista->nodo_inicio;
    for(int i=INICIO_ITERACION; i<lista->cantidad_elem-2; i++){
        nodo_iterador = nodo_iterador->siguiente;
    }
    nodo_liberador = nodo_iterador->siguiente;
    lista->nodo_fin = nodo_iterador;
    nodo_iterador->siguiente = NULL;
    free(nodo_liberador);
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    int estado = ERROR;
    nodo_t* nodo_liberador = NULL;
    
    if(lista){    
        if(lista->cantidad_elem != CANTIDAD_INICIAL){
            if(posicion<(lista->cantidad_elem-1)){
                if(posicion == PRIMER_ELEMENTO){
                    nodo_liberador = lista->nodo_inicio;
                    lista->nodo_inicio = lista->nodo_inicio->siguiente;
                    free(nodo_liberador);
                }
                else{                
                    borrar_elemento_seleccionado(lista, posicion);
                }
                lista->cantidad_elem--;
                estado = EXITO;
            }
            else{
                if(lista_borrar(lista) == EXITO){
                    estado = EXITO;
                }
            }
        }
    }
    return estado;
}

void borrar_elemento_seleccionado(lista_t* lista, size_t posicion){
    nodo_t* nodo_iter = NULL;
    nodo_t* nodo_liberador = NULL;
    
    nodo_iter = lista->nodo_inicio;
    for(int i=INICIO_ITERACION;i<posicion-1;i++){
        nodo_iter = nodo_iter->siguiente;
    }
    nodo_liberador = nodo_iter->siguiente;
    nodo_iter->siguiente = nodo_liberador->siguiente; 
    free(nodo_liberador);
}

void* lista_elemento_en_posicion (lista_t* lista, size_t posicion){
    void* elemento = NULL;
    nodo_t* nodo_auxi = NULL;
    
    if((lista) && (posicion < lista->cantidad_elem)){
        nodo_auxi = lista->nodo_inicio;
        if(posicion == PRIMER_ELEMENTO){
            elemento = nodo_auxi->elemento;
        }
        else if(posicion == SEGUNDO_ELEMENTO){
            elemento = nodo_auxi->siguiente->elemento;
        }
        else{
            for(int i=INICIO_ITERACION; i<posicion; i++){
                nodo_auxi = nodo_auxi->siguiente;
            }
            elemento = nodo_auxi->elemento;
        }
    }
    return elemento;
}

void* lista_ultimo(lista_t* lista){
    void* elemento = NULL;
    
    if(lista){
        if(lista->cantidad_elem > CANTIDAD_INICIAL){
            elemento = lista->nodo_fin->elemento;
        }
    }
    return elemento;
}

bool lista_vacia(lista_t* lista){
    bool estado = false;
    
    if(!lista){
        estado = true;
    }
    else{
        if(lista->cantidad_elem == CANTIDAD_INICIAL){
            estado = true;
        }
    }
    return estado;
}

size_t lista_elementos(lista_t* lista){
    size_t elementos = LISTA_VACIA;
    
    if(lista){
        elementos = (size_t)lista->cantidad_elem;
    }
    return elementos;
}

void lista_destruir(lista_t* lista){
    if(!lista){
        return;
    }    
    bool esta_vacia = lista_vacia(lista);
    while(!esta_vacia){
        lista_borrar(lista);
        esta_vacia = lista_vacia(lista);
    }
    free(lista);
}

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
    nodo_t* nodo_auxi;
    
    if(!lista){
        return;
    }   
    nodo_auxi = lista->nodo_inicio;
    for(int i=INICIO_ITERACION; i<lista->cantidad_elem; i++){
        void* elemento = nodo_auxi->elemento;
        funcion(elemento);
        nodo_auxi = nodo_auxi->siguiente;
    }
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista){
        return NULL;
    }
    lista_iterador_t* iterador = (lista_iterador_t*) malloc (sizeof(lista_iterador_t));
    if(!iterador){
        return NULL;
    }
    iterador->pos_inicial = true;
    iterador->lista = lista;
    iterador->corriente = lista->nodo_inicio;
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    bool estado = false;
    
    if(iterador){
        if(iterador->corriente){
            if((iterador->lista->nodo_inicio == iterador->corriente) && (iterador->pos_inicial)){
                estado = true;
            }
            else if(iterador->corriente->siguiente){
                estado = true;
            }
        }
    }
    return estado;
}
 
void* lista_iterador_siguiente(lista_iterador_t* iterador){
    void* elemento = NULL;
    
    if(iterador){
        if(iterador->corriente){
            if((iterador->lista->nodo_inicio == iterador->corriente) && (iterador->pos_inicial)){
                elemento = iterador->lista->nodo_inicio->elemento;
                iterador->pos_inicial = false;
            }   
            else{
                iterador->corriente = iterador->corriente->siguiente;
                if(iterador->corriente){
                    elemento = iterador->corriente->elemento;
                }
            }
        }
    }
    return elemento;
}
    
void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}
