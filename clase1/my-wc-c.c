 
#include <stdio.h>

int
main(){
	long nc, nl, nw;
	nc=0;
	nc=0;
	nl=0;
	int c, isword;
	isword=0;
	c=getchar();
	while(c!=EOF){
		if(c == '\n'){
			++nl;
		}
		if(c==' '|| c=='\n' || c=='\t' ){
			isword=1;
		}
		else if(isword){
			++nw;
			isword=0;
		}
		++nc;
		c=getchar();

	}
	printf("El numero de caracteres  es %ld \n",nc);
	printf("El numero de lineas es %ld \n",nl);
	printf("El numero de palabras es %ld \n",nw);
	return 0;

}
