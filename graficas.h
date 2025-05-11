#include <stdio.h> 
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>


#define MAX_ANYOS 10
#define MESES 12

#define MAX_CUENCAS 20
#define MAX_EMBALSES 50
#define MAX_NOMBRE 50




void graficas_niveles() {
    FILE *pf;
    char cuenca[50], embalse[50];   
    char cuencaArchivo[50], embalseArchivo[50], mes[20];
    float valores[MAX_ANYOS];
    char linea[1024];
    char entrada[20];
    char respuesta;
    int i,j;
    int num_cuencas=0;
    char cuencas[MAX_CUENCAS][MAX_NOMBRE];
    int anios[100], aniosArchivo[100];
    
    
    do {
    	
    	pf = fopen("dataset.csv", "r");
    if (pf == NULL) {
        printf("Error al abrir el fichero.\n");
        
    }
    
	
    
    fgets(linea,sizeof(linea),pf);
    
     while (fgets(linea, sizeof(linea), pf))  //lee todas las lineas del archivo
    {
        char cuenca[MAX_NOMBRE];
        sscanf(linea, "%[^,]", cuenca);  //solo lee hasta la primera coma,la cuenca

       
        int existe = 0;
        for (i = 0; i < num_cuencas; i++) //con esto compara la cuenca que ha leido con la de la siguiente line y si es la misma pasa sin guardar
        {
            if (strcmp(cuencas[i], cuenca) == 0)
            {
                existe = 1;
                break;
            }
        }
        if (!existe)
        {
            strcpy(cuencas[num_cuencas], cuenca);
            num_cuencas++;
        }
    }

    // Mostrar cuencas y pedir selección
    printf("Cuencas hidrograficas:\n\n");  //esto sirve para mostrar todas las cuencas que se han guardado en el vector
    for (i = 0; i < num_cuencas; i++)
    {
        printf("%d. %s\n", i + 1, cuencas[i]);
    }
    int opcion;
    printf("Seleccione una cuenca: ");    //esta parte ya es pedirle al usuario que seleccione una cuenca
    scanf("%d", &opcion);
    
    
	if (opcion < 1 || opcion > num_cuencas)
    {
		printf("Opcion no valida.\n");
		do 
		{
			printf("Introduce de nuevo la cuenca:\t");
			scanf("%d", &opcion);
			if (opcion < 1 || opcion > num_cuencas)
			{
				printf("Opcion no valida.\n");
			}
		}
		while (opcion < 1 || opcion > num_cuencas);
        
    }
    
    system("cls");

    
    char cuenca_seleccionada[MAX_NOMBRE];    //se guarda la cuenca seleccionada por el usuario
    strcpy(cuenca_seleccionada, cuencas[opcion - 1]);

    
    rewind(pf);
    fgets(linea, sizeof(linea), pf); // se vuelve a saltar la primera linea

    char embalses[MAX_EMBALSES][MAX_NOMBRE];
    int num_embalses = 0;

    while (fgets(linea, sizeof(linea), pf))  //igual que antes va leyendo todas las lineas del archivo
    {
        char cuenca[MAX_NOMBRE], embalse[MAX_NOMBRE];
        sscanf(linea, "%[^,],%[^,]", cuenca, embalse); //lee hasta a segunda coma

        if (strcmp(cuenca, cuenca_seleccionada) == 0)
        {
            
            int existe = 0;
            for (j = 0; j < num_embalses; j++)
            {
                if (strcmp(embalses[j], embalse) == 0)
                {
                    existe = 1;
                    break;
                }
            }
            if (!existe)
            {
                strcpy(embalses[num_embalses], embalse);
                num_embalses++;
            }
        }
    }

   
    printf("\nEmbalses de la cuenca %s:\n", cuenca_seleccionada);   //te muestra los embalses que se han guardado en la matriz
    for (j = 0; j < num_embalses; j++)
    {
        printf("%d. %s\n", j + 1, embalses[j]);
    }

    
    printf("Seleccione un embalse: ");   //seleccionas el embalse
    int embalse_opcion;
    scanf("%d", &embalse_opcion);
    
    char embalse_seleccionado[MAX_NOMBRE];
    strcpy(embalse_seleccionado, embalses[embalse_opcion - 1]);

    if (embalse_opcion < 1 || embalse_opcion > num_embalses)
    {
        printf("Opcion de embalse no valida.\n");
        do 
		{
			printf("Introduce de nuevo el embalse:\t");
			scanf("%d", &embalse_opcion);
			if (embalse_opcion < 1 || embalse_opcion > num_embalses)
			{
				printf("Opcion de embalse no valida.\n");
			}
			
		}
		while (embalse_opcion < 1 || embalse_opcion > num_embalses);
        
    }
    
    system("cls");
    
	
	int anyo_usuario, indice = -1;
	
	FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        printf("No se pudo abrir Gnuplot\n");
        
    }
    
    rewind(pf);  
    fgets(linea, sizeof(linea), pf);

    int anio_inicial = 2012;
    int num_anyos = 10;
    float valores_por_anio[MAX_ANYOS] = {0};

    while (fgets(linea, sizeof(linea), pf)) {
        char cuenca_temp[MAX_NOMBRE], embalse_temp[MAX_NOMBRE];
        float valores_temp[MAX_ANYOS];

    sscanf(linea, "%[^,],%[^,],%*[^,],%*[^,],%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
           cuenca_temp, embalse_temp,
           &valores_temp[0], &valores_temp[1], &valores_temp[2], &valores_temp[3],
           &valores_temp[4], &valores_temp[5], &valores_temp[6], &valores_temp[7],
           &valores_temp[8], &valores_temp[9]);

    if (strcmp(cuenca_temp, cuenca_seleccionada) == 0 &&
        strcmp(embalse_temp, embalse_seleccionado) == 0) {
        for (i = 0; i < num_anyos; i++) {
            valores_por_anio[i] = valores_temp[i];
        }
        break; 
    }

}

    fprintf(gnuplotPipe, "set title 'Evolucion del embalse %s (%s)'\n", embalse_seleccionado, cuenca_seleccionada);
    fprintf(gnuplotPipe, "set xlabel 'Anyo'\n");
    fprintf(gnuplotPipe, "set ylabel 'Volumen (hm^3)'\n");
    fprintf(gnuplotPipe, "set xtics rotate\n");
    fprintf(gnuplotPipe, "plot '-' with linespoints title 'Volumen por anyo'\n");
    
    for (i = 0; i < num_anyos; i++) {
    fprintf(gnuplotPipe, "%d %f\n", anio_inicial + i, valores_por_anio[i]);
}
fprintf(gnuplotPipe, "e\n");
fflush(gnuplotPipe);
pclose(gnuplotPipe);


	fclose(pf);
	
    printf ("Desea hacer otra operacion? (S/N) : \t");
        scanf (" %c",&respuesta);
        
        system("cls");
	
	
     
	}while ((respuesta=='S') || (respuesta=='s'));
	
	if ((respuesta=='N')||(respuesta=='n'))
	{
		printf("Gracias por usar nuestro programa :) \n");
	}
	
	
	
}


