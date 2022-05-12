
# Define una constante que tiene las banderas de compilacion
COMOPT=-Wall -std=c99 -ggdb -Werror
### -Wall : muestra todos los warnings
### -std = c99 : utiliza el estandar c99
### -ggbd : permite utilizar los ejecutables con el debugger
### -Werror : todos los warnings son errores

# Genera el ejecutable
obligatorio1: obligatorio1.o libbits.a
	gcc $(COMOPT) -o obligatorio1 obligatorio1.o -L./ -lbits

# Compila bits .c a codigo objeto
bits.o: bits.c
	gcc $(COMOPT) -o bits.o -c bits.c

# Compila obligatorio1 .c a codigo objeto
obligatorio1.o: obligatorio1.c
	gcc $(COMOPT) -o obligatorio1.o -c obligatorio1.c

# Crea la biblioteca libbits
libbits.a: bits.o
	ar rcs libbits.a bits.o
	
# Borra los archivos (si existen ) que son producto de la compilacion
clean:
	rm -f *.a *.o obligatorio1
