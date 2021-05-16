#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#define MAXLINE 1024
int fgetline(FILE *fp, char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getc(fp)) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}
void *malloc_or_exit(size_t size)
{
    void *p = malloc(size);
    if (p == NULL)
    {
        error(EXIT_FAILURE, errno, "malloc error - exit\n");
    }
    return p;
}
void *realloc_or_exit(void *ptr, size_t size)
{
    void *p = realloc(ptr, size);
    if (p == NULL)
    {
        error(EXIT_FAILURE, errno, "realloc error - exit\n");
    }
}
int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        return 0;
    }
    int num_argv;
    FILE *fprog;
    char *prog;
    char *lprog;
    int line_counter;
    int max_line_default = 10;
    char line[MAXLINE];
    int pos, lr, len, used;
    int linesNumber;
    char *last_lines[linesNumber];
    for (int i = 0; i < linesNumber; i++)
    {
        last_lines[i] = NULL;
    }
    if (argv[1][0] != '-')
    {
        num_argv = 1;
        linesNumber = max_line_default;
    }
    else
    {
         num_argv = 2;
         linesNumber = atoi(argv[1] + 1);
    }
    for (; num_argv < argc; num_argv++)
    {
        prog = (const char *)argv[num_argv];
        if ((fprog = fopen(prog, "r")) == NULL)
        {
            error(1, errno, "can't open file '%s'", prog);
        }
    }
    for (pos = lr = 0; (len = fgetline(fprog, line, MAXLINE)) > 0; pos = (pos + 1) % linesNumber, lr++)
    {
        free(last_lines[pos]);
        last_lines[pos] = malloc_or_exit(len + 1);
        strcpy(last_lines[pos], line);
    }
    if (lr > linesNumber)
    {
        used = linesNumber;
    }
    else
    {
        used = lr;
    }
    for (int j = 0; j < used; j++)
    {
        pos = (pos + linesNumber - 1) % linesNumber;
    }
    while (used-- > 0)
    {
        printf("%s", last_lines[pos]);
        pos = (pos + 1) % linesNumber;
    }
}