#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdbool.h>


#define MAX_RUTA 100
#define MAX_LONGITUD_CAMINO 200
#define MAX_COMANDOS 4
#define MAX_CLAVE 20
#define LISTAR_TODOS -1

typedef struct configuracion{
    int resistencia_torre_1;
    int resistencia_torre_2;
    int enanos_nivel_1;
    int enanos_nivel_2;
    int enanos_nivel_3;
    int enanos_nivel_4;
    int elfos_nivel_1;
    int elfos_nivel_2;
    int elfos_nivel_3;
    int elfos_nivel_4;
    int enanos_extra;
    int enanos_coste_torre_1;
    int enanos_coste_torre_2;
    int elfos_extra;
    int elfos_coste_torre_1;
    int elfos_coste_torre_2;
    int enanos_fallo;
    int enanos_critico;
    int elfos_fallo;
    int elfos_critico;
    float velocidad_juego;
    char caminos[MAX_RUTA];
    char repeticion[MAX_RUTA];
} configuracion_t;

#include "defendiendo_torres.h"

typedef struct caminos{
    coordenada_t camino_1_nivel_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1_nivel_1;
    coordenada_t camino_2_nivel_1[MAX_LONGITUD_CAMINO];
	int tope_camino_2_nivel_1;
    coordenada_t camino_1_nivel_2[MAX_LONGITUD_CAMINO];
	int tope_camino_1_nivel_2;
    coordenada_t camino_2_nivel_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2_nivel_2;
    coordenada_t camino_1_nivel_3[MAX_LONGITUD_CAMINO];
	int tope_camino_1_nivel_3;
    coordenada_t camino_2_nivel_3[MAX_LONGITUD_CAMINO];
	int tope_camino_2_nivel_3;
    coordenada_t camino_1_nivel_4[MAX_LONGITUD_CAMINO];
	int tope_camino_1_nivel_4;
    coordenada_t camino_2_nivel_4[MAX_LONGITUD_CAMINO];
	int tope_camino_2_nivel_4;
} caminos_t;

/*
* Verifica que los parametros acerca de la configuraciónn y la grabación
* (en caso de que sean ingresados) sean válidos.
* Sobre la ruta de configuracion verifica que el archivo exista. 
* Si no fue ingresada ninguna, se jugara con la configuracion por defecto
* Sobre la grabacion verifica que sea una ruta finalizada en dat
* Si no fue ingresada ninguna, la partida no se grabará
* Devuelve TRUE si el programa debe proseguir con la ejecucion del juego
* Devuelve FALSE si hubo errores y no se puede jugar el juego
*/
bool comando_jugar(int argc, char* argv[], char ruta_configuracion[MAX_RUTA], char ruta_grabacion[MAX_RUTA]);

/*
* Verifica que el usuario haya ingresado la ruta de un archivo que posea una partida
* grabada para luego reproducirla con la velocidad deseada por el usuario (en caso
* de que haya ingresado un valor sobre ella).
*/
void comando_poneme_la_repe(int argc, char* argv[]);

/*
* Verifica que el usuario haya ingresado una ruta terminada en .txt para luego escribir
* la configuracion ingresada por el usuario.
*/
void comando_crear_configuracion(int argc, char* argv[]);

/*
* Verifica que el usuario haya ingresado una ruta terminada en .txt para luego escribir
* los caminos creados por el usuario.
*/
void comando_crear_camino(int argc, char* argv[]);

/*
* Verifica que el usuario haya ingresado la ruta de una configuracion existente para
* luego mostrar el ranking relacionada a ella.
* Si el usuario agrega por parametro una velocidad a listar. se verifica que dicho valor
* sea mayor a 0 para luego mostrar dicha cantidad
*/
void comando_ranking(int argc, char* argv[]);

/*
* Calcula  y devuelve el puntaje del jugador en base a la configuracion inicial de la partida
* y la cantidad de orcos muertos.
* nivel_actual debe ser un entero entre 1 y 4 (ambos inclusive)
* configuracion debe tener todos sus campos inicializados y validos
* orcos_muertos debe tener un entero inicizlizado desde la posicion 0 hasta la posicion [nivel_actual-1]
*/
int calcular_puntaje(int nivel_actual, configuracion_t configuracion, int orcos_muertos[4]);

/*
* Escribe la puntuacion del jugador en un archivo ranking .csv relacionada a la configuracion
* con la que se jugó.
* Recibe:
* puntaje: un entero positivo
* config: ruta de archivo de configuracion ya existente (si recibe -1 significa que se esta
* jugando con la configuracion por defecto)
*/
void escribir_puntaje_en_ranking(int puntaje, char config[MAX_RUTA]);

/*
* Recibe un nivel con todas sus estructuras válidas
* Devuelve la cantidad de orcos muertos en dicho nivel
*/
int orcos_muertos_en_nivel(nivel_t nivel);

/*
* Mostrara la grabacion de una partida con la velocidad recibida
* La partida se obtendra de un archivo que se espera que exista y cuya ruta se ingresa por
* ruta_grabacion
*/
void mostrar_repeticion(char ruta_grabacion[MAX_RUTA], float velocidad);

/*
* Se espera una ruta_configuracion que contenga la ruta de una configuracion existente
* para luego mostrar en pantalla el ranking guardado en el archivo de ranking .csv 
* relacionado a dicha configuración.
* Listar indicará la cantidad de puestos a mostrar en pantalla. Si este valor es '-1'
* se mostraran todos los registros.
*/
void mostrar_ranking(char ruta_configuracion[MAX_RUTA], int listar);

/*
* Recibe una cadena de caracteres que será el nombre del archivo que contenga los caminos
* creados por el usuario.
* Se crearan los caminos de los 4 niveles del juego (6 en total).
*/
void crear_camino(char* nombre_archivo);

/*
* Recibe una cadena de caracteres que será el nombre del archivo que contenga la configuración
* ingresada por el usuario.
* Pide al usuario que ingrese el valor inicial de cada elemento del juego para luego escribir
* todos los datos en un archivo
*/
void crear_configuracion(char* nombre_archivo);

/*
* Recive en argc un entero que corresponde a la cantidad de parametros ingresados por el usuario.
* Devuelve true si la cantidad es mayor a 1 y menor o igual a 4.
* Devuelve False en caso contrario imprimiendo por pantalla el caso de error.
*/
bool cantidad_parametros_valida(int argc);

/*
* Verifica que la cantidad de caracteres ingresada en ruta tenga un largo mayor a 4 y una
* terminacion '.txt'.
*/
bool es_txt_valido(char ruta[MAX_RUTA]);

/*
* Verifica que la cantidad de caracteres ingresada en ruta tenga un largo mayor a 4 y una
* terminacion '.dat'.
*/
bool es_dat_valido(char ruta[MAX_RUTA]);

/*
* Devuelve TRUE si alguna coordenada de camino coincide con las coordenadas de entrada y/o torre.
* camino deberá ser un camino válido.
* tope_camino positivo.
* entrada y torre coordenadas validas del tablero.
*/
bool camino_valido(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino, coordenada_t entrada, coordenada_t torre);

/*
* Verifica que la cantidad de caracteres ingresada en ruta corresponda a un archivo que pueda ser
* abierto para ser leido.
*/
bool existe_archivo(char ruta[MAX_RUTA]);

/*
* Se encarga de cargar los 6 caminos del juegos en caminos
* Los caminos se obtendran de un archivo cuyo nombre se corresponde a la cadena de caracteres
* ingresada en ruta que se espera que dicho archivo exista y pueda ser leido.
*/
void cargar_caminos_desde_archivo(caminos_t* caminos, char ruta[MAX_RUTA]);

/*
* Se encarga de cargar en configuracion los valores iniciales por defecto de los elementos
* del juego.
*/
void asignar_valores_por_defecto(configuracion_t* configuracion);

/*
* Se encarga de cargar en configuracion los valores que se encuentren en un archivo en la estructura
* configuracion recibida.
* Se espera recibir una ruta de un archivo existente y que pueda ser leido.
*/
void cargar_configuracion_de_archivo(char ruta[MAX_RUTA], configuracion_t* configuracion);

/*
* Asocia el string recibido por clave con el campo correspondiente de configuracion
* para luego cargar el valor siguiente del archivo en la estructura configuracion recibida.
* Se espera que archivo contenga un archivo ya abierto en modo lectura.
*/
void procesar_clave(FILE* archivo, char clave[MAX_CLAVE], configuracion_t* configuracion);

/*
* Copia los datos del vector origen en el vector destino
*/
void copiar_camino(coordenada_t destino[MAX_LONGITUD_CAMINO], int* tope_destino, coordenada_t origen[MAX_LONGITUD_CAMINO], int tope_origen);

/*
* inicializa los caminos caminos que seran usados en el juego
* ruta debe ser "-1" o un string correspondiente a un archivo de caminos existente y listo
* para ser leido.
* Si ruta es "-1" los caminos seran al azar.
* Si posee la ruta de un archivo los caminos serán leidos desde el mismo.
*/
void inicializar_caminos(caminos_t* caminos, char ruta[MAX_RUTA]);

/*
* inicializa los valores de la estructura recibida con valores '-1'
*/
void inicializar_configuracion(configuracion_t* configuracion);

#endif