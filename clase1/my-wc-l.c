 #include<stdio.h>

int
main(){
	int lc;
	lc=0;
	int c;	
	while((c=getchar())!=EOF){
		if(c=='\n'){
			++lc;
		}
		
	}
	printf("La cantidad de saltos de linea es %d \n", lc);
	return 0;
}
