
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

#define ERROR_MAIN 1

int main(int argc, char** argv) {
	Imagen_t pin, pout, pcriptoim;
	CodigoError_t CE;
	FormatoPPM_t formato; 
	
	if(argc < 2) {
		return ERROR_MAIN;
	}
	
	if(!(strcmp(argv[1], "convertir_formato")) && argc == 5) {
		if(strcmp(argv[4], "plano") && strcmp(argv[4], "no_plano")) {
			return ERROR_MAIN;
		} else {
			CE = leer_imagen(argv[2], &pin);
			if(CE != OK) {
				if(CE == PPM_DATOS_INVALIDOS) { 
					destruir_imagen(&pin);
					return CE;
				} else {
					//Si se retorno con otro error, no hay
					//memoria para liberar y hacer destruir_imagen(&pin)
					//causaria comportamiento indeterminado.
					return CE;
				}
			} else {
				formato = !strcmp(argv[4], "plano") ? PLANO : NO_PLANO;
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
		if(strcmp(argv[4], "plano") && strcmp(argv[4], "no_plano")) {
			return ERROR_MAIN;
		} else {
			CE = leer_imagen(argv[2], &pin);
			if(CE != OK) {
				if(CE == PPM_DATOS_INVALIDOS) { 
					destruir_imagen(&pin);
					return CE;
				} else {
					return CE;
				}
			} else {
				CE = filtrar_sepia(&pin, &pout);
				if(CE != OK) {
					//No hay que liberar pout ya que si hubo
					//error en filtrar_sepia, la memoria no
					//llego a reservarse para pout
					destruir_imagen(&pin);
					return CE;
				} else {
					formato = !strcmp(argv[4], "plano") ? PLANO : NO_PLANO;
					CE = escribir_imagen(&pout, argv[3], formato);
					if(CE != OK) {
						//Aca si hay que liberar pout ya que
						//ya que filtrar_sepia no devolvio error
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
		if((strcmp(argv[6], "plano") && strcmp(argv[6], "no_plano")) || atoi(argv[4]) < 1 || atoi(argv[4]) > 19) {
			return ERROR_MAIN;
		} else {
			CE = generar_cripto_imagen(&pin, atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
			if(CE != OK) {
				//Si hubo error, inicializar_imagen ya libero la memoria
				return CE;
			} else {
				formato = !strcmp(argv[6], "plano") ? PLANO : NO_PLANO;
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
			return ERROR_MAIN; //retorna 1
		} else {
			CE = validar_cripto_imagen(&pin);
			if(CE != OK) {
				destruir_imagen(&pin);
				printf("Error: Cripto-imagen no válida\n");
				return ERROR_MAIN; //retorna 1
			} else {
				destruir_imagen(&pin);
				printf("Cripto-imagen válida\n");
				return OK; //retorna 0
			}
		}
	} else if(!(strcmp(argv[1], "encriptar_imagen")) && argc == 6) {
		if((strcmp(argv[5], "plano") && strcmp(argv[5], "no_plano"))) {
			return ERROR_MAIN;
		} else {
			CE = leer_imagen(argv[3], &pcriptoim);
			if(CE != OK) {
				if(CE == PPM_DATOS_INVALIDOS) { 
					destruir_imagen(&pcriptoim);
					return CE;
				} else {
					//Si se retorno con otro error, no hay
					//memoria para liberar y hacer destruir_imagen(&pcriptoim)
					//causaria comportamiento indeterminado.
					return CE;
				}
			} else {
				CE = validar_cripto_imagen(&pcriptoim);
				if(CE != OK) {
					destruir_imagen(&pcriptoim);
					printf("Error: Cripto-imagen no válida\n");
					return ERROR_MAIN; //retorna 1
				} else {
					CE = leer_imagen(argv[2], &pin);
					if(CE != OK) {
						destruir_imagen(&pcriptoim);
						if(CE == PPM_DATOS_INVALIDOS) { 
							destruir_imagen(&pin);
							return CE;
						} else {
							//Si se retorno con otro error, no hay
							//memoria para liberar y hacer destruir_imagen(&pin)
							//causaria comportamiento indeterminado.
							return CE;
						}
					} else {
						CE = encriptar_imagen(&pin, &pcriptoim, &pout);
						if(CE != OK) {
							destruir_imagen(&pcriptoim);
							destruir_imagen(&pin);
							return CE;
						} else {
							formato = !strcmp(argv[5], "plano") ? PLANO : NO_PLANO;
							CE = escribir_imagen(&pout, argv[4], formato);
							if(CE != OK) {
								destruir_imagen(&pcriptoim);
								destruir_imagen(&pin);
								destruir_imagen(&pout);
								return CE;
							} else {
								destruir_imagen(&pcriptoim);
								destruir_imagen(&pin);
								destruir_imagen(&pout);
								return OK;
							}
						}
					}
				}
			}		
		}
	}
	
	return ERROR;
}

