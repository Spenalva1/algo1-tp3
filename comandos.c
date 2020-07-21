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
void crear_camino(char* nombre_archivo){
    nivel_caminos_t nivel_caminos;
    nivel_caminos.numero_nivel = 1;
    definir_limites(&nivel_caminos);
    nivel_caminos.tope_camino_1 = 0;
    nivel_caminos.tope_camino_2 = 0;
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
        (nivel_caminos.numero_nivel)++;
        nivel_caminos.tope_camino_1 = 0;
        nivel_caminos.tope_camino_2 = 0;
        definir_limites(&nivel_caminos);
    }
}