#include "reino.h"

#define SIMULACION 'S'
#define AGREGAR_CASA 'A'
#define LISTAR_CASAS 'L'
#define CASAS_EXTINTAS 'E'
#define SALIR 'Q'
#define AYUDA 'H'
#define ERROR -1
#define EXITO 0
#define CONTINUAR_SIMULACION 'C'
#define HAY_GANADOR 1
#define SIN_CASAS 2
#define MAX_COMANDO 20
#define MAX_PROGRAMA 20
#define MAX_ARCHIVO 10
#define SIN_ANIOS 0
#define CANTIDAD_MINIMA_ANIOS 0

/*
 * Funcion que recibe un comando y mientras sea invalido lo vuelve a pedir por consola. Devuelve un comando valido.
 */
char validar_comando(char comando);

/*
 * Funcion que dada una cantidad de años para simular en el reino valida que dicho numero sea positivo. Vuelve a 
 * pedir que se ingrese en caso contrario.
 */
int validar_anios_simulacion(int anios_simulacion);

/*
 * Procedimiento que dado un nombre valido de casa ganadora de la simulacion lo anuncia por pantalla. 
 */
void anunciar_resultado(int resultado_simulacion, char casa_ganadora[MAXIMO_VECTOR], int anios_simulacion);


int main(){
    char comando;
    reino_t* reino = NULL;
    int anios_simulacion = SIN_ANIOS;
    char casa_ganadora[MAXIMO_VECTOR];
    char archivo_casas[MAXIMO_VECTOR];
    char estado_programa = CONTINUAR_SIMULACION;
    int resultado_simulacion = ERROR;
   
    printf("\n\n~ Bienvenido al programa simulador de GAME OF THRONES ~\n\n");   
    explicar_comandos();
    printf("\nPor favor, indique su comando:\n");
    scanf(" %c", &comando);
    
    comando = validar_comando(comando);    
       
    reino = reino_crear();
    if(!reino){
        printf("\nOcurrio un error inesperado en el programa :/\n");
        return ERROR;
    }
                           
    while((comando != SALIR) && (estado_programa == CONTINUAR_SIMULACION)){        
        if(comando == SIMULACION){
            printf("\nPor favor, ingrese la cantidad de años que desea que pasen (debera ser un numero positivo):\n");
            scanf(" %i", &anios_simulacion); 
            anios_simulacion = validar_anios_simulacion(anios_simulacion);         
            resultado_simulacion = iniciar_simulacion(reino, anios_simulacion, casa_ganadora);
            anunciar_resultado(resultado_simulacion, casa_ganadora, anios_simulacion);
        }
        else if(comando == AGREGAR_CASA){
            printf("\nPor favor, ingrese en donde se encuentra la informacion sobre las casas (nombre del archivo):\n");
            scanf(" %s", archivo_casas);                                   
            agregar_casa(reino, archivo_casas) == EXITO ? printf("\n\tOperacion exitosa, se agregaron las casas correctamente :)\n") : printf("\nFallo en la operacion, no se pudieron agregar las casas :(\n");   
        }
        else if(comando == LISTAR_CASAS){
            listar_casas(reino);
        }
        else if(comando == CASAS_EXTINTAS){
            mostrar_casas_extintas(reino);
        }
        else if(comando == AYUDA){
            explicar_comandos();
        }
        else{
            finalizar_programa(reino);
        }
      
        printf("\nSi desea continuar ingresando comandos, presione C (MAYUSCULA), de lo contrario, presione otra letra.\n");
        scanf(" %c", &estado_programa);
        
        if(estado_programa == CONTINUAR_SIMULACION){
            printf("\nPor favor, indique su proximo comando.\nSi no recuerda cuales son los comandos, presione H (MAYUSCULA):\n");
            scanf(" %c", &comando);
            comando = validar_comando(comando); 
        }  
     }
   
    finalizar_programa(reino);
}

char validar_comando(char comando){

    while((comando != SIMULACION) && (comando != AGREGAR_CASA) && (comando != LISTAR_CASAS) && (comando != CASAS_EXTINTAS) && (comando != SALIR) ){
        if(comando != AYUDA){       
            printf("\nComando invalido, por favor vuelva a intentar.\n\n");
        }
        explicar_comandos();
        printf("\nPor favor, indique su comando:\n");
        scanf(" %c", &comando);   
    }
    return comando;
}

int validar_anios_simulacion(int anios_simulacion){
    while(anios_simulacion < CANTIDAD_MINIMA_ANIOS){
        printf("\nLa cantidad de años ingresada no es valida :( recuerde que esta debe ser un numero positivo. Por favor, vuelva a intentar:\n");
        scanf(" %i", &anios_simulacion);
    }
    return anios_simulacion;
}

void anunciar_resultado(int resultado_simulacion, char casa_ganadora[MAXIMO_VECTOR], int anios_simulacion){
    
    if(resultado_simulacion == HAY_GANADOR){
        printf("\n\tPasados %i años la casa ganadora es: *redoblantes*... ¡%s!", anios_simulacion, casa_ganadora);
    }
    else if(resultado_simulacion == SIN_CASAS){
        printf("\n\tLa simulacion no pudo realizarse ya que previamente no se ingresaron casas.\n\tPor favor, intente nuevamente con otro comando.\n");
    }
    else{
        printf("\n\tOcurrio un error inesperado durante la simulacion :( \n");
    }
    printf("\n\n\tFin de la simulacion.\n\n");
}

