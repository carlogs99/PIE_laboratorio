
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
	
	if(!(strcmp(argv[1], "convertir_formato"))) {
		if(argc != 5 || (strcmp(argv[4], "PLANO") && strcmp(argv[4], "NO_PLANO"))) {
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
	} else if(!(strcmp(argv[1], "filtrar_sepia"))) {
		if(argc != 5 || (strcmp(argv[4], "PLANO") && strcmp(argv[4], "NO_PLANO"))) {
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
	}
	
	
	
	return ERROR;
}

