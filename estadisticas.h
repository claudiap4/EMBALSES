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
	float suma = 0.0, media = 0.0;
	for (int i = 0; i < MESES; i++) suma = suma + datos[indice].valores[i];
            media = suma / MESES;
            printf("Media del anyo %d: %.2f\n", anyo_usuario, media);
            
    return media;        
};

float varianza_archivo(struct EmbalseDatos datos[], int indice, int anyo_usuario)
{
	float suma = 0, media = 0, varianza = 0;
	for (int i = 0; i < MESES; i++) suma = suma + datos[indice].valores[i];
            media = suma / MESES;
            for (int i = 0; i < MESES; i++)
                varianza = varianza + pow(datos[indice].valores[i] - media, 2);
            varianza /= MESES;
            printf("Varianza del anyo %d: %.4f\n", anyo_usuario, varianza);
            
    return varianza;        
};

float desviacion_tipica_archivo(struct EmbalseDatos datos[], int indice, int anyo_usuario)
{
	float suma = 0, media = 0, varianza = 0, desviacion = 0;
	for (int i = 0; i < MESES; i++) suma += datos[indice].valores[i];
            media = suma / MESES;
            for (int i = 0; i < MESES; i++)
                varianza += pow(datos[indice].valores[i] - media, 2);
            varianza /= MESES;
            desviacion = sqrt(varianza);
            printf("Desviacion tipica del anyo %d: %.4f\n", anyo_usuario, desviacion);
            return desviacion;
}

float mediana_archivo (struct EmbalseDatos datos[], int indice, int anyo_usuario)
{
	 float copia[MESES];
            for (int i = 0; i < MESES; i++)
                copia[i] = datos[indice].valores[i];

            // ordenamos los datos
            for (int i = 0; i < MESES - 1; i++) 
			{
                for (int j = 0; j < MESES - i - 1; j++) 
				{
                    if (copia[j] > copia[j + 1]) 
					{
                        float aux = copia[j];
                        copia[j] = copia[j + 1];
                        copia[j + 1] = aux;
                    }
                }
            }

            float mediana;
            if (MESES % 2 == 0)
                mediana = (copia[MESES/2 - 1] + copia[MESES/2]) / 2;
            else
                mediana = copia[MESES/2];

            printf("Mediana del anyo %d: %.2f\n", anyo_usuario, mediana); 
            return mediana;
};

float moda_archivo (struct EmbalseDatos datos[], int indice, int anyo_usuario)
{
	float moda = datos[indice].valores[0];
            int max_repeticiones = 0;

            for (int i = 0; i < MESES; i++) {
                int repeticiones = 0;
                for (int j = 0; j < MESES; j++) {
                    if (fabs(datos[indice].valores[i] - datos[indice].valores[j]) < 0.001)
                        repeticiones++;
                }
                if (repeticiones > max_repeticiones) {
                    max_repeticiones = repeticiones;
                    moda = datos[indice].valores[i];
                }
            }

            if (max_repeticiones <= 1)
                printf("No hay moda: todos los valores son distintos.\n");
            else
                printf("Moda del anyo %d: %.2f (repetido %d veces)\n", anyo_usuario, moda, max_repeticiones);
                return moda;
}