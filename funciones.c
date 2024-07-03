#include <stdio.h>
#include <string.h>
#include "funciones.h"

void leerClientes(char clientes[][2][40]) {
    FILE *file = fopen("clientes.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < 5; i++) {
            fscanf(file, "%s %s", clientes[i][0], clientes[i][1]);
        }
        fclose(file);
    }
}

void guardarClientes(char clientes[][2][40]) {
    FILE *file = fopen("clientes.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < 5; i++) {
            fprintf(file, "%s %s\n", clientes[i][0], clientes[i][1]);
        }
        fclose(file);
    }
}

void leerReservas(int reserva[][4]) {
    FILE *file = fopen("reservas.txt", "r");
    if (file != NULL) {
        for (int i = 0; i < 10; i++) {
            fscanf(file, "%d %d %d %d", &reserva[i][0], &reserva[i][1], &reserva[i][2], &reserva[i][3]);
        }
        fclose(file);
    }
}

void guardarReservas(int reserva[][4]) {
    FILE *file = fopen("reservas.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < 10; i++) {
            fprintf(file, "%d %d %d %d\n", reserva[i][0], reserva[i][1], reserva[i][2], reserva[i][3]);
        }
        fclose(file);
    }
}

void ingresarCliente(char clientes[][2][40]) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(clientes[i][0], "") == 0) {
            printf("Ingrese nombre del nuevo cliente: ");
            fgets(clientes[i][0], 40, stdin);
            clientes[i][0][strcspn(clientes[i][0], "\n")] = '\0';  

            printf("Ingrese cedula del nuevo cliente: ");
            fgets(clientes[i][1], 40, stdin);
            clientes[i][1][strcspn(clientes[i][1], "\n")] = '\0';  

            guardarClientes(clientes);
            break;
        }
    }
    imprimirClientes(clientes);
}

void imprimirClientes(char clientes[][2][40]) {
    for (int i = 0; i < 5; i++) {
        printf("%s\t\t%s\n", clientes[i][0], clientes[i][1]);
    }
}

void listarPeliculas(char peliculas[][4][40]) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(peliculas[i][0], "") != 0) {
            printf("ID: %s, Titulo: %s, Hora: %s, Genero: %s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
        }
    }
}

void buscarporNombre(char peliculas[][4][40]) {
    char nombre[40];
    printf("Ingrese el nombre de la pelicula: ");
    fgets(nombre, 40, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';  

    for (int i = 0; i < 10; i++) {
        if (strcmp(peliculas[i][1], nombre) == 0) {
            printf("Pelicula encontrada: ID: %s, Titulo: %s, Hora: %s, Genero: %s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            return;
        }
    }
    printf("Pelicula no encontrada.\n");
}

void buscarporGenero(char peliculas[][4][40]) {
    char genero[40];
    printf("Ingrese el genero de la pelicula: ");
    fgets(genero, 40, stdin);
    genero[strcspn(genero, "\n")] = '\0';  

    for (int i = 0; i < 10; i++) {
        if (strcmp(peliculas[i][3], genero) == 0) {
            printf("Pelicula encontrada: ID: %s, Titulo: %s, Hora: %s, Genero: %s\n", peliculas[i][0], peliculas[i][1], peliculas[i][2], peliculas[i][3]);
            return;
        }
    }
    printf("Pelicula no encontrada.\n");
}

void comprarTicket(char peliculas[][4][40], double precio[], char clientes[][2][40], int reserva[][4]) {
    int idPelicula, tipoTicket, clienteIndex, cantidadEntradas;
    double totalPrecio;

    listarPeliculas(peliculas);
    printf("Ingrese el ID de la pelicula: ");
    scanf("%d", &idPelicula);
    getchar(); 

    if (idPelicula < 1 || idPelicula > 10 || strcmp(peliculas[idPelicula - 1][0], "") == 0) {
        printf("ID de pelicula no valido.\n");
        return;
    }

    printf("Tipos de ticket:\n");
    printf("0: General ($7.00)\n");
    printf("1: Niño ($3.50)\n");
    printf("2: Mayor de 60 ($3.00)\n");
    printf("Ingrese el tipo de ticket: ");
    scanf("%d", &tipoTicket);
    getchar(); 

    if (tipoTicket < 0 || tipoTicket > 2) {
        printf("Tipo de ticket no valido.\n");
        return;
    }

    printf("Ingrese la cantidad de entradas: ");
    scanf("%d", &cantidadEntradas);
    getchar(); 

    if (cantidadEntradas < 1) {
        printf("Cantidad de entradas no valida.\n");
        return;
    }

    imprimirClientes(clientes);
    printf("Ingrese el indice del cliente (1-5): ");
    scanf("%d", &clienteIndex);
    getchar();

    if (clienteIndex < 1 || clienteIndex > 5 || strcmp(clientes[clienteIndex - 1][0], "") == 0) {
        printf("Indice de cliente no valido.\n");
        return;
    }

    totalPrecio = precio[tipoTicket] * cantidadEntradas;

    for (int i = 0; i < 10; i++) {
        if (reserva[i][0] == -1) {
            reserva[i][0] = idPelicula - 1;
            reserva[i][1] = clienteIndex - 1;
            reserva[i][2] = tipoTicket;
            reserva[i][3] = cantidadEntradas;
            printf("Ticket(s) comprado(s) exitosamente!\n");
            printf("Total a pagar: $%.2f\n", totalPrecio);
            guardarReservas(reserva);
            return;
        }
    }

    printf("No hay espacio para más reservas.\n");
}

void verCompras(char peliculas[][4][40], double precio[], char clientes[][2][40], int reserva[][4]) {
    printf("Listado de compras:\n");
    for (int i = 0; i < 10; i++) {
        if (reserva[i][0] != -1) {
            int idPelicula = reserva[i][0];
            int clienteIndex = reserva[i][1];
            int tipoTicket = reserva[i][2];
            int cantidadEntradas = reserva[i][3];
            double totalPrecio = precio[tipoTicket] * cantidadEntradas;
            printf("Cliente: %s, Pelicula: %s, Hora: %s, Genero: %s, Tipo de ticket: %s, Cantidad: %d, Precio total: $%.2f\n",
                   clientes[clienteIndex][0],
                   peliculas[idPelicula][1],
                   peliculas[idPelicula][2],
                   peliculas[idPelicula][3],
                   tipoTicket == 0 ? "General" : (tipoTicket == 1 ? "Niño" : "Mayor de 60"),
                   cantidadEntradas,
                   totalPrecio);
        }
    }
}