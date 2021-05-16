#include <stdio.h>
#define MAXLINE 1000

int my_stred(char *pajar, char *aguja);
int my_strlen(char *str);

int main(){
	//char pajar[]= {}

	return 0;
}

int my_stred(char *pajar, char *aguja){
	char *p;
	char *a;
	int lenp, lena;
	lenp= my_strlen(pajar);
	lena= my_strlen(aguja);
	a= aguja +lena;
	for(p=pajar+ lenp; p>pajar; p--){
		if(*p==*a && a!= aguja){
			a--;
		}else if(*p==*a && a==aguja){
			return 1;
		}else{
			return 0;
		}
	}

}

int my_strlen(char *str){
	char *s;
	int size;
	for(s=str; *s!='\0'; s++){
		++size;
	}
	return size;
}

