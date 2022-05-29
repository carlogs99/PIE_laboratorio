
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
	
	//Logica inversa a inicializar_imagen para liberar memoria
	for(int i = 0 ; i < nFilas ; i++) {
		free((pin->pixeles)[i]);
	}
	
	free(pin->pixeles);
	
	//Pone atributos en cero
	pin->filas = 0;
	pin->columnas = 0;
	
	return OK;
}

CodigoError_t duplicar_imagen(const Imagen_t* pin, Imagen_t* pout) {	
	return inicializar_imagen(pout, pin->filas, pin->columnas);
}

CodigoError_t leer_imagen(const char* ruta_imagen, Imagen_t*pin) {
	FILE* fp;
	char* num_magico, ancho_img_str, alto_img_str;
	FormatoPPM_t formato_img;
	int filas, columnas;
	
	fp = fopen(ruta_imagen, "r");
	if(fp == NULL) {
		return PPM_ARCHIVO_INEXISTENTE;
	}
	
	//Lectura del encabezado:
	//El asterisco suprime el argumento de valor maximo canal
	//se asume que este es siempre 255
	if(fscanf(fp, "%s %s %s %*s", num_magico, ancho_img_str, alto_img_str) != 3) {
		return PPM_ERROR_LECTURA;
	}
	
	//Chequeos de formato del encabezado:
	if(num_magico == "P3") {
		formato_img = PLANO;
	} else if(num_magico == "P6") {
		formato_img = NO_PLANO;
		
	} else {
		return PPM_ENCABEZADO_INVALIDO;
	}
	
	if(!(filas = atoi(alto_img_str))) {
		return PPM_ENCABEZADO_INVALIDO;
	}
	
	if(!(columnas = atoi(ancho_img_str))) {
		return PPM_ENCABEZADO_INVALIDO;
	}
	
	
	
	
	
}


