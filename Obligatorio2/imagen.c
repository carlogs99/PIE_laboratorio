
/**
 * @file imagen.c
 * @author Carlos Gruss
 * @date 28 may 2022
 * @brief Codigo fuente biblioteca de manejo de imagenes y encriptación 
 * para Obligatorio 2 PIE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "bits.h"
#include "imagen.h"

CodigoError_t inicializar_imagen(Imagen_t* pin, int filas, int columnas) {
	// Inicializacion de filas y columnas de la imagen
	pin->filas = filas;
	pin->columnas = columnas;
	
	//Reserva de memoria para los pixeles de la imagen:
	
	//Reserva primero la memoria para la "columna" de punteros a fila:
	pin->pixeles = (pixel_t**) malloc(filas * sizeof(pixel_t*));
	//Chequear validez de la reserva:
	if(pin->pixeles == NULL) {
		return ERROR;
	}
	
	//Luego reserva la memoria para cada fila:
	for(int i = 0 ; i < filas ; i++) {
		(pin->pixeles)[i] = (pixel_t*) malloc(columnas * sizeof(pixel_t));
		if((pin->pixeles)[i] == NULL) {
			//En caso de error libera memoria ya asignada
			for(int j = i-1 ; j >= 0 ; j--) {
				free((pin->pixeles)[j]);
			}
			return ERROR;
		}
	}
	
	return OK;
}

CodigoError_t destruir_imagen(Imagen_t* pin) {
	int nFilas = pin->filas;
	
	//Logica inversa a inicializar_imagen
	for(int i = 0 ; i < nFilas ; i++) {
		free((pin->pixeles)[i]);
	}
	
	free(pin->pixeles);
	
	return OK;
}

