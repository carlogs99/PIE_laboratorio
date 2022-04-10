#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

// Para los testeos no se planea agregar chequeo de la entrada
// el correcto funcionamiento de los tests queda a merced del tester
int main(int argc, char** argv){
	/* test: bit
	unsigned int buffer = atoi(argv[1]);
	int pos_bit = atoi(argv[2]);
	printf("%d\n", bit(buffer, pos_bit));
	return 0;
	*/
	
	/* test: ver_binario 
	unsigned int buffer = atoi(argv[1]);
	int pos_ls = atoi(argv[2]);
	int pos_ms = atoi(argv[3]);
	ver_binario(buffer, pos_ls, pos_ms);
	return 0;
	*/
	
	/* test: set_bit 
	unsigned int buffer = atoi(argv[1]);
	int pos = atoi(argv[2]);
	int valor = atoi(argv[3]);
	ver_binario(buffer, 0, 31);
	ver_binario(set_bit(buffer, pos, valor), 0 , 31);
	return 0;
	*/
	
	/* test: crear_mascara 
	int pos_ls = atoi(argv[1]);
	int pos_ms = atoi(argv[2]);
	ver_binario(crear_mascara(pos_ls, pos_ms), 0, 31);
	return 0;
	*/
	
	/* test: concatena
	unsigned int buffer_ms = 629145;
	unsigned int buffer_ls = 26214;
	ver_binario(concatena(buffer_ms, buffer_ls, 10), 0, 31);
	return 0;
	*/
	
	/* test: espejar 
	unsigned int buffer = atoi(argv[1]);
	int num_bits = atoi(argv[2]);
	ver_binario(buffer, 0, 31);
	ver_binario(espejar(buffer, num_bits), 0, 31);
	return 0;
	*/
	
	/* test: paridad 
	unsigned int buffer = atoi(argv[1]);
	ver_binario(buffer, 0, 31);
	printf("%d\n", paridad(buffer));
	return 0;
	*/
	
	/* test: ver_clave 
	struct Clave_t clave;
	clave.valor = atoi(argv[1]);
	ver_clave(clave);
	return 0;
	*/
	
	/* test: rotar_clave 
	struct Clave_t clave;
	clave.valor = atoi(argv[1]);
	clave.largo = atoi(argv[2]);
	printf("%d\n", clave.largo);
	ver_binario(clave.valor, 0, 31);
	clave = rotar_clave(clave, 2);
	ver_binario(clave.valor, 0, 31);
	return 0;
	*/ 
	
	/* test: encriptar */
	printf("Testeando encriptar con los siguientes parametros:\n");
	//unsigned int buffer = 629145; // ejemplo de la letra
	unsigned int buffer = atoi(argv[1]);
	struct Clave_t clave;
	unsigned int criptog;
	//clave.valor = 102; // ejemplo de la letra
	clave.valor = atoi(argv[2]); 
	clave.largo = atoi(argv[3]);
	
	printf("buffer: ");
	ver_binario(buffer, 0, 31);
	
	printf("clave: ");
	ver_clave(clave);
	printf("largo clave: ");
	printf("%d\n", clave.largo);
	printf("------------------------------------\n");
	
	criptog = encriptar(buffer, clave);
	printf("criptograma: ");
	ver_binario(criptog, 0, 31);
	//printf(criptog == 3448942581 ? "funciono encriptado\n" : "no funciono encriptado\n"); //para el ejemplo de la letra
	
	/*
	printf("desencriptado: ");
	ver_binario(encriptar(criptog, clave), 0, 31);
	printf((encriptar(criptog, clave)) == buffer ? "funciono desencriptado\n" : "no funciono desencriptado\n");
	*/
	
	return 0;
}
