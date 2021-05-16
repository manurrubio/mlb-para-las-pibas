#include <stdio.h>

int
main(void)
{
	float celcius, fahrenheit;
	fahrenheit = 0;
	while(fahrenheit < 40){
		celcius = (fahrenheit - 32)*5/9;
		printf("%f grados fahrenheit son %f grados celcius\n", fahrenheit,celcius);
		fahrenheit++;
	}
	return 0;
}
