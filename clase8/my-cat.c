#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>

void filecopy(FILE *ipf, FILE *opf)
{
	char c;

	while ((c = getc(ipf)) != EOF)
	{
		putc(c, opf);
	}
}

int main(int argc, char *argv[])
{

	FILE *fp;

	char *prog = argv[0];

	if (argc == 1)
	{
		filecopy(stdin, stdout);
	}
	else
	{
		while (--argc > 0)
		{

			if ((fp = fopen(*++argv, "r")) == NULL)
			{
				error(1, errno, "can't open file '%s'", *argv);
				//fprintf(stderr, "%s: can't open %s\n", prog,  *argv);
				//exit(1);
			}
			else
			{
				filecopy(fp, stdout);
				fclose(fp);
			}
		}
	}

	if (ferror(stdout))
	{

		error(2, errno, "error writing stdout\n");
		//fprintf(stderr, "%s: error writig stdout\n", prog);
		//exit(2);
	}

	exit(0);
}
