#include "reino.h"

#define ERROR -1
#define EXITO 0
#define CASA 'C'
#define PERSONA 'I'
#define MODO_LECTURA "r"
#define ARCHIVO_NOMBRES "nombres.txt"
#define MAYOR_EL_PRIMERO -1
#define MAYOR_EL_SEGUNDO 1
#define SON_IGUALES 0
#define COMPARADOR 0
#define HAY_GANADOR 1
#define SIN_CASAS 2
#define SEGUIR_RECORRIENDO false
#define MAX_NOMBRE 20
#define MAXIMO_VECTOR 100
#define NO_HAY_CASAS 0
#define INICIO_ITERACION 0
#define POSICION_INICIAL 0
#define NO_HAY_FALLECIDOS 0
#define EDAD_MUERTE 60
#define DIFERENCIA_INICIAL 0
#define SIN_PERSONAS 0
#define EDAD_NACIDO 0
#define MINIMO_LEIDOS 0
#define FORMATO_CASAS "%[^;];%i;%i\n"
#define FORMATO_NACIDOS "%[^\n]\n"
#define FORMATO_CASA " %c;"
#define FORMATO_PERSONA "%[^;];%i\n"
#define INICIO_QSORT 0
#define MAXIMO 100


/*
 * Funcion que compara los elementos del abb; devuelve 0 en caso de ser iguales, 1 si el primer elemento es mayor, 
 * y 2 en caso contrario.
 */
int comparar_elementos(void* primer_elemento, void* segundo_elemento);

/*
 * Procedimiento que dado un elemento del abb, libera la memoria reservada para el mismo.
 */
void destruir_elementos(void* elemento);

/*
 * Procedimiento que destruye los elementos del abb de manera recursiva, liberando la memoria resevada para los mismos.
 * Recibe una casa y lista de personas valida.
 */
void destruir_elementos_rec(casa_t* casa, lista_t* personas);

/*
 * Funcion que recibe una lista valida y un elemento del arbol(casa); y determina la gente fallecida y 
 * por nacer en dicha casa.
 */
bool actualizar_edades(void* elemento, void* lista_auxi);

/*
 * Procedimiento que se encarga de la realizacion de todas las operaciones relacionadas con la determinacion de las
 * fallecidas para una determinada casa enviada por parametros. Recibe una casa y lista de personas valida. En 
 * caso de que dicha casa se quede sin integrantes, la misma se agregara a la lista auxiliar recibida por parametros.
 */
void obtener_fallecidos(casa_t* casa, lista_t* lista_auxi);

/*
 * Procedimiento que dada una casa incrementa la edad de todas las personas de la misma. Si la persona muere 
 * se la inserta en una lista de fallecidos.
 */
void sumar_edad(casa_t* casa, lista_t* lista_fallecidos);

/*
 * Procedimiento que recibe una casa y una lista de posiciones de la gente fallecida; y borra a dichas 
 * personas de la casa. 
 */
void borrar_fallecidos(casa_t* casa, lista_t* lista_fallecidos);

/*
 * Procedimiento que recibe una casa valida y reliza las operaciones necesarias para los nuevos nacimientos que tienen que 
 * producirse en dicha casa.
 */
void obtener_nacimientos(casa_t* casa);

/*
 * Procedimiento que dada una lista de personas y la cantidad de deben integrarse los incluye en la misma.
 */
void agregar_nacidos(lista_t* personas, int cantidad_nacidos);

/* 
 * Funcion que crea una nueva persona reservando la memoria necesaria para la misma; inicianizandola con un nombre y edad.
 */
persona_t* inicializar_persona(FILE* f_nacidos);

/*
 * Funcion que recibe un reino y una lista validos; en donde se borran del arbol las casas almacenadas en 
 * dicha lista. Devuelve 0 si se realizo con exito o -1 en caso de error.
 */
int borrar_casas_extintas(reino_t* reino, lista_t* lista_auxi);

/*
 * Procedimiento que recibe una cola y una lista de casas extintas y agrega dichas casas a la cola.
 */
void agregar_extintas_a_cola(cola_t* casas_extintas, lista_t* lista_auxi);

/*
 * Funcion que dado un archivo de casas inicializa la casa siguiente con los valores que corresponda.
 */
casa_t* inicializo_casa(FILE* f_casas);

/*
 * Funcion que dada una casa actualiza los datos que esta contiene. Devuelve dicha casa.
 */
casa_t* actualizar_casa(casa_t* casa, FILE* f_casas, int* estado_personas, char* indice, int* leidos);

/* 
 * Funcion que dado un archivo de casas y una casa, crea e inicializa la siguiente persona en el archivo. Devuelve 
 * 0 en caso de exito o -1 en caso contrario.
 */
int agregar_persona(FILE* f_casas, casa_t* casa);

/*
 * Procedimiento ordena el vector de casas enviado por parametros
 */
void quick_sort(casa_t* vector_casas[], int cantidad_casas);

/*
 * Procedimiento que recibe un vector de casas, con su inicio y fin; y determinado un pivote se vuelve a llamar 
 * con los valores anteriores y posteriores a este.
 */
void quick_sort_rec(casa_t* vector_casas[], int inicio, int fin);

/*
 * Funcion que dado un vector de casas, y evaluando los valores de sus elementos, devuelve en que posicion se
 * ubica el pivote determinado, segun la convencion de dicho algoritmo.
 */
int pivotear(casa_t** vector_casas, int inicio, int fin);

/*
 * Procedimiento que dado un vector de casas y dos posiciones, las intercambia entre si.
 */
void swapear(casa_t** vector_casas, int posicion_1, int posicion_2);

/*
 * Procedimiento que dado un vector y la cantidad de elementos(casas) que este contiene, muestra el 
 * nombre de cada casa por pantalla.
 */
void mostrar_casas(casa_t* vector_casas[], int cantidad_casas);

/*
 * Procedimiento que dada una cola de casas extintas libera dicha cola destruyendo los elementos de la misma.
 */
void destruir_casas_extintas(cola_t* casas_extintas);

/*
 * Procedimiento que dada una casa libera la memoria reservada en la misma para sus elementos.
 */
void liberar_casa(casa_t* casa);

/*
 * Procedimiento que dada una casa libera la memoria reservada previamente para la misma.
 */
void destruir_casa(casa_t* casa);

/*
 * Procedimiento que dada una persona, libera la memoria reservada previamente para la misma.
 */
void destruir_persona(void* persona);

/*
 * Procedimiento que dado un abb de casas libera la memoria reservada para el mismo.
 */
void destruir_casas(abb_t* casas);


reino_t* reino_crear(){
    reino_t* reino = NULL;
    
    reino = malloc(sizeof(reino_t));
    
    if(!reino){
        return reino;
    }
    
    reino->casas = arbol_crear(comparar_elementos, destruir_elementos);
    if(!reino->casas){
        free(reino);
        return reino;
    }
    reino->cantidad_casas = NO_HAY_CASAS;
    
    reino->casas_extintas = cola_crear();
    if(!reino->casas_extintas){
        arbol_destruir(reino->casas);
        free(reino);       
        return reino;
    } 
    
    return reino;
}

int comparar_elementos(void* primer_elemento, void* segundo_elemento){

    if((!primer_elemento) || (!segundo_elemento)){
        return SON_IGUALES;
    }
    if(strcmp(((casa_t*)primer_elemento)->nombre, ((casa_t*)segundo_elemento)->nombre) < COMPARADOR){
        return MAYOR_EL_PRIMERO;
    }
    else if(strcmp(((casa_t*)primer_elemento)->nombre, ((casa_t*)segundo_elemento)->nombre) > COMPARADOR){
        return MAYOR_EL_SEGUNDO;
    }
    return SON_IGUALES;
}

void destruir_elementos(void* elemento){
    
    if(!elemento){
        return;
    }
    casa_t* casa = (casa_t*)elemento;
    
    if(!casa->personas){
        destruir_casa(casa);
        return;
    }
    destruir_elementos_rec(casa, casa->personas);  
}

void destruir_elementos_rec(casa_t* casa, lista_t* personas){
   
    if(lista_vacia(personas)){
        lista_destruir(personas);
        destruir_casa(casa);
        return;
    }
    persona_t* persona = (persona_t*)lista_ultimo(personas);
    free(persona);
    lista_borrar(personas);
    destruir_elementos_rec(casa, personas);
}

void explicar_comandos(){
    printf("\n\t#COMANDOS#\n\n\t· Para INICIAR LA SIMULACION ingrese la letra S.\n\t· Para AGREGAR CASAS al reino ingrese la letra A.\n\t· Para LISTAR LAS CASAS por cantidad de integrantes, de mayor a menor ingrese la letra L.\n\t· Para MOSTRAR LAS CASAS EXTINTAS en el orden en el fueron desapareciendo ingrese la letra E.\n\t· Para SALIR ingrese la letra Q.\n\n\tTodas las letras deberan ingresarse en MAYUSCULA.\n\n");
}

int iniciar_simulacion(reino_t* reino, int anios_simulacion, char casa_ganadora[MAXIMO_VECTOR]){
    int estado_simulacion = ERROR;
    abb_liberar_elemento liberador_auxi = NULL;
    
    if(!reino){
        return estado_simulacion;
    }
    if((!reino->casas) || (!reino->casas_extintas)){
        return estado_simulacion;    
    }
    
    if(reino->cantidad_casas == NO_HAY_CASAS){
        return SIN_CASAS;
    }

    lista_t* lista_auxi = lista_crear();
    if(!lista_auxi){
        return estado_simulacion;
    }

    liberador_auxi = reino->casas->destructor;
    reino->casas->destructor = NULL;  

    for(int i=INICIO_ITERACION; i<anios_simulacion; i++){
        abb_con_cada_elemento(reino->casas, ABB_RECORRER_INORDEN, actualizar_edades, (void*)lista_auxi);
        int estado_borrado = borrar_casas_extintas(reino, lista_auxi);

        if(estado_borrado == EXITO){
            agregar_extintas_a_cola(reino->casas_extintas, lista_auxi);
        }
        
        while(!lista_vacia(lista_auxi)){
            lista_borrar(lista_auxi);
        }
    }

    reino->casas->destructor = liberador_auxi;
    lista_destruir(lista_auxi);
    
    int cantidad_casas = reino->cantidad_casas;
    casa_t* vector_casas[cantidad_casas];    
    int cantidad_guardadas = arbol_recorrido_inorden(reino->casas, (void**)vector_casas, cantidad_casas);
    quick_sort(vector_casas, cantidad_casas);

    if(cantidad_guardadas == NO_HAY_CASAS){
        return estado_simulacion;
    }
    else{
        strcpy(casa_ganadora, vector_casas[POSICION_INICIAL]->nombre);
        estado_simulacion = HAY_GANADOR;
    }
    return estado_simulacion;
}

bool actualizar_edades(void* elemento, void* lista_auxi){
        
    if(!elemento){
        return SEGUIR_RECORRIENDO;
    }
    
    obtener_fallecidos((casa_t*)elemento, (lista_t*)lista_auxi);
    obtener_nacimientos((casa_t*)elemento);
        
    return SEGUIR_RECORRIENDO;
}

void obtener_fallecidos(casa_t* casa, lista_t* lista_auxi){
    size_t cantidad_fallecidos = NO_HAY_FALLECIDOS;
    lista_t* lista_fallecidos = lista_crear();
    
    if(!lista_fallecidos){
        return;
    }
    
    sumar_edad(casa, lista_fallecidos);
    cantidad_fallecidos = lista_elementos(lista_fallecidos);
    if(cantidad_fallecidos > NO_HAY_FALLECIDOS){
        borrar_fallecidos(casa, lista_fallecidos);
    }
    
    if(lista_vacia(casa->personas)){
        lista_insertar(lista_auxi, casa);
    }
    lista_destruir(lista_fallecidos);
}

void sumar_edad(casa_t* casa, lista_t* lista_fallecidos){
    persona_t* persona = NULL;
    size_t posicion_lista = POSICION_INICIAL;
    
    if(!casa->personas){
        return;
    }
    lista_iterador_t* iterador = lista_iterador_crear(casa->personas);
    if(!iterador){
        return;
    }
    
    while(lista_iterador_tiene_siguiente(iterador)){
        persona = (persona_t*)lista_iterador_siguiente(iterador);
        persona->edad += casa->factor_envejecimiento;
        if(persona->edad >= EDAD_MUERTE){
            free(persona);
            lista_insertar(lista_fallecidos, (void*)posicion_lista);
        }
        posicion_lista++;
    }
    lista_iterador_destruir(iterador);
}

void borrar_fallecidos(casa_t* casa, lista_t* lista_fallecidos){
    size_t diferencia = DIFERENCIA_INICIAL;
    
    for(size_t i=INICIO_ITERACION; i<lista_elementos(lista_fallecidos); i++){
        size_t posicion = (size_t)lista_elemento_en_posicion(lista_fallecidos, i);
        lista_borrar_de_posicion(casa->personas,posicion-diferencia);   
        diferencia++;
        casa->cantidad_personas--;
    }
}

void obtener_nacimientos(casa_t* casa){
    int cantidad_nacidos = SIN_PERSONAS;
    
    if(casa->cantidad_personas > SIN_PERSONAS){
        cantidad_nacidos = (casa->cantidad_personas / casa->factor_nacimiento);
        agregar_nacidos(casa->personas, cantidad_nacidos);
        casa->cantidad_personas += cantidad_nacidos;
    }
}

void agregar_nacidos(lista_t* personas, int cantidad_nacidos){
    FILE* f_nacidos;
    persona_t* persona;
    int contador_bebe = SIN_PERSONAS;
    
    f_nacidos = fopen(ARCHIVO_NOMBRES, MODO_LECTURA);
    if(!f_nacidos){
        return;
    }
    
    while(contador_bebe < cantidad_nacidos){
        persona = inicializar_persona(f_nacidos);
        lista_insertar(personas, (void*)persona);
        contador_bebe++;
    }  
    fclose(f_nacidos);
}

persona_t* inicializar_persona(FILE* f_nacidos){
    persona_t* persona = NULL;
    
    persona = (persona_t*)malloc(sizeof(persona_t));
    if(!persona){
        return persona;
    }
    
    if(fscanf(f_nacidos, FORMATO_NACIDOS, persona->nombre) > SIN_PERSONAS){
        persona->edad = EDAD_NACIDO;
    }

    return persona;
} 

int borrar_casas_extintas(reino_t* reino, lista_t* lista_auxi){
    size_t cantidad_extintas = lista_elementos(lista_auxi);
    int estado = ERROR;
    
    for(size_t i=INICIO_ITERACION; i<cantidad_extintas; i++){
        estado = arbol_borrar(reino->casas, (void*)lista_elemento_en_posicion(lista_auxi, i));
        if(estado == EXITO){
            reino->cantidad_casas--;
        }
    }
    return estado;
}

void agregar_extintas_a_cola(cola_t* casas_extintas, lista_t* lista_auxi){ 
    size_t cantidad_extintas = lista_elementos(lista_auxi);
    size_t posicion_lista = POSICION_INICIAL;
    
    for(size_t i=INICIO_ITERACION; i<cantidad_extintas; i++){
        cola_encolar(casas_extintas, (void*)lista_elemento_en_posicion(lista_auxi, posicion_lista));
        posicion_lista++;
    }
}

int agregar_casa(reino_t* reino, char archivo_casas[MAXIMO_VECTOR]){
    FILE* f_casas;
    int leidos = MINIMO_LEIDOS;
    int estado_casas = EXITO;
    int estado_personas = EXITO;
    int agregue = ERROR;
    char indice;
    casa_t* casa = NULL;
   
    f_casas = fopen(archivo_casas, MODO_LECTURA);
    if(!f_casas){
        printf("Error en la apertura del archivo de casas :(\n");
        return ERROR;
    } 
    
    leidos = fscanf(f_casas, FORMATO_CASA, &indice);
    
    while(leidos > MINIMO_LEIDOS){
        if(indice == CASA){
            casa = inicializo_casa(f_casas);
            leidos = fscanf(f_casas, FORMATO_CASA, &indice);
            
            casa_t* casa_auxi = arbol_buscar(reino->casas, (void*)casa);
            if(!casa_auxi){
                if(casa){
                    casa = actualizar_casa(casa, f_casas, &estado_personas, &indice, &leidos);
                    estado_casas += arbol_insertar(reino->casas, (void*)casa);
                    printf("\n\tSe agrego la casa %s, con %i personas :)", casa->nombre, casa->cantidad_personas);
                    reino->cantidad_casas++;
                }
            }
            else{
                int personas_al_momento = casa_auxi->cantidad_personas;
                casa_auxi = actualizar_casa(casa_auxi, f_casas, &estado_personas, &indice, &leidos);
                printf("\n\tSe agregaron %i personas a la casa %s :) (total integrantes: %i)", casa_auxi->cantidad_personas - personas_al_momento, casa->nombre, casa_auxi->cantidad_personas);
                destruir_casa(casa);
            }  
        }
    }
        
    fclose(f_casas);
    
    if((estado_casas == EXITO) && (estado_personas == EXITO)){
        agregue = EXITO;
    }
    
    return agregue;
}

casa_t* inicializo_casa(FILE* f_casas){
    casa_t* casa = NULL;
    
    casa = (casa_t*) malloc(sizeof(casa_t));
    
    if(casa){
        fscanf(f_casas, FORMATO_CASAS, casa->nombre, &(casa->factor_envejecimiento), &(casa->factor_nacimiento));
        casa->personas = NULL;
        casa->cantidad_personas = SIN_PERSONAS;
    }
    
    return casa;
}

casa_t* actualizar_casa(casa_t* casa, FILE* f_casas, int* estado_personas, char* indice, int* leidos){

    if(casa){
        while((*indice == PERSONA) && (*leidos > MINIMO_LEIDOS)){
            if(!casa->personas){
                casa->personas = lista_crear();
            }
            if(casa->personas){
                *estado_personas = agregar_persona(f_casas, casa);
                *leidos = fscanf(f_casas, FORMATO_CASA, indice);
            }
        }
    }
    return casa;
}

int agregar_persona(FILE* f_casas, casa_t* casa){
    persona_t* persona = NULL;
    int estado = EXITO;

    persona = (persona_t*) malloc(sizeof(persona_t));
    
    if(persona){
        fscanf(f_casas, FORMATO_PERSONA, persona->nombre, &(persona->edad));
        estado += lista_insertar(casa->personas, (void*)persona);  
        casa->cantidad_personas++;
    }
    
    return estado;
}

void listar_casas(reino_t* reino){
    
    if(!reino){
        printf("\nOcurrio un error al momento de listar las casas :(\n");
        return;
    }
    
    int cantidad_casas = reino->cantidad_casas;
    casa_t* vector_casas[cantidad_casas];
    
    arbol_recorrido_inorden(reino->casas, (void**)vector_casas, cantidad_casas);
    
    quick_sort(vector_casas, cantidad_casas);
    mostrar_casas(vector_casas, cantidad_casas);
}

void quick_sort(casa_t* vector_casas[], int cantidad_casas){
    
    quick_sort_rec(vector_casas, INICIO_QSORT, cantidad_casas-1);
}

void quick_sort_rec(casa_t* vector_casas[], int inicio, int fin){

    if(inicio >= fin){
        return;
    }
    int pivote = pivotear(vector_casas, inicio, fin);
    if(pivote != ERROR){
        quick_sort_rec(vector_casas, inicio, pivote-1);
        quick_sort_rec(vector_casas, pivote+1, fin);
    }
}

int pivotear(casa_t** vector_casas, int inicio, int fin){
    casa_t* casa_actual = NULL;
    casa_t* casa_pivote = NULL;

    if(!vector_casas){
        return ERROR;
    }
    casa_pivote = vector_casas[fin];
    if(!casa_pivote){
        return ERROR;
    }
    int posicion_pivote = inicio;
    int valor_pivote = casa_pivote->cantidad_personas;
    
    for(int i=inicio; i<fin; i++){
        casa_actual = vector_casas[i];
        if(casa_actual){
            if(casa_actual->cantidad_personas > valor_pivote){
                swapear(vector_casas, i, posicion_pivote);
                posicion_pivote++;
            }
        }
    }
    swapear(vector_casas, posicion_pivote, fin);
    return posicion_pivote;
}

void swapear(casa_t** vector_casas, int posicion_1, int posicion_2){
    
    if(!vector_casas){
        return;
    }
    casa_t* auxi = vector_casas[posicion_1];
    vector_casas[posicion_1] = vector_casas[posicion_2];
    vector_casas[posicion_2] = auxi;
}

void mostrar_casas(casa_t* vector_casas[], int cantidad_casas){
    
    if(!vector_casas){
        printf("\nError intentando mostrar casas :(\n");
        return;
    }
    
    printf("\n\tA continuacion se enlistan las casas actuales por orden de cantidad de integrantes:\n\n");
    for(int i=INICIO_ITERACION; i<cantidad_casas; i++){
        casa_t* casa = (casa_t*)vector_casas[i];
        if(casa){
            printf("\t·Casa nº%i: %s (cantidad de integrantes: %i).\n", i+1, casa->nombre, casa->cantidad_personas);
        }
    }
    printf("\n\tNo hay mas casas disponibles para listar :(\n");
    printf("\n");
}

void mostrar_casas_extintas(reino_t* reino){
    
    if(!reino){
        return;
    }
    if(!reino->casas_extintas){
        return;
    }
    if(cola_vacia(reino->casas_extintas)){
        printf("\n\n\tNo hay mas casas extintas disponibles :(\n");
        return;
    }
    casa_t* casa = (casa_t*)cola_primero(reino->casas_extintas);
    if(casa){
        printf("\n\t· Casa extinta: %s", casa->nombre);
        cola_desencolar(reino->casas_extintas);
        liberar_casa(casa);
        destruir_casa(casa);
    }
    mostrar_casas_extintas(reino);
}

int finalizar_programa(reino_t* reino){
   
    if(!reino){
        return ERROR;
    }
    
    if(reino->casas_extintas){
        destruir_casas_extintas(reino->casas_extintas);
    }
    if(reino->casas){
        destruir_casas(reino->casas);
    }

    free(reino);
    return EXITO;
}

void destruir_casas_extintas(cola_t* casas_extintas){
    
    if(cola_vacia(casas_extintas)){
        cola_destruir(casas_extintas);
        return;    
    }
    casa_t* casa = (casa_t*)cola_primero(casas_extintas);
    liberar_casa(casa);
    destruir_casa(casa);
    cola_desencolar(casas_extintas);
    destruir_casas_extintas(casas_extintas);
}

void liberar_casa(casa_t* casa){
    
    if(!casa){
        return;
    }
    if(!casa->personas){
        return;
    }
    lista_con_cada_elemento(casa->personas, destruir_persona);
    lista_destruir(casa->personas);
}

void destruir_casa(casa_t* casa){
    
    free(casa);
}

void destruir_persona(void* persona){
  
    if(!persona){
        return;
    }
    free(persona);
}

void destruir_casas(abb_t* casas){

    arbol_destruir(casas);
}
