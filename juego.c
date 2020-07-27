#include "comandos.h"
#include "defendiendo_torres.h"
#include "animos.h"
#include "utiles.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define COLUMNAS_NIVEL1 15
#define FILAS_NIVEL1 15
#define COLUMNAS_NIVEL2 15
#define FILAS_NIVEL2 15
#define COLUMNAS_NIVEL3 20
#define FILAS_NIVEL3 20
#define COLUMNAS_NIVEL4 20
#define FILAS_NIVEL4 20
#define ELFOS 'L'
#define ENANOS 'G'
#define ORCOS 'O'
#define ENANOS_ATAQUE 60
#define ENANOS_ATAQUE_LETAL 100
#define ELFOS_ATAQUE 30
#define ELFOS_ATAQUE_LETAL 70
#define ORCOS_NIVEL_1 100
#define ORCOS_NIVEL_2 200
#define ORCOS_NIVEL_3 300
#define ORCOS_NIVEL_4 500
#define JUEGO_PERDIDO -1
#define JUEGO_JUGANDO 0
#define NIVEL_JUGANDO 0
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL1 25
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL2 50
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL3 50
#define FRECUENCIA_DEFENSOR_EXTRA_NIVEL4 50
#define SI 'S'
#define NO 'N'
#define POR_DEFECTO -1
#define POR_DEFECTO_STRING "-1"
#define YA_ASIGNADO_CHAR 'Y'
#define YA_ASIGNADO -1
#define COMANDO_RANKING "ranking"
#define COMANDO_CONFIGURACION "crear_configuracion"
#define COMANDO_CAMINO "crear_camino"
#define COMANDO_REPE "poneme_la_repe"
#define COMANDO_JUGAR "jugar"

/*
* Inicializara un nivel, cargando sus caminos, defensores y enemigos.
* nivel_numero debera ser un entero entre 1 y 4 (inlcusive ambos).
*/
void inicializar_nivel(nivel_t* nivel, int nivel_numero, caminos_t caminos);

/*
* Creara y ubicará los defensores iniciales segun el nivel actual de juego.
* Juego deberá estar ya iniciaizado.
*/
void defensores_iniciales(juego_t* juego, configuracion_t configuracion);

/*
* Se desarrollará el nivel indicado por nivel_numero (numero entero entre 1 y 4 ambos inclusive) del juego
* hasta que todos los orcos sean eliminados o una de las torres sea destruida.
* Juego deberá estar ya iniciaizado
*/
void jugar_nivel(juego_t* juego, int nivel_numero, caminos_t caminos, configuracion_t configuracion, FILE* archivo);

/*
* Agregará la cantidad indicada por tope de defensores del tipo indicado por "tipo" en el tablero del nivel actual de juego.
* Juego deberá estar ya iniciaizado
* tipo debe ser "G" o "L".
* tope debe ser positivo.
*/
void agregar_varios_defensores(juego_t* juego, char tipo, int tope);

/*
* Devuelve variable del tipo coordenada_t con informacón obtenida del usuario
* tipo debe ser "G" o "L"
*/
coordenada_t pedir_coordenadas_defensor(char tipo);

/*
* numero_nivel: numero entero entre 1 y 4 ambos inclusive
* devuelve TRUE: si coordenada esta dentro de los límites del tablero perteneciente al tablero del nivel indicado por numero_nivel.
* devuelve FALSE: si coordenada NO esta dentro de los límites del tablero perteneciente al tablero del nivel indicado por numero_nivel.
*/
bool coordenada_valida(coordenada_t coordenada, int numero_nivel);

/*
* Agrega un defensor (indicado por tipo) al nivel actual de juego, actualizando la resistensia de las torres y la cantidad de defensores extras restantes.
* tipo debe ser "G" o "L".
* Juego deberá estar ya iniciaizado.
*/
void agregar_defensor_extra(juego_t* juego, char tipo, configuracion_t configuracion);

/*
* Dependiendo del nivel y de las condiciones actuales de juego, agregará, en caso de que el jugador lo desee, un defensor extra al nivel actual del juego.
* Juego deberá estar ya iniciaizado.
*/
void defensor_extra(juego_t* juego, configuracion_t configuracion);

/*
* Pregunta al usuario si quiere agregar un defensor del tipo "tipo" al tablero del nivel actual.
* Devuelve TRUE en caso de que SÍ lo desee.
* Devuelve FALSE en caso de que NO lo desee.
* tipo debe ser "G" o "L".
*/
bool quiere_defensor_extra(char tipo, configuracion_t configuracion);

/*
* Imprimirá en pantalla un cartel indicandole al usuario cómo termino la partida
* Si estado es -1 le indicará que perdió la partida.
* Si estado es distinto de -1 le indicará que ganó la partida.
*/
void mostrar_resultado(int estado, int puntaje);

/*
*
*/
void jugar(char ruta_configuracion[MAX_RUTA], char ruta_grabacion[MAX_RUTA]);

int main(int argc, char* argv[]){
    if(cantidad_parametros_valida(argc)){
        bool comando_valido = false;
        if(strcmp(COMANDO_RANKING, argv[1]) == 0){
			comando_ranking(argc, argv);
            comando_valido = true;
        }else if(strcmp(COMANDO_CAMINO, argv[1]) == 0){
			comando_crear_camino(argc, argv);
            comando_valido = true;
        }else if(strcmp(COMANDO_CONFIGURACION, argv[1]) == 0){
			comando_crear_configuracion(argc, argv);
            comando_valido = true;
        }else if(strcmp(COMANDO_REPE, argv[1]) == 0){
			comando_poneme_la_repe(argc, argv);
            comando_valido = true;
        }else if(strcmp(COMANDO_JUGAR, argv[1]) == 0){
			char ruta_configuracion[MAX_RUTA];
			char ruta_grabacion[MAX_RUTA];
			if(comando_jugar(argc, argv, ruta_configuracion, ruta_grabacion)){
    			jugar(ruta_configuracion, ruta_grabacion);
			}
            comando_valido = true;
        }
        if(!comando_valido){
            printf("No se ingresó un comando valido!\n");
        }
    }
    return 0;
}

void jugar(char ruta_configuracion[MAX_RUTA], char ruta_grabacion[MAX_RUTA]){
	configuracion_t configuracion;
    juego_t juego;
	inicializar_configuracion(&configuracion);
	if(strcmp(ruta_configuracion, POR_DEFECTO_STRING) != 0){
		cargar_configuracion_de_archivo(ruta_configuracion, &configuracion);
	}else{
		configuracion.enanos_fallo = POR_DEFECTO;
	}
	asignar_valores_por_defecto(&configuracion);
	if(configuracion.enanos_fallo == POR_DEFECTO){
		int viento, humedad;
		char animo_legolas, animo_gimli;
		animos(&viento, &humedad , &animo_legolas , &animo_gimli);
    	inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli, configuracion);
	}else{
		inicializar_juego(&juego, YA_ASIGNADO, YA_ASIGNADO, YA_ASIGNADO_CHAR, YA_ASIGNADO_CHAR, configuracion);
	}

	caminos_t caminos;
	inicializar_caminos(&caminos, configuracion.caminos);

	srand ((unsigned)time(NULL));

	FILE* archivo;
	if(strcmp(ruta_grabacion, POR_DEFECTO_STRING) != 0){
		archivo = fopen(ruta_grabacion, "w");
	}

	int orcos_muertos[4];
    int i = 0;
    while(estado_juego(juego) == JUEGO_JUGANDO){
        i++;
        jugar_nivel(&juego, i, caminos, configuracion, archivo);
		orcos_muertos[i-1] = orcos_muertos_en_nivel(juego.nivel);
    }

	int puntaje = calcular_puntaje(juego.nivel_actual, configuracion, orcos_muertos);
	escribir_puntaje_en_ranking(puntaje, ruta_configuracion);
    mostrar_resultado(estado_juego(juego), puntaje);

	if(strcmp(ruta_grabacion, POR_DEFECTO_STRING) != 0){
		fclose(archivo);
	}
}

void mostrar_resultado(int estado, int puntaje){
    if(estado == JUEGO_PERDIDO){
        printf("*****************************************\n");
        printf("*****************************************\n");
        printf("**                                     **\n");
        printf("**            ¡HAS PERDIDO!            **\n");
        printf("**         SUERTE EN LA PROXIMA        **\n");
        printf("**                                     **\n");
        printf("*****************************************\n");
        printf("*****************************************\n");
    }else{
        printf("*****************************************\n");
        printf("*****************************************\n");
        printf("**                                     **\n");
        printf("**            ¡HAS GANADO!             **\n");
        printf("**          GRACIAS POR JUGAR          **\n");
        printf("**                                     **\n");
        printf("*****************************************\n");
        printf("*****************************************\n");
    }
    printf("PUNTAJE: %d\n", puntaje);
}

bool coordenada_valida(coordenada_t coordenada, int numero_nivel){
	switch (numero_nivel){
		case 1:
			return (coordenada.fil < FILAS_NIVEL1 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL1 && coordenada.col >= 0);
			break;
		case 2:
			return (coordenada.fil < FILAS_NIVEL2 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL2 && coordenada.col >= 0);
			break;
		case 3:
			return (coordenada.fil < FILAS_NIVEL3 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL3 && coordenada.col >= 0);
			break;
		case 4:
			return (coordenada.fil < FILAS_NIVEL4 && coordenada.fil >= 0) && (coordenada.col < COLUMNAS_NIVEL4 && coordenada.col >= 0);
			break;
		default:
			break;
	}
    return false;
}

coordenada_t pedir_coordenadas_defensor(char tipo){
    coordenada_t coordenada;
    if(tipo == ENANOS){
        printf("Coordenadas para un enano (F C): ");
    }else{
        printf("Coordenadas para un elfo (F C): ");
    }
    scanf("%d %d", &coordenada.fil, &coordenada.col);
    return coordenada;
}

void agregar_varios_defensores(juego_t* juego, char tipo, int tope){
    coordenada_t posicion;
    for(int i = 0; i < tope; i++){
        mostrar_juego(*juego);
        posicion = pedir_coordenadas_defensor(tipo);
        while(agregar_defensor(&(juego->nivel), posicion, tipo) == -1 || !coordenada_valida(posicion, juego->nivel_actual)){
            printf("Recuerde que debe ingresar una posicion que se encuentre dentro de los limites del tablero, y que no coincida con ningun camino ni defensor existente.\n");
            posicion = pedir_coordenadas_defensor(tipo);
        }
    }

}

void defensores_iniciales(juego_t* juego, configuracion_t configuracion){
	juego->nivel.tope_defensores = 0;
    switch (juego->nivel_actual){
        case 1:
            agregar_varios_defensores(juego, ENANOS, configuracion.enanos_nivel_1);
            agregar_varios_defensores(juego, ELFOS, configuracion.elfos_nivel_1);
            break;
        
        case 2:
            agregar_varios_defensores(juego, ENANOS, configuracion.enanos_nivel_2);
            agregar_varios_defensores(juego, ELFOS, configuracion.elfos_nivel_2);
            break;
        
        case 3:
            agregar_varios_defensores(juego, ENANOS, configuracion.enanos_nivel_3);
            agregar_varios_defensores(juego, ELFOS, configuracion.elfos_nivel_3);
            break;
        
        case 4:
            agregar_varios_defensores(juego, ENANOS, configuracion.enanos_nivel_4);
            agregar_varios_defensores(juego, ELFOS, configuracion.elfos_nivel_4);
            break;
        
        default:
            break;
    }
}

void inicializar_nivel(nivel_t* nivel, int nivel_numero, caminos_t caminos){
	nivel->tope_enemigos = 0;

	switch (nivel_numero){
	case 1:
		copiar_camino(nivel->camino_1, &(nivel->tope_camino_1), caminos.camino_1_nivel_1, caminos.tope_camino_1_nivel_1);
		copiar_camino(nivel->camino_2, &(nivel->tope_camino_2), caminos.camino_2_nivel_1, caminos.tope_camino_2_nivel_1);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_1;
		break;

	case 2:
		copiar_camino(nivel->camino_1, &(nivel->tope_camino_1), caminos.camino_1_nivel_2, caminos.tope_camino_1_nivel_2);
		copiar_camino(nivel->camino_2, &(nivel->tope_camino_2), caminos.camino_2_nivel_2, caminos.tope_camino_2_nivel_2);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_2;
		break;

	case 3:
		copiar_camino(nivel->camino_1, &(nivel->tope_camino_1), caminos.camino_1_nivel_3, caminos.tope_camino_1_nivel_3);
		copiar_camino(nivel->camino_2, &(nivel->tope_camino_2), caminos.camino_2_nivel_3, caminos.tope_camino_2_nivel_3);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_3;
		break;
		
	case 4:
		copiar_camino(nivel->camino_1, &(nivel->tope_camino_1), caminos.camino_1_nivel_4, caminos.tope_camino_1_nivel_4);
		copiar_camino(nivel->camino_2, &(nivel->tope_camino_2), caminos.camino_2_nivel_4, caminos.tope_camino_2_nivel_4);

        nivel->max_enemigos_nivel = ORCOS_NIVEL_4;
		break;

	default:
		break;
	}
}

void jugar_nivel(juego_t* juego, int nivel_numero, caminos_t caminos, configuracion_t configuracion, FILE* archivo){
    bool ultimo_extra_preguntado = false;
    juego->nivel_actual = nivel_numero;
    inicializar_nivel(&(juego->nivel), nivel_numero, caminos);
    defensores_iniciales(juego, configuracion);

    mostrar_juego(*juego);
    while(estado_nivel(juego->nivel) == NIVEL_JUGANDO && estado_juego(*juego) != JUEGO_PERDIDO){
		

        detener_el_tiempo(configuracion.velocidad_juego);
        jugar_turno(juego);
        mostrar_juego(*juego);
        if(juego->nivel.tope_enemigos > 0 && juego->nivel.tope_enemigos <= juego->nivel.max_enemigos_nivel && !ultimo_extra_preguntado)
		    defensor_extra(juego, configuracion);
        if(juego->nivel.tope_enemigos == juego->nivel.max_enemigos_nivel)
            ultimo_extra_preguntado = true;

		if(archivo != NULL){
			fwrite(juego, sizeof(juego_t), 1, archivo);
		}
    }
}

void agregar_defensor_extra(juego_t* juego, char tipo, configuracion_t configuracion){
	coordenada_t posicion;
	posicion = pedir_coordenadas_defensor(tipo);
	while(agregar_defensor(&(juego->nivel), posicion, tipo) == -1 || !coordenada_valida(posicion, juego->nivel_actual)){
		printf("Recuerde que debe ingresar una posicion que se encuentre dentro de los limites del tablero, y que no coincida con ningun camino ni defensor existente.\n");
        posicion = pedir_coordenadas_defensor(tipo);
	}
	if(tipo == ENANOS){
		juego->torres.resistencia_torre_1 -= configuracion.enanos_coste_torre_1;
		juego->torres.resistencia_torre_2 -= configuracion.enanos_coste_torre_2;
		(juego->torres.enanos_extra)--;
	}else if(tipo == ELFOS){
		juego->torres.resistencia_torre_1 -= configuracion.elfos_coste_torre_1;
		juego->torres.resistencia_torre_2 -= configuracion.elfos_coste_torre_2;
		(juego->torres.elfos_extra)--;
	}
}



void defensor_extra(juego_t* juego, configuracion_t configuracion){
    bool agrego_enano = false;
	switch (juego->nivel_actual){
		case 1:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL1 == 0 && juego->torres.resistencia_torre_2 > configuracion.enanos_coste_torre_2 && juego->torres.resistencia_torre_1 > configuracion.enanos_coste_torre_1 && juego->torres.enanos_extra > 0){
				if(quiere_defensor_extra(ENANOS, configuracion)){
					agregar_defensor_extra(juego, ENANOS, configuracion);
				}
			}
			break;
		case 2:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL2 == 0 && juego->torres.resistencia_torre_1 > configuracion.elfos_coste_torre_1 && juego->torres.resistencia_torre_2 > configuracion.elfos_coste_torre_2 && juego->torres.elfos_extra > 0){
				if(quiere_defensor_extra(ELFOS, configuracion)){
					agregar_defensor_extra(juego, ELFOS, configuracion);
				}
			}
			break;
		case 3:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL3 == 0 && juego->torres.resistencia_torre_2 > configuracion.enanos_coste_torre_2 && juego->torres.resistencia_torre_1 > configuracion.enanos_coste_torre_1 && juego->torres.enanos_extra > 0){
				if(quiere_defensor_extra(ENANOS, configuracion)){
					agregar_defensor_extra(juego, ENANOS, configuracion);
                    agrego_enano = true;
                }
			}
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL3 == 0 && juego->torres.resistencia_torre_1 > configuracion.elfos_coste_torre_1 && juego->torres.resistencia_torre_2 > configuracion.elfos_coste_torre_2 && juego->torres.elfos_extra > 0 && !agrego_enano){
				if(quiere_defensor_extra(ELFOS, configuracion))
					agregar_defensor_extra(juego, ELFOS, configuracion);
			}
			break;
		case 4:
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL4 == 0 && juego->torres.resistencia_torre_2 > configuracion.enanos_coste_torre_2 && juego->torres.resistencia_torre_1 > configuracion.enanos_coste_torre_1 && juego->torres.enanos_extra > 0){
				if(quiere_defensor_extra(ENANOS, configuracion)){
					agregar_defensor_extra(juego, ENANOS, configuracion);
                    agrego_enano = true;
                }
			}
			if(juego->nivel.tope_enemigos % FRECUENCIA_DEFENSOR_EXTRA_NIVEL4 == 0 && juego->torres.resistencia_torre_1 > configuracion.elfos_coste_torre_1 && juego->torres.resistencia_torre_2 > configuracion.elfos_coste_torre_2 && juego->torres.elfos_extra > 0 && !agrego_enano){
				if(quiere_defensor_extra(ELFOS, configuracion))
					agregar_defensor_extra(juego, ELFOS, configuracion);
			}
			break;
		
		default:
			break;
	}
}

bool quiere_defensor_extra(char tipo, configuracion_t configuracion){
	char respuesta;
    if(tipo == ENANOS){
        printf("Desea agregar un enano extra? le costará %d de resistencia la torre 1 y %d a la torre 2 (S | N): ", configuracion.enanos_coste_torre_1, configuracion.enanos_coste_torre_2);
    }else if((tipo == ELFOS)){
        printf("Desea agregar un elfo extra? le costará %d de resistencia la torre 1 y %d a la torre 2 (S | N): ", configuracion.elfos_coste_torre_1, configuracion.elfos_coste_torre_2);
    }
	scanf(" %c", &respuesta);
	while(respuesta != SI && respuesta != NO){
        printf("Debe ingresar el caracter 'S' o 'N': ");
		scanf(" %c", &respuesta);
	}
    return respuesta == SI;
}