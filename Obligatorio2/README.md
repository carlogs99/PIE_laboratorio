# Autotest obligatorio 2 - 2022

Antes de poder compilar el autotest, debe colocar en un mismo directorio todos los archivos incluidos en el .zip que descargó. Además, debe colocar en el directorio los siguientes archivos:

- bits.c
- bits.h
- imagen.c
- imagen.h
- obligatorio2.c

## Compilar autotest

Abra una terminal en el directorio donde colocó todos los archivos y corra el comando `make -f Makefile_autotest_2`. El Makefile_autotest_2 proporcionado genera su ejecutable obligatorio2 y un ejecutable test_funciones. Recuerde volver a correr el comando `make -f Makefile_autotest_2` cada vez que modifique su entrega.

## Test de funciones

El script *tests_funciones.sh* llama a las funciones varias veces con distintas opciones, resumiendo los resultados al final.

Para correrlo utilice el siguiente comando:
```bash
bash tests_funciones.sh
```

## Test linea de comandos

El script *tests_linea_de_comandos.sh* llama a su ejecutable de obligatorio2 varias veces con distintas opciones.

Para correrlo utilice el siguiente comando:
```bash
bash tests_linea_de_comandos.sh
```

En cada llamada el script hace el chequeo de memoria con valgrind y en caso de haber algún error lo reporta en un log dentro del directorio logs_linea_de_comandos/.

Además, guarda la imagen resultante en el directorio imagenes/resultados/ y la compara con el resultado esperado, que se encuentra en imagenes/referencias/.

En caso de encontrar diferencias entre la imagen resultante y su referencia, se hace un reporte en el directorio logs_linea_de_comandos/.

Al final del script se borran todos los logs que no contienen errores y se muestra un resumen de los resultados obtenidos.

### Resumen

El resumen de resultados es una tabla con tres columnas: subcomando, errores de memoria, y errores de resultado.

La columna de errores de memoria indica cuantos de los tests con valgrind dieron error para un subcomando dado, sobre el total de tests realizados. Por ejemplo, si la columna muestra 2 / 4, esto significa que de 4 veces que se testeó el subcomando, 2 tuvieron errores de memoria.

La columna de errores de resultado indica cuantas veces las imagenes resultantes de llamar al subcomando fueron diferentes a la imagen de referencia. Además, si por alguna razón no se llego a generar una imagen al correr el subcomando (e.g. el programa dio segmentation fault antes de escribir la imagen), esto también será detectado como un error de resultado.

A modo de ejemplo, imagine que se corre el comando filtrar_sepia 4 veces, de las cuales dos no llegan a generar una imagen, una genera una imagen distinta a la esperada, y otra genera el resultado correcto. En ese caso el resumen mostrará 3 / 4 en el campo de errores de resultado de filtrar_sepia.
