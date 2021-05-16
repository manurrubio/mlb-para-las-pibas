/********************************************************************************
 * getch y ungetch - versión del libro K&R sección 4.3
 *******************************************************************************/
#include <stdio.h>

#define BUFSIZE 100

static char buf[BUFSIZE];           // buffer for ungetch
static int bufp = 0;                // next free position in buf

int
getch(void)                         // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void
ungetch(int c)                      // push character back to input
{
    if (bufp >= BUFSIZE) {
        fprintf(stderr, "ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
