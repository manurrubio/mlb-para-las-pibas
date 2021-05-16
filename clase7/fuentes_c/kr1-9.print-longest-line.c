/*
 * print-longest-line.c
 *
 * Programa que escribe la línea más larga de la entrada
 * Versión del libro K&R, sección 1.9
 *
 * Usa la función getline que lee una línea usando getchar, devuelve el largo
 * Usa la función copy que copia un string de caracteres en otro
 *
*/

#include <stdio.h>
#define MAXLINE 1024        // tamaño máximo de una línea de entrada

int
my_getline(char s[], int lim)      // lee una línea de stdin, retorna el largo
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

void
copy(char to[], char from[])
{
    // copia el string 'from' al 'to', supone que hay espacio suficiente
    int i;

    i = 0;
    while ( (to[i] = from[i]) != '\0') {
        ++i;
    }
}


int
main(void)
{
    int len;                // tamaño de la línea corriente
    int max;                // tamaño de la línea más larga hasta el momento
    char line[MAXLINE];     // línea corriente
    char longest[MAXLINE];  // línea más larga se va almacenando acá

    max = 0;
    while ( (len = my_getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {          // hubo una línea de entrada al menos
        printf("%s", longest);
    }
    return 0;
}
