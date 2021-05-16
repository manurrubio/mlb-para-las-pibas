#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wrappers.h"
#include "anagramas-hash.h"

int
main(int argc, char *argv[])
{
    FILE *fp;
    char word[MAXWORD], key[MAXWORD];
    unsigned int h;
    struct hashnode *anagrams[HASHSIZE] = { NULL };
    struct hashnode *hn;
    struct listnode *p;

    if (argc == 1) {
        fprintf(stderr, "Uso:\n  %s -a|--all\n  %s palabra [palabra ...]\n",
                        argv[0],  argv[0]);
        exit(1);
    }

    fp = fopen_or_exit(DICT, "r"); // abre el diccionario (archivo que contiene todas las palabras)

    //while (fgetword_normalizada (fp, word, MAXWORD) != NULL) { // lee todas las palabras del diccionario
    while (fgetword_lower_alpha_normal (fp, word, MAXWORD) != NULL) { // lee todas las palabras del diccionario
        strcpy(key, word);              // para cada palabra, la copia en key
        sort_word(key);                 // ordena key
        h = hash(key) % HASHSIZE;       // genera índice del array
        anagrams[h] = hash_insert_word(anagrams[h], key, word); // inserta la palabra word con clave key
    }

    if (argc > 1 && (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0) ) {
        // -a o --all
        for (int i=0; i<HASHSIZE; i++) {
            // recorre array de hash
            for (hn=anagrams[i]; hn != NULL; hn = hn->next) {
                // recorre colisiones (claves con el mismo hash)
                if (hn->wlist->qty > 1) {
                    // si una clave tiene varias palabras en la lista
                    printf("Clave %s, %d palabras: ", hn->key, hn->wlist->qty);
                    for (p = hn->wlist->first; p != NULL; p = p->next) {
                        printf("%s%c", p->word, p->next != NULL ? ',' : '\n');
                    }
                }
            }
        }
    } else {    // no es opción -a/--all sino una lista de palabras
        while (--argc > 0) {
            strcpy(key, *++argv);
            sort_word(key);
            h = hash(key) % HASHSIZE;
            for (hn=anagrams[h]; hn != NULL && strcmp(key, hn->key) != 0; hn = hn->next) {
                ;   // recorre las claves que tienen el mismo hash
            }
            if (hn == NULL) {                   // Clave no encontrada
                printf("Palabra %s no existe en diccionario.\n", *argv);
            } else {                            // Clave encontrada
                for (p=hn->wlist->first; p!=NULL && strcmp(*argv, p->word) != 0; p=p->next) {
                    ;                           // busco si la palabra buscada está en la lista
                }
                if (p != NULL) {                // la palabra estaba
                    if (hn->wlist->qty > 1) {   // y hay anagramas !
                        printf("Clave %s, %d palabras: ", hn->key, hn->wlist->qty);
                        for (p = hn->wlist->first; p != NULL; p = p->next) {
                            printf("%s%c", p->word, p->next != NULL ? ',' : '\n');
                        }
                    } else {                    // No hay anagramas para esa palabra
                        printf("Palabra %s no tiene anagramas.\n", *argv);
                    }
                } else {                        // la palabra no estaba
                    printf("Palabra %s no existe en diccionario.\n", *argv);
                }
            }
        }
    }

    exit(0);
}

struct list *
list_create(void) {
    struct list *mylist;
    mylist = (struct list *) malloc_or_exit(sizeof (struct list));
    
    mylist->first = mylist->last = NULL;

    mylist->qty = 0;

    return mylist;
}

struct list *
list_insert_last_word(struct list *l, char *word) {
    // guardar word en otro espacio
    // inserta una palabra al final de la lista l, retorna el puntero a la lista
    // si la lista es NULL, crea una nueva

    struct listnode *mylistnode;
    mylistnode = (struct listnode *) malloc_or_exit(sizeof (struct listnode));
    mylistnode->word = strdup_or_exit (word);
    mylistnode->next = NULL;


    if (l == NULL){
            l = list_create();
    }
    if (l->first == NULL) {
        l->first = l->last = mylistnode; //generar el nodo - malloc un list node
        l->qty = 1;
    } else {
        l->last->next = mylistnode;
        l->last = mylistnode;
        l->qty ++;
    }

    return l;
}


// agregar la palabra al principio de la lista de anagramas
// busca key en el hash (y si no encuentra inserta key al inicio en lista simple)
// luego agrega palabra al final de la lista de anagramas asociadas a la key
// retorna siempre el primero de la lista: node si key estaba o el nuevo nodo si se insertó
struct hashnode *
hash_insert_word(struct hashnode *node, char *key, char *word){
    
    struct hashnode *np;

    for (np = node ; np != NULL ; np = np->next){
        if (strcmp(np->key, key) == 0){
            list_insert_last_word(np->wlist, word);
            return node;
        }
    }
    if (np == NULL){
        np = (struct hashnode *) malloc_or_exit(sizeof (struct hashnode));
        np->key = strdup_or_exit (key);
        np->next = node; //insertando new_node al ppio
        np->wlist = list_insert_last_word(NULL, word); // list insert contempla que la lista sea NULL
    } else {
        np->wlist = list_insert_last_word(np->wlist, word);
    } 
    return np;
}


// ordena EN EL LUGAR la palabra 'word' según código ASCII en forma ascendente
    //ordena las letras de cada palabra

char *
sort_word(char *word){
 
    char *min;
    char temp; //donde guardo infomacion de los punteros
    char *p, *q;
   
    for (p = word; *p != '\0'; p ++){
        min = p;
        for (q = p+1; *q != '\0'; q++){
            if (*min > *q){
                min = q;
            }    
        }
        temp = *min;
        *min = *p;
        *p = temp;
    }
    return word;  
}


// escribe (printf) la lista de anagramas para ese hashnode
void print_anagrams(struct hashnode *hn){

    struct listnode *ln;
    for (ln = hn->wlist->first; ln != NULL; ln = ln->next){
        printf("%s \n", ln->word);
    }
}