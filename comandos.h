#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdbool.h>


#define MAX_RUTA 100
#define MAX_LONGITUD_CAMINO 200
#define MAX_COMANDOS 4
#define MAX_CLAVE 20

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
*
*/
int calcular_puntaje(int nivel_actual, configuracion_t configuracion, int orcos_muertos[4]);

/*
*
*/
void escribir_puntaje_en_ranking(int puntaje, char config[MAX_RUTA]);

/*
*
*/
int orcos_muertos_en_nivel(nivel_t nivel);

/*
*
*/
void mostrar_repeticion(char ruta_grabacion[MAX_RUTA], float velocidad);

/*
*
*/
void crear_camino(char* nombre_archivo);

/*
*
*/
void crear_configuracion(char* nombre_archivo);

/*
*
*/
bool ruta_caminos_valida(char ruta[MAX_RUTA]);

/*
*
*/
bool cantidad_parametros_valida(int argc);

/*
*
*/
bool es_txt_valido(char ruta[MAX_RUTA]);

/*
*
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
*
*/
bool escribir_estado_juego_en_archivo(FILE* archivo, juego_t juego);

/*
*
*/
bool existe_archivo(char ruta[MAX_RUTA]);

/*
*
*/
void cargar_caminos_desde_archivo(caminos_t* caminos, char ruta[MAX_RUTA]);

/*
*
*/
void asignar_valores_por_defecto(configuracion_t* configuracion);

/*
*
*/
void cargar_configuracion_de_archivo(char ruta[MAX_RUTA], configuracion_t* configuracion);

/*
*
*/
void procesar_clave(FILE* archivo, char clave[MAX_CLAVE], configuracion_t* configuracion);

/*
*
*/
void copiar_camino(coordenada_t destino[MAX_LONGITUD_CAMINO], int* tope_destino, coordenada_t origen[MAX_LONGITUD_CAMINO], int tope_origen);

/*
*
*/
void inicializar_caminos(caminos_t* caminos, char ruta[MAX_RUTA]);

/*
*
*/
void inicializar_configuracion(configuracion_t* configuracion);

#endif