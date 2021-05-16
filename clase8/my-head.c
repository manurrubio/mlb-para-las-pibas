#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#define MAXLINE 1000
int main(int argc, char const *argv[])
{

    FILE *fp; //archivo que abro
    char *a; //puntero de argv-->recorre todos los argumentos
    char *prog; // donde guardo mi archivo
    char *lp; //lineas del programa
    char line[MAXLINE];
    int line_number;
    int count_arg;
    int def;
    int arg;
    int over; //me indica cuando ya estan todas las lineas impresas
    arg=atoi(argv[1]);
    a = strdup(argv); // me paro en el primer argumento--> my-head
    def= 10; // se imprimen 10 lineas si no pongo el numero de lineas

    *a++; // me paro en el segundo argumento--> el numero (si tiene)

    if (argc >= 1 && arg!=NULL)
    {
        count_arg=2;
        line_number = 1;
        *a++; //pasa al archivo 
        for (a; *a!= '\0' ; *a++)
        {
            over=0; 
            prog = (char *)argv[count_arg]; 
            if ((fp = fopen(prog, "r")) == NULL)
            {
                error(1, 0, "No se puede abrir el archivo %s", prog);
            }
            for (line_number; line_number <= abs(arg) && over==0; line_number++)
            {
                lp = fgets(line, MAXLINE, fp);
                if(lp==NULL){
                    printf("\n");
                    line_number--; //entro en el for pero no imprimió :C
                    ++count_arg; //paso al siguiente archivo 
                    over=1;
                }else{
                    printf("%s", lp);
                }
            }
        }
        printf("\n");
    }
    else
    {
        count_arg=1; 
        line_number = 1;

        for (a; *a!= '\0' ; *a++)
        {
            over=0; 
            prog = (char *)argv[count_arg]; 
            if ((fp = fopen(prog, "r")) == NULL)
            {
                error(1, 0, "No se puede abrir el archivo %s, no llega a haber 10 lineas entre los programas a imprimir", prog);
            }
            for (line_number; line_number <= def && over==0; line_number++)
            {
                lp = fgets(line, MAXLINE, fp);
                if(lp==NULL){
                    printf("\n");
                    line_number--; //entro en el for pero no imprimió :C
                    ++count_arg; //paso al siguiente archivo 
                    over=1;
                }else{
                    printf("%s", lp);
                }
            }
        }
        printf("\n");
        
    }

    if (ferror(stdout))
    {
        fclose(fp);
        error(2, errno, "error writing stdout\n");
    }
    return 0;
}