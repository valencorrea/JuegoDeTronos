#include "abb.h"
#include <stdio.h>

#define SON_IGUALES 0
#define MAYOR_EL_PRIMERO 1
#define MAYOR_EL_SEGUNDO -1
#define SIN_ELEMENTOS 0
#define INSERTE 0
#define NO_INSERTE -1
#define ELIMINE 0
#define NO_ELIMINE -1
#define SIN_HIJOS 0
#define UNICO_HIJO 1
#define DOS_HIJOS 2
#define CANTIDAD_NULA 0
#define EXITO 0
#define ERROR -1
#define NO_RECORRO true
#define RECORRO false


/*
 * Funcion que recibe un arbol por parametros y lo inicializa con sus valores correspondientes. El arbol recibido
 * es valido. Devuelve dicha estructura.
 */
abb_t* inicializar_arbol(abb_t* arbol, abb_comparador comparador, abb_liberar_elemento destructor);

/*
 * Funcion recursiva que se llama a si misma hasta llegar a una posicion "hoja" en donde insertar el elemento 
 * recibido por parametros. Devuelve el elemento si se esta en aquella posicion o la raiz en 
 * caso contrario.
 */
nodo_abb_t* arbol_insertar_rec(abb_comparador comparador, nodo_abb_t* nodo, void* elemento, int* estado);

/*
 * Procedimiento que recibe un nodo y elemento validos, e inicializa la estructura con los valores
 * correspondientes. 
 */
nodo_abb_t* inicializar_nodo(nodo_abb_t* nodo_nuevo, void* elemento);

/*
 * Funcion recursiva que utilizando un comparador busca dentro del arbol el elemento recibido por parametros.
 * Devuelve el elemento o NULL en caso de que este no se encuentre. 
 */
void* arbol_buscar_rec(abb_comparador comparador, nodo_abb_t* nodo, void* elemento);

/*
 * Funcion recursiva que elimina el nodo contenedor del elemento recibido por parametros de manera
 * recursiva. Devuelve 0 si pudo eliminarlo o -1 sino pudo.
 */
nodo_abb_t* arbol_borrar_rec(nodo_abb_t* padre, void* elemento, abb_comparador comparador, abb_liberar_elemento destructor, int* estado);

/*
 * Funcion que determinado un padre a eliminar, devuelve el hijo por el cual este deberia ser reemplazado
 */
nodo_abb_t* obtener_hijo(nodo_abb_t* padre, int* cantidad);

/*
 * Funcion que dado un nodo padre determina la cantidad de hijos que posee un nodo y la devuelve.
 */
int cantidad_hijos(nodo_abb_t* padre);

/*
 * Funcion que dado un nodo hijo determina cual es el familiar que posee el elemento mas chico y lo devuelve.
 */
nodo_abb_t* hijo_menor_de_los_mayores(nodo_abb_t* hijo);

/*
 * Funcion recursiva que recorre un arbol guardando sus elementos en un vector de manera inorden. Devuelve
 * la cantidad de elementos que pudieron ser almacenados en el mismo.
 */
int arbol_recorrido_inorden_rec(nodo_abb_t* nodo, int* elementos_almacenados, void** array, int tamanio_array);

/*
 * Funcion recursiva que recorre un arbol guardando sus elementos en un vector de manera postorden. Devuelve
 * la cantidad de elementos que pudieron ser almacenados en el mismo.
 */
int arbol_recorrido_postorden_rec(nodo_abb_t* nodo, int* elementos_almacenados, void** array, int tamanio_array);

/*
 * Funcion recursiva que recorre un arbol guardando sus elementos en un vector de manera preorden. Devuelve
 * la cantidad de elementos que pudieron ser almacenados en el mismo.
 */
int arbol_recorrido_preorden_rec(nodo_abb_t* nodo, int* elementos_almacenados, void** array, int tamanio_array);

/*
 * Procedimiento recursivo que visita los elementos del arbol segun el recorrido especificado hasta que 
 * no haya o que la funcion que se le aplica a estos retorne true.
 */
void abb_con_cada_elemento_rec(nodo_abb_t* nodo, int recorrido, bool (*funcion) (void*, void*), void* extra);

/*
 * Procedimiento recursivo que recorre el arbol de manera postorden invocando al destructor con cada nodo.
 */
void arbol_destruir_rec(nodo_abb_t* nodo, abb_liberar_elemento destructor);

/*
 * Procedimiento que itera dentro del arbol siguiendo el recorrido inorden hasta que no haya mas
 * nodos o la funcion aplicada devuelva true.
 */
void iterar_inorden(nodo_abb_t* nodo, bool (*funcion) (void*, void*), void* extra, bool* estado);

/*
 * Procedimiento que itera dentro del arbol siguiendo el recorrido preorden hasta que no haya mas
 * nodos o la funcion aplicada devuelva true.
 */
void iterar_preorden(nodo_abb_t* nodo, bool (*funcion) (void*, void*), void* extra, bool* estado);

/*
 * Procedimiento que itera dentro del arbol siguiendo el recorrido postorden hasta que no haya mas
 * nodos o la funcion aplicada devuelva true.
 */
void iterar_postorden(nodo_abb_t* nodo, bool (*funcion) (void*, void*), void* extra, bool* estado);


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    abb_t* arbol = NULL;
    
    if(!comparador){
        return NULL;
    }   
    arbol = (abb_t*) malloc (sizeof(abb_t));
    if(arbol){
       arbol = inicializar_arbol(arbol, comparador, destructor);
    }
    return arbol;
}

abb_t* inicializar_arbol(abb_t* arbol, abb_comparador comparador, abb_liberar_elemento destructor){
    arbol->nodo_raiz = NULL;
    arbol->comparador = comparador;
    arbol->destructor = destructor;
    return arbol;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    int estado = NO_INSERTE;
    
    if(arbol){
        arbol->nodo_raiz = arbol_insertar_rec(arbol->comparador, arbol->nodo_raiz, elemento, &estado);
    }
    return estado;
}

nodo_abb_t* arbol_insertar_rec(abb_comparador comparador, nodo_abb_t* nodo, void* elemento, int* estado){
    nodo_abb_t* auxi = NULL;

    if(!nodo){
        auxi = (nodo_abb_t*) malloc(sizeof(nodo_abb_t));
        if(auxi){
            auxi = inicializar_nodo(auxi, elemento);
            *estado = INSERTE;
            return auxi;
        }
    }
    if(comparador(nodo->elemento, elemento) == MAYOR_EL_PRIMERO){
        nodo->izquierda = arbol_insertar_rec(comparador, nodo->izquierda, elemento, estado);
    }
    else{
        nodo->derecha = arbol_insertar_rec(comparador, nodo->derecha, elemento, estado);   
    }
    return nodo;
}

nodo_abb_t* inicializar_nodo(nodo_abb_t* nodo_nuevo, void* elemento){
    nodo_nuevo->elemento = elemento;
    nodo_nuevo->izquierda = NULL;
    nodo_nuevo->derecha = NULL;
    return nodo_nuevo;
}

void* arbol_buscar(abb_t* arbol, void* elemento){    
    if(arbol){
        return arbol_buscar_rec(arbol->comparador, arbol->nodo_raiz, elemento);
    }
    return NULL;
}

void* arbol_buscar_rec(abb_comparador comparador, nodo_abb_t* nodo, void* elemento){     
    if(!nodo){
        return NULL; 
    }   
    if(comparador(nodo->elemento, elemento) == SON_IGUALES){
        return nodo->elemento;
    }
    else if(comparador(nodo->elemento, elemento) == MAYOR_EL_PRIMERO){
        return arbol_buscar_rec(comparador, nodo->izquierda, elemento);
    }
    else{
        return arbol_buscar_rec(comparador, nodo->derecha, elemento);
    }
}

int arbol_borrar(abb_t* arbol, void* elemento){
    int estado = NO_ELIMINE;
    
    if(arbol){
        arbol->nodo_raiz = arbol_borrar_rec(arbol->nodo_raiz, elemento, arbol->comparador, arbol->destructor, &estado);
    }
    return estado;
}

nodo_abb_t* arbol_borrar_rec(nodo_abb_t* padre, void* elemento, abb_comparador comparador, abb_liberar_elemento destructor, int* estado){
    nodo_abb_t* hijo = NULL;
    int cantidad_hijos = SIN_HIJOS;
    
    if(!padre){
        return NULL;
    }
    if(comparador(padre->elemento, elemento) == SON_IGUALES){
        hijo = obtener_hijo(padre, &cantidad_hijos);
        if(cantidad_hijos == DOS_HIJOS){
            if(destructor){
                destructor(padre->elemento);
            }
            padre->elemento = hijo->elemento;
            padre->derecha = arbol_borrar_rec(padre->derecha, hijo->elemento, comparador, NULL, estado);  
            *estado = ELIMINE; 
            return padre;
        }
        else{
            if(destructor){
                destructor(padre->elemento);
            }
            free(padre);
        }
        *estado = ELIMINE;
        return hijo;
    }
    else if(comparador(padre->elemento, elemento) == MAYOR_EL_PRIMERO){
        padre->izquierda = arbol_borrar_rec(padre->izquierda, elemento, comparador, destructor, estado);
    }
    else{
        padre->derecha = arbol_borrar_rec(padre->derecha, elemento, comparador, destructor, estado);
    }
    return padre;
} 

nodo_abb_t* obtener_hijo(nodo_abb_t* padre, int* cantidad){
    nodo_abb_t* hijo = NULL;

    if(cantidad_hijos(padre) == UNICO_HIJO){
        hijo = padre->derecha ? padre->derecha : padre->izquierda;
        *cantidad = UNICO_HIJO;
    }
    else if(cantidad_hijos(padre) == DOS_HIJOS){
        hijo = hijo_menor_de_los_mayores(padre->derecha);
        *cantidad = DOS_HIJOS;
    }
    return hijo;
}

int cantidad_hijos(nodo_abb_t* padre){
    int cantidad = SIN_HIJOS;
    
    if((!padre->izquierda  && padre->derecha) || (padre->izquierda && (!padre->derecha))){
        cantidad = UNICO_HIJO;
    }
    else if(padre->izquierda && padre->derecha){
        cantidad = DOS_HIJOS;
    }
    return cantidad;
}

nodo_abb_t* hijo_menor_de_los_mayores(nodo_abb_t* hijo){
    if(!hijo){
        return NULL;
    }
    if(!hijo->izquierda){
        return hijo;
    }
    return hijo_menor_de_los_mayores(hijo->izquierda);
}

void* arbol_raiz(abb_t* arbol){
    void* raiz = NULL;
    
    if(arbol){
        if(arbol->nodo_raiz){
            raiz = arbol->nodo_raiz->elemento;
        }
    }
    return raiz;
}

bool arbol_vacio(abb_t* arbol){
    bool estado = true;
    
    if(arbol){
        if(arbol->nodo_raiz){
            estado = false;
        }
    }
    return estado;
}

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
    int elementos_almacenados = SIN_ELEMENTOS;
    
    if(arbol && array){
        elementos_almacenados = arbol_recorrido_inorden_rec(arbol->nodo_raiz, &elementos_almacenados, array, tamanio_array);
    }
    return elementos_almacenados;
}

int arbol_recorrido_inorden_rec(nodo_abb_t* nodo, int* elementos_almacenados, void** array, int tamanio_array){ 
    if(!nodo){
        return SIN_ELEMENTOS;
    }
    arbol_recorrido_inorden_rec(nodo->izquierda, elementos_almacenados, array, tamanio_array);          
    if(*elementos_almacenados < tamanio_array){
        array[*elementos_almacenados] = nodo->elemento;
        (*elementos_almacenados)++; 
    }
    arbol_recorrido_inorden_rec(nodo->derecha, elementos_almacenados, array, tamanio_array);     
    return *elementos_almacenados;
}

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
    int elementos_almacenados = SIN_ELEMENTOS;

    if(arbol && array){
        elementos_almacenados = arbol_recorrido_postorden_rec(arbol->nodo_raiz, &elementos_almacenados, array, tamanio_array);
    }
    return elementos_almacenados;
}

int arbol_recorrido_postorden_rec(nodo_abb_t* nodo, int* elementos_almacenados, void** array, int tamanio_array){ 
    if(!nodo){
        return SIN_ELEMENTOS;
    }
    arbol_recorrido_postorden_rec(nodo->izquierda, elementos_almacenados, array, tamanio_array);          
    arbol_recorrido_postorden_rec(nodo->derecha, elementos_almacenados, array, tamanio_array); 
    if(*elementos_almacenados < tamanio_array){
        array[*elementos_almacenados] = nodo->elemento;
        (*elementos_almacenados)++;    
    }
    return *elementos_almacenados;
}

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
    int elementos_almacenados = SIN_ELEMENTOS;

    if(arbol && array){
        elementos_almacenados = arbol_recorrido_preorden_rec(arbol->nodo_raiz, &elementos_almacenados, array, tamanio_array);
    }
    return elementos_almacenados;
}

int arbol_recorrido_preorden_rec(nodo_abb_t* nodo, int* elementos_almacenados, void** array, int tamanio_array){ 
    if(!nodo){
        return SIN_ELEMENTOS;
    }
    if(*elementos_almacenados < tamanio_array){
        array[*elementos_almacenados] = nodo->elemento;
        (*elementos_almacenados)++; 
    }
    arbol_recorrido_preorden_rec(nodo->izquierda, elementos_almacenados, array, tamanio_array);          
    arbol_recorrido_preorden_rec(nodo->derecha, elementos_almacenados, array, tamanio_array);    
    return *elementos_almacenados;
}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
    bool estado = RECORRO;
    
    if((!arbol) || (!funcion)){
        return;
    }  
    if(recorrido == ABB_RECORRER_INORDEN){
        iterar_inorden(arbol->nodo_raiz, funcion, extra, &estado);
    }
    else if(recorrido == ABB_RECORRER_PREORDEN){
        iterar_preorden(arbol->nodo_raiz, funcion, extra, &estado);
    }
    else{
        iterar_postorden(arbol->nodo_raiz, funcion, extra, &estado);
    }
}

void iterar_inorden(nodo_abb_t* nodo, bool (*funcion) (void*, void*), void* extra, bool* estado){
    if((!nodo) || (*estado == NO_RECORRO)){
        return;
    }
    iterar_inorden(nodo->izquierda, funcion, extra, estado);
    if(*estado == RECORRO){
        if(funcion(nodo->elemento, extra)){
            *estado = NO_RECORRO;
            return;
        }
    }
    iterar_inorden(nodo->derecha, funcion, extra, estado);
}

void iterar_preorden(nodo_abb_t* nodo, bool (*funcion) (void*, void*), void* extra, bool* estado){
    if((!nodo) || (*estado == NO_RECORRO)){
        return;
    }
    if(*estado == RECORRO){
       if(funcion(nodo->elemento, extra)){
            *estado = NO_RECORRO;
            return;
        }
    }
    iterar_preorden(nodo->izquierda, funcion, extra, estado);
    iterar_preorden(nodo->derecha, funcion, extra, estado);    
}

void iterar_postorden(nodo_abb_t* nodo, bool (*funcion) (void*, void*), void* extra, bool* estado){
    if((!nodo) || (*estado == NO_RECORRO)){
        return;
    }
    iterar_postorden(nodo->izquierda, funcion, extra, estado);
    iterar_postorden(nodo->derecha, funcion, extra, estado);
    if(*estado == RECORRO){
        if(funcion(nodo->elemento, extra)){
            *estado = NO_RECORRO;
           return;
        }
    }
}

void arbol_destruir(abb_t* arbol){
    if(arbol){
        arbol_destruir_rec(arbol->nodo_raiz, arbol->destructor);
        free(arbol);
    }
}

void arbol_destruir_rec(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(!nodo){
        return;
    }
    arbol_destruir_rec(nodo->izquierda, destructor);
    arbol_destruir_rec(nodo->derecha, destructor);
    if(destructor){
        destructor(nodo->elemento);
    }
    free(nodo);
}
