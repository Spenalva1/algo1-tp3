#include "juego.h"
#include "comandos.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define RANKING "ranking"
#define CAMINO "crear_camino"
#define CONFIGURACION "crear_configuracion"
#define REPE "poneme_la_repe"
#define JUGAR "jugar"
#define TXT ".txt"
#define MAX_RUTA 30

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

int main(int argc, char *argv[]){
    if(argc > 1){
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
            printf("JUGAR\n");
            comando_valido = true;
        }
        if(!comando_valido){
            printf("No se ingreso un comando valido!\n");
        }
    }else{
        printf("mal\n");
    }
    return 0;
}