//
// Created by Álvaro on 12/05/2023.
//

#ifndef AGENDAJUGADORESFICHEROS_FUNCIONES_H
#define AGENDAJUGADORESFICHEROS_FUNCIONES_H

#define MAX_CHAR 255

typedef enum posiciones{
    DELANTERO, MEDIOCENTRO, DEFENSA, PORTERO
}tPosicion;

typedef struct agendaJugadores{
    char nombre[MAX_CHAR];
    char apellidos[MAX_CHAR];
    char equipo[MAX_CHAR];
    int dorsal;
    int anyoNacimiento;
} tJugador;


int menu();
void leerAgenda();
void nuevaPersona();
void borrarJugador();
void exportarFichero();
void importarFichero();
void importarFichero_2();

#endif //AGENDAJUGADORESFICHEROS_FUNCIONES_H
