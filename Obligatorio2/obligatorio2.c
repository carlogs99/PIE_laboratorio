
/**
 * @file obligatorio2.c
 * @author Carlos Gruss
 * @date 28 may 2022
 * @brief Codigo fuente main con implementacion de subcomandos y main 
 * para Obligatorio 2 PIE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "bits.h"
#include "imagen.h"

int main(int argc, char** argv) {
	Imagen_t pin;
	CodigoError_t CE; 
	
	/*Tests basicos inicializar_imagen y destruir_imagen
	Imagen_t pin;
	CodigoError_t codigoIni = inicializar_imagen(&pin, 10, 12);
	printf("CodigoError inicializar_imagen: %d\n", codigoIni);
	printf("nFilas = %d, nCol = %d\n", pin.filas, pin.columnas);
	for(int i = 0 ; i < 10 ; i++) {
		for(int j = 0 ; j < 12 ; j++) {
			printf("Contenido en IMG(%d, %d) = %d\n", i, j, (pin.pixeles)[i][j]); 
		}
	}
	
	CodigoError_t codigoDest = destruir_imagen(&pin);
	printf("CodigoError destruir_imagen: %d\n", codigoDest);
	*/
	
	/*Test para leer_imagen y escribir_imagen 
	Imagen_t pin;
	CodigoError_t CE = leer_imagen("./imagenes_ppm/lagartija_plano.ppm", &pin);
	printf("CodigoError leer_imagen: %d\n", CE);
	for(int i = 0 ; i < pin.filas ; i++) {
		for(int j = 0 ; j < pin.columnas ; j++) {
			printf("Contenido en IMG(%d, %d) = %u\n", i, j, (pin.pixeles)[i][j]); 
		}
	}
	
	CE = escribir_imagen(&pin, "./lagartija_plano_copy.ppm", NO_PLANO);
	printf("CodigoError escribir_imagen: %d\n", CE);
	
	CE = destruir_imagen(&pin);
	printf("CodigoError destruir_imagen: %d\n", CE);
	*/
	
	//Subcomando: convertir_formato
	//Subcomando para convertir de formato plano a no plano y viceversa.
	//Formato: ./obligatorio2 convertir_formato RUTA_IM_ENTRADA RUTA_IM_SALIDA FORMATO_PPM
	if(!(strcmp(argv[1], "convertir_formato"))){
		if(argc != 5) {
			return ERROR;
		} else {
			CE = leer_imagen(argv[2], &pin);
			if(CE != OK) {
				return CE;
			} else {
				CE = escribir_imagen(&pin, argv[3], PLANO);
				if(CE != OK) {
					return CE;
				} else {
					return OK;
				}
			}
		}
	}
	
	
	
	
	return OK;
}

