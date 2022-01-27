#include <stdio.h>
#include "stack.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    struct stack_t *stos;
    int err = stack_init(&stos);
    if(err == 2)
        return printf("Failed to allocate memory"), 8;
    int opt, num, err_code;
    while(1){
        printf("Co chcesz zrobic?");
        err = scanf("%d", &opt);
        if(err != 1)
            return printf("Incorrect input"), stack_destroy(&stos), 1;
        switch (opt) {
            case 0:
                stack_destroy(&stos);
                return 0;
            case 1:
                printf("Podaj liczbe:");
                err = scanf("%d", &num);
                if(err != 1)
                    return printf("Incorrect input"), stack_destroy(&stos), 1;
                err = stack_push(stos, num);
                if(err == 2)
                    return printf("Failed to allocate memory"), stack_destroy(&stos), 8;
                break;
            case 2:
                num = stack_pop(stos, &err_code);
                if(err_code == 1)
                    printf("Stack is empty\n");
                else
                    printf("%d\n", num);
                break;
            case 3:
                if(stack_empty(stos))
                    printf("1\n");
                else
                    printf("0\n");
                break;
            case 4:
                if(stack_empty(stos))
                    printf("Stack is empty\n");
                else{
                    stack_display(stos);
                    printf("\n");
                }
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
}
