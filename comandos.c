#include "comandos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define COLUMNAS_NIVEL1 15
#define FILAS_NIVEL1 15
#define COLUMNAS_NIVEL2 15
#define FILAS_NIVEL2 15
#define COLUMNAS_NIVEL3 20
#define FILAS_NIVEL3 20
#define COLUMNAS_NIVEL4 20
#define FILAS_NIVEL4 20
#define COLUMNAS_NIVEL1 15
#define FILAS_NIVEL1 15
#define COLUMNAS_NIVEL2 15
#define FILAS_NIVEL2 15
#define COLUMNAS_NIVEL3 20
#define FILAS_NIVEL3 20
#define COLUMNAS_NIVEL4 20
#define FILAS_NIVEL4 20
#define CAMINO ' '
#define ENTRADA 'E'
#define TORRE 'T'
#define VACIO '#'
#define ARRIBA 'W'
#define DERECHA 'D'
#define IZQUIERDA 'A'
#define ABAJO 'S'
#define RESISTENCIA_TORRE_MINIMA 50
#define RESISTENCIA_TORRE_MAXIMA 10000
#define DEFENSORES_MINIMOS 2
#define DEFENSORES_MAXIMOS 15
#define EXTRAS_MINIMOS 0
#define EXTRAS_MAXIMOS 20
#define COSTE_EXTRAS_MINIMO 0
#define COSTE_EXTRAS_MAXIMO 150
#define PORCENTAJE_MINIMO 1
#define PORCENTAJE_MAXIMO 99
#define POR_DEFECTO -1
#define POR_DEFECTO_STRING "-1"
#define VELOCIDAD_MINIMA 0.25
#define VELOCIDAD_MAXIMA 5.0
#define CLAVE_RESISTENCIA_TORRES "RESISTENCIA_TORRES"
#define CLAVE_ENANOS_INICIO "ENANOS_INICIO"
#define CLAVE_ELFOS_INICIO "ELFOS_INICIO"
#define CLAVE_ENANOS_EXTRA "ENANOS_EXTRA"
#define CLAVE_ELFOS_EXTRA "ELFOS_EXTRA"
#define CLAVE_ENANOS_ANIMO "ENANOS_ANIMO"
#define CLAVE_ELFOS_ANIMO "ELFOS_ANIMO"
#define CLAVE_VELOCIDAD "VELOCIDAD"
#define CLAVE_CAMINOS "CAMINOS"
#define RUTA_RANKING_BASE "ranking"
#define FORMATO_CONFIGURACION "%[^=]="
#define CAMPOS_RANKING 2
#define LISTAR_CLAVE "listar"
#define LISTAR_MINIMO 1
#define VELOCIDAD_CLAVE "velocidad"
#define GRABACION_CLAVE "grabacion"
#define CONFIGURACION_CLAVE "config"
#define ARCHIVO_AUXILIAR "aux.csv"
#define TXT ".txt"
#define DAT ".dat"
#define CSV ".csv"
#define MIN_COMANDOS 2
#define ENANOS_NIVEL_1 5
#define ENANOS_NIVEL_2 0
#define ENANOS_NIVEL_3 3
#define ENANOS_NIVEL_4 4
#define ELFOS_NIVEL_1 0
#define ELFOS_NIVEL_2 5
#define ELFOS_NIVEL_3 3
#define ELFOS_NIVEL_4 4
#define ENANOS_COSTE_TORRE_1 50
#define ENANOS_COSTE_TORRE_2 0
#define ELFOS_COSTE_TORRE_1 0
#define ELFOS_COSTE_TORRE_2 50
#define VELOCIDAD 0.5
#define MULTIPLICADOR_ORCOS_MUERTOS 1000
#define MAX_NOMBRE 50
#define FORMATO_CAMINOS "%[^\n]\n"
#define FORMATO_COORDENADAS "%d;%d\n"
#define NO_HAY_REGISTROS -1
#define SEPARADOR "="
#define FORMATO_TORRES "%s=%d,%d\n"
#define FORMATO_DEFENSORES_INICIO "%s=%d,%d,%d,%d\n"
#define FORMATO_DEFENSORES_EXTRAS "%s=%d,%d,%d\n"
#define FORMATO_ANIMOS "%s=%d,%d\n"
#define FORMATO_VELOCIDAD "%s=%f\n"
#define FORMATO_CAMINOS_RUTA "%s=%s\n"

typedef struct nivel_caminos {
    int numero_nivel;

	coordenada_t camino_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1;
	
	coordenada_t camino_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2;

    int tope_filas;
    int tope_columnas;
} nivel_caminos_t;

void procesar_clave(FILE* archivo, char clave[MAX_CLAVE], configuracion_t* configuracion){
	if(strcmp(CLAVE_RESISTENCIA_TORRES, clave) == 0){
		fscanf(archivo, "%d,%d\n", &(configuracion->resistencia_torre_1), &(configuracion->resistencia_torre_2));	
	}else if(strcmp(CLAVE_ENANOS_INICIO, clave) == 0){
		fscanf(archivo, "%d,%d,%d,%d\n", &(configuracion->enanos_nivel_1), &(configuracion->enanos_nivel_2), &(configuracion->enanos_nivel_3), &(configuracion->enanos_nivel_4));
	}else if(strcmp(CLAVE_ELFOS_INICIO, clave) == 0){
		fscanf(archivo, "%d,%d,%d,%d\n", &(configuracion->elfos_nivel_1), &(configuracion->elfos_nivel_2), &(configuracion->elfos_nivel_3), &(configuracion->elfos_nivel_4));
	}else if(strcmp(CLAVE_ENANOS_EXTRA, clave) == 0){
		fscanf(archivo, "%d,%d,%d\n", &(configuracion->enanos_extra), &(configuracion->enanos_coste_torre_1), &(configuracion->enanos_coste_torre_2));
	}else if(strcmp(CLAVE_ELFOS_EXTRA, clave) == 0){
		fscanf(archivo, "%d,%d,%d\n", &(configuracion->elfos_extra), &(configuracion->elfos_coste_torre_1), &(configuracion->elfos_coste_torre_2));
	}else if(strcmp(CLAVE_ENANOS_ANIMO, clave) == 0){
		fscanf(archivo, "%d,%d\n", &(configuracion->enanos_fallo), &(configuracion->enanos_critico));
	}else if(strcmp(CLAVE_ELFOS_ANIMO, clave) == 0){
		fscanf(archivo, "%d,%d\n", &(configuracion->elfos_fallo), &(configuracion->elfos_critico));
	}else if(strcmp(CLAVE_VELOCIDAD, clave) == 0){
		fscanf(archivo, "%f\n", &(configuracion->velocidad_juego));
	}else if(strcmp(CLAVE_CAMINOS, clave) == 0){
		fscanf(archivo, "%s\n", configuracion->caminos);
	}
}

void asignar_valores_por_defecto(configuracion_t* configuracion){
	if(configuracion->resistencia_torre_1 == POR_DEFECTO){
		configuracion->resistencia_torre_1 = VIDA_INICIAL_TORRE;
	}
	if(configuracion->resistencia_torre_2 == POR_DEFECTO){
		configuracion->resistencia_torre_2 = VIDA_INICIAL_TORRE;
	}
	if(configuracion->enanos_nivel_1 == POR_DEFECTO){
		configuracion->enanos_nivel_1 = ENANOS_NIVEL_1;
	}
	if(configuracion->enanos_nivel_2 == POR_DEFECTO){
		configuracion->enanos_nivel_2 = ENANOS_NIVEL_2;
	}
	if(configuracion->enanos_nivel_3 == POR_DEFECTO){
		configuracion->enanos_nivel_3 = ENANOS_NIVEL_3;
	}
	if(configuracion->enanos_nivel_4 == POR_DEFECTO){
		configuracion->enanos_nivel_4 = ENANOS_NIVEL_4;
	}
	if(configuracion->elfos_nivel_1 == POR_DEFECTO){
		configuracion->elfos_nivel_1 = ELFOS_NIVEL_1;
	}
	if(configuracion->elfos_nivel_2 == POR_DEFECTO){
		configuracion->elfos_nivel_2 = ELFOS_NIVEL_2;
	}
	if(configuracion->elfos_nivel_3 == POR_DEFECTO){
		configuracion->elfos_nivel_3 = ELFOS_NIVEL_3;
	}
	if(configuracion->elfos_nivel_4 == POR_DEFECTO){
		configuracion->elfos_nivel_4 = ELFOS_NIVEL_4;
	}
	if(configuracion->enanos_extra == POR_DEFECTO){
		configuracion->enanos_extra = ENANOS_EXTRA;
	}
	if(configuracion->enanos_coste_torre_1 == POR_DEFECTO){
		configuracion->enanos_coste_torre_1 = ENANOS_COSTE_TORRE_1;
	}
	if(configuracion->enanos_coste_torre_2 == POR_DEFECTO){
		configuracion->enanos_coste_torre_2 = ENANOS_COSTE_TORRE_2;
	}
	if(configuracion->elfos_extra == POR_DEFECTO){
		configuracion->elfos_extra = ELFOS_EXTRA;
	}
	if(configuracion->elfos_coste_torre_1 == POR_DEFECTO){
		configuracion->elfos_coste_torre_1 = ELFOS_COSTE_TORRE_1;
	}
	if(configuracion->elfos_coste_torre_2 == POR_DEFECTO){
		configuracion->elfos_coste_torre_2 = ELFOS_COSTE_TORRE_2;
	}
	if(configuracion->velocidad_juego == POR_DEFECTO){
		configuracion->velocidad_juego = VELOCIDAD;
	}
}

void cargar_configuracion_de_archivo(char ruta[MAX_RUTA], configuracion_t* configuracion){
	FILE* archivo = fopen(ruta, "r");
	char clave[MAX_CLAVE];
	int leidos = fscanf(archivo, FORMATO_CONFIGURACION, clave);
	while(leidos == 1){
		procesar_clave(archivo, clave, configuracion);
		leidos = fscanf(archivo, FORMATO_CONFIGURACION, clave);
	}
	fclose(archivo);
}

void copiar_camino(coordenada_t destino[MAX_LONGITUD_CAMINO], int* tope_destino, coordenada_t origen[MAX_LONGITUD_CAMINO], int tope_origen){
	for(int i = 0; i < tope_origen; i++){
		destino[i].fil = origen[i].fil;
		destino[i].col = origen[i].col;
	}
	*tope_destino = tope_origen;
}

void cargar_caminos_desde_archivo(caminos_t* caminos, char ruta[MAX_RUTA]){
	FILE* archivo = fopen (ruta, "r");
	char coordenada[MAX_RUTA];
    char* token;
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	fscanf(archivo, FORMATO_CAMINOS, coordenada);

	caminos->tope_camino_1_nivel_1 = 0;
	caminos->tope_camino_2_nivel_1 = 0;
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	while (strcmp(coordenada, "NIVEL=2")){
		token = strtok(coordenada, ";");
		caminos->camino_1_nivel_1[caminos->tope_camino_1_nivel_1].fil = atoi(token);
        token = strtok(NULL, ";");
		caminos->camino_1_nivel_1[caminos->tope_camino_1_nivel_1].col = atoi(token);
		(caminos->tope_camino_1_nivel_1)++;
		fscanf(archivo, FORMATO_CAMINOS, coordenada);
	}

	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	caminos->tope_camino_1_nivel_2 = 0;
	caminos->tope_camino_2_nivel_2 = 0;
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	while (strcmp(coordenada, "NIVEL=3")){
		token = strtok(coordenada, ";");
		caminos->camino_2_nivel_2[caminos->tope_camino_2_nivel_2].fil = atoi(token);
        token = strtok(NULL, ";");
		caminos->camino_2_nivel_2[caminos->tope_camino_2_nivel_2].col = atoi(token);
		(caminos->tope_camino_2_nivel_2)++;
		fscanf(archivo, FORMATO_CAMINOS, coordenada);
	}

	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	caminos->tope_camino_1_nivel_3 = 0;
	caminos->tope_camino_2_nivel_3 = 0;
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	while (strcmp(coordenada, "CAMINO=2")){
		token = strtok(coordenada, ";");
		caminos->camino_1_nivel_3[caminos->tope_camino_1_nivel_3].fil = atoi(token);
        token = strtok(NULL, ";");
		caminos->camino_1_nivel_3[caminos->tope_camino_1_nivel_3].col = atoi(token);
		(caminos->tope_camino_1_nivel_3)++;
		fscanf(archivo, FORMATO_CAMINOS, coordenada);
	}
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	while (strcmp(coordenada, "NIVEL=4")){
		token = strtok(coordenada, ";");
		caminos->camino_2_nivel_3[caminos->tope_camino_2_nivel_3].fil = atoi(token);
        token = strtok(NULL, ";");
		caminos->camino_2_nivel_3[caminos->tope_camino_2_nivel_3].col = atoi(token);
		(caminos->tope_camino_2_nivel_3)++;
		fscanf(archivo, FORMATO_CAMINOS, coordenada);
	}
	
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	caminos->tope_camino_1_nivel_4 = 0;
	caminos->tope_camino_2_nivel_4 = 0;
	fscanf(archivo, FORMATO_CAMINOS, coordenada);
	while (strcmp(coordenada, "CAMINO=2")){
		token = strtok(coordenada, ";");
		caminos->camino_1_nivel_4[caminos->tope_camino_1_nivel_4].fil = atoi(token);
        token = strtok(NULL, ";");
		caminos->camino_1_nivel_4[caminos->tope_camino_1_nivel_4].col = atoi(token);
		(caminos->tope_camino_1_nivel_4)++;
		fscanf(archivo, FORMATO_CAMINOS, coordenada);
	}
	int coordenada_leida = fscanf(archivo, FORMATO_CAMINOS, coordenada);
	while (coordenada_leida == 1){
		token = strtok(coordenada, ";");
		caminos->camino_2_nivel_4[caminos->tope_camino_2_nivel_4].fil = atoi(token);
        token = strtok(NULL, ";");
		caminos->camino_2_nivel_4[caminos->tope_camino_2_nivel_4].col = atoi(token);
		(caminos->tope_camino_2_nivel_4)++;
		coordenada_leida = fscanf(archivo, FORMATO_CAMINOS, coordenada);
	}

	fclose(archivo);
}

bool es_txt_valido(char ruta[MAX_RUTA]){
    if(strcmp(ruta+strlen(ruta)-4, TXT)==0){
        if(strlen(ruta) > 4){
            return true;
        }else{
            printf("Debe ingresar al menos un caracter además de la terminación '.txt'.\n");
        }
    }else{
        printf("Debe ingresar un nombre de archivo terminado en '.txt'.\n");
    }
    return false;
}

bool es_dat_valido(char ruta[MAX_RUTA]){
    if(strcmp(ruta+strlen(ruta)-4, DAT)==0){
        if(strlen(ruta) > 4){
            return true;
        }else{
            printf("Debe ingresar al menos un caracter además de la terminación '.dat'.\n");
        }
    }else{
        printf("Debe ingresar un nombre de archivo terminado en '.dat'.\n");
    }
    return false;
}

bool existe_archivo(char ruta[MAX_RUTA]){

    FILE* archivo = fopen(ruta, "r");
    if(archivo){
        fclose(archivo);
        return true;
    }
    printf("El archivo %s no existe!\n", ruta);
    return false;
}

bool cantidad_parametros_valida(int argc){
    if(argc <= MAX_COMANDOS && argc > 1){
        return true;
    }
    if(argc > MAX_COMANDOS){
        printf("Demasiados parametros!\n");
    }
    if(argc < MIN_COMANDOS){
        printf("No se ingresó un comando!\n");
    }
    return false;
}


void inicializar_caminos(caminos_t* caminos, char ruta[MAX_RUTA]){
	if(strcmp(ruta, POR_DEFECTO_STRING) == 0){

		coordenada_t entrada;
		coordenada_t torre;

		// nivel 1
		entrada.col = COLUMNAS_NIVEL1 - 1;
		entrada.fil = rand() % FILAS_NIVEL1;
		torre.col = 0;
		torre.fil = rand() % FILAS_NIVEL1;
		obtener_camino(caminos->camino_1_nivel_1, &(caminos->tope_camino_1_nivel_1), entrada, torre);
		caminos->tope_camino_2_nivel_1 = 0;

		//nivel 2
		entrada.col = 0;
		entrada.fil = rand() % FILAS_NIVEL2;
		torre.col = COLUMNAS_NIVEL2 - 1;
		torre.fil = rand() % FILAS_NIVEL2;
		obtener_camino(caminos->camino_2_nivel_2, &(caminos->tope_camino_2_nivel_2), entrada, torre);
		caminos->tope_camino_1_nivel_2 = 0;

		//nivel 3
		entrada.fil = 0;
		entrada.col = rand() % (COLUMNAS_NIVEL3 / 2);
		torre.fil = FILAS_NIVEL3 - 1;
		torre.col = rand() % (COLUMNAS_NIVEL3 / 2);
		obtener_camino(caminos->camino_1_nivel_3, &(caminos->tope_camino_1_nivel_3), entrada, torre);
		entrada.col = (rand() % (COLUMNAS_NIVEL3 / 2)) + (COLUMNAS_NIVEL3 / 2);
		torre.col = (rand() % (COLUMNAS_NIVEL3 / 2)) + (COLUMNAS_NIVEL3 / 2);
		obtener_camino(caminos->camino_2_nivel_3, &(caminos->tope_camino_2_nivel_3), entrada, torre);
        while(!camino_valido(caminos->camino_2_nivel_3, caminos->tope_camino_2_nivel_3, caminos->camino_1_nivel_3[0], caminos->camino_1_nivel_3[caminos->tope_camino_1_nivel_3 - 1])){
			obtener_camino(caminos->camino_2_nivel_3, &(caminos->tope_camino_2_nivel_3), entrada, torre);
		}

		//nivel 4
		entrada.fil = FILAS_NIVEL4 - 1;;
		entrada.col = rand() % (COLUMNAS_NIVEL4 / 2);
		torre.fil = 0;
		torre.col = rand() % (COLUMNAS_NIVEL4 / 2);
		obtener_camino(caminos->camino_1_nivel_4, &(caminos->tope_camino_1_nivel_4), entrada, torre);
		entrada.col = (rand() % (COLUMNAS_NIVEL4 / 2)) + (COLUMNAS_NIVEL4 / 2);
		torre.col = (rand() % (COLUMNAS_NIVEL4 / 2)) + (COLUMNAS_NIVEL4 / 2);
		obtener_camino(caminos->camino_2_nivel_4, &(caminos->tope_camino_2_nivel_4), entrada, torre);
        while(!camino_valido(caminos->camino_2_nivel_4, caminos->tope_camino_2_nivel_4, caminos->camino_1_nivel_4[0], caminos->camino_1_nivel_4[caminos->tope_camino_1_nivel_4 - 1])){
			obtener_camino(caminos->camino_2_nivel_4, &(caminos->tope_camino_2_nivel_4), entrada, torre);
		}
	}else{
		cargar_caminos_desde_archivo(caminos, ruta);
	}

}


/* 
*	Representa el camino con caracteres CAMINO en una matriz tablero ya inicializada
*/
static void insertar_camino_en_tablero(char tablero[MAX_COLUMNAS][MAX_FILAS], coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	if(tope_camino > 0){
		for (int i = 1; i < tope_camino - 1; i++){
			tablero[camino[i].fil][camino[i].col] = CAMINO;
		}
	}
}

/*
* Se espera un tablero con sus estructuras validas y pos_entrada y pos_torre unas posiciones validas del tablero
* Guarda el caracter ENTRADA en la posicion pos_entrada.
* Guarda el caracter TORRE en la posicion pos_torre.
*/
void insertar_extermos_camino(char tablero[MAX_COLUMNAS][MAX_FILAS], coordenada_t pos_entrada, coordenada_t pos_torre){
    tablero[pos_entrada.fil][pos_entrada.col] = ENTRADA;
    tablero[pos_torre.fil][pos_torre.col] = TORRE;
}

/* 
*	inicializa la matriz con valores VACIO
*/
static void inicializar_tablero(char tablero[MAX_COLUMNAS][MAX_FILAS], int tope_filas, int tope_columnas){
	for (int i = 0; i < tope_filas; i++){
		for (int j = 0; j < tope_columnas; j++){	
			tablero[i][j] = VACIO;
		} 
	}
}

/*
* Muestra en pantalla el camino recivido en nivel_caminos
* camino recive valores 1 o 2
*/
void mostrar_camino(nivel_caminos_t nivel_caminos, int camino){
	system("clear");
    switch (nivel_caminos.numero_nivel){
		case 1:
            printf("CAMINO NIVEL 1\n");
			break;
		case 2:
            printf("CAMINO NIVEL 2\n");
			break;
		case 3:
            if(camino == 1){
                printf("CAMINO 1 NIVEL 3\n");
            }else{
                printf("CAMINO 2 NIVEL 3\n");
            }
			break;
		case 4:
            if(camino == 1){
                printf("CAMINO 1 NIVEL 4\n");
            }else{
                printf("CAMINO 2 NIVEL 4\n");
            }
			break;
		default:
			break;
	}
	char tablero[MAX_COLUMNAS][MAX_FILAS];

    inicializar_tablero(tablero, nivel_caminos.tope_filas, nivel_caminos.tope_columnas);
	insertar_camino_en_tablero(tablero, nivel_caminos.camino_1, nivel_caminos.tope_camino_1);
	insertar_camino_en_tablero(tablero, nivel_caminos.camino_2, nivel_caminos.tope_camino_2);
    if(nivel_caminos.tope_camino_1 > 0){
        insertar_extermos_camino(tablero, nivel_caminos.camino_1[0], nivel_caminos.camino_1[nivel_caminos.tope_camino_1 - 1]);
    }
    if(nivel_caminos.tope_camino_2 > 0){
        insertar_extermos_camino(tablero, nivel_caminos.camino_2[0], nivel_caminos.camino_2[nivel_caminos.tope_camino_2 - 1]);
    }

	printf("                        ");
	for(int i = 0; i < (nivel_caminos.tope_columnas - 10); i++){
		printf("1 ");
	}
	printf("\n    ");
	for(int i = 0; i < nivel_caminos.tope_columnas; i++){
		if(i > 9){
			printf("%d ", i-10);
		}else{
			printf("%d ", i);
		}
	}
	printf("\n\n");
	for (int i = 0; i < nivel_caminos.tope_filas; i++){
		if(i < 10){
			printf(" %d  ", i);
		}else{
			printf("%d  ", i);
		}
		for (int j = 0; j < nivel_caminos.tope_columnas; j++){	
			printf("%c ",tablero[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool camino_valido(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino, coordenada_t entrada, coordenada_t torre){
    bool camino_valido = true;
    int i = 0;
    while(i < tope_camino && camino_valido){
        if((camino[i].fil == entrada.fil && camino[i].col == entrada.col) || (camino[i].fil == torre.fil && camino[i].col == torre.col))
            camino_valido = false;
        i++;
    }
    return camino_valido;
}

/*
* Devuelve TRUE si coordenada posee una posicion valida en el camino recibido dependiendo el nivel de nivel_caminos
* Se reciben valores 1 o 2 de camino
*/
bool entrada_valida(coordenada_t coordenada, nivel_caminos_t nivel_caminos, int camino){
    bool entrada_valida = true;
    switch (nivel_caminos.numero_nivel){
		case 1:
			if(!((coordenada.col == nivel_caminos.tope_columnas - 1) && (coordenada.fil >= 0) && (coordenada.fil < nivel_caminos.tope_filas))){
                entrada_valida = false;
                printf("la entrada debe estar en la columna %d y entre la fila 0 y %d inclusive: ", nivel_caminos.tope_columnas - 1, nivel_caminos.tope_filas - 1);
            }
			break;
		case 2:
			if(!((coordenada.col == 0) && (coordenada.fil >= 0) && (coordenada.fil < nivel_caminos.tope_filas))){
                entrada_valida = false;
                printf("la entrada debe estar en la columna 0 y entre la fila 0 y %d inclusive: ", nivel_caminos.tope_filas - 1);
            }
			break;
		case 3:
			if(!((coordenada.fil == 0) && (coordenada.col >= 0) && (coordenada.col < nivel_caminos.tope_columnas))){
                printf("la entrada debe estar en la fila 0 y entre la columna 0 y %d inclusive: ", nivel_caminos.tope_columnas - 1);
                entrada_valida = false;
            }
            if((camino == 2) && (coordenada.fil == nivel_caminos.camino_1[0].fil) && (coordenada.col == nivel_caminos.camino_1[0].col)){
                printf("la entrada no puede coincidir con la entrada del camino 1: ");
                entrada_valida = false;
            }
			break;
		case 4:
			if(!((coordenada.fil == nivel_caminos.tope_filas - 1) && (coordenada.col >= 0) && (coordenada.col < nivel_caminos.tope_columnas))){
                printf("la entrada debe estar en la fila %d y entre la columna 0 y %d inclusive: ", nivel_caminos.tope_filas - 1, nivel_caminos.tope_columnas - 1);
                entrada_valida = false;
            }
            if((camino == 2) && (coordenada.fil == nivel_caminos.camino_1[0].fil) && (coordenada.col == nivel_caminos.camino_1[0].col)){
                printf("la entrada no puede coincidir con la entrada del camino 1: ");
                entrada_valida = false;
            }
			break;
		default:
			break;
	}
    return entrada_valida;
}

/*
* guada en nivel_caminos la posicion coordenada en el camino de camino_numero.
* Se espera que coordenada posea una posicion valida del camino.
*/
void insertar_coordenada_en_camino(nivel_caminos_t* nivel_caminos, coordenada_t coordenada, int camino_numero){
    if(camino_numero == 1){
        nivel_caminos->camino_1[nivel_caminos->tope_camino_1] = coordenada;
        (nivel_caminos->tope_camino_1)++;
    }else{
        nivel_caminos->camino_2[nivel_caminos->tope_camino_2] = coordenada;
        (nivel_caminos->tope_camino_2)++;
    }
}

/*
* Devuelve TRUE si coordenada posee una posicion valida en el camino recibido dependiendo el nivel de nivel_caminos
* Se reciben valores 1 o 2 de camino
*/
bool torre_valida(nivel_caminos_t nivel_caminos, int camino_numero){
    bool torre_valida = false;
    switch (nivel_caminos.numero_nivel){
        case 1:
            if(nivel_caminos.camino_1[nivel_caminos.tope_camino_1 - 1].col == 0){
                torre_valida = true;
            }else{
                printf("La Torre debe estar en la columna 0.");
            }
            break;
        case 2:
            if(nivel_caminos.camino_2[nivel_caminos.tope_camino_2 - 1].col == nivel_caminos.tope_columnas - 1){
                torre_valida = true;
            }else{
                printf("La Torre debe estar en la columna %d.", nivel_caminos.tope_columnas - 1);
            }
            break;
        case 3:
            if(nivel_caminos.camino_1[nivel_caminos.tope_camino_1 - 1].fil == nivel_caminos.tope_filas - 1){
                torre_valida = true;
            }else{
                printf("La Torre debe estar en la fila %d.", nivel_caminos.tope_filas - 1);
            }
            if((camino_numero == 2) && (nivel_caminos.camino_1[nivel_caminos.tope_camino_1 - 1].col == nivel_caminos.camino_2[nivel_caminos.tope_camino_2 - 1].col)){
                printf("La torre no puede coincidir con la torre del camino 1.");
                torre_valida = false;
            }
            break;
        case 4:
            if(nivel_caminos.camino_1[nivel_caminos.tope_camino_1 - 1].fil == 0){
                torre_valida = true;
            }else{
                printf("La Torre debe estar en la fila 0.");
            }
            if((camino_numero == 2) && (nivel_caminos.camino_1[nivel_caminos.tope_camino_1 - 1].col == nivel_caminos.camino_2[nivel_caminos.tope_camino_2 - 1].col)){
                printf("La torre no puede coincidir con la torre del camino 1.");
                torre_valida = false;
            }
            break;
        default:
            break;
    }
    return torre_valida;
}

/*
* Devuelve true si movimiento corresponde a una coordenada válida. Devuelve false en caso contrario.
*/
bool insertar_movimiento(char movimiento, nivel_caminos_t* nivel_caminos, int camino_numero){
    bool movimiento_valido = false;
    switch (movimiento){
        case ARRIBA:
            if(camino_numero == 1){
                if(nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].fil > 0){
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].fil = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].fil - 1;
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].col = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].col;
                    movimiento_valido = true;
                }
            }else{
                if(nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].fil > 0){
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].fil = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].fil - 1;
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].col = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].col;
                    movimiento_valido = true;
                }
            }
            break;
        case IZQUIERDA:
            if(camino_numero == 1){
                if(nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].col > 0){
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].col = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].col - 1;
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].fil = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].fil;
                    movimiento_valido = true;
                }
            }else{
                if(nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].col > 0){
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].col = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].col - 1;
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].fil = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].fil;
                    movimiento_valido = true;
                }
            }
            break;
        case DERECHA:
            if(camino_numero == 1){
                if(nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].col < nivel_caminos->tope_columnas - 1){
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].col = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].col + 1;
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].fil = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].fil;
                    movimiento_valido = true;
                }
            }else{
                if(nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].col < nivel_caminos->tope_columnas - 1){
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].col = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].col + 1;
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].fil = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].fil;
                    movimiento_valido = true;
                }
            }
            break;
        case ABAJO:
            if(camino_numero == 1){
                if(nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].fil < nivel_caminos->tope_filas - 1){
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].fil = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].fil + 1;
                    nivel_caminos->camino_1[nivel_caminos->tope_camino_1].col = nivel_caminos->camino_1[nivel_caminos->tope_camino_1 - 1].col;
                    movimiento_valido = true;
                }
            }else{
                if(nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].fil < nivel_caminos->tope_filas - 1){
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].fil = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].fil + 1;
                    nivel_caminos->camino_2[nivel_caminos->tope_camino_2].col = nivel_caminos->camino_2[nivel_caminos->tope_camino_2 - 1].col;
                    movimiento_valido = true;
                }
            }
            break;
        case TORRE:
            if(torre_valida(*nivel_caminos, camino_numero)){
                movimiento_valido = true;
            }
        default:
            break;
    }

    if((movimiento_valido) && (movimiento != TORRE)){
        if(camino_numero == 1){
            (nivel_caminos->tope_camino_1)++;
        }else{
            (nivel_caminos->tope_camino_2)++;
        }
    }else{
        if(movimiento != TORRE){
            printf ("Movimiento no válido!!");
        }
    }
    return movimiento_valido;
}

/*
* Pide al usuario un caracter hasta qué este corresponda a un movimiento válido, devuelve true si el caracter valido ingresado es TORRE
*/
bool pedir_movimiento(nivel_caminos_t* nivel_caminos, int camino_numero){
    char movimiento;
    printf("  %c -> Izquierda\n  %c -> Abajo\n  %c -> Derecha\n  %c -> Arriba\n  %c -> Terminar\nIngrese un caracter: ", IZQUIERDA, ABAJO, DERECHA, ARRIBA, TORRE);
    scanf(" %c", &movimiento);
    while(!insertar_movimiento(movimiento, nivel_caminos, camino_numero)){
        printf("  %c -> Izquierda\n  %c -> Abajo\n  %c -> Derecha\n  %c -> Arriba\n  %c -> Terminar\nIngrese un caracter: ", IZQUIERDA, ABAJO, DERECHA, ARRIBA, TORRE);
        scanf(" %c", &movimiento);
    }
    return movimiento == TORRE;
}


/*
* Pide al usuario que ingrese un camino a base de caracteres que representan las posiciones arriba, derecha, izquierda y abajo
* Devuelve true si el camino pudo ser creado exitosamente. Devuelve false en caso contrario
*/
bool pedir_camino(nivel_caminos_t* nivel_caminos, int camino){
    mostrar_camino(*nivel_caminos, camino);
    coordenada_t coordenada;
    bool camino_terminado = false;
    printf("ingrese la posicion de entrada (F C): ");
    scanf(" %d %d", &coordenada.fil, &coordenada.col);
    while(!entrada_valida(coordenada, *nivel_caminos, camino)){
        scanf(" %d %d", &coordenada.fil, &coordenada.col);
    }
    insertar_coordenada_en_camino(nivel_caminos, coordenada, camino); 
    int i = 1;
    while((i < MAX_LONGITUD_CAMINO) && !camino_terminado){
        mostrar_camino(*nivel_caminos, camino);
        camino_terminado = pedir_movimiento(nivel_caminos, camino);
        i++;
    }
    if (i < MAX_LONGITUD_CAMINO){
        mostrar_camino(*nivel_caminos, camino);
        printf("Camino terminado!!\n");
        detener_el_tiempo(2);
        return true;
    }
    printf("El camino tiene que ser terminado en menos de %d movimientos! Se procederá a realizar de nuevo el camino.\n", MAX_LONGITUD_CAMINO);
    return false;
}

/*
* Define los valores de nivel_caminos dependiendo el nivel obtenido de dicha estructura en nivel_caminos.numero_nivel
*/
void definir_limites(nivel_caminos_t* nivel_caminos){
	switch (nivel_caminos->numero_nivel){
		case 1:
			nivel_caminos->tope_filas = FILAS_NIVEL1;
			nivel_caminos->tope_columnas = COLUMNAS_NIVEL1;
			break;
		case 2:
			nivel_caminos->tope_filas = FILAS_NIVEL2;
			nivel_caminos->tope_columnas = COLUMNAS_NIVEL2;
			break;
		case 3:
			nivel_caminos->tope_filas = FILAS_NIVEL3;
			nivel_caminos->tope_columnas = COLUMNAS_NIVEL3;
			break;
		case 4:
			nivel_caminos->tope_filas = FILAS_NIVEL4;
			nivel_caminos->tope_columnas = COLUMNAS_NIVEL4;
			break;
		default:
			break;
	}
}

/*
*
*/
void escribir_coordenadas_en_archivo(FILE* archivo, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
    for(int i = 0; i < tope_camino; i++){
        fprintf(archivo, FORMATO_COORDENADAS, camino[i].fil, camino[i].col);
    }
}

/*
*
*/
void escribir_configuracion_en_archivo(char ruta[MAX_RUTA], configuracion_t configuracion){
    FILE* archivo = fopen(ruta, "w");
    fprintf(archivo, FORMATO_TORRES, CLAVE_RESISTENCIA_TORRES, configuracion.resistencia_torre_1, configuracion.resistencia_torre_2);
    fprintf(archivo, FORMATO_DEFENSORES_INICIO, CLAVE_ENANOS_INICIO, configuracion.enanos_nivel_1, configuracion.enanos_nivel_2, configuracion.enanos_nivel_3, configuracion.enanos_nivel_4);
    fprintf(archivo, FORMATO_DEFENSORES_INICIO, CLAVE_ELFOS_INICIO, configuracion.elfos_nivel_1, configuracion.elfos_nivel_2, configuracion.elfos_nivel_3, configuracion.elfos_nivel_4);
    fprintf(archivo, FORMATO_DEFENSORES_EXTRAS, CLAVE_ENANOS_EXTRA, configuracion.enanos_extra, configuracion.enanos_coste_torre_1, configuracion.enanos_coste_torre_2);
    fprintf(archivo, FORMATO_DEFENSORES_EXTRAS, CLAVE_ELFOS_EXTRA, configuracion.elfos_extra, configuracion.elfos_coste_torre_1, configuracion.elfos_coste_torre_2);
    fprintf(archivo, FORMATO_ANIMOS, CLAVE_ENANOS_ANIMO, configuracion.enanos_fallo, configuracion.enanos_critico);
    fprintf(archivo, FORMATO_ANIMOS, CLAVE_ELFOS_ANIMO, configuracion.elfos_fallo, configuracion.elfos_critico);
    fprintf(archivo, FORMATO_VELOCIDAD, CLAVE_VELOCIDAD, configuracion.velocidad_juego);
    fprintf(archivo, FORMATO_CAMINOS_RUTA, CLAVE_CAMINOS, configuracion.caminos);
    fclose(archivo);
}

/*
* Escribe los caminos de un nivel en el archivo recibido
* Se espera que el archivo ya esté abierto en modo escritura
*/
void escribir_caminos_en_archivo(FILE* archivo, nivel_caminos_t nivel_caminos){
    switch(nivel_caminos.numero_nivel){
        case 1:
            fprintf(archivo, "NIVEL=1\nCAMINO=1\n");
            escribir_coordenadas_en_archivo(archivo, nivel_caminos.camino_1, nivel_caminos.tope_camino_1);
            break;
        case 2:
            fprintf(archivo, "NIVEL=2\nCAMINO=1\n");
            escribir_coordenadas_en_archivo(archivo, nivel_caminos.camino_2, nivel_caminos.tope_camino_2);
            break;
        case 3:
            fprintf(archivo, "NIVEL=3\nCAMINO=1\n");
            escribir_coordenadas_en_archivo(archivo, nivel_caminos.camino_1, nivel_caminos.tope_camino_1);
            fprintf(archivo, "CAMINO=2\n");
            escribir_coordenadas_en_archivo(archivo, nivel_caminos.camino_2, nivel_caminos.tope_camino_2);
            break;
        case 4:
            fprintf(archivo, "NIVEL=4\nCAMINO=1\n");
            escribir_coordenadas_en_archivo(archivo, nivel_caminos.camino_1, nivel_caminos.tope_camino_1);
            fprintf(archivo, "CAMINO=2\n");
            escribir_coordenadas_en_archivo(archivo, nivel_caminos.camino_2, nivel_caminos.tope_camino_2);
            break;
        default:
            break;
    }
}

void inicializar_configuracion(configuracion_t* configuracion){
	configuracion->resistencia_torre_1 = POR_DEFECTO;
	configuracion->resistencia_torre_2 = POR_DEFECTO;
	configuracion->enanos_nivel_1 = POR_DEFECTO;
	configuracion->enanos_nivel_2 = POR_DEFECTO;
	configuracion->enanos_nivel_3 = POR_DEFECTO;
	configuracion->enanos_nivel_4 = POR_DEFECTO;
	configuracion->elfos_nivel_1 = POR_DEFECTO;
	configuracion->elfos_nivel_2 = POR_DEFECTO;
	configuracion->elfos_nivel_3 = POR_DEFECTO;
	configuracion->elfos_nivel_4 = POR_DEFECTO;
	configuracion->enanos_extra = POR_DEFECTO;
	configuracion->enanos_coste_torre_1 = POR_DEFECTO;
	configuracion->enanos_coste_torre_2 = POR_DEFECTO;
	configuracion->elfos_extra = POR_DEFECTO;
	configuracion->elfos_coste_torre_1 = POR_DEFECTO;
	configuracion->elfos_coste_torre_2 = POR_DEFECTO;
	configuracion->velocidad_juego = POR_DEFECTO;
	strcpy(configuracion->caminos, POR_DEFECTO_STRING);
}

void crear_camino(char* nombre_archivo){
    nivel_caminos_t nivel_caminos;
    nivel_caminos.numero_nivel = 1;
    definir_limites(&nivel_caminos);
    nivel_caminos.tope_camino_1 = 0;
    nivel_caminos.tope_camino_2 = 0;
    FILE* archivo = fopen(nombre_archivo, "w");
    while(nivel_caminos.numero_nivel < 5){
        if(nivel_caminos.numero_nivel != 2){
            while (!pedir_camino(&nivel_caminos, 1)){
                nivel_caminos.tope_camino_1 = 0;
            }
        }
        if(nivel_caminos.numero_nivel >= 2){
            while (!pedir_camino(&nivel_caminos, 2)){
                nivel_caminos.tope_camino_2 = 0;
            }
        }
        escribir_caminos_en_archivo(archivo, nivel_caminos);
        (nivel_caminos.numero_nivel)++;
        nivel_caminos.tope_camino_1 = 0;
        nivel_caminos.tope_camino_2 = 0;
        definir_limites(&nivel_caminos);
    }
    fclose(archivo);
    printf("Caminos guardados en '%s'!", nombre_archivo);
}

/*
* Devuelve true si resistencia es mayor o igual a RESISTENCIA_TORRE_MINIMA y menor o igual a RESISTENCIA_TORRE_MÁXIMA.
* Devuelve true tambien si es igual a POR_DEFECTO.
* Devuelve false en caso contrario.
*/
bool resistencia_torre_valida(int resistencia){
    return (((resistencia >= RESISTENCIA_TORRE_MINIMA) && (resistencia <= RESISTENCIA_TORRE_MAXIMA)) || (resistencia == POR_DEFECTO));
}

/*
* Devuelve true si defensores es mayor o igual a DEFENSORES_MINIMOS y menor o igual a DEFENSORES_MAXIMOS
* Devuelve true tambien si es igual a POR_DEFECTO
* Devuelve false en caso contrario.
*/
bool cantidad_defensores_valida(int defensores){
    return (((defensores >= DEFENSORES_MINIMOS) && (defensores <= DEFENSORES_MAXIMOS)) || (defensores == POR_DEFECTO));
}

/*
* Devuelve true si extra es mayor o igual a EXTRAS_MINIMOS y menor o igual a EXTRAS_MAXIMOS
* Devuelve true tambien si es igual a POR_DEFECTO
* Devuelve false en caso contrario.
*/
bool cantidad_extra_valida(int extra){
    return (((extra >= EXTRAS_MINIMOS) && (extra <= EXTRAS_MAXIMOS)) || (extra == POR_DEFECTO));
}

/*
* Devuelve true si extra es mayor o igual a COSTE_EXTRAS_MINIMO y menor o igual a COSTE_EXTRAS_MAXIMO
* Devuelve true tambien si es igual a POR_DEFECTO
* Devuelve false en caso contrario.
*/
bool coste_extra_valido(int extra){
    return (((extra >= COSTE_EXTRAS_MINIMO) && (extra <= COSTE_EXTRAS_MAXIMO)) || (extra == POR_DEFECTO));
}

/*
* Devuelve true si porcentaje es mayor o igual a PORCENTAJE_MINIMO y menor o igual a PORCENTAJE_MAXIMO
* Devuelve true tambien si es igual a POR_DEFECTO
* Devuelve false en caso contrario.
*/
bool porcentaje_valido(int porcentaje){
    return (((porcentaje >= PORCENTAJE_MINIMO) && (porcentaje <= PORCENTAJE_MAXIMO)) || (porcentaje == POR_DEFECTO));
}

/*
* Devuelve true si velocidad es mayor o igual a VELOCIDAD_MINIMA y menor o igual a VELOCIDAD_MAXIMA
* Devuelve true tambien si es igual a POR_DEFECTO
* Devuelve false en caso contrario.
*/
bool velocidad_valida(float velocidad){
    return (((velocidad >= VELOCIDAD_MINIMA) && (velocidad <= VELOCIDAD_MAXIMA)) || (velocidad == POR_DEFECTO));
}

/*
* verifica que la cadena de caracteres ingresadas en "ruta" corresponda a un archivo que pueda
* ser abierto.
* Devuelve TRUE en caso de que exista.
* Devuelve False en caso de que el archivo no se pueda abrir o si el largo de la cadena
* es menor a 4 o mayor a 100
*/
bool ruta_caminos_valida(char ruta[MAX_RUTA]){
    if(strcmp(ruta, "-1") == 0){
        return true;
    }
    if(strlen(ruta) <= 4 || strlen(ruta) >= MAX_RUTA){
        return false;
    }
    FILE* archivo = fopen(ruta, "r");
    if(archivo){
        fclose(archivo);
        return true;
    }
    return false;
}


void crear_configuracion(char* nombre_archivo){
    configuracion_t configuracion;
    printf("Se le preguntara sobre cada dato del juego. Si no desea modificar alguno de ellos ingrese '%d'.\n", POR_DEFECTO);
    printf("Resistencia torre 1: ");
    scanf("%d", &(configuracion.resistencia_torre_1));
    while(!resistencia_torre_valida(configuracion.resistencia_torre_1)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", RESISTENCIA_TORRE_MINIMA, RESISTENCIA_TORRE_MINIMA);
        scanf("%d", &(configuracion.resistencia_torre_1));
    }

    printf("Resistencia torre 2: ");
    scanf("%d", &(configuracion.resistencia_torre_2));
    while(!resistencia_torre_valida(configuracion.resistencia_torre_2)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", RESISTENCIA_TORRE_MINIMA, RESISTENCIA_TORRE_MINIMA);
        scanf("%d", &(configuracion.resistencia_torre_2));
    }

    printf("Enanos nivel 1: ");
    scanf("%d", &(configuracion.enanos_nivel_1));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_1)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.enanos_nivel_1));
    }

    printf("Enanos nivel 2: ");
    scanf("%d", &(configuracion.enanos_nivel_2));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_2)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.enanos_nivel_2));
    }

    printf("Enanos nivel 3: ");
    scanf("%d", &(configuracion.enanos_nivel_3));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_3)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.enanos_nivel_3));
    }

    printf("Enanos nivel 4: ");
    scanf("%d", &(configuracion.enanos_nivel_4));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_4)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.enanos_nivel_4));
    }

    printf("Elfos nivel 1: ");
    scanf("%d", &(configuracion.elfos_nivel_1));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_1)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.elfos_nivel_1));
    }

    printf("Elfos nivel 2: ");
    scanf("%d", &(configuracion.elfos_nivel_2));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_2)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.elfos_nivel_2));
    }

    printf("Elfos nivel 3: ");
    scanf("%d", &(configuracion.elfos_nivel_3));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_3)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.elfos_nivel_3));
    }

    printf("Elfos nivel 4: ");
    scanf("%d", &(configuracion.elfos_nivel_4));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_4)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", DEFENSORES_MINIMOS, DEFENSORES_MAXIMOS);
        scanf("%d", &(configuracion.elfos_nivel_4));
    }

    printf("Enanos extra: ");
    scanf("%d", &(configuracion.enanos_extra));
    while(!cantidad_extra_valida(configuracion.enanos_extra)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", EXTRAS_MINIMOS, EXTRAS_MAXIMOS);
        scanf("%d", &(configuracion.enanos_extra));
    }

    printf("Coste de enanos extra en torre 1: ");
    scanf("%d", &(configuracion.enanos_coste_torre_1));
    while(!coste_extra_valido(configuracion.enanos_coste_torre_1)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", COSTE_EXTRAS_MINIMO, COSTE_EXTRAS_MAXIMO);
        scanf("%d", &(configuracion.enanos_coste_torre_1));
    }

    printf("Coste de enanos extra en torre 2: ");
    scanf("%d", &(configuracion.enanos_coste_torre_2));
    while(!coste_extra_valido(configuracion.enanos_coste_torre_2)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", COSTE_EXTRAS_MINIMO, COSTE_EXTRAS_MAXIMO);
        scanf("%d", &(configuracion.enanos_coste_torre_2));
    }

    printf("Elfos extra: ");
    scanf("%d", &(configuracion.elfos_extra));
    while(!cantidad_extra_valida(configuracion.elfos_extra)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", EXTRAS_MINIMOS, EXTRAS_MAXIMOS);
        scanf("%d", &(configuracion.elfos_extra));
    }

    printf("Coste de elfos extra en torre 1: ");
    scanf("%d", &(configuracion.elfos_coste_torre_1));
    while(!coste_extra_valido(configuracion.elfos_coste_torre_1)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", COSTE_EXTRAS_MINIMO, COSTE_EXTRAS_MAXIMO);
        scanf("%d", &(configuracion.elfos_coste_torre_1));
    }

    printf("Coste de elfos extra en torre 2: ");
    scanf("%d", &(configuracion.elfos_coste_torre_2));
    while(!coste_extra_valido(configuracion.elfos_coste_torre_2)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", COSTE_EXTRAS_MINIMO, COSTE_EXTRAS_MAXIMO);
        scanf("%d", &(configuracion.elfos_coste_torre_2));
    }

    printf("Fallo enanos: ");
    scanf("%d", &(configuracion.enanos_fallo));
    while(!porcentaje_valido(configuracion.enanos_fallo)){
        printf("Debe ingresar un número entre %d y %d inclusive ambos: ", PORCENTAJE_MINIMO, PORCENTAJE_MAXIMO);
        scanf("%d", &(configuracion.enanos_fallo));
    }

    if(configuracion.enanos_fallo != POR_DEFECTO){
        printf("Las siguientes 3 preguntas no se podra ingresar el valor '%d'\n", POR_DEFECTO);

        printf("Critico enanos: ");
        scanf("%d", &(configuracion.enanos_critico));
        while(!porcentaje_valido(configuracion.enanos_critico) || configuracion.enanos_critico == POR_DEFECTO){
            printf("Debe ingresar un número entre %d y %d inclusive ambos: ", PORCENTAJE_MINIMO, PORCENTAJE_MAXIMO);
            scanf("%d", &(configuracion.enanos_critico));
        }

        printf("Fallo elfos: ");
        scanf("%d", &(configuracion.elfos_fallo));
        while(!porcentaje_valido(configuracion.elfos_fallo) || configuracion.elfos_fallo == POR_DEFECTO){
            printf("Debe ingresar un número entre %d y %d inclusive ambos: ", PORCENTAJE_MINIMO, PORCENTAJE_MAXIMO);
            scanf("%d", &(configuracion.elfos_fallo));
        }

        printf("Critico elfos: ");
        scanf("%d", &(configuracion.elfos_critico));
        while(!porcentaje_valido(configuracion.elfos_critico) || configuracion.elfos_critico == POR_DEFECTO){
            printf("Debe ingresar un número entre %d y %d inclusive ambos: ", PORCENTAJE_MINIMO, PORCENTAJE_MAXIMO);
            scanf("%d", &(configuracion.elfos_critico));
        }
    }else{
        configuracion.enanos_critico = POR_DEFECTO;
        configuracion.elfos_fallo = POR_DEFECTO;
        configuracion.elfos_critico = POR_DEFECTO;
    }

    printf("Velocidad juego: ");
    scanf("%f", &(configuracion.velocidad_juego));
    while(!velocidad_valida(configuracion.velocidad_juego)){
        printf("Debe ingresar un número entre %f y %f inclusive ambos: ", VELOCIDAD_MINIMA, VELOCIDAD_MAXIMA);
        scanf("%f", &(configuracion.velocidad_juego));
    }

    printf("Caminos juego (ruta del archivo .txt): ");
    scanf("%s", configuracion.caminos);
    while(!ruta_caminos_valida(configuracion.caminos)){
        printf("Debe ingresar la ruta de un archivo EXISTENTE de caminos (de extencion .txt): ");
        scanf("%s", configuracion.caminos);
    }
    
    escribir_configuracion_en_archivo(nombre_archivo, configuracion);

    printf("Configuracion guardada en '%s'!\n", nombre_archivo);
    
}

int orcos_muertos_en_nivel(nivel_t nivel){
    int orcos_nivel = 0;
    for(int i = 0; i < nivel.tope_enemigos; i++){
        if(!(nivel.enemigos[i].vida > 0) && ((nivel.enemigos[i].camino == 1 && nivel.enemigos[i].pos_en_camino < (nivel.tope_camino_1 - 1)) || ((nivel.enemigos[i].camino == 2 && nivel.enemigos[i].pos_en_camino < (nivel.tope_camino_2 - 1))))){
            orcos_nivel++;
        }
    }
    return orcos_nivel;
}

/*
* Recibe un string y crea uno nuevo en base al recibido agregandole el prefijo RUTA_RANKING_BASE y el sufijo CSV
* En caso de que el string recibido sea igual a POR_DEFECTO_STRING, el nuevo string solo esta formado por el prefijo y el sufijo
*/
void construir_ruta_ranking(char config[MAX_RUTA], char ruta[MAX_RUTA]){
    strcpy(ruta, RUTA_RANKING_BASE);
    if(strcmp(config, POR_DEFECTO_STRING) != 0){
        config[strlen(config) - 4] = '\0';
        strcat(ruta, "_");
        strcat(ruta, config);
    }
    strcat(ruta, CSV);
}

void mostrar_ranking(char ruta_configuracion[MAX_RUTA], int listar){
    char ruta[MAX_RUTA];
    construir_ruta_ranking(ruta_configuracion, ruta);
    FILE* archivo = fopen(ruta, "r");
    char nombre[MAX_NOMBRE];
    int puntaje = NO_HAY_REGISTROS;

    if(archivo){
        int i = 0;
        int leidos = fscanf(archivo, "%[^;];%d\n", nombre, &puntaje);
        if(leidos==CAMPOS_RANKING){
            printf("PUNTOS         NOMBRE\n");
            while(leidos == CAMPOS_RANKING && (i < listar || listar == LISTAR_TODOS)){
                printf("%d             %s\n", puntaje, nombre);
                leidos = fscanf(archivo, "%[^;];%d\n", nombre, &puntaje);
                i++;
            }
        }
        fclose(archivo);
    }
    if(puntaje == NO_HAY_REGISTROS){
        printf("Todavia no hay rankings para la congifuración ingresada.\n");
    }
}


void preguntar_nombre(char nombre[MAX_NOMBRE]){
    printf("Ingrese su nombre para guardar en el ranking: ");
    scanf(" %s", nombre);
    while (strlen(nombre) < 1){
        printf("Ingrese su nombre para guardar en el ranking: ");
        scanf(" %s", nombre);
    }
}

void escribir_puntaje_en_ranking(int puntaje, char config[MAX_RUTA]){
    char ruta[MAX_RUTA];
    char nombre[MAX_NOMBRE];
    preguntar_nombre(nombre);
    construir_ruta_ranking(config, ruta);
    FILE* archivo = fopen(ruta, "r");
    if(!archivo){
        archivo = fopen(ruta, "w");
        fprintf(archivo, "%s;%d\n", nombre, puntaje);
    }else{
        FILE* archivo_aux = fopen(ARCHIVO_AUXILIAR, "w");
        char nombre_aux[MAX_NOMBRE];
        int puntaje_aux;
        int leidos = fscanf(archivo, "%[^;];%d\n", nombre_aux, &puntaje_aux);
        if(leidos < CAMPOS_RANKING){
            fprintf(archivo_aux, "%s;%d\n", nombre, puntaje);
        }else{
            while(leidos == CAMPOS_RANKING){
                if((puntaje > puntaje_aux) || ((puntaje == puntaje_aux) && (strcmp(nombre, nombre_aux) < 0))){
                    fprintf(archivo_aux, "%s;%d\n", nombre, puntaje);
                    puntaje = POR_DEFECTO;
                }
                fprintf(archivo_aux, "%s;%d\n", nombre_aux, puntaje_aux);
                leidos = fscanf(archivo, "%[^;];%d\n", nombre_aux, &puntaje_aux);
            }
            if(puntaje != POR_DEFECTO){
                fprintf(archivo_aux, "%s;%d\n", nombre, puntaje);
            }
        }
        fclose(archivo_aux);
        rename(ARCHIVO_AUXILIAR, ruta);
    }
    fclose(archivo);
}

int calcular_puntaje(int nivel_actual, configuracion_t configuracion, int orcos_muertos[4]){
    int puntaje;
    for(int i = 0; i < nivel_actual; i++){
        puntaje += orcos_muertos[i];
    }
    puntaje = puntaje * MULTIPLICADOR_ORCOS_MUERTOS;
    int divisor = configuracion.resistencia_torre_1 + configuracion.resistencia_torre_2;
    divisor += configuracion.enanos_nivel_1 + configuracion.enanos_nivel_2 + configuracion.enanos_nivel_3 + configuracion.enanos_nivel_4;
    divisor += configuracion.elfos_nivel_1 + configuracion.elfos_nivel_2 + configuracion.elfos_nivel_3 + configuracion.elfos_nivel_4;
    divisor += configuracion.enanos_extra + configuracion.elfos_extra;
    return puntaje / divisor;
}

void mostrar_repeticion(char ruta[MAX_RUTA], float velocidad){
    FILE* archivo = fopen(ruta, "r");
    juego_t juego;
    fread(&juego, sizeof(juego_t), 1, archivo);
    while(!feof(archivo)){
        mostrar_juego(juego);
        detener_el_tiempo(velocidad);
        fread(&juego, sizeof(juego_t), 1, archivo);
    }
    fclose(archivo);
}

void comando_ranking(int argc, char* argv[]){
	int i = 2;
	bool hay_errores = false;
	bool hay_cofiguracion = false;
	int listar = LISTAR_TODOS;
	char* token;
	char ruta_configuracion[MAX_RUTA];
	while(i <= MAX_COMANDOS && i < argc){
		token = strtok(argv[i], SEPARADOR);
		if(strcmp(token, CONFIGURACION_CLAVE) == 0){
			token = strtok(NULL, SEPARADOR);
			hay_cofiguracion = true;
			if(token != NULL){
				if(existe_archivo(token)){
					strcpy(ruta_configuracion, token);
				}else{
					hay_errores = true;
				}
			}else{
				printf("Debe ingresar el archivo de la configuración\n");
				hay_errores = true;
			}
		}else if(strcmp(token, LISTAR_CLAVE) == 0){
			token = strtok(NULL, SEPARADOR);
			if(token != NULL){
				listar = atoi(token);
				if(listar < LISTAR_MINIMO){
					printf("El valor a listar debe ser mayor o igual a %d\n", LISTAR_MINIMO);
					hay_errores = true;
				}
			}else{
				printf("Debe ingresar el valor a listar.\n");
				hay_errores = true;
			}
		}	
		i++;
	}
	if(!hay_cofiguracion){
		strcpy(ruta_configuracion, POR_DEFECTO_STRING);
	}
	if(!hay_errores){
		mostrar_ranking(ruta_configuracion, listar);
	}
}

void comando_crear_camino(int argc, char* argv[]){
	if(argc > 2){
		if(es_txt_valido(argv[2])){
			crear_camino(argv[2]);
		}
	}else{
		printf("Debe ingresar el nombre de archivo para guardar el camino.\n");
	}
}

void comando_crear_configuracion(int argc, char* argv[]){
	if(argc > 2){
		if(es_txt_valido(argv[2])){
			crear_configuracion(argv[2]);
		}
	}else{
		printf("Debe ingresar el nombre de archivo para guardar la configuración.\n");
	}
}

void comando_poneme_la_repe(int argc, char* argv[]){
    int i = 2;
    bool hay_errores = false;
    bool hay_grabacion = false;
    float velocidad = VELOCIDAD;
    char* token;
    char ruta_grabacion[MAX_RUTA];
    while(i <= MAX_COMANDOS && i < argc){
        token = strtok(argv[i], SEPARADOR);
        if(strcmp(token, GRABACION_CLAVE) == 0){
            token = strtok(NULL, SEPARADOR);
            hay_grabacion = true;
            if(token != NULL){
                if(existe_archivo(token)){
                    strcpy(ruta_grabacion, token);
                }else{
                    hay_errores = true;
                }
            }else{
                printf("Debe ingresar el archivo que contiene la grabacion\n");
                hay_errores = true;
            }
        }else if(strcmp(token, VELOCIDAD_CLAVE) == 0){
            token = strtok(NULL, SEPARADOR);
            if(token != NULL){
                velocidad = (float)atof(token);
            }else{
                printf("Debe ingresar el valor de la velocidad.\n");
                hay_errores = true;
            }
        }	
        i++;
    }
    if(!hay_grabacion){
        printf("Debe ingresar el nombre del archivo de la repetición.\n");
        hay_errores = true;
    }
    if(!hay_errores){
        mostrar_repeticion(ruta_grabacion, velocidad);
    }
}

bool comando_jugar(int argc, char* argv[], char ruta_configuracion[MAX_RUTA], char ruta_grabacion[MAX_RUTA]){
	int i = 2;
	bool hay_que_grabar = false;
	bool hay_configuracion = false;
	bool hay_errores = false;
	char* token;
	while(i <= MAX_COMANDOS && i < argc){
		token = strtok(argv[i], SEPARADOR);
		if(strcmp(token, CONFIGURACION_CLAVE) == 0){
			token = strtok(NULL, SEPARADOR);
			if(token != NULL){
				if(existe_archivo(token)){
					hay_configuracion = true;
					strcpy(ruta_configuracion, token);
				}else{
					hay_errores = true;
				}
			}else{
				printf("Debe ingresar el nombre de un archivo .txt para guardar la configuracion.\n");
				hay_errores = true;
			}
		}else if(strcmp(token, GRABACION_CLAVE) == 0){
			token = strtok(NULL, SEPARADOR);
			if(token != NULL){
				if(es_dat_valido(token)){
					hay_que_grabar = true;
					strcpy(ruta_grabacion, token);
				}else{
					hay_errores = true;
				}
			}else{
				printf("Debe ingresar el nombre de un archivo .dat para guardar la grabación.\n");
				hay_errores = true;
			}
		}
		i++;
	}
    if(!hay_errores){
        if(hay_configuracion){
            printf("Se obtendrá la config de: %s.\n", ruta_configuracion);
        }else{
            strcpy(ruta_configuracion, POR_DEFECTO_STRING);
        }
        if(hay_que_grabar){
            printf("Se grabará la partida en: %s.\n", ruta_grabacion);
        }else{
            strcpy(ruta_grabacion, POR_DEFECTO_STRING);
        }
        if(hay_configuracion || hay_que_grabar){
            detener_el_tiempo(2);
        }
    }
    return !hay_errores;
}