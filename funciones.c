//
// Created by Álvaro on 12/05/2023.
//

#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FICHERO_AUX "agenda.dat"
#define AUXILIAR "auxiliar.dat"

void vaciaPalabra(char *entrada){
    for ( int i = 0; i<MAX_CHAR; i++){
        entrada[i] = 0;
    }
}


int menu(){
    int opcion;

    printf("Menu de agenda\n");
    printf("--------------------------------------------------\n");
    printf("[1] Ver agenda\n[2] Anyadir jugado\n[3] Borrar jugador\n[4] Importar agenda a fichero de texto\n[5] Exportar agenda de fichero de texto\n");
    printf("--------------------------------------------------\n");

    printf("Introduze tu opcion:");
    fscanf(stdin, "%d", &opcion);
    return opcion;
}

void leerAgenda(){
    tJugador persona[1];
    int n =  1;
    FILE *f = fopen(FICHERO_AUX, "rb");
    if (f == NULL){
        perror("Error en apertura: ");
        exit(-1);
    }
    fread(persona, sizeof(tJugador), 1, f);
    while(!feof(f)){
        fprintf(stdout, "%i;%s;%s;%s;%i;%i\n", n, persona->nombre, persona->apellidos, persona->equipo, persona->dorsal, persona->anyoNacimiento);
        n++;
        fread(persona, sizeof(tJugador), 1, f);
    }
    fclose(f);
}

void nuevaPersona(){
    tJugador *persona;
    FILE *f = fopen(FICHERO_AUX, "ab");
    printf("Nombre:");
    fflush(stdin);
    gets(persona->nombre);
    printf("Apellidos:");
    gets(persona->apellidos);
    printf("Equipo:");
    fflush(stdin);
    gets(persona->equipo);
    printf("Dorsal:");
    fscanf(stdin, "%d", &persona->dorsal);
    printf("Anyo de nacimiento:");
    fscanf(stdin, "%d", &persona->anyoNacimiento);
    fwrite(persona, sizeof(tJugador), 1, f);
    fclose(f);
}


void borrarJugador(){
    int id;
    int contador = 1;
    tJugador persona[1];
    printf("Id del jugador: ");
    scanf("%d", &id);
    FILE *agenda = fopen(FICHERO_AUX, "rb");
    FILE *aux = fopen(AUXILIAR, "wb");
    fread(persona, sizeof(tJugador), 1, agenda);
    while (!feof(agenda)){
        if (contador!=id){
            fwrite(persona, sizeof (tJugador), 1, aux);
            fread(persona, sizeof(tJugador), 1, agenda);
            contador++;
        }else {
            contador++;
            fread(persona, sizeof(tJugador), 1, agenda);
        }
    }
    fclose(agenda), fclose(aux);
    agenda = fopen(FICHERO_AUX, "wb"), aux = fopen(AUXILIAR, "rb");
    fread(persona, sizeof(tJugador), 1, aux);
    while (!feof(aux)){
        fwrite(persona, sizeof (tJugador), 1, agenda);
        fread(persona, sizeof(tJugador), 1, aux);

    }
    fclose(agenda), fclose(aux);
}





void exportarFichero(){
    tJugador persona[1];
    int n;
    char fichero[MAX_CHAR], aux[MAX_CHAR];
    FILE *agenda = fopen(FICHERO_AUX, "rb");
    printf("Introduzca el nombre del fichero:");
    fflush(stdin);
    gets(fichero);
    if (fopen(fichero, "r") == NULL){
        n = 1;
        FILE *f = fopen(fichero, "w");
        fread(persona, sizeof(tJugador), 1, agenda);
        while(!feof(agenda)){
            fprintf(f, "%i;%s;%s;%s;%i;%i\n", n, persona->nombre, persona->apellidos, persona->equipo, persona->dorsal, persona->anyoNacimiento);
            n++;
            fread(persona, sizeof(tJugador), 1, agenda);
        }
        fclose(f);
    }else{
        printf("El archivo que ha introducido ya tiene contenido, quiere sobreescribir sobre el (s/n):");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "s") == 0 || strcmp(aux, "S") == 0){
            n = 1;
            FILE *f = fopen(fichero, "w");
            fread(persona, sizeof(tJugador), 1, agenda);
            while(!feof(agenda)){
                fprintf(f, "%i;%s;%s;%s;%i;%i\n", n, persona->nombre, persona->apellidos, persona->equipo, persona->dorsal, persona->anyoNacimiento);
                n++;
                fread(persona, sizeof(tJugador), 1, agenda);
            }
            fclose(f);
        }else{
            printf("\t\t:::PROCESO ABORTADO:::");
        }
    }
    fclose(agenda);
}

void importarFichero(){
    char aux[MAX_CHAR], fichero[MAX_CHAR];
    FILE *agenda = fopen(FICHERO_AUX, "rb");
    if (agenda != NULL){
        printf("Actualmente se encuentran datos en memoria, desea sobreescribirlos (s/n):");
        fflush(stdin);
        gets(aux);
        if (strcmp(aux, "s") == 0 || strcmp(aux, "S") == 0){
            fclose(agenda);
            agenda = fopen(FICHERO_AUX, "wb");
            printf("Nombre de su fichero:");
            gets(fichero);
            FILE *f = fopen(fichero, "r");
            while(!feof(f)){
                fgets(aux, MAX_CHAR, f);
                tJugador persona[1];
                char nombre[MAX_CHAR] = "", apellido[MAX_CHAR] = "", equipo[MAX_CHAR] = "", aux2[MAX_CHAR] = "";
                int n = 0, dorsal = 0, anyo = 0;
                char *p;
                p = aux;
                int i = 0, j = 0;
                while (*(p+i) != '\0'){
                    if (*(p+i) == ';'){
                        j = 0;
                        i++;
                        if (n == 0){
                            n = atoi(aux2);
                        }else{
                            if (strcmp(nombre, "") == 0){
                                strcpy(nombre, aux2);
                            }else{
                                if (strcmp(apellido, "") == 0){
                                    strcpy(apellido, aux2);
                                }else{
                                    if (strcmp(equipo, "") == 0){
                                        strcpy(equipo, aux2);
                                    }else{
                                        if (dorsal == 0){
                                            dorsal = atoi(aux2);
                                        }else{
                                            if (anyo == 0){
                                                anyo = atoi(aux2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        vaciaPalabra(aux2);
                    }else{
                        aux2[j] = p[i];
                        i++;
                        j++;

                    }
                }
                anyo = atoi(aux2);
                vaciaPalabra(aux2);
                strcpy(persona->nombre, nombre);
                strcpy(persona->apellidos, apellido);
                strcpy(persona->equipo, equipo);
                persona->dorsal = dorsal;
                persona->anyoNacimiento = anyo;
                fwrite(persona, sizeof(tJugador),1, agenda);
            }
            fclose(f);
        }else printf("\t\t:::ABORTANDO PROCESO:::");
    }else{
        fclose(agenda);
        agenda = fopen(FICHERO_AUX, "wb");
        printf("Nombre de su fichero:");
        gets(fichero);
        FILE *f = fopen(fichero, "r");
        while(!feof(f)){
            fgets(aux, MAX_CHAR, f);
            tJugador persona[1];
            char nombre[MAX_CHAR] = "", apellido[MAX_CHAR] = "", equipo[MAX_CHAR] = "", aux2[MAX_CHAR] = "";
            int n = 0, dorsal = 0, anyo = 0;
            char *p;
            p = aux;
            int i = 0, j = 0;
            while (*(p+i) != '\0'){
                if (*(p+i) == ';'){
                    j = 0;
                    i++;
                    if (n == 0){
                        n = atoi(aux2);
                    }else{
                        if (strcmp(nombre, "") == 0){
                            strcpy(nombre, aux2);
                        }else{
                            if (strcmp(apellido, "") == 0){
                                strcpy(apellido, aux2);
                            }else{
                                if (strcmp(equipo, "") == 0){
                                    strcpy(equipo, aux2);
                                }else{
                                    if (dorsal == 0){
                                        dorsal = atoi(aux2);
                                    }else{
                                        if (anyo == 0){
                                            anyo = atoi(aux2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    vaciaPalabra(aux2);
                }else{
                    aux2[j] = p[i];
                    i++;
                    j++;

                }
            }
            anyo = atoi(aux2);
            vaciaPalabra(aux2);
            strcpy(persona->nombre, nombre);
            strcpy(persona->apellidos, apellido);
            strcpy(persona->equipo, equipo);
            persona->dorsal = dorsal;
            persona->anyoNacimiento = anyo;
            fwrite(persona, sizeof(tJugador),1, agenda);
        }
        fclose(f);
    }
    fclose(agenda);
}

void importarFichero_2(){
    tJugador *persona;
    int num;
    char file[MAX_CHAR];
    printf("Nombre del fichero:");
    fflush(stdin);
    gets(file);
    FILE *f = fopen(file, "r");
    if (f ==  NULL){
        perror("Errorn en la aperura: ");
        exit(-1);
    }
    FILE *agenda = fopen(FICHERO_AUX, "wb");
    while(!feof(f)){
        fscanf(f, "%d[^;]", &num);
        fscanf(f, "%s[^;]", persona->nombre);
        fscanf(f, "%s[^;]", persona->apellidos);
        fscanf(f, "%s[^;]", persona->equipo);
        fscanf(f, "%d^;]", &persona->dorsal);
        fscanf(f, "%d[^;]", &persona->anyoNacimiento);
        fwrite(persona, sizeof(tJugador), 1, agenda);
    }
}