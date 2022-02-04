#include <stdlib.h>
#include "stack.h"
#include <stdio.h>

int stack_init(struct stack_t **stack){
    if(!stack) return 1;
    *stack = calloc(1, sizeof(struct stack_t));
    if(!*stack)
        return 2;
    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, int value){
    if(!stack) return 1;
    struct node_t *temp = calloc(1, sizeof(struct node_t));
    if(!temp)
        return 2;
    temp->data = value;
    temp->next = stack->head;
    stack->head = temp;
    return 0;
}

int stack_pop(struct stack_t* stack, int *err_code){
    if(!stack){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    if(stack_empty(stack)){
        if(err_code)
            *err_code = 1;
        return 1;
    }
    struct node_t *temp = stack->head;
    int value = stack->head->data;
    stack->head = stack->head->next;
    free(temp);
    if(err_code)
        *err_code = 0;
    return value;
}

void stack_display(const struct stack_t* stack){
    if(!stack || !stack->head) return;
    struct node_t *temp = stack->head;
    while(temp){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

void stack_destroy(struct stack_t** stack){
    if(!stack) return;
    struct node_t *temp;
    struct node_t *next = (*stack)->head;
    while(next){
        temp = next;
        next = next->next;
        free(temp);
    }
    free(*stack);
}

int stack_empty(const struct stack_t* stack){
    if(!stack) return 2;
    if(!stack->head) return 1;
    return 0;
}
