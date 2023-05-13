#include <stdio.h>
#include "funciones.h"


int main() {
    int opcion;
    do
    {
        opcion = menu();
        switch (opcion)
        {
            case 1:
                printf("Ha selecionado la opcion de ver la agenda\n");
                leerAgenda();
                break;
            case 2:
                printf("Ha selecionado la opcion de añyadir un nuevo jugador\n");
                nuevaPersona();
                //nuevoJugador(agenda, numJugadores);
                //numJugadores++;
                /*
                if (numJugadores==tamanyoLista){
                    aumentarLista(agenda, numJugadores);
                    tamanyoLista+=5;
                }
                 */
                break;
            case 3:
                printf("Ha selecionado la opcion de eliminar un jugador\n");
                //borrarPersona();
                borrarJugador();
                //borrarJugador(agenda, numJugadores);
                //numJugadores--;
                break;
            case 4:
                printf("Ha selecionado la opcion de importar conatactos desde un fichero de texto\n");
                importarFichero();
                //importarArchivos_2(agenda, &numJugadores);
                break;
            case 5:
                printf("Ha seleccionado la opcion de exportar una agenda a un fichero de texto\n");
                exportarFichero();
                //exportarFichero(agenda, numJugadores);
                break;
            case 0:
                printf("\t\t:::SALIENDO DEL PROGRAMA:::");
                break;
            default:
                printf("Su opcion es incorrecta\n\t\t:::REDIRIGIEDO AL MENU:::\n");
                break;
        }

    } while (opcion != 0);
    return 0;
}
