#include <stdio.h>

main(void){
	printf("Tabla celsius - fahrenheit \n");
	float celsius;
	int  fahr, lower, upper, step;
	lower=0;
	upper=300;
	step=20;
	fahr=lower;
	while(fahr<upper){
		celsius= (fahr-32)*5/9;
		printf("%.2f - %.2d \n", celsius,fahr);
		fahr=fahr+step;
	}
}
