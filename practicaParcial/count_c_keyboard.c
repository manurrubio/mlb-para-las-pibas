/*  Como alternativa(s) al fold, mejorar los programas de la semana 4, para que acepten una lista de archivos opcionales.
Por ejemplo:./count-words arch1.txt arch2.txt
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
struct key
{
    char *word;
    int count;
} keytab[] = {"auto", 0, "break", 0, "case", 0};
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))
#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)
int getword(FILE *, char *, int);
int binsearch(char *, struct key *, int);
int main(int argc, char const *argv[]){
    if (argc == 1)
    {
        return 0;
    }
    int n;
    struct tnode *root;
    char word[MAXWORD];
    int num_argv;
    FILE *fprog;
    const char *prog;
    root = NULL;
    for (num_argv = 1; num_argv < argc; num_argv++){
        prog = (const char *)argv[num_argv];
        if ((fprog = fopen(prog, "r")) == NULL)
        {
            error(1, errno, "can't open file '%s'", prog);
        }
        while(getword(fprog, word, MAXWORD) != EOF){
            if(isalpha(word[0])){
                if((n = binsearch(word, keytab, NKEYS)) >= 0){
                    keytab[n].count++;
                }
            }   
        }
        for(n = 0; n < NKEYS; n++){
            if(keytab[n].count > 0){
                printf("%4d %s \n", keytab[n].count, keytab[n].word);
            }
        }
    }
    return 0;
}
int binsearch(char *word, struct key tab[], int n){
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high){
        mid = (low + high)/2;
        if ((cond = strcmp(word, tab[mid].word)) < 0){
            high = mid - 1;
        }
        else if(cond > 0){
            low = mid + 1;
        }
        else{
            return mid;
        }
    }
    return -1;
}
int getword(FILE *fp, char *word, int lim){
    int c;
    char *w = word;
    while (isspace(c = getc(fp)))
        ;
    if (c != EOF){
        *w++ = c;
    }
    if(!isalpha(c)){
        *w = '\0';
        return c;
    }
    for( ; --lim > 0; w++){
        if(!isalnum(*w = getc(fp))){
            ungetc(*w, fp);
            break;
        }
    }
    *w = '\0';
    return word[0];
}