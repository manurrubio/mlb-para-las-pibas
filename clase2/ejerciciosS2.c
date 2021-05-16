#include <stdio.h>

#define MAXLINE 1000

int my_strlen(char s[]);
int my_strcmp(char s[],char t[]);
void my_strcpy(char s[], char t[]);
void my_strncpy(char s[], char t[], int n);

int main(){
	char text[MAXLINE];
	char text2[MAXLINE];
	int n;
	int c;
	int i=0;
	int j=0;
	int k=0;
	while((c=getchar())!= EOF && c!= '\n'){
		text[i] = c;
		++i;
	}
	if(c=='\n'){
		//consideramos enter como cambiar string
		while((c=getchar())!=EOF && c!= '\n'){
			text2[j]=c;
			++j;
		}
	}
	n=4;
	text[i]= '\0';
	text2[j]= '\0';
	my_strncpy(text,text2,n);
	//int ret = my_strcmp(text, text2);
	//printf("El mas largo es %d \n", ret);
	return 0;
}

int my_strlen(char s[]){
	int counter=0;
	for(int i=0; s[i]!= '\0';++i){
		++counter;
	}
	return counter;
}
int my_strcmp(char s[], char t[]){
	//función que compara s y t
	int ret, lens, lent,i;
	lens=0;
	lent=0;
	lens= my_strlen(s);
	lent= my_strlen(t);
	if(lens>lent){
		return lens;
	}else if(lens<lent){
		return -1;
	}else{
		for(i=0; s[i]=t[i]; ++i){
			if(s[i]== '\n'){
				return 0;
			}
		}
		return -2;
	}
}

void my_strcpy(char s[], char t[]){
	int comp; //no sirve si =-1, pued t>s
	comp= my_strcmp(s,t);
	int lent= my_strlen(t);
	if(comp!=-1){
		int i;
		for(i=0; t[i]!= '\0'; ++i){
			s[i]=t[i];
		}
		s[i]='\0';
		printf("El string copiado es: \n");
		for(int j=0; j<lent; ++j){
			putchar(s[j]);
		}
		printf("\n");

	}else{
		printf("No es posible copiar el string t en s \n");
	}

}


void my_strncpy(char s[],char t[], int n){
	int comp = my_strcmp(s, t);
	int lens= my_strlen(s);
   	if(comp != -1){
	        int i;
        	for (i = 0; t[i]<n; i++) {
        		s[i] = t[i];
        	}
        	s[i] = '\0';
        	printf("Se copio en el primer string: \n");
        	for(int j = 0; j <n; ++j){
            		putchar(s[j]);
			printf("\n");
        	}
	}else if(lens>n){
		int i;
		for(i=0;t[i]<n; ++i){
			s[i]=t[i];
		}
		s[i] = '\0';
		printf("Se copio en el primer string: \n");
		for(int j=0; j<n; ++j){
			putchar(s[j]);
			printf("\n");
		}
	}else{
        printf("No es posible copiar el string t en el string s");
    }
}
