
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
 * para sus nuevos pixeles. NO se debe inicializar los pixeles con ningun valor 
 * en particular, basta con dejar el valor que por defecto asigne malloc.
 *
 * @param pin Puntero a imagen a inicializar.
 * @param filas Cantidad de filas de la imagen.
 * @param columnas Cantidad de columnas de la imagen.
 *
 * @return Devuelve un valor de tipo CodigoError_t segun el caso.
 */
CodigoError_t inicializar_imagen(Imagen_t* pin, int filas, int columnas);

CodigoError_t destruir_imagen(Imagen_t* pin);

CodigoError_t duplicar_imagen(const Imagen_t* pin, Imagen_t* pout);

CodigoError_t leer_imagen(const char* ruta_imagen, Imagen_t*pin);

CodigoError_t escribir_imagen(const Imagen_t* pin, const char* ruta_imagen, 
FormatoPPM_t formato);

CodigoError_t filtrar_sepia(const Imagen_t* pin, Imagen_t* pout);

CodigoError_t generar_cripto_imagen(Imagen_t* pcriptoim, int filas, int columnas,
int min_largo_clave);

CodigoError_t validar_cripto_imagen(const Imagen_t* pcriptoim);

CodigoError_t encriptar_imagen(const Imagen_t* pin, const Imagen_t* prcriptoim,
Imagen_t* pout);



