#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOPE_PANTANOS 4300
#define TOPE_FILAS 100
#define TOPE_COLUMNAS 20


	

void mostrar_tabla() {
    FILE *f = fopen("dataset.csv", "r");
    if (f==NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }

    char linea[TOPE_PANTANOS];
    char *columnas[TOPE_COLUMNAS];
    char datos[TOPE_FILAS][TOPE_PANTANOS];
    char embalse_buscado[50];
    int num_columnas = 0, num_filas = 0;

    if (fgets(linea, sizeof(linea), f)) {
        char *palabra = strtok(linea, ",\n");
        while (palabra) {
            columnas[num_columnas++] = strdup(palabra);
            palabra = strtok(NULL, ",\n");
        }
    }

    // Limpiar buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Introduce el nombre del embalse (exactamente como aparece): ");
    printf("Ejemplo: Jarrama");
    fgets(embalse_buscado, sizeof(embalse_buscado), stdin);
    embalse_buscado[strcspn(embalse_buscado, "\n")] = '\0'; 
    system("cls");

    while (fgets(linea, sizeof(linea), f)) {
        if (strstr(linea, embalse_buscado)) {
            strcpy(datos[num_filas++], linea);
        }
    }

    fclose(f);

    if (num_filas == 0) {
        printf("No se encontraron datos para el embalse '%s'.\n", embalse_buscado);
    } else {
        printf("\nEmbalse: %s\n", embalse_buscado);
        printf("-----------------------------------------------------\n");
        printf("%-10s", "Embalse");
        for (int i = 2; i < num_columnas; i++) {
            printf(" | %-6s", columnas[i]);
        }
        printf("\n---------------------------------------------------\n");

        for (int i = 0; i < num_filas; i++) {
            char *token = strtok(datos[i], ",\n");
            token = strtok(NULL, ",\n"); 
            printf("%-10s", token); 

            for (int j = 2; j < num_columnas; j++) {
                token = strtok(NULL, ",\n");
                printf(" | %-6s", token ? token : "0");
            }
            printf("\n");
        }
    }
}