/*
 * Programa main para probar str
 *
 * El programa recibe dos argumentos, pajar y aguja
 * Escribe por stdout la salida
 *
 */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    extern int my_strstr(char *pajar, char *aguja);

    char *pajar, *aguja;

    if (argc != 3) {
        fprintf(stderr, "Error: debe pasar dos y solo dos argumentos\nUso: %s pajar aguja\n", argv[0]);
        exit(1);
    }

    pajar = argv[1];
    aguja = argv[2];

    printf("El resultado de buscar la aguja '%s' en el pajar '%s' es %d.\n",
            aguja, pajar, my_strstr(pajar, aguja));
    exit(0);
}
