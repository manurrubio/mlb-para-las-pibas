#include <stdio.h>
#include <ctype.h>

extern int getch(void);
extern void ungetch(int c);

int getword(char *word, int lim)
{
    // getword: get next word or character from input
    int c;
    char *w = word;

    while (isspace(c = getch())) {
        ;
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim> 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}
