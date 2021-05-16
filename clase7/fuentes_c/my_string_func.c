/********************************************************************************
 *
 * funciones my_strXXX, hacen lo mismo que las de la biblioteca estándar
 * sirven para practicar uso de punteros
 * para fines didácticos, también se muestran las versiones que están
 * programadas usando arrays de char
 *
 *******************************************************************************/

int
my_strlen_a(char s[])   // strlen, versión array
{
    int len;

    for (len = 0; s[len] != '\0'; len++)
        ; // solamente itera hasta encontrar \0
    return len;
}

int
my_strlen(char *s)      // strlen, versión punteros
{
    char *p;

    for (p = s; *p != '\0'; p++)
        ; // solamente itera hasta encontrar \0
    return p - s;
}

void
my_strcpy_a(char s1[], char s2[])       // strcpy, versión array
{
    int i;

    for (i = 0; s2[i] != '\0'; i++) {
        s1[i] = s2[i];  // copia cada carácter antes de \0
    }
    s1[i] = s2[i];      // al final copia el \0
}

void
my_strcpy(char *s1, char *s2)           // strcpy, versión punteros
{
    while ( (*s1++ = *s2++) != '\0')    // la comparación con \0 podría omitirse
        ;                               // el while copia todos los caracteres incluso el \0
}

int
my_strcmp_a(char s1[], char s2[])       // strcmp, versión array, versión libro K&R
{
    int i;

    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') {
            return 0;
        }
    }
    return s1[i] - s2[i];
}

int
my_strcmp(char *s1, char *s2)           // strcmp, versión punteros, versión libro K&R
{
    for ( ; *s1 == *s2; s1++, s2++) {
        if (*s1 == '\0') {
            return 0;
        }
    }
    return *s1 - *s2;
}

#define is_upper(c) (c >= 'A' && c <= 'Z')  // funciona solo caracteres ASCII
#define to_lower(c) (is_upper(c) ? (c - 'A' + 'a') : c)

int
my_strcasecmp_a(char s1[], char s2[])   // strcasecmp, versión array
{
    int i;
    char c1, c2;

    for (i = 0; s1[i] != '\0'; i++) {
        c1 = to_lower(s1[i]);
        c2 = to_lower(s2[i]);

        if (c1 != c2)
            break;
    }
    // si acá s1[i] == 0, si s2[i] == 0 también, serán iguales
    return to_lower(s1[i]) - to_lower(s2[i]);
}

int
my_strcasecmp(char *s1, char *s2)       // strcasecmp, versión punteros
{
    char c1, c2;

    for ( ; *s1 != '\0'; s1++, s2++) {
        c1 = to_lower(*s1);
        c2 = to_lower(*s2);

        if (c1 != c2)
            break;
    }
    // si acá *s1 == 0, si *s2 == 0 también, serán iguales
    return to_lower(*s1) - to_lower(*s2);
}

char *
my_strcat(char *dest, char *src)
{
    // agrega src al final de dest, no controla capacidad de dest

    char *p;

    for (p=dest; *p != '\0'; p++) { // busca el final de dest
        ;
    }
    my_strcpy(p, src);

    return dest;
}


int
my_strend(char *src, char *end)
{
    // retorna 1 si el string end está al final del string src, 0 en caso contrario.

    int len_src, len_end;

    len_src = my_strlen(src);
    len_end = my_strlen(end);

    if (len_src < len_end) {
        return 0;   // control para evitar buffer overflow
    }
    return my_strcmp(end, src + len_src - len_end) == 0;
}

char *
my_strncpy(char *dest, char *src, int n)
{
    // idem strcpy pero copia como máximo n bytes
    // NOTA: si copia n bytes, no asegura haber copiado \0 final
    //       si copia menos de n, luego rellena con \0
    // retorna dest
    char *s1, *s2;

    s1 = dest;
    s2 = src;
    while (n-- > 0 && (*s1++ = *s2++) != '\0')
        ;
    while (n-- > 0)
        *s1++ = '\0';
    return dest;
}

char *
my_strncat(char *dest, char *src, int n)
{
    // agrega src al final de dest, no controla capacidad de dest
    // NOTA: si copia n bytes, no asegura haber copiado \0 final
    //       si copia menos de n, luego rellena con \0

    char *p;

    for (p=dest; *p != '\0'; p++) { // busca el final de dest
        ;
    }
    my_strncpy(p, src, n);

    return dest;
}

int
my_strncmp(char *s1, char *s2, int n)
{
    for ( ; n > 0 && *s1 == *s2; n--, s1++, s2++) {
        if (*s1 == '\0') {
            return 0;
        }
    }
    return (n > 0) ? *s1 - *s2 : 0;
}

/*
char * my_index(char *s, int c);
char * my_rindex(char *s, int c);
char * my_strstr(char *haystack, char *needle);

*/
