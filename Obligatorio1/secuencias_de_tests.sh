# Secuencia de llamadas a ./test_obligatorio1 para testear
# todas las funciones

printf "Borrando log de errores...\n\n" && rm -f errores.txt

./test_obligatorio1 bit 01010 3;
./test_obligatorio1 bit 01010 0;
./test_obligatorio1 bit 01010 31;
./test_obligatorio1 bit 10000001 0;
./test_obligatorio1 bit 10000000000000000000000000000000 31;
./test_obligatorio1 bit 10000000000000010000000000000000 16;

./test_obligatorio1 ver_binario 0 0 0;
./test_obligatorio1 ver_binario 1 0 0;
./test_obligatorio1 ver_binario 01010  1 3;
./test_obligatorio1 ver_binario 10000000000000010000000000000000 0 31;

./test_obligatorio1 set_bit 101010 0 1;
./test_obligatorio1 set_bit 101010 0 0;
./test_obligatorio1 set_bit 101010 31 1;
./test_obligatorio1 set_bit 101010 31 0;
./test_obligatorio1 set_bit 101010 2 1;
./test_obligatorio1 set_bit 101010 3 0;

./test_obligatorio1 crear_mascara 0 0;
./test_obligatorio1 crear_mascara 0 31;
./test_obligatorio1 crear_mascara 31 31;
./test_obligatorio1 crear_mascara 1 24;
./test_obligatorio1 crear_mascara 2 2;

./test_obligatorio1 concatena 1111 0000 4;
./test_obligatorio1 concatena 1111 0000 2;
./test_obligatorio1 concatena 0000 1111 4;
./test_obligatorio1 concatena 0000 1111 2;
./test_obligatorio1 concatena 1010101010101010 0101010101010101 16;
./test_obligatorio1 concatena 111111111111111111 0101010101010101 14;

./test_obligatorio1 espejar 110 2;
./test_obligatorio1 espejar 110 3;
./test_obligatorio1 espejar 110 4;
./test_obligatorio1 espejar 110 1;
./test_obligatorio1 espejar 10000000000000000000000000000001 2;
./test_obligatorio1 espejar 10000000000000000000000000000000 32;
./test_obligatorio1 espejar 10000000000000000000000000000000 1;

./test_obligatorio1 paridad 0;
./test_obligatorio1 paridad 1;
./test_obligatorio1 paridad 100000001;
./test_obligatorio1 paridad 10000000000000000000000000000001;
./test_obligatorio1 paridad 10000000000000010000000000000001;
./test_obligatorio1 paridad 111111111111111;

./test_obligatorio1 ver_clave 0101010 7;
./test_obligatorio1 ver_clave 0 1;
./test_obligatorio1 ver_clave 1 1;
./test_obligatorio1 ver_clave 11111111111111111111111111111111 32;
./test_obligatorio1 ver_clave 00000000000000000000000000000000 32;

./test_obligatorio1 rotar_clave 0101010 7  1;
./test_obligatorio1 rotar_clave 0101010 7  8;
./test_obligatorio1 rotar_clave 0101010 7  32;
./test_obligatorio1 rotar_clave 00001 5  4;
./test_obligatorio1 rotar_clave 11111 5  5;

./test_obligatorio1 encriptar 11111111111111111111111111111111 0101010 7;
./test_obligatorio1 encriptar 00000000000000000000000000000000 0101010 7;
./test_obligatorio1 encriptar 100 0101010 7;
./test_obligatorio1 encriptar 100 10100101001010010100 20;
./test_obligatorio1 encriptar 11111111111111110000000000000000 10100101001010010100 20;
./test_obligatorio1 encriptar 10101010 1 1;
./test_obligatorio1 encriptar 10101010 0 1;


if [ -s errores.txt ]; then # Verifica si el archivo NO es vacio
        # si no es vacio, hay errores
        printf "\x1B[31mHay errores.\x1B[0m\n";
        printf "Por más información consultar errores.txt\n\n"
else
        # si es vacio, entonces no hay errores y se borra el archivo
        printf "\x1B[32mNo se detectaron errores.\x1B[0m\n\n";
        rm errores.txt;
fi