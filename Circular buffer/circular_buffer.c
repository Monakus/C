#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

int circular_buffer_create(struct circular_buffer_t *cb, int N){
    if(!cb || N <= 0) return 1;
    cb->ptr = (int*) malloc(sizeof(int)*N);
    if(!cb->ptr) return 2;
    cb->begin = 0;
    cb->end = 0;
    cb->capacity = N;
    cb->full = 0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){
    if(!cb || N <=0) return 1;
    *cb = (struct circular_buffer_t*) malloc(sizeof(struct circular_buffer_t));
    if(!*cb) return 2;
    if(circular_buffer_create(*cb, N) != 0) return free(*cb), 2;
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *cb){
    if(!cb) return;
    free(cb->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **cb){
    if(!cb) return;
    circular_buffer_destroy(*cb);
    free(*cb);
}

int circular_buffer_empty(const struct circular_buffer_t *cb){
    if(!cb || !cb->ptr || cb->capacity <= 0 || cb->end < 0 || cb->end >= cb->capacity ||
       cb->begin < 0 || cb->begin >= cb->capacity) return -1;

    if(cb->begin == cb->end && cb->full == 0) return 1;
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *cb){
    if(!cb || !cb->ptr || cb->capacity <= 0 || cb->end < 0 || cb->end >= cb->capacity ||
       cb->begin < 0 || cb->begin >= cb->capacity) return -1;

    if(cb->full == 1) return 1;
    return 0;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    if(!cb || !cb->ptr || cb->capacity <= 0 || cb->end < 0 || cb->end >= cb->capacity ||
       cb->begin < 0 || cb->begin >= cb->capacity) return 1;

    if(circular_buffer_full(cb)){
        *(cb->ptr + cb->begin) = value;
        cb->end = (cb->end+1)%cb->capacity;
        cb->begin = (cb->begin+1)%cb->capacity;
    }
    else{
        *(cb->ptr + cb->end) = value;
        cb->end = (cb->end+1)%cb->capacity;
        if(cb->end == cb->begin)
            cb->full = 1;
    }
    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *cb, int *err_code){
    if(!cb || !cb->ptr || cb->capacity <= 0 || cb->end < 0 || cb->end >= cb->capacity ||
       cb->begin < 0 || cb->begin >= cb->capacity){
        if(err_code)
            *err_code = 1;
        return 1;
    }

    if(circular_buffer_empty(cb)){
        if(err_code)
            *err_code = 2;
        return 2;
    }

    int wartosc = *(cb->ptr + cb->begin);
    if(circular_buffer_full(cb)){
        cb->begin = (cb->begin+1)%cb->capacity;
        cb->full = 0;
    }
    else
        cb->begin = (cb->begin+1)%cb->capacity;

    if(err_code)
        *err_code = 0;
    return wartosc;
}

int circular_buffer_pop_back(struct circular_buffer_t *cb, int *err_code){
    if(!cb || !cb->ptr || cb->capacity <= 0 || cb->end < 0 || cb->end >= cb->capacity ||
       cb->begin < 0 || cb->begin >= cb->capacity){
        if(err_code)
            *err_code = 1;
        return 1;
    }

    if(circular_buffer_empty(cb)){
        if(err_code)
            *err_code = 2;
        return 2;
    }

    int end = cb->end == 0 ? cb->capacity-1 : cb->end-1;
    int wartosc = *(cb->ptr + end);
    if(circular_buffer_full(cb))
        cb->full = 0;

    if(cb->end == 0)
        cb->end = cb->capacity-1;
    else
        cb->end--;

    if(err_code)
        *err_code = 0;
    return wartosc;
}

void circular_buffer_display(const struct circular_buffer_t *cb){
    if(!cb || circular_buffer_empty(cb)) return;
    if(cb->end > cb->begin){
        for (int i = cb->begin; i < cb->end; ++i)
            printf("%d ", *(cb->ptr+i));
    }else if(cb->begin > cb->end){
        int i = cb->begin, ilosc = 0;
        while (ilosc < (cb->capacity -(cb->begin - cb->end))){
            printf("%d ", *(cb->ptr+i));
            i = (i+1)%cb->capacity;
            ilosc++;
        }
    }else{
        int i = cb->begin, ilosc = 0;
        while (ilosc < cb->capacity){
            printf("%d ", *(cb->ptr+i));
            i = (i+1)%cb->capacity;
            ilosc++;
        }
    }

}
