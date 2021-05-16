#include <stdlib.h>

#include <stdio.h>

#include <error.h>

#include <errno.h>

#include <string.h>

#define MAXLINE 1000

int main(int argc, char const *argv[])

{

    int num_argv;

    FILE *fprog;

    char *prog;

    char *lprog;

    int line;

    int max_line_default = 10;

    char line1[MAXLINE];

    if (argc > 1 && strcmp(argv[1], "-n") == 0)
    {

        for (num_argv = 2; num_argv < argc; num_argv++)

        {

            prog = (const char *)argv[num_argv];

            if ((fprog = fopen(prog, "r")) == NULL)

            {

                error(1, errno, "can't open file '%s'", prog);
            }

            for (line = 1; line <= *argv[1]; line++)

            {

                lprog = fgets(line1, MAXLINE, fprog);

                printf("%s", lprog);
            }
        }
    }
    else
    {

        for (num_argv = 1; num_argv < argc; num_argv++)

        {

            prog = (const char *)argv[num_argv];

            if ((fprog = fopen(prog, "r")) == NULL)

            {

                error(1, errno, "can't open file '%s'", prog);
            }

            for (line = 1; line <= max_line_default; line++)

            {

                lprog = fgets(line1, MAXLINE, fprog);

                printf("%s", lprog);
            }
        }
    }

    if (ferror(stdout))

    {
        fclose(fprog1);

        fclose(fprog2);

        error(2, errno, "error writing stdout\n");
    }

    exit(0);
}