/*
 * Escribe un histograma horizontal de largo de palabras
 * Se considera una palabra a una secuencia de bytes separada por espacios
 *
 */

#include <stdio.h>

#define IN   1          // dentro de una palabra
#define OUT  0          // fuera de una palabra
#define MAXL 12         // largo máximo de una palabra para el histograma

int
main(void)
{
    int c;              // el valor de retorno de getchar() es un int !!!
    int state;          // estado dentro o fuera de una palabra (IN/OUT)
    int wordlen;        // largo de la palabra corriente
    int wordlengths[MAXL];   // array que aloja la cantidad de palabras con ese largo
                        // se usará el índice 0 (cero) para palabras más largas que MAXL
    int i, j;

    for (i=0; i<MAXL; i++) {
        wordlengths[i] = 0;   // inicialización del array explícitamente
    }

    state = OUT;        // estado inicial es OUT

    while ( (c=getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                if (wordlen < MAXL) {   // chequeo largo de la palabra leída
                    wordlengths[wordlen]++;
                } else {
                    wordlengths[0]++;   // palabras muy largas a la posición 0
                }
            }
            state = OUT;
        } else if (state == OUT) {  // arranca la palabra
            state = IN;
            wordlen = 1;
        } else {                    // en medio de una palabra
            wordlen++;
        }
    }

    for (i=1; i<MAXL; i++) {
        printf("Largo = %3d: ", i);
        for (j=0; j<wordlengths[i]; j++) {
            putchar('*');
        }
        putchar('\n');
    }
    printf("Largo > %3d: ", MAXL - 1);
    for (j=0; j<wordlengths[0]; j++) {
        putchar('*');
    }
    putchar('\n');

    return 0;
}
