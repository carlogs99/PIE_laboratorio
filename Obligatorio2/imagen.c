
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
	char num_magico[3], ancho_img_str[6], alto_img_str[6], 
	aux_pixel_R[4], aux_pixel_G[4], aux_pixel_B[4];
	FormatoPPM_t formato_img;
	int filas, columnas;
	pixel_t aux_pixel;
	char aux_byte_R, aux_byte_G, aux_byte_B;
	
	fp = fopen(ruta_imagen, "r");
	if(fp == NULL) {
		return PPM_ARCHIVO_INEXISTENTE;
	}
	
	//Lectura del encabezado:
	//El asterisco (%*s) suprime el argumento de valor maximo canal
	//se asume que este es siempre 255
	if(fscanf(fp, "%s %s %s %*s", num_magico, ancho_img_str, alto_img_str) != 3) {
		fclose(fp);
		return PPM_ERROR_LECTURA;
	} else {
		//Chequeos de formato del encabezado:
		//Chequeo numero magico
		if(!(strcmp(num_magico, "P3"))) {
			formato_img = PLANO;
		} else if(!(strcmp(num_magico, "P6"))) {
			formato_img = NO_PLANO;
			
		} else {
			fclose(fp);
			return PPM_ENCABEZADO_INVALIDO;
		}
		//Chequeo numero de filas
		if(!(filas = atoi(alto_img_str))) {
			fclose(fp);
			return PPM_ENCABEZADO_INVALIDO;
		}
		//Chequeo numero de columnas
		if(!(columnas = atoi(ancho_img_str))) {
			fclose(fp);
			return PPM_ENCABEZADO_INVALIDO;
		}
	}
	
	//Inicializar imagen:
	if(inicializar_imagen(pin, filas, columnas) == ERROR) {
		fclose(fp);
		return ERROR;
	}
	
	//Leer imagen:
	if(formato_img == PLANO) {
		fscanf(fp, " "); //Saltear espacio blanco hasta comienzo pixels
		for(int i = 0 ; i < filas ; i++) {
			for(int j = 0 ; j < columnas ; j++) {
				if(fscanf(fp, "%s %s %s", aux_pixel_R, aux_pixel_G, aux_pixel_B) != 3) {
					fclose(fp);
					return PPM_DATOS_INVALIDOS;
				}		
				aux_pixel = atoi(aux_pixel_R);
				aux_pixel = concatena(aux_pixel, atoi(aux_pixel_G), 8);
				aux_pixel = concatena(aux_pixel, atoi(aux_pixel_B), 8);
				(pin->pixeles)[i][j] = aux_pixel;
			}	
		}
	} else if (formato_img == NO_PLANO) {
		fscanf(fp, " "); //Saltear espacio blanco hasta comienzo pixels
		for(int i = 0 ; i < filas ; i++) {
			for(int j = 0 ; j < columnas ; j++) {
				if((aux_byte_R = fgetc(fp)) == EOF && feof(fp)) {
					fclose(fp);
					return PPM_DATOS_INVALIDOS;
				}
				if((aux_byte_G = fgetc(fp)) == EOF && feof(fp)) {
					fclose(fp);
					return PPM_DATOS_INVALIDOS;
				}
				if((aux_byte_B = fgetc(fp)) == EOF && feof(fp)) {
					fclose(fp);
					return PPM_DATOS_INVALIDOS;
				}
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
		if(fprintf(fp, "%s\n%u\n%u\n%u\n", "P3", pin->columnas, pin->filas, 255) < 0) {
			fclose(fp);
			return PPM_ERROR_ESCRITURA;
		}
		for(int i = 0 ; i < (pin->filas) ; i++) {
			for(int j = 0 ; j < (pin->columnas) ; j++) {
				aux_pixel_R = ((pin->pixeles)[i][j] & mascara_R) >> 16;
				aux_pixel_G = ((pin->pixeles)[i][j] & mascara_G) >> 8;
				aux_pixel_B = ((pin->pixeles)[i][j] & mascara_B);
			
				if(fprintf(fp, "%u %u %u\t", aux_pixel_R, aux_pixel_G, aux_pixel_B) < 0) {
					fclose(fp);
					return PPM_ERROR_ESCRITURA;
				} 
			}
		}
	} else if(formato == NO_PLANO) {
		fprintf(fp, "%s\n%u\n%u\n%u\n", "P6", pin->columnas, pin->filas, 255);
		for(int i = 0 ; i < (pin->filas) ; i++) {
			for(int j = 0 ; j < (pin->columnas) ; j++) {
				aux_pixel_R = ((pin->pixeles)[i][j] & mascara_R) >> 16;
				aux_pixel_G = ((pin->pixeles)[i][j] & mascara_G) >> 8;
				aux_pixel_B = ((pin->pixeles)[i][j] & mascara_B);
				
				if(fputc(aux_pixel_R, fp) == EOF) {
					fclose(fp);
					return PPM_ERROR_ESCRITURA;
				}
				if(fputc(aux_pixel_G, fp) == EOF) {
					fclose(fp);
					return PPM_ERROR_ESCRITURA;
				}
				if(fputc(aux_pixel_B, fp) == EOF) {
					fclose(fp);
					return PPM_ERROR_ESCRITURA;
				}
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
			
			R_out = min(round(0.393*R_in + 0.769*G_in + 0.189*B_in), 255);
			G_out = min(round(0.349*R_in + 0.686*G_in + 0.168*B_in), 255);
			B_out = min(round(0.272*R_in + 0.534*G_in + 0.131*B_in), 255);
			
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
			largo_clave = rand() % (19 + 1 - min_largo_clave) + min_largo_clave;
			mascara_clave = crear_mascara(0, largo_clave-1);
			clave = rand() & mascara_clave;
			clave = (largo_clave << 19) | clave;
			
			(pcriptoim->pixeles)[i][j] = clave;
		}
	}
	
	return OK;
}

CodigoError_t validar_cripto_imagen(const Imagen_t* pcriptoim) {
	unsigned int mascara_largo, largo_clave;
	
	mascara_largo = crear_mascara(19, 23);
	
	for(int i = 0 ; i < (pcriptoim->filas) ; i++) {
		for(int j = 0 ; j < (pcriptoim->columnas) ; j++) {
			largo_clave = (mascara_largo & (pcriptoim->pixeles)[i][j]) >> 19;
			
			if(largo_clave > 19 || largo_clave < 1) {
				return PPM_CRIPTO_NO_VALIDA;
			}
		}
	}
	
	return OK;
}

CodigoError_t encriptar_imagen(const Imagen_t* pin, const Imagen_t* pcriptoim,
Imagen_t* pout) {
	Clave_t clave;
	pixel_t cripto_pixel;
	
	if(inicializar_imagen(pout, pin->filas, pin->columnas)) {
		return ERROR;
	}
	
	for(int i = 0 ; i < (pin->filas) ; i++) {
		for(int j = 0 ; j < (pin->columnas) ; j++) {
			cripto_pixel = (pcriptoim->pixeles)[i%(pcriptoim->filas)][j%(pcriptoim->columnas)];
			clave.largo = (cripto_pixel >> 19) & crear_mascara(0, 4);
			clave.valor = cripto_pixel & crear_mascara(0, clave.largo);
			
			(pout->pixeles)[i][j] = encriptar((pin->pixeles)[i][j], clave);
		}
	}
	
	return OK;
}

pixel_t min(unsigned int a, unsigned int b) {
	return (a <= b) ? a : b;
}
