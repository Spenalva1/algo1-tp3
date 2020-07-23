#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdbool.h>


#define MAX_RUTA 30
#define MAX_LONGITUD_CAMINO 200

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
void crear_camino(char* nombre_archivo);

/*
*
*/
void crear_configuracion(char* nombre_archivo);

/*
*
*/
bool ruta_caminos_valida(char ruta[MAX_RUTA]);

#endif