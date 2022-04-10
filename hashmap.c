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

    long i = hash(key, map -> capacity);
    while(map-> buckets[i] != NULL){
        if (is_equal(map -> buckets[i] -> key, key) == 1){
            map -> current = i;
            map -> size = map -> size -1;
            map -> buckets[i] -> key = NULL;
            break;
        }
        i++;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   

    long i = hash(key,map -> capacity);
    while(map-> buckets[i] != NULL){
        if (is_equal(map -> buckets[i] -> key,key ) == 1){
            map -> current = i;
            break;
        }
        else i++;  
    }
    map -> current = i;

    return map -> buckets[i];
}

Pair * firstMap(HashMap * map) {
    for (int i=0; i < map -> capacity; i++){
        if(map -> buckets[i]){
            if ((map -> buckets[i] -> key) && (map -> buckets[i] -> value)){
                map -> current = i;
                return map -> buckets[i];
            }
        }
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
for (int i=0; i < map -> capacity; i++){
        if(map -> buckets[i+1]){
            if ((map -> buckets[i+1] -> key) && (map -> buckets[i+1] -> value)){
                map -> current = (i+1);
                return map -> buckets[i+1];
            }
        }
    }
    return NULL;
}
