
/**
 * @file imagen.h
 * @author Carlos Gruss
 * @date 28 may 2022
 * @brief Header biblioteca de manejo imagenes y encriptacion 
 * para Obligatorio 2 PIE.
 */

typedef unsigned int pixel_t;

typedef struct imagen {
	int filas;
	int columnas;
	pixel_t** pixeles;
} Imagen_t;

typedef enum formato_ppm{PLANO, NO_PLANO} FormatoPPM_t;

typedef enum codigo_error{OK, PPM_ARCHIVO_INEXISTENTE, PPM_ERROR_LECTURA,
PPM_ENCABEZADO_INVALIDO, PPM_DATOS_INVALIDOS, PPM_ERROR_ESCRITURA, 
PPM_CRIPTO_NO_VALIDA, ERROR} CodigoError_t;

/**
 * @brief Inicializa los datos de la imagen apuntada por pin y reserva memoria 
 * para sus nuevos pixeles. NO inicializa los pixeles con ningun valor 
 * en particular, deja el valor que por defecto asigne malloc.
 *
 * @param pin Puntero a imagen a inicializar.
 * @param filas Cantidad de filas de la imagen.
 * @param columnas Cantidad de columnas de la imagen.
 *
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t inicializar_imagen(Imagen_t* pin, int filas, int columnas);

/**
 * @brief Libera la memoria asociada a los pixeles de la imagen apuntada por pin
 * y pone todos sus atributos en 0.
 *
 * Se asume que pin se encuentra inicializada al pasarse a la funcion.
 *
 * @param pin Puntero a imagen a destruir.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t destruir_imagen(Imagen_t* pin);

/**
 * @brief Copia los atributos filas y columnas de la imagen apuntada por pin 
 * en la imagen apuntada por pout. Ademas reserva la memoria para los pixeles 
 * de pout. NO se debe inicializar los pixeles con ningun valor en particular.
 *
 * Se asume que previo a la llamada de esta funcion, la imagen apuntada por pout 
 * no tiene reservada memoria para sus pixeles, es decir, no se debe llamar 
 * a destruir imagen.
 *
 * @param pin  Puntero a imagen fuente que se desea duplicar.
 * @param pout Puntero a imagen que quedara inicializada.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t duplicar_imagen(const Imagen_t* pin, Imagen_t* pout);

/**
 * @brief Lee el contenido del archivo ubicado en ruta imagen y lo guarda en 
 * la imagen apuntada por pin. Se asume que no se ha inicializado pin.
 * Se implementa la lectura de imagenes en formatos PPM y PPM plano.
 *
 * @param ruta_imagen Ruta desde donde leer la imagen.
 * @param pin Puntero a tipo Imagen_t, en el que cargar el contenido leido.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t leer_imagen(const char* ruta_imagen, Imagen_t* pin);

/**
 * Guarda el contenido de la imagen pin en el archivo especificado 
 * por ruta, formatos PPM y PPM plano.
 * Asume que pin esta inicializada previo a la llamada de la funcion.
 *
 * @param pin Puntero a imagen que se desea escribir a archivo.
 * @param ruta_imagen Ruta en la que se desea escribir el archivo.
 * @param formato Formato de escritura (PPM binario o PPM plano).
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t escribir_imagen(const Imagen_t* pin, const char* ruta_imagen, 
FormatoPPM_t formato);

/**
 * @brief Se asume que pin esta inicializada al pasarse a la funcion, 
 * mientras que pout no lo esta.
 * Aplica un filtro sepia sobre la imagen de entrada apuntada por pin y guarda 
 * el resultado en la imagen apuntada por pout. La reserva de memoria para los
 * pixeles de pout se realiza dentro de la funcion.
 *
 * @param pin Puntero conteniendo la imagen a filtrar.
 * @param pout Puntero conteniendo el resultado de aplicar el filtro sepia.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t filtrar_sepia(const Imagen_t* pin, Imagen_t* pout);

/**
 * @brief Inicializa la imagen apuntada por pcriptoim reservando memoria para 
 * sus pixeles, y los rellena con claves de Vigenere aleatorias cuyo largo minimo 
 * es el especificado por min_largo_clave y cuyo largo maximo es 19.
 * Se asume que pcriptoim no esta inicializada previo a la llamada de la funcion. 
 * Tambien se asume que 1 ≤ min_largo_clave ≤ 19.
 * 
 * @param pcriptoim Puntero a imagen en el que generar la cripto-imagen.
 * @param filas Numero de filas de la cripto-imagen deseada.
 * @param columnas Numero de columnas de la cripto-imagen deseada.
 * @param min_largo_clave Largo minimo de cada clave de Vig`enere.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t generar_cripto_imagen(Imagen_t* pcriptoim, int filas, int columnas,
int min_largo_clave);

/**
 * @brief Evalua si un puntero a imagen es una cripto-imagen valida para el 
 * algoritmo de  encriptacion, es decir todos sus largos son mayores o iguales 
 * a 1 y menores o iguales a 19. En caso de serlo retorna OK, y en caso 
 * contrario retorna PPM_CRIPTO_NO_VALIDA.
 * Se asume que pcriptoim esta inicializada previo a la llamada de la funcion.
 * 
 * @param pcriptoim Puntero a imagen con la candidata a cripto-imagen a evaluar.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t validar_cripto_imagen(const Imagen_t* pcriptoim);

/**
 * @brief Aplica una encriptacion de Vigenere con una clave distinta para cada pixel 
 * de la imagen apuntada por pin de acuerdo al contenido de cada pixel de 
 * pcriptoim. El resultado se guarda en la imagen apuntada por pout. 
 * La reserva de memoria para los pixeles de pout se debe realizar dentro de 
 * la funcion. Se asume que pin y pcriptoim estan inicializadas y que pout no 
 * lo esta al llamar la funcion. Tambien se asume que pcriptoim siempre seguira 
 * el formato de cripto-imagen indicado (largo de clave menor o igual a 19).
 * 
 * @param pin Puntero conteniendo la imagen a encriptar.
 * @param pcriptoim Puntero a la cripto-imagen utilizada para encriptar.
 * @param pout Puntero conteniendo el resultado de encriptar.
 * 
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t encriptar_imagen(const Imagen_t* pin, const Imagen_t* pcriptoim,
Imagen_t* pout);

/**
 * Devuelve el minimo de dos numeros enteros.
 *
 * @param a Primer numero.
 * @param b Segundo numero.
 * 
 * @return Minimo entre a y b.
 */
pixel_t min(unsigned int a, unsigned int b);
