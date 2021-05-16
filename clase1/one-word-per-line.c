#include <stdio.h>
int
main(){
	int c;	
	while((c=getchar())!=EOF){
		if(c==' ' || c=='\n'){
			printf("\n");
		}else{
			putchar(c);
		}
	}
	return 0;

}
