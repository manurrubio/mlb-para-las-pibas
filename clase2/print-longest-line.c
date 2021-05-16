#include <stdio.h>
#define MAXLINE 1000

int get_line(char s[]);

int main()
{
	char actual[MAXLINE];
	char max[MAXLINE];
	max[0] = '\0';
	actual[0] = '\0';
	int i;
	i = 0;
	int lenact, lenmax, c;
	while ((c = getchar()) != EOF)
	{
		if (c != '\n')
		{
			actual[i] = c;
			i++;
		}
		else
		{
			actual[i] = '\0';
			lenact = get_line(actual);
			lenmax = get_line(max);
			if (lenact > lenmax)
			{
				for (int k = 0; k < lenact; k++)
				{
					max[k] = actual[k];
				}
			}
			actual[0] = '\0';
			i = 0;
		}
	}
	printf("la linea mas larga es: ");
	int toprint;
	toprint = get_line(max);
	for (int j = 0; j < toprint; j++)
	{
		putchar(max[j]);
	}
	printf("'\n'");
	return 0;
}

//getline devuelve la cantidad de caracteres de la
//lines
int get_line(char s[])
{
	int counter = 0;
	for (int i = 0; s[i] != '\0'; ++i)
	{
		++counter;
	}
	return counter;
}
