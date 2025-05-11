#include <stdio.h>
#include <stdlib.h>
#include "pack_estadistico.h"
#include "graficas.h"
#include "inicio_sesion.h"
#include "mostrar_tabla.h"


  
int main() {
	
	inicio_sesion();
    
	int opcion;
	
    do {
        
		printf("\n           PAGINA PRINCIPAL           \n");
        printf("1. Pack Estadistico\n");
        printf("2. Graficas de Niveles\n");
        printf("3. Mostrar tablas de valores\n");
		printf("4. Cerrar sesion\n");
        printf("Selecciona una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
        printf("Entrada invalida. Intente de nuevo.\n");
        while (getchar() != '\n');  // Limpiar buffer
        continue;
    }

        switch (opcion) {
            case 1:
                pack_estadistico();
                system ("cls");
                break;
            case 2:
                graficas_niveles();
                break;
            case 3:
			    mostrar_tabla();
				break;
			case 4:
                system ("cls");
				printf("Sesion cerrada. Gracias por usar el programa.\n");
                exit(0);
                break;
            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 4);
    
    return 0;


}
