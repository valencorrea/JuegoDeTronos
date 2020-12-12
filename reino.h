#ifndef __REINO_H__
#define __REINO_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"
#include "abb.h"
#include "cola.h"

#define ERROR -1
#define MAXIMO_VECTOR 100


typedef struct persona{
    char nombre[MAXIMO_VECTOR];
    int edad;
}persona_t;

typedef struct casa{
    char nombre[MAXIMO_VECTOR];
    int factor_envejecimiento;
    int factor_nacimiento;
    lista_t* personas;
    int cantidad_personas;
}casa_t;

typedef struct reino{
    abb_t* casas;
    int cantidad_casas;
    cola_t* casas_extintas;
}reino_t;


/*
 * Funcion que se encarga de la creacion del reino reservando la memoria necesaria para el mismo.
 */
reino_t* reino_crear();

/*
 * Procedimietno que explica los comandos con los que se desarrollara el programa a lo largo del mismo.
 */
void explicar_comandos();

/*
 * Funcion dada una cantidad de años, simula dicha cantidad en el reino y devuelve 1 en caso de que haya ganador,
 * 2 en caso de que previamente no se hayan ingresado casas, y -1 en cualquier otro caso de error durante dicha simulacion.
 */
int iniciar_simulacion(reino_t* reino, int anios_simulacion, char casa_ganadora[MAXIMO_VECTOR]);

/*
 * Funcion que dado un nombre de un archivo inicial en donde se encuentra la informacion de las casas, agrega
 * las mismas al reino. En caso de existir la casa solo se agregaran integrantes a la misma. Devuelve 0 en caso 
 * de resolverlo exitosamente o -1 si hubo un error.
 */
int agregar_casa(reino_t* reino, char archivo_casas[MAXIMO_VECTOR]);

/*
 * Procedimiento que se encarga de listar las casas que se encuentran en el reino al momento; de forma 
 * decreciente por cantidad de integrantes.
 */
void listar_casas(reino_t* reino);

/*
 * Procedimiento que muestra las casas que se quedaron sin integrantes, unicamente si no fueron mostradas previamente.
 */
void mostrar_casas_extintas(reino_t* reino);

/*
 * Funcion que se encarga de realizar las operaciones necesarias para la finalizacion del programa. Devuelve 0 en 
 * caso de ser exitosa y -1 en cualquier otro caso.
 */
int finalizar_programa(reino_t* reino);


#endif /* __REINO_H__ */
