
typedef struct Clave_t {
	unsigned int valor;
	int largo;
} Clave_t;

int bit(unsigned int buffer, int pos_bit);

void ver_binario(unsigned int buffer, int pos_ls, int pos_ms);

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


