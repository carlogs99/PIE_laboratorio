
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
#include <string.h>
#include <math.h>
#include "bits.h"
#include "imagen.h"

#define mascara_R crear_mascara(16, 23)
#define mascara_G crear_mascara(8, 15)
#define mascara_B crear_mascara(0, 7)

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

CodigoError_t leer_imagen(const char* ruta_imagen, Imagen_t* pin) {
	FILE* fp;
	char *num_magico, *ancho_img_str, *alto_img_str,
	*aux_pixel_R, *aux_pixel_G, *aux_pixel_B;
	FormatoPPM_t formato_img;
	int filas, columnas;
	pixel_t aux_pixel;
	char aux_byte_R, aux_byte_G, aux_byte_B;
	
	fp = fopen(ruta_imagen, "r");
	if(fp == NULL) {
		return PPM_ARCHIVO_INEXISTENTE;
	}
	
	//Lectura del encabezado:
	//Reserva memoria para los datos a leer
	num_magico = (char*) malloc(2 * sizeof(char));
	ancho_img_str = (char*) malloc(4 * sizeof(char));
	alto_img_str = (char*) malloc(4 * sizeof(char));
	//El asterisco suprime el argumento de valor maximo canal
	//se asume que este es siempre 255
	if(fscanf(fp, "%s %s %s %*s", num_magico, ancho_img_str, alto_img_str) != 3) {
		free(num_magico);
		free(ancho_img_str);
		free(alto_img_str);
		fclose(fp);
		return PPM_ERROR_LECTURA;
	}
	
	//Chequeos de formato del encabezado:
	if(!(strcmp(num_magico, "P3"))) {
		formato_img = PLANO;
	} else if(!(strcmp(num_magico, "P6"))) {
		formato_img = NO_PLANO;
		
	} else {
		free(num_magico);
		free(ancho_img_str);
		free(alto_img_str);
		fclose(fp);
		return PPM_ENCABEZADO_INVALIDO;
	}
	
	if(!(filas = atoi(alto_img_str))) {
		free(num_magico);
		free(ancho_img_str);
		free(alto_img_str);
		fclose(fp);
		return PPM_ENCABEZADO_INVALIDO;
	}
	
	if(!(columnas = atoi(ancho_img_str))) {
		free(num_magico);
		free(ancho_img_str);
		free(alto_img_str);
		fclose(fp);
		return PPM_ENCABEZADO_INVALIDO;
	}
	
	//Libera memoria de los datos del encabezado:
	free(num_magico);
	free(ancho_img_str);
	free(alto_img_str);
	
	//Inicializar imagen:
	if(inicializar_imagen(pin, filas, columnas) == ERROR) {
		fclose(fp);
		return ERROR;
	}
	
	//Leer imagen:
	if(formato_img == PLANO) {
		fscanf(fp, " "); //Saltear espacio blanco hasta comienzo pixels
		aux_pixel_R = (char*) malloc(3 * sizeof(char));
		aux_pixel_G = (char*) malloc(3 * sizeof(char));
		aux_pixel_B = (char*) malloc(3 * sizeof(char));
		for(int i = 0 ; i < filas ; i++) {
			for(int j = 0 ; j < columnas ; j++) {
				fscanf(fp, "%s %s %s", aux_pixel_R, aux_pixel_G, aux_pixel_B);		//IMPLEMENTAR ERROR PPM_DATOS_INVALIDOS
				aux_pixel = atoi(aux_pixel_R);
				aux_pixel = concatena(aux_pixel, atoi(aux_pixel_G), 8);
				aux_pixel = concatena(aux_pixel, atoi(aux_pixel_B), 8);
				(pin->pixeles)[i][j] = aux_pixel;
			}	
		}
		free(aux_pixel_R);
		free(aux_pixel_G);
		free(aux_pixel_B);
	} else if (formato_img == NO_PLANO) {
		fscanf(fp, " "); //Saltear espacio blanco hasta comienzo pixels
		for(int i = 0 ; i < filas ; i++) {
			for(int j = 0 ; j < columnas ; j++) {
				aux_byte_R = fgetc(fp);
				aux_byte_G = fgetc(fp);
				aux_byte_B = fgetc(fp);
				aux_pixel = aux_byte_R;
				aux_pixel = concatena(aux_pixel, aux_byte_G, 8);
				aux_pixel = concatena(aux_pixel, aux_byte_B, 8);
				(pin->pixeles)[i][j] = aux_pixel;
			}	
		}
	}
	
	fclose(fp);
	return OK;
}

CodigoError_t escribir_imagen(const Imagen_t* pin, const char* ruta_imagen, 
FormatoPPM_t formato) {
	FILE* fp;
	unsigned int aux_pixel_R, aux_pixel_G, aux_pixel_B;
	
	
	fp = fopen(ruta_imagen, "w");
	if(fp == NULL) {
		return PPM_ERROR_ESCRITURA;
	}
	
	if(formato == PLANO) {
		fprintf(fp, "%s\n%u\n%u\n%u\n", "P3", pin->columnas, pin->filas, 255);		//ERROR CHECKING FALTA
		for(int i = 0 ; i < (pin->filas) ; i++) {
			for(int j = 0 ; j < (pin->columnas) ; j++) {
				aux_pixel_R = ((pin->pixeles)[i][j] & mascara_R) >> 16;
				aux_pixel_G = ((pin->pixeles)[i][j] & mascara_G) >> 8;
				aux_pixel_B = ((pin->pixeles)[i][j] & mascara_B);
			
				fprintf(fp, "%u %u %u\t", aux_pixel_R, aux_pixel_G, aux_pixel_B); 
			}
		}
	} else if(formato == NO_PLANO) {
		fprintf(fp, "%s\n%u\n%u\n%u\n", "P6", pin->columnas, pin->filas, 255);
		for(int i = 0 ; i < (pin->filas) ; i++) {
			for(int j = 0 ; j < (pin->columnas) ; j++) {
				aux_pixel_R = ((pin->pixeles)[i][j] & mascara_R) >> 16;
				aux_pixel_G = ((pin->pixeles)[i][j] & mascara_G) >> 8;
				aux_pixel_B = ((pin->pixeles)[i][j] & mascara_B);
				
				fputc(aux_pixel_R, fp);
				fputc(aux_pixel_G, fp);
				fputc(aux_pixel_B, fp);
			}
		}
	} else {
		fclose(fp);
		return ERROR;
	}
	
	fclose(fp);
	return OK;
}

CodigoError_t filtrar_sepia(const Imagen_t* pin, Imagen_t* pout) {
	unsigned int R_in, G_in, B_in, R_out, G_out, B_out, aux_pixel;
	
	if(inicializar_imagen(pout, pin->filas, pin->columnas)) {
		return ERROR;
	}
	
	for(int i = 0 ; i < (pin->filas) ; i++) {
		for(int j = 0 ; j < (pin->columnas) ; j++) {
			R_in = ((pin->pixeles)[i][j] & mascara_R) >> 16;
			G_in = ((pin->pixeles)[i][j] & mascara_G) >> 8;
			B_in = ((pin->pixeles)[i][j] & mascara_B);
			
			R_out = min(round(0.393*R_in + 0.769*B_in + 0.189*G_in), 255);
			G_out = min(round(0.349*R_in + 0.686*B_in + 0.168*G_in), 255);
			B_out = min(round(0.272*R_in + 0.534*B_in + 0.131*G_in), 255);
			
			aux_pixel = R_out;
			aux_pixel = concatena(aux_pixel, G_out, 8);
			aux_pixel = concatena(aux_pixel, B_out, 8);
			
			(pout->pixeles)[i][j] = aux_pixel;
		}
	}
	
	return OK;
}

CodigoError_t generar_cripto_imagen(Imagen_t* pcriptoim, int filas, int columnas,
int min_largo_clave) {
	unsigned int largo_clave, mascara_clave, clave;

	if(inicializar_imagen(pcriptoim, filas, columnas)) {
		return ERROR;
	}
	
	for(int i = 0 ; i < filas ; i++) {
		for(int j = 0 ; j < columnas ; j++) {
			largo_clave = rand() % (min_largo_clave + 1);
			mascara_clave = crear_mascara(0, largo_clave-1);
			clave = rand() & mascara_clave;
			clave = (largo_clave << 19) | clave;
			
			(pcriptoim->pixeles)[i][j] = clave;
		}
	}
	
	return OK;
}

pixel_t min(unsigned int a, unsigned int b) {
	return (a <= b) ? a : b;
}
