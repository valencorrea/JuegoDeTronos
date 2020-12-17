
## TRABAJO PRACTICO: JUEGO DE TRONOS

## · Compilacion y ejecucion ·

Para un manejo mas sencillo del programa, se opto por utilizar la herramienta 'makefile'. 
Corriendo en la terminal make seguido de una palabra precisa se puede realizar ya sea la compilacion (make build),
ejecucion (make run), verificacion de perdida de mememoria (make valgrind) y el debugging (make gdb) 
en caso de que se lo quiera.

    
## · Contenido de la entrega ·

En este trabajo se entrega:  

* un .c juego_de_tronos a evaluar (contenedor de la estructura principal del programa)
* un .c reino a evaluar 
* un .h reino a evaluar
* un archivo de texto nombres.txt necesario para la ejecucion del programa
* un archivo de texto casas.txt con el que fue probado el programa
* un TDA lista (con sus correspondientes .c y .h)
* un TDA cola (con sus correspondientes .c y .h)     
* un TDA abb (con sus correspondientes .c y .h)
* un archivo makefile 
* un archivo pdf con el enunciado del trabajo practico

       
## · Sobre el funcionamiento del programa en general ·     
    
El presente programa tiene como objetivo una simulacion del reino de game of thrones. Para concretar lo dicho, durante su funcionamiento se establece el uso de los siguientes comandos:

* A: agrega casas al reino a partir de un archivo determinado
* S: simula el paso de una cantidad de años determinada por el usuario
* L: lista la cantidad de casas actuales por cantidad de integrantes en orden descendente
* E: muestra las casas que se quedaron sin integrantes en orden de desaparicion
* H: explica cuales son los comandos a utilizar dentro del programa
* Q: finaliza el programa
    

## · Algunas decisiones de diseño ·

* Sobre el programa: se opto por separar el main de demas implementaciones de funciones para tener mejor visibilidad de como se maneja y esta hecha la logica y estructura de dicho programa. Ademas, se trato llevar la mayor parte de interaccion con el usuario al main para de esta forma aislar lo mas posible el 'que' del 'como'
    
* Sobre el uso de funciones: se opto por indicar sus firmas en la parte superior del programa; para asi luego ir llamandolas en 'orden de aparicion', lo cual se supone mas legible.
    
* Sobre los structs: 
    * Reino: para un manejo mas dinamico se incluyo la cantidad de casas que posee dicho reino. Ademas, el uso del puntero a las casas que fueron extintas fue suma importancia ya que de otra forma este seria de mas dificil acceso.
    * Casa: Analogamente al item anterior se incluyo la cantidad de personas que se encuentra en dicha casa, a modo de simplificacion. Luego, se encuentran los campos de las caracteristicas propias de una casa las cuales deben ser definidas.
    * Persona: Para el struct persona se incluyo unicamente lo necesario.
    
* Sobre el archivo de texto nombres.txt: Dado que se pedia inicializar a las personas que nacian debido al paso del tiempo con una edad y un nombre, se creo el archivo de texto enunciado, con el objetivo de simplificar dicha tarea realizandola de una forma practica.
    
* Sobre el comando H: Dado que es probable que un usuario que no utilice frecuentemente el programa no recuerde con exactitud los comandos con los que se maneja el presente trabajo, se incluyo a la lista de comandos basicos la H en funcion de brindar soporte y explicaciones cuando se lo necesite.
    
* Sobre la utilizacion de la funcion quicksort: Dado que ciertas veces se requeria de un reorden en un determinado vector, se eligio utilizar este metodo para concretar dicha actividad por el motivo de que posee un tiempo de complegidad computacional bastante mas bajo que otros metodos vistos al momento.
     

## TRABAJO PRACTICO: JUEGO DE TRONOS
