/*
 * Escribe un histograma vertical de largo de palabras
 * Se considera una palabra a una secuencia de bytes separada por espacios
 *
 */

#include <stdio.h>

#define IN       1      // dentro de una palabra
#define OUT      0      // fuera de una palabra
#define MAXL    12      // largo máximo de una palabra para el histograma
#define HEIGHT  20      // Altura del histograma vertical

int
main(void)
{
    int c;              // el valor de retorno de getchar() es un int !!!
    int state;          // estado dentro o fuera de una palabra (IN/OUT)
    int wordlen;        // largo de la palabra corriente
    int wordlengths[MAXL];   // array que aloja la cantidad de palabras con ese largo
                        // se usará el índice 0 (cero) para palabras más largas que MAXL
    int maxwordlength;  // mayor valor del array anterior (para calcular 'altura' del histog)
    int i, h;
    double factor;      // para aplastar las cantidades si son mayores que HEIGHT

    /********************************************************************************
     * Inicialización
     *
     *******************************************************************************/
    for (i=0; i<MAXL; i++) {
        wordlengths[i] = 0;   // inicialización del array explícitamente
    }
    maxwordlength = 0;

    state = OUT;        // estado inicial es OUT

    /********************************************************************************
     * Loop que lee la entrada y carga array wordlengths y variable maxwordlength
     *
     *******************************************************************************/
    while ( (c=getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                if (wordlen < MAXL) {   // chequeo largo de la palabra leída
                    i = wordlen;
                } else {
                    i = 0;              // palabras muy largas a la posición 0
                }
                if (++wordlengths[i] > maxwordlength) {
                    maxwordlength = wordlengths[i];
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

    /********************************************************************************
     * Escritura del histograma vertical
     *
     *******************************************************************************/

    factor = maxwordlength <= HEIGHT ? 1.0 : (float) maxwordlength / (float) HEIGHT;

    for (h = maxwordlength / factor; h > 0; h--) { // el histograma se arranca "desde arriba"
        printf("%8d ", (int) (h * factor));        // rótulo de la escala vertical
        for (i=1; i<MAXL; i++) {    // veo cuál frecuencia es > maxwordlength
            printf(" %2c ", wordlengths[i] >= h * factor ? '*' : ' ');
        }
        printf(" %2c\n", wordlengths[0] >= h * factor ? '*' : ' ');
    }

    // Primera línea (la de más abajo)
    printf("%8s ", "Largos");
    for (i=1; i<MAXL; i++) {
        printf(" %2d ", i);
    }
    printf(" >%d\n", MAXL-1);

    return 0;
}
