#include "array.h"
#include <stdio.h>
#include <stdlib.h>

int array_create(struct array_t *a, int N){
    if(!a || N <= 0) return 1;
    a->ptr = (int*) malloc(sizeof(int)*N);
    if(!a->ptr) return 2;
    a->size = 0;
    a->capacity = N;
    return 0;
}

int array_push_back(struct array_t *a, int value){
    if(!a || !a->ptr || a->size < 0 || a->size > a->capacity  || a->capacity <= 0) return 1;
    if(a->size == a->capacity){
        int *temp = (int*) realloc(a->ptr, sizeof(int)*a->capacity*2);
        if(!temp) return 2;
        a->ptr = temp;
        a->capacity *= 2;
    }
    *(a->ptr+a->size) = value;
    a->size++;
    return 0;
}

void array_display(const struct array_t *a){
    if(!a || !a->ptr || a->size <= 0 || a->size > a->capacity || a->capacity <= 0) return;
    for (int i = 0; i < a->size; ++i)
        printf("%d ", *(a->ptr+i));
}

void array_destroy(struct array_t *a){
    if(!a) return;
    free(a->ptr);
}

int array_create_struct(struct array_t **a, int N){
    if(!a || N <= 0) return 1;
    *a = (struct array_t*) malloc(sizeof(struct array_t));
    if(!*a) return 2;
    if(array_create(*a, N) != 0){
        return free(*a), 2;
    }
    return 0;
}

void array_destroy_struct(struct array_t **a){
    if(!a) return;
    array_destroy(*a);
    free(*a);
}

int array_remove_item(struct array_t *a, int value){
    if(!a || !a->ptr || a->size < 0 || a->size > a->capacity  || a->capacity <= 0) return -1;

    int ilosc = 0;
    for (int i = 0; i < a->size; ++i) {
        if(*(a->ptr+i) == value){
            for (int j = i; j < a->size-1; ++j) {
                *(a->ptr+j) = *(a->ptr+j+1);
            }
            a->size--, ilosc++, i--;
        }
    }

    if(a->capacity > 1){
        float x = (float) a->size, y = (float) a->capacity;
        if(x/y < 0.25f){
            int *temp = (int*) realloc(a->ptr, sizeof(int)*a->capacity/2);
            if(!temp) return 0;
            a->ptr = temp;
            a->capacity = a->capacity/2;
        }
    }
    return ilosc;
}
