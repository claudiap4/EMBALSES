#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "estadisticas.h"

#define MAX_ANYOS 10   // ajusta según cuántos años tengas en el archivo
#define MESES 12

//estas tres variables son para el inicio
#define MAX_CUENCAS 20
#define MAX_EMBALSES 50
#define MAX_NOMBRE 50

#define MAX_DATOS 1000

typedef struct {
    int ano;
    char nombre[50];
    float datos[12];
} DatosEmbalse;

// Prototipos de funciones
void mostrarGraficoEmbalse();
void estadisticasEmbalse();


int main() {
    int opcion;
    char respuesta;

    do {
        printf("====== MENU PRINCIPAL ======\n");
        printf("1. Mostrar grafico de un embalse\n");
        printf("2. Calcular estadisticas del nivel de agua de un embalse\n");
        printf("3. Mostrar tabla de un embalse \n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        system("cls");

        switch(opcion) {
            case 1:
                mostrarGraficoEmbalse();
                break;
            case 2:
                estadisticasEmbalse();
                break;
            case 3:
                printf("Gracias por usar el programa.\n");
                return 0;
            default:
                printf("Opcion invalida.\n");
        }

        printf("\nDesea volver al menu? (S/N): ");
        scanf(" %c", &respuesta);
        system("cls");

    } while (respuesta == 'S' || respuesta == 's');

    return 0;
}


