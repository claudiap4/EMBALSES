# EMBALSES
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>


#define MAX_ANYOS 20   
#define MESES 12



struct EmbalseDatos {
    int anyo;
    float valores[MESES];
};

float maximo_archivo(struct EmbalseDatos datos[], int indice, int anyo_usuario) {

float max = FLT_MIN;

   for (int i = 0; i < MESES; i++)
                if (datos[indice].valores[i] > max) max = datos[indice].valores[i];
            printf("Maximo del anyo %d: %.2f\n", anyo_usuario, max);  
			
	return max;		 	
};

float minimo_archivo(struct EmbalseDatos datos[], int indice, int anyo_usuario) {

float min = FLT_MAX;

   for (int i = 0; i < MESES; i++)
                if (datos[indice].valores[i] < min) min = datos[indice].valores[i];
            printf("Minimo del anyo %d: %.2f\n", anyo_usuario, min);  
			
	return min;		 	
};

float media_archivo(struct EmbalseDatos datos[], int indice, int anyo_usuario)
{
	for (int i = 0; i < MESES; i++) suma = suma + datos[indice].valores[i];
            media = suma / MESES;
            printf("Media del anyo %d: %.2f\n", anyo_usuario, media);
            
    return media;        
};

float (struct EmbalseDatos datos[], int indice, int anyo_usuario)
{
	for (int i = 0; i < MESES; i++) suma = suma + datos[indice].valores[i];
            media = suma / MESES;
            for (int i = 0; i < MESES; i++)
                varianza = varianza + pow(datos[indice].valores[i] - media, 2);
            varianza /= MESES;
            printf("Varianza del anyo %d: %.4f\n", anyo_usuario, varianza);
            
    return varianza;        
};

