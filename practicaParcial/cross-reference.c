/*Como alternativa(s) al fold, mejorar los programas de la semana 4, para que acepten una lista de archivos opcionales.
Por ejemplo:./count-words arch1.txt arch2.txt
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#define MAXWORD 100
#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)
int line = 1;
struct tnode
{
    char *word; //Puntero al texto
    char lines[MAXWORD];
    struct tnode *left; //Puntero a hijo izquierdo
    struct tnode *right;  //Puntero a hijo derecho
};
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(FILE *, char *, int);
int main(int argc, char const *argv[]){
    if (argc == 1)
    {
        return 0;
    }
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
                root = addtree(root, word);
            }
        }
    }
    treeprint(root);
    return 0;
}
struct tnode *talloc(void);
char *my_strdup(char *);
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    char lin[5];
    sprintf(lin,"%d", line);
    if(p == NULL)
    {
        p = talloc();
        p->word = my_strdup(w);
        strcat(p->lines,lin);
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        strcat(p->lines,", ");
        strcat(p->lines,lin);
    }
    else if(cond < 0){
        p->left = addtree(p->left, w);
    }
    else
    {
        p->right = addtree(p->right, w);
    }
    return p;  
}
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%s [%s]\n", p->word, p->lines);
        treeprint(p->right);
    }
}
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}
char *my_strdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p; 
}
int getword(FILE *fp, char *word, int lim){
    int c;
    char *w = word; //Apunta al primer elemento de word, es similar a hacer *w = &word[0] 
    while (isspace(c = getc(fp)))
    {
        if (c == '\n'){
            line++;
        }
    }
    if (c != EOF){
        *w++ = c;  //Aumento la direccion de memoria de w y en esta guardo c, por ej si w apauntaba a word[0] ahora apunta a word[1] y word[1] = c
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