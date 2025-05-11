#include <stdio.h> 
#include <string.h>
#include <float.h>
#include <math.h>
#include <funciones.h>


#define MAX_ANYOS 10   // ajusta según cuántos años tengas en el archivo
#define MESES 12
 
//estas tres variables son para el inicio
#define MAX_CUENCAS 20
#define MAX_EMBALSES 50
#define MAX_NOMBRE 50


int main() {
    FILE *pf;
    char cuenca[50], embalse[50];   
    char cuencaArchivo[50], embalseArchivo[50], mes[20];
    float valores[MAX_ANYOS];
    char linea[1024];
    DatosEmbalse datos[MAX_ANYOS];
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
        return -1;
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
    printf("Cuencas hidrograficas:\n");  //esto sirve para mostrar todas las cuencas que se han guardado en el vector
    for (i = 0; i < num_cuencas; i++)
    {
        printf("%d. %s\n", i + 1, cuencas[i]);
    }
    int opcion;
    printf("Seleccione una cuenca : ");    //esta parte ya es pedirle al usuario que seleccione una cuenca
    scanf("%d", &opcion);
    if (opcion < 1 || opcion > num_cuencas)
    {
		printf("Opcion no valida.\n");
		do 
		{
			printf("Introduce de nuevo la cuenca:\t");
			scanf("%d", &opcion);
		}
		while (opcion < 1 || opcion > num_cuencas);
        
    }

    
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

    if (embalse_opcion < 1 || embalse_opcion > num_embalses)
    {
        printf("Opcion de embalse no valida.\n");
        do 
		{
			printf("Introduce de nuevo el embalse:\t");
			scanf("%d", &embalse_opcion);
		}
		while (embalse_opcion < 1 || embalse_opcion > num_embalses);
        
    }
    
	
	int anyo_usuario, indice = -1;
	

	printf("Introduce el anyo que deseas analizar (2012-2021): ");
    scanf("%d", &anyo_usuario);
    
    if (anyo_usuario < 2012 || anyo_usuario > 2021) {
        printf("Anyo fuera de rango.\n");
        do 
		{
			printf("Introduce de nuevo el anyo:\t");
			scanf("%d", &anyo_usuario);
		}
		while (anyo_usuario < 2012 || anyo_usuario > 2021);
        
    }

    rewind(pf);
    fgets(linea, sizeof(linea), pf); // Saltar cabecera

    int mes_index;
    indice = 0; // posición fija ya que ahora trabajamos directo con un solo año
    for (j = 0; j < MESES; j++) {
        datos[indice].valores[j] = 0; // inicializar
    }

    while (fgets(linea, sizeof(linea), pf)) {
        char cuencaArchivo[MAX_NOMBRE], embalseArchivo[MAX_NOMBRE];
        int mes;
        float valores_anyos[10];

        sscanf(linea, "%[^,],%[^,],%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
               cuencaArchivo, embalseArchivo, &mes,
               &valores_anyos[0], &valores_anyos[1], &valores_anyos[2], &valores_anyos[3], &valores_anyos[4],
               &valores_anyos[5], &valores_anyos[6], &valores_anyos[7], &valores_anyos[8], &valores_anyos[9]);

        if (strcmp(cuencaArchivo, cuenca_seleccionada) == 0 &&
            strcmp(embalseArchivo, embalses[embalse_opcion - 1]) == 0 &&
            mes >= 1 && mes <= 12) {
            
            datos[indice].anyo = anyo_usuario;
            datos[indice].valores[mes - 1] = valores_anyos[anyo_usuario - 2012];
        }
    }

    
    printf("1) Maximo\n2) Minimo\n3) Media\n4) Varianza\n5) Desviacion tipica\n6) Mediana\n7) Moda\n");
    printf("Selecciona una opcion (1-7): ");
    scanf("%d", &opcion);
    
    if (opcion < 1 || opcion > 7) {
        printf("Numero invalido\n");
        do 
		{
			printf("Introduce de nuevo el numero:\t");
			scanf("%d", &opcion);
		}
		while (opcion < 1 || opcion > 7);
        
    }
	


   float suma = 0, media = 0, varianza = 0, desviacion = 0;
   float max = FLT_MIN, min = FLT_MAX;
	
	switch (opcion) {
        case 1: // máximo
            maximo_archivo(datos, indice,  anyo_usuario);  //en el parentesis va lo que tiene que coger
            break;

        case 2: // mínimo
            minimo_archivo(datos,  indice,  anyo_usuario);
            break;
            

        case 3: // media
            media_archivo(datos, indice,  anyo_usuario);
            break;

        case 4: // varianza
            varianza_archivo(datos, indice,  anyo_usuario);
            break;

        case 5: // desviación típica
              desviacion_tipica_archivo(datos, indice, anyo_usuario);
            break;
        
		case 6: // mediana
            mediana_archivo(datos, indice, anyo_usuario);
            break;
            
		case 7: // moda
		    moda_archivo(datos, indice, anyo_usuario);
		    break;
	}
        
		
		fclose(pf);
        
        printf ("Desea hacer otra operacion? (S/N) : \n");
        scanf (" %c",&respuesta);
	
	
     
	}while ((respuesta=='S') || (respuesta=='s'));
	
	if ((respuesta=='N')||(respuesta=='n'))
	{
		printf("Gracias :) \n");
	}
	

    return 0;
}

