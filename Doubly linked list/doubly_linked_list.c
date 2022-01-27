#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t *lista = calloc(1, sizeof(struct doubly_linked_list_t));
    if(!lista)
        return NULL;
    return lista;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(!dll) return 1;
    struct node_t *node = calloc(1, sizeof(struct node_t));
    if(!node)
        return 2;

    if(!dll->tail){
        node->data = value;
        node->next = NULL;
        node->prev = NULL;
        dll->head = node;
        dll->tail = node;
    }else{
        node->data = value;
        node->next = NULL;
        node->prev = dll->tail;
        dll->tail->next = node;
        dll->tail = node;
    }
    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value){
    if(!dll) return 1;
    struct node_t *node = calloc(1, sizeof(struct node_t));
    if(!node)
        return 2;

    if(!dll->head){
        node->data = value;
        node->next = NULL;
        node->prev = NULL;
        dll->head = node;
        dll->tail = node;
    }else{
        node->data = value;
        node->next = dll->head;
        node->prev = NULL;
        dll->head->prev = node;
        dll->head = node;
    }
    return 0;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->head || !dll->tail){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    int value;
    if(!dll->head->next){
        value = dll->head->data;
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        if(err_code)
            *err_code = 0;
        return value;
    }
    struct node_t *temp = dll->head;
    value = dll->head->data;
    dll->head = dll->head->next;
    dll->head->prev = NULL;
    free(temp);

    if(err_code)
        *err_code = 0;
    return value;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->head || !dll->tail){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    int value;
    if(!dll->head->next){
        value = dll->head->data;
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
        if(err_code)
            *err_code = 0;
        return value;
    }
    struct node_t *temp = dll->head;
    while(temp->next->next)
        temp = temp->next;
    value = temp->next->data;
    free(temp->next);
    dll->tail = temp;
    dll->tail->next = NULL;

    if(err_code)
        *err_code = 0;
    return value;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->head || !dll->tail){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    if(err_code)
        *err_code = 0;
    return dll->tail->data;
}
int dll_front(const struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->head || !dll->tail){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    if(err_code)
        *err_code = 0;
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll){
    if(!dll || !dll->head || !dll->tail) return NULL;
    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll){
    if(!dll || !dll->head || !dll->tail) return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll){
    if(!dll) return -1;
    if(!dll->head || !dll->tail) return 0;
    struct node_t *temp = dll->head;
    int count = 0;
    while(temp){
        count++;
        temp = temp->next;
    }
    return count;
}

int dll_is_empty(const struct doubly_linked_list_t* dll){
    if(!dll) return -1;
    if(!dll->head || !dll->tail) return 1;
    return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(!dll || (index > 0 && (int)index >= dll_size(dll))){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    struct node_t *temp = dll->head;
    unsigned int curr_index = 0;
    while(temp){
        if(curr_index == index)
            break;
        temp = temp->next;
        curr_index++;
    }
    if(err_code)
        *err_code = 0;
    return temp->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value){
    if(!dll || (int)index < 0 || (index > 0 && (int)index > dll_size(dll))) return 1;

    if(index == 0){
        int err = dll_push_front(dll, value);
        if(err == 2)
            return 2;
        return 0;
    }

    struct node_t *temp = dll->head;
    unsigned int curr_index = 0;
    while(temp){
        if(curr_index+1 == index){
            if(temp->next){
                struct node_t *new_node = calloc(1, sizeof(struct node_t));
                if(!new_node)
                    return 2;
                new_node->data = value;
                new_node->next = temp->next;
                new_node->prev = temp;

                temp->next = new_node;
                new_node->next->prev = new_node;
            }else{
                int err = dll_push_back(dll, value);
                if(err == 2)
                    return 2;
                break;
            }
            return 0;
        }
        temp = temp->next;
        curr_index++;
    }
    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(!dll || (int)index < 0 || (index > 0 && (int)index >= dll_size(dll))){
        if(err_code)
            *err_code = 1;
        return 1;
    }

    struct node_t *temp = dll->head;
    unsigned int curr_index = 0;
    int value;
    if(index == 0){
        value = dll_pop_front(dll, err_code);
        return value;
    }
    while(temp){
        if(curr_index+1 == index){
            if(temp->next->next){
                struct node_t *del_node = temp->next;
                value = temp->next->data;
                temp->next = temp->next->next;
                temp->next->prev = temp;
                free(del_node);
                break;
            }else{
                value = dll_pop_back(dll, err_code);
                break;
            }
        }
        temp = temp->next;
        curr_index++;
    }

    if(err_code)
        *err_code = 0;
    return value;
}

void dll_clear(struct doubly_linked_list_t* dll){
    if(!dll || !dll->head || !dll->tail) return;
    struct node_t *temp;
    struct node_t *next = dll->head;
    while(next){
        temp = next;
        next = next->next;
        free(temp);
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll){
    if(!dll || !dll->head || !dll->head) return;
    struct node_t *temp = dll->head;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if(!dll || !dll->head || !dll->head) return;
    struct node_t *temp = dll->tail;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->prev;
    }
}

