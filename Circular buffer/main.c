#include <stdio.h>
#include "circular_buffer.h"

int main(){
    int roz;
    printf("Podaj rozmiar bufora:");
    if(scanf("%d", &roz) != 1)
        return printf("Incorrect input"), 1;

    if(roz <= 0)
        return printf("Incorrect input data"), 2;

    struct circular_buffer_t *buffer;
    int x = circular_buffer_create_struct(&buffer, roz);
    if(x == 1 || x == 2)
        return printf("Failed to allocate memory"), 8;

    int temp, odp, err_code;
    while (1){
        printf("Co chcesz zrobic:");
        if(scanf("%d", &odp) != 1){
            circular_buffer_destroy_struct(&buffer);
            return printf("Incorrect input"), 1;
        }
        switch (odp) {
            case 0:
                circular_buffer_destroy_struct(&buffer);
                return 0;
            case 1:
                printf("Podaj liczbe:");
                if(scanf("%d", &temp) != 1){
                    circular_buffer_destroy_struct(&buffer);
                    return printf("Incorrect input"), 1;
                }
                circular_buffer_push_back(buffer, temp);
                break;
            case 2:
                temp = circular_buffer_pop_back(buffer, &err_code);
                if(err_code == 2)
                    printf("Buffer is empty\n");
                else
                    printf("%d\n", temp);
                break;
            case 3:
                temp = circular_buffer_pop_front(buffer, &err_code);
                if(err_code == 2)
                    printf("Buffer is empty\n");
                else
                    printf("%d\n", temp);
                break;
            case 4:
                if(circular_buffer_empty(buffer))
                    printf("Buffer is empty\n");
                else{
                    circular_buffer_display(buffer);
                    printf("\n");
                }
                break;
            case 5:
                if(circular_buffer_empty(buffer))
                    printf("1\n");
                else
                    printf("0\n");
                break;
            case 6:
                if(circular_buffer_full(buffer))
                    printf("1\n");
                else
                    printf("0\n");
                break;
            default:
                printf("Incorrect input data\n");
                continue;
        }
    }
}
