
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
#include <math.h>
#include "bits.h"
#include "imagen.h"

int main(int argc, char** argv) {
	Imagen_t pin, pout;
	CodigoError_t CE;
	FormatoPPM_t formato; 
	
	if(argc < 2) {
		return ERROR;
	}
	
	if(!(strcmp(argv[1], "convertir_formato")) && argc == 5) {
		if(strcmp(argv[4], "PLANO") && strcmp(argv[4], "NO_PLANO")) {
			return ERROR;
		} else {
			CE = leer_imagen(argv[2], &pin);
			if(CE != OK) {
				destruir_imagen(&pin);
				return CE;
			} else {
				formato = !strcmp(argv[4], "PLANO") ? PLANO : NO_PLANO;
				CE = escribir_imagen(&pin, argv[3], formato);
				if(CE != OK) {
					destruir_imagen(&pin);
					return CE;
				} else {
					destruir_imagen(&pin);
					return OK;
				}
			}
		}
	} else if(!(strcmp(argv[1], "filtrar_sepia")) && argc == 5) {
		if(strcmp(argv[4], "PLANO") && strcmp(argv[4], "NO_PLANO")) {
			return ERROR;
		} else {
			CE = leer_imagen(argv[2], &pin);
			if(CE != OK) {
				destruir_imagen(&pin);
				return CE;
			} else {
				CE = filtrar_sepia(&pin, &pout);
				if(CE != OK) {
					destruir_imagen(&pin);
					destruir_imagen(&pout);
					return CE;
				} else {
					formato = !strcmp(argv[4], "PLANO") ? PLANO : NO_PLANO;
					CE = escribir_imagen(&pout, argv[3], formato);
					if(CE != OK) {
						destruir_imagen(&pin);
						destruir_imagen(&pout);
						return CE;
					} else {
						destruir_imagen(&pin);
						destruir_imagen(&pout);
						return OK;
					}
				}
			}
		}
	} else if(!(strcmp(argv[1], "generar_cripto_imagen")) && argc == 7) {
		if((strcmp(argv[6], "PLANO") && strcmp(argv[6], "NO_PLANO")) || atoi(argv[4]) < 1 || atoi(argv[4]) > 19) {
			return ERROR;
		} else {
			CE = generar_cripto_imagen(&pin, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
			if(CE != OK) {
				destruir_imagen(&pin);
				return CE;
			} else {
				formato = !strcmp(argv[6], "PLANO") ? PLANO : NO_PLANO;
				CE = escribir_imagen(&pin, argv[5], formato);
				if(CE != OK) {
					destruir_imagen(&pin);
					return CE;
				} else {
					destruir_imagen(&pin);
					return OK;
				}
			}
	
		}
	} else if(!(strcmp(argv[1], "validar_cripto_imagen")) && argc == 3) {
		CE = leer_imagen(argv[2], &pin);
		if(CE != OK) {
			destruir_imagen(&pin);
			printf("Error: Cripto-imagen no válida\n");
			return 1;
		} else {
			CE = validar_cripto_imagen(&pin);
			printf("Cripto-imagen válida\n");
			return OK;
		}
	}
	
	
	return ERROR;
}

