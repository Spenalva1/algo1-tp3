#include "comandos.h"
#include "juego.h"
#include "utiles.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define RANKING "ranking"
#define CAMINO "crear_camino"
#define CONFIGURACION "crear_configuracion"
#define CONFIGURACION_CLAVE "config"
#define GRABACION_CLAVE "grabacion"
#define REPE "poneme_la_repe"
#define JUGAR "jugar"
#define TXT ".txt"
#define MAX_RUTA 30
#define MAX_COMANDOS 4
#define MIN_COMANDOS 4
#define SEPARADOR "="
#define POR_DEFECTO "-1"

/*
*
*/
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

int main(int argc, char *argv[]){
    if(cantidad_parametros_valida(argc)){
        bool comando_valido = false;
        if(strcmp(RANKING, argv[1]) == 0){
            printf("MOSTRAR RANKING\n");
            comando_valido = true;
        }else if(strcmp(CAMINO, argv[1]) == 0){
            if(argc > 2){
                if(es_txt_valido(argv[2])){
                    crear_camino(argv[2]);
                }
            }else{
                printf("Debe ingresar el nombre de archivo para guardar el camino.\n");
            }
            comando_valido = true;
        }else if(strcmp(CONFIGURACION, argv[1]) == 0){
            if(argc > 2){
                if(es_txt_valido(argv[2])){
                    crear_configuracion(argv[2]);
                }
            }else{
                printf("Debe ingresar el nombre de archivo para guardar la configuración.\n");
            }
            comando_valido = true;
        }else if(strcmp(REPE, argv[1]) == 0){
            printf("REPE\n");
            comando_valido = true;
        }else if(strcmp(JUGAR, argv[1]) == 0){
            int i = 2;
            bool hay_que_grabar = false;
            bool hay_configuracion = false;
            bool hay_errores = false;
            char ruta_grabacion[MAX_RUTA];
            char ruta_configuracion[MAX_RUTA];
            char* token;
            while(i <= MAX_COMANDOS && i < argc){
                token = strtok(argv[i], SEPARADOR);
                if(strcmp(token, CONFIGURACION_CLAVE) == 0){
                    token = strtok(NULL, SEPARADOR);
                    if(existe_archivo(token)){
                        hay_configuracion = true;
                        strcpy(ruta_configuracion, token);
                    }else{
                        hay_errores = true;
                    }
                }
                if(strcmp(token, GRABACION_CLAVE) == 0){
                    token = strtok(NULL, SEPARADOR);
                    if(existe_archivo(token)){
                        hay_que_grabar = true;
                        strcpy(ruta_grabacion, token);
                    }else{
                        hay_errores = true;
                    }
                }
                i++;
            }
            if(!hay_errores){
                if(hay_configuracion){
                    printf("Se obtendra la config de: %s.\n", ruta_configuracion);
                }else{
                    strcpy(ruta_configuracion, POR_DEFECTO);
                }
                if(hay_que_grabar){
                    printf("Se grabará la partida en: %s.\n", ruta_grabacion);
                }else{
                    strcpy(ruta_grabacion, POR_DEFECTO);
                }
                detener_el_tiempo(3);
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