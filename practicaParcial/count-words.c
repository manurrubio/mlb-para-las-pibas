#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#define getch() getchar()
#define ungetch(c) ungetc(c, stdin)
#define MAXWORD 100
//struct tnode *addtree(struct tnode *,char *);
//void treeprint(struct tnode *);
//int getword(char *,int);
struct tnode
{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
int getword(FILE *fp,char *word, int lim)
{
    int c;
    char *w = word;
    while (isspace(c = getc(fp)))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
    {
        if (!isalnum(*w = getc(fp)))
        {
            ungetc(*w, fp);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}
char *my_strdup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p;
}
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = my_strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        p->count++;
    }
    else if (cond < 0)
    {
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
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}
/* conteo de frecuencia de palabras */
main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        return 0;
    }
    struct tnode *root;
    char word[MAXWORD];
    int num_argv;
    FILE *fprog;
    char *prog;
    root = NULL;
    for (num_argv = 1; num_argv < argc; num_argv++)
    {
        prog = (const char *)argv[num_argv];
        if ((fprog = fopen(prog, "r")) == NULL)
        {
            error(1, errno, "can't open file '%s'", prog);
        }
        while (getword(fprog,word, MAXWORD) != EOF)
        {
            if (isalpha(word[0]))
            {
                root = addtree(root, word);
            }
        }
    }
    treeprint(root);
    return 0;
}