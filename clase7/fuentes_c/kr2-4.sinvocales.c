/*
 * 0xx-sinvocales.c
 * Programa que elimina vocales de la entrada
 * Usa una función squeeze(char s1[], char s2[])
 *
*/

#include <stdio.h>
#define MAXLINE 1024

int
getline(char s[], int lim)      // lee una línea de stdin, retorna el largo
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


int
found(char c, char s[])         // retorna 1 si c está en s, 0 si no
{
    int i;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}


void
squeeze(char s1[], char s2[])   // elimina de s1 los caracteres de s2
{
    int i, j;

    for (i = j = 0; s1[i] != '\0'; i++) {
        if (!found(s1[i], s2)) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

int
main(void)
{
    char vocales[] = "AEIOUaeiou";
    char line[MAXLINE];

    while (getline(line, MAXLINE) > 0) {
        squeeze(line, vocales);
        printf("%s", line);
    }
    return 0;
}
