#include "comandos.h"
#include "defendiendo_torres.h"
#include "utiles.h"
#include "juego.h"
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
#define VELOCIDAD_MINIMA 0.5
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

typedef struct nivel_caminos {
    int numero_nivel;

	coordenada_t camino_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1;
	
	coordenada_t camino_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2;

    int tope_filas;
    int tope_columnas;
} nivel_caminos_t;


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
*
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
*
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

/*
*
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
*
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
*
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
*
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
*
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
*
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
*
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
        fprintf(archivo, "%d;%d\n", camino[i].fil, camino[i].col);
    }
}

/*
*
*/
void escribir_configuracion_en_archivo(char ruta[MAX_RUTA], configuracion_t configuracion){
    FILE* archivo = fopen(ruta, "w");
    fprintf(archivo, "%s=%d,%d\n", CLAVE_RESISTENCIA_TORRES, configuracion.resistencia_torre_1, configuracion.resistencia_torre_2);
    fprintf(archivo, "%s=%d,%d,%d,%d\n", CLAVE_ENANOS_INICIO, configuracion.enanos_nivel_1, configuracion.enanos_nivel_2, configuracion.enanos_nivel_3, configuracion.enanos_nivel_4);
    fprintf(archivo, "%s=%d,%d,%d,%d\n", CLAVE_ELFOS_INICIO, configuracion.elfos_nivel_1, configuracion.elfos_nivel_2, configuracion.elfos_nivel_3, configuracion.elfos_nivel_4);
    fprintf(archivo, "%s=%d, %d, %d\n", CLAVE_ENANOS_EXTRA, configuracion.enanos_extra, configuracion.enanos_coste_torre_1, configuracion.enanos_coste_torre_2);
    fprintf(archivo, "%s=%d, %d, %d\n", CLAVE_ELFOS_EXTRA, configuracion.elfos_extra, configuracion.elfos_coste_torre_1, configuracion.elfos_coste_torre_2);
    fprintf(archivo, "%s=%d, %d\n", CLAVE_ENANOS_ANIMO, configuracion.enanos_fallo, configuracion.enanos_critico);
    fprintf(archivo, "%s=%d, %d\n", CLAVE_ELFOS_ANIMO, configuracion.elfos_fallo, configuracion.elfos_critico);
    fprintf(archivo, "%s=%f\n", CLAVE_VELOCIDAD, configuracion.velocidad_juego);
    fprintf(archivo, "%s=%s\n", CLAVE_CAMINOS, configuracion.caminos);
    fclose(archivo);
}

/*
*
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
        //DESPUES DE ACA SE BORRA EL CAMINO, HABRIA QUE ESCRIBIRLO
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
*
*/
bool resistencia_torre_valida(int resistencia){
    return (((resistencia >= RESISTENCIA_TORRE_MINIMA) && (resistencia <= RESISTENCIA_TORRE_MAXIMA)) || (resistencia == POR_DEFECTO));
}

/*
*
*/
bool cantidad_defensores_valida(int defensores){
    return (((defensores >= DEFENSORES_MINIMOS) && (defensores <= DEFENSORES_MAXIMOS)) || (defensores == POR_DEFECTO));
}

/*
*
*/
bool cantidad_extra_valida(int extra){
    return (((extra >= EXTRAS_MINIMOS) && (extra <= EXTRAS_MAXIMOS)) || (extra == POR_DEFECTO));
}

/*
*
*/
bool coste_extra_valido(int extra){
    return (((extra >= COSTE_EXTRAS_MINIMO) && (extra <= COSTE_EXTRAS_MAXIMO)) || (extra == POR_DEFECTO));
}

/*
*
*/
bool porcentaje_valido(int porcentaje){
    return (((porcentaje >= PORCENTAJE_MINIMO) && (porcentaje <= PORCENTAJE_MAXIMO)) || (porcentaje == POR_DEFECTO));
}

/*
*
*/
bool velocidad_valida(float velocidad){
    return (((velocidad >= VELOCIDAD_MINIMA) && (velocidad <= VELOCIDAD_MAXIMA)) || (velocidad == POR_DEFECTO));
}

/*
*
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
        printf("Debe ingresar un número entre 50 y 10000 inclusive ambos: ");
        scanf("%d", &(configuracion.resistencia_torre_1));
    }

    printf("Resistencia torre 2: ");
    scanf("%d", &(configuracion.resistencia_torre_2));
    while(!resistencia_torre_valida(configuracion.resistencia_torre_2)){
        printf("Debe ingresar un número entre 50 y 10000 inclusive ambos: ");
        scanf("%d", &(configuracion.resistencia_torre_2));
    }

    printf("Enanos nivel 1: ");
    scanf("%d", &(configuracion.enanos_nivel_1));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_1)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_nivel_1));
    }

    printf("Enanos nivel 2: ");
    scanf("%d", &(configuracion.enanos_nivel_2));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_2)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_nivel_2));
    }

    printf("Enanos nivel 3: ");
    scanf("%d", &(configuracion.enanos_nivel_3));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_3)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_nivel_3));
    }

    printf("Enanos nivel 4: ");
    scanf("%d", &(configuracion.enanos_nivel_4));
    while(!cantidad_defensores_valida(configuracion.enanos_nivel_4)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_nivel_4));
    }

    printf("Elfos nivel 1: ");
    scanf("%d", &(configuracion.elfos_nivel_1));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_1)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_nivel_1));
    }

    printf("Elfos nivel 2: ");
    scanf("%d", &(configuracion.elfos_nivel_2));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_2)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_nivel_2));
    }

    printf("Elfos nivel 3: ");
    scanf("%d", &(configuracion.elfos_nivel_3));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_3)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_nivel_3));
    }

    printf("Elfos nivel 4: ");
    scanf("%d", &(configuracion.elfos_nivel_4));
    while(!cantidad_defensores_valida(configuracion.elfos_nivel_4)){
        printf("Debe ingresar un número entre 2 y 15 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_nivel_4));
    }

    printf("Enanos extra: ");
    scanf("%d", &(configuracion.enanos_extra));
    while(!cantidad_extra_valida(configuracion.enanos_extra)){
        printf("Debe ingresar un número entre 0 y 20 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_extra));
    }

    printf("Coste de enanos extra en torre 1: ");
    scanf("%d", &(configuracion.enanos_coste_torre_1));
    while(!coste_extra_valido(configuracion.enanos_coste_torre_1)){
        printf("Debe ingresar un número entre 0 y 150 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_coste_torre_1));
    }

    printf("Coste de enanos extra en torre 2: ");
    scanf("%d", &(configuracion.enanos_coste_torre_2));
    while(!coste_extra_valido(configuracion.enanos_coste_torre_2)){
        printf("Debe ingresar un número entre 0 y 150 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_coste_torre_2));
    }

    printf("Elfos extra: ");
    scanf("%d", &(configuracion.elfos_extra));
    while(!cantidad_extra_valida(configuracion.elfos_extra)){
        printf("Debe ingresar un número entre 0 y 20 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_extra));
    }

    printf("Coste de elfos extra en torre 1: ");
    scanf("%d", &(configuracion.elfos_coste_torre_1));
    while(!coste_extra_valido(configuracion.elfos_coste_torre_1)){
        printf("Debe ingresar un número entre 0 y 150 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_coste_torre_1));
    }

    printf("Coste de elfos extra en torre 2: ");
    scanf("%d", &(configuracion.elfos_coste_torre_2));
    while(!coste_extra_valido(configuracion.elfos_coste_torre_2)){
        printf("Debe ingresar un número entre 0 y 150 inclusive ambos: ");
        scanf("%d", &(configuracion.elfos_coste_torre_2));
    }

    printf("Fallo enanos: ");
    scanf("%d", &(configuracion.enanos_fallo));
    while(!porcentaje_valido(configuracion.enanos_fallo)){
        printf("Debe ingresar un número entre 1 y 99 inclusive ambos: ");
        scanf("%d", &(configuracion.enanos_fallo));
    }

    if(configuracion.enanos_fallo != POR_DEFECTO){
        printf("Las siguientes 3 preguntas no se podra ingresar el valor '%d'\n", POR_DEFECTO);

        printf("Critico enanos: ");
        scanf("%d", &(configuracion.enanos_critico));
        while(!porcentaje_valido(configuracion.enanos_critico) || configuracion.enanos_critico == POR_DEFECTO){
            printf("Debe ingresar un número entre 1 y 99 inclusive ambos: ");
            scanf("%d", &(configuracion.enanos_critico));
        }

        printf("Fallo elfos: ");
        scanf("%d", &(configuracion.elfos_fallo));
        while(!porcentaje_valido(configuracion.elfos_fallo) || configuracion.elfos_fallo == POR_DEFECTO){
            printf("Debe ingresar un número entre 1 y 99 inclusive ambos: ");
            scanf("%d", &(configuracion.elfos_fallo));
        }

        printf("Critico elfos: ");
        scanf("%d", &(configuracion.elfos_critico));
        while(!porcentaje_valido(configuracion.elfos_critico) || configuracion.elfos_critico == POR_DEFECTO){
            printf("Debe ingresar un número entre 1 y 99 inclusive ambos: ");
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
        printf("Debe ingresar un número entre 1 y 99 inclusive ambos: ");
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