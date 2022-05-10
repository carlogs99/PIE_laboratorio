
/**
 * @file bits.h
 * @author Carlos Gruss
 * @date 09 may 2022
 * @brief Header biblioteca de manejo de bits y encriptación para Obligatorio 1
 * PIE.
 */
 
/**
 * @struct Clave_t
 *
 * Estructura para representar claves de Vigenère de cualquier tamaño
 * menor o igual a 32. Clave.valor contiene la clave en sus clave.largo bits
 * menos significativos, y ceros en el resto de sus bits.
 *
 * Ejemplo: 
 * 1110001 tiene clave.valor == 0x00000071 y clave.largo == 7.
 */
typedef struct Clave_t {
	unsigned int valor;
	int largo;
} Clave_t;

/**
 * @brief Devuelve el valor del bit de buffer en la posicion pos_bit.
 * 
 * Ejemplo:
 * @code
 * bit(2, 1)
 * @endcode
 * Va a retornar el entero 1.
 *
 * @param buffer Entero sin signo al que se le quiere testear el valor.
 * @param pos_bit Posición sobre la cual se quiere testear el valor del bit.
 * @return Valor del bit pos_bit de buffer. Será un entero 1 o 0.
 */
int bit(unsigned int buffer, int pos_bit);

/**
 * @brief Muestra en pantalla los bits entre el pos_ms bit más significativo 
 * (inclusive) y el pos_ls bit menos significativo (inclusive) de la palabra de 
 * entrada buffer en forma binaria. Imprimirá pos_ms − pos_ls+1 bits sin 
 * espacios entre ellos teniendo a la izquierda el bit más significativo y con 
 * un salto de linea final ("\n"). Se debe suponer que 31 ≥ pos_ms ≥ pos_ls ≥ 0,
 * en caso contrario el comportamiento es indeterminado.
 * 
 * Ejemplo:
 * @code
 * ver_binario(3, 0, 3)
 * @endcode
 * Imprime en pantalla "0011".
 *
 * @param buffer Entero sin signo a imprimir en pantalla.
 * @param pos_ls Posición mínima a mostrar.
 * @param pos_ms Posición máxima a mostrar.
 * @return Nulo.
 */
void ver_binario(unsigned int buffer, int pos_ls, int pos_ms);

/**
 * @brief Establece el bit pos de buffer a 0 o a 1 según el valor del parámetro
 * valor y devuelve el buffer con ese bit seteado al valor correspondiente. 
 * Se supone que valor es 0 o 1, en caso contrario el comportamiento 
 * es indeterminado.
 * 
 * Ejemplo:
 * @code
 * set_bit(0, 0, 1)
 * @endcode
 * Convierte el número 0 en 1.
 *
 * @param buffer Entero sin signo al que se le quiere modificar un bit.
 * @param pos_ls Posición  del bit que se quiere modificar.
 * @param pos_ms Valor que se le quiere fijar al bit pos. 
 * Se supone que valor es 0 o 1.
 * @return Entero sin signo igual a buffer, con el bit pos modificado 
 * con el valor de valor
 */
unsigned int set_bit(unsigned int buffer, int pos, int valor);

unsigned int crear_mascara(int pos_ls, int pos_ms);

unsigned int concatena(unsigned int buffer_ms, unsigned int buffer_ls, int num_bits_ls);

unsigned int espejar(unsigned int buffer, int num_bits);

int paridad(unsigned int buffer);

void ver_clave(Clave_t clave);

Clave_t rotar_clave(Clave_t clave, unsigned int nrot);

unsigned int encriptar(unsigned int buffer, Clave_t clave);

unsigned int permutar_bits(unsigned int buffer, int pos_a, int pos_b);

int power(int base, unsigned int exponent);


