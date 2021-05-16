# La variable CFLAGS indica las banderas para el compilador C
CFLAGS=-Wall -Wextra -std=gnu99 -ggdb
# Este sería el ejecutable, sus dependencias son los .o

anagramas-hash:		hash.o fgetword-normalizada.o wrappers.o anagramas-hash.o
# make sabe que cada .o depende del .c correspondiente
# Solo se agrega la dependencia al .h
anagramas-hash.o:    anagramas-hash.h wrappers.h