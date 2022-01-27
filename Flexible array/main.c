#include <stdio.h>
#include "array.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(){
    int roz;
    printf("Podaj rozmiar tablicy:");
    if(scanf("%d", &roz) != 1)
        return printf("Incorrect input"), 1;

    if(roz <= 0) return printf("Incorrect input data"), 2;

    struct array_t *tab;
    int x = array_create_struct(&tab, roz);
    if(x == 1 || x == 2) return printf("Failed to allocate memory"), 8;

    int temp, ilosc = 0, buffer_full = 0, odp;
    while(1){
        printf("Co chcesz zrobic:");
        if(scanf("%d", &odp) != 1){
            array_destroy_struct(&tab);
            return printf("Incorrect input"), 1;
        }
        switch (odp){
            case 0:
                array_destroy_struct(&tab);
                return 0;
            case 1:
                printf("Podaj kolejne liczby, ktore maja zostac dodane do tablicy:");
                while(1){
                    if(buffer_full) break;
                    if(scanf("%d", &temp)!=1){
                        array_destroy_struct(&tab);
                        return printf("Incorrect input"), 1;
                    }
                    if(temp == 0) break;
                    x = array_push_back(tab, temp);
                    if(x == 0) ilosc++;
                    if(x == 2) buffer_full = 1;
                }
                break;
            case 2:
                printf("Podaj kolejne liczby, ktore maja zostac usuniete z tablicy:");
                while(1){
                    if(scanf("%d", &temp)!=1){
                        array_destroy_struct(&tab);
                        return printf("Incorrect input"), 1;
                    }
                    if(temp == 0) break;
                    x = array_remove_item(tab, temp);
                    if(x > 0) ilosc -= x;
                    if(x == -1){
                        array_destroy_struct(&tab);
                        return printf("Incorrect input"), 1;
                    }
                }
                break;
            default:
                printf("Incorrect input data\n");
                continue;
        }

        if(buffer_full){
            printf("Failed to allocate memory\n");
            while(getchar()!='\n');
            buffer_full = 0;
            array_display(tab);
            printf("\n");
        }else if(ilosc == 0)
            printf("Buffer is empty\n");
        else{
            array_display(tab);
            printf("\n");
        }
    }
}
