#include <stdio.h>
int
main(){
	int c;
	int space; // uso la variable space de "bool"--> si ya habia espacio=1
	space=0;
	while((c=getchar())!=EOF){
		if(c==' '){
			if(space==0){
				putchar(c);
				}
			++space;
		}else{
			space=0;
			putchar(c);
		}
	}
}
