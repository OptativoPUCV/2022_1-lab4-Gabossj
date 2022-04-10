#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    Pair *newData = createPair(key, value);
    long i = hash (key, map ->capacity);

    if(!(map -> buckets[i])){
        map -> buckets[i] = newData;
        (map-> size)++;
    }
    else{
        while(map -> buckets[i]){
            i++;
            if (i == map -> capacity) i=0;
            if(!(map -> buckets[i])){
                map -> buckets[i] = newData;
                (map-> size)++;
                break;
            }
        }
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    
    /*
    ------------
    (map -> capacity) = 2 * (map -> capacity);

    */

    /*  duplicar map capac
        aux_array = hashArray
        map->hash array = calloc capac
        map-> size = 0
        recorrer aux_array reinsertar elementos
    */
}


HashMap * createMap(long capacity) {
    HashMap *nuevo = (HashMap*) malloc(sizeof(HashMap));
    nuevo -> buckets = (Pair**) calloc(capacity, sizeof(Pair*));
    nuevo -> size = 0;
    nuevo -> capacity = capacity;
    nuevo -> current = -1;

    return nuevo;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   

    long pos = hash(key,map -> capacity);
    while(!(map->buckets[pos])){
    //do{
        if (is_equal(map -> buckets[pos] -> key,key ) == 1){
            map -> current = pos;
            break;
        }
        else pos++;
    
    }
    //}while(map -> buckets[pos]);

    return map -> buckets[pos];
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
