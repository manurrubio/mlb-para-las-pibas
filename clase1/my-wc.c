#include <stdio.h>
int
main(){
	int c;
	int wc, lc,cc;
	int last; //guardo el ultimo char
	wc=0;
	lc=1;
	cc=0;
	last= ' ';
	while((c=getchar())!=EOF){
		if(c=='\n'){
			++lc;
			if(last!='\n'&& last!=' '){
				++wc;
			}
		}else if (c==' '){
			++wc;
		}
		last=c;
		++cc;

	}
	printf("La cantidad de palabras es %d \n", wc);
	printf("La cantidad de lineas es %d \n", lc);
	printf("La cantidad de caracteres es %d \n",cc);
}
