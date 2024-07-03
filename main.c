#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[]) {
    char peliculas[10][4][40] = {
        {"1", "Avatar", "10:20", "Fantasia"},
        {"2", "Intensamente 2", "12:00", "Infantil"},
        {"3", "Godzilla", "14:20", "Fantasia"},
        {"4", "Caballeros del Zodiaco", "15:35", "Animada"},
        {"5", "Actividad Paranormal 2", "16:20", "Terror"},
        {"6", "Duro de Matar", "10:00", "Accion"},
        {"7", "Kimetsu no yaiba", "16:00", "Animada"},
        {"8", "Rapunzel", "13:30", "Infantil"},
        {"9", "Interestelar", "18:55", "Fantasia"},
        {"10", "Sonrie", "20:00", "Terror"}
    };

    double precio[3] = {7, 3.5, 3};

    char clientes[5][2][40] = {
        {"", ""},
        {"Luis", "1234567887"},
        {"", ""},
        {"", ""},
        {"", ""}
    };

    int reserva[10][4] = {
        {0, 1, 2, 1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1}
    };

    
    leerClientes(clientes);
    leerReservas(reserva);

    int opcion1 = 0, opcion2 = 0, opcion3 = 0;

    do {
        printf("Escoja una opcion:\n");
        printf("1. Ingresar Cliente\n");
        printf("2. Ver Peliculas\n");
        printf("3. Buscar Pelicula\n");
        printf("4. Comprar Ticket\n");
        printf("5. Ver Compras\n>> ");
        scanf("%d", &opcion2);
        getchar(); 

        switch (opcion2) {
            case 1:
                ingresarCliente(clientes);
                break;
            case 2:
                listarPeliculas(peliculas);
                break;
            case 3:
                printf("1. Por nombre\n");
                printf("2. Por Genero\n>> ");
                scanf("%d", &opcion3);
                getchar(); 
                switch (opcion3) {
                    case 1:
                        buscarporNombre(peliculas);
                        break;
                    case 2:
                        buscarporGenero(peliculas);
                        break;
                    default:
                        printf("Opcion no valida.\n");
                        break;
                }
                break;
            case 4:
                comprarTicket(peliculas, precio, clientes, reserva);
                break;
            case 5:
                verCompras(peliculas, precio, clientes, reserva);
                break;
            default:
                printf("Opcion no valida.\n");
                break;
        }

        printf("Desea escoger una nueva opcion: 1.Si / 2.No\n>> ");
        scanf("%d", &opcion1);
        getchar(); 
    } while (opcion1 == 1);

    guardarClientes(clientes);
    guardarReservas(reserva);

    return 0;
}