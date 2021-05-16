#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key
{
    char *word;
    int count;
} keytab[] = {"auto", 0, "break", 0, "case", 0};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))
#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)


int getword(char *, int);
int binsearch(char *, struct key *, int);

//PUNTEROS: Se incializan int *w; ahora w apunta a una direccion de memoria, haciendo *w accedemos a lo que hay adentro de esa direccion, ej *w = 1

int main(){
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF){
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

int getword(char *word, int lim){
    int c;
    char *w = word; //Apunta al primer elemento de word, es similar a hacer *w = &word[0] 

    while (isspace(c = getch()))
        ;
    if (c != EOF){
        *w++ = c;  //Aumento la direccion de memoria de w y en esta guardo c, por ej si w apauntaba a word[0] ahora apunta a word[1] y word[1] = c
    }
    if(!isalpha(c)){
        w = '\0';
        return c;
    }
    for( ; --lim > 0; w++){
        if(!isalnum(w = getch())){
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}