#include <stdio.h>
#include "doubly_linked_list.h"
#include "stdlib.h"

int main() {
    struct doubly_linked_list_t *lista = dll_create();
    if(!lista)
        return printf("Failed to allocate memory"), 8;
    int opt, num, index, err_code;
    while(1){
        printf("Co chcesz zrobic?");
        int err = scanf("%d", &opt);
        if(err != 1)
            return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
        switch (opt){
            case 0: //zakończenie działania programu
                return dll_clear(lista), free(lista), 0;
            case 1: //dodanie na koniec listy
                printf("Podaj liczbe");
                err = scanf("%d", &num);
                if(err != 1)
                    return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
                err = dll_push_back(lista, num);
                if(err == 2)
                    return printf("Failed to allocate memory"), dll_clear(lista), free(lista), 8;
                break;
            case 2: //usunięcie ostatniego elementu
                num = dll_pop_back(lista, &err_code);
                if(err_code == 1)
                    printf("List is empty\n");
                else
                    printf("%d\n", num);
                break;
            case 3: //dodanie na początek listy
                printf("Podaj liczbe");
                err = scanf("%d", &num);
                if(err != 1)
                    return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
                err = dll_push_front(lista, num);
                if(err == 2)
                    return printf("Failed to allocate memory"), dll_clear(lista), free(lista), 8;
                break;
            case 4: //usunięcie pierwszego elementu
                num = dll_pop_front(lista, &err_code);
                if(err_code == 1)
                    printf("List is empty\n");
                else
                    printf("%d\n", num);
                break;
            case 5: //dodanie elementu na podanej pozycji
                printf("Podaj liczbe");
                err = scanf("%d", &num);
                if(err != 1)
                    return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
                printf("Podaj index");
                err = scanf("%d", &index);
                if(err != 1)
                    return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
                if(index < 0)
                    printf("Index out of range\n");
                err = dll_insert(lista, index, num);
                if(err == 1)
                    printf("Index out of range\n");
                else if(err == 2)
                    return printf("Failed to allocate memory"), dll_clear(lista), free(lista), 8;
                break;
            case 6: //usunięcie elementu na podanej pozycji
                if(dll_is_empty(lista)){
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj index");
                err = scanf("%d", &index);
                if(err != 1)
                    return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
                if(index < 0)
                    printf("Index out of range\n");
                num = dll_remove(lista, index, &err_code);
                if(err_code == 1)
                    printf("Index out of range\n");
                else
                    printf("%d\n", num);
                break;
            case 7: //wyświetlenie wartości ostatniego elementu
                if(!lista->tail)
                    printf("List is empty\n");
                else
                    printf("%d\n", lista->tail->data);
                break;
            case 8: //wyświetlenie wartości pierwszego elementu
                if(!lista->head)
                    printf("List is empty\n");
                else
                    printf("%d\n", lista->head->data);
                break;
            case 9: //sprawdzenie czy lista jest pusta
                if(dll_is_empty(lista))
                    printf("1\n");
                else
                    printf("0\n");
                break;
            case 10: //wyświetlenie liczby elementów
                printf("%d\n", dll_size(lista));
                break;
            case 11: //usunięcie wszystkich elementów z listy
                dll_clear(lista);
                break;
            case 12: //wyświetlenie wartości elementu na podanej pozycji
                if(dll_is_empty(lista)){
                    printf("List is empty\n");
                    break;
                }
                printf("Podaj index");
                err = scanf("%d", &index);
                if(err != 1)
                    return printf("Incorrect input"), dll_clear(lista), free(lista), 1;
                if(index < 0)
                    printf("Index out of range\n");
                num = dll_at(lista, index, &err_code);
                if(err_code == 1)
                    printf("Index out of range\n");
                else
                    printf("%d\n", num);
                break;
            case 13: //wyświetlenie wartości wszystkich elementów
                if(dll_is_empty(lista))
                    printf("List is empty\n");
                else{
                    dll_display(lista);
                    printf("\n");
                }
                break;
            case 14: //wyświetlenie wartości wszystkich elementów od tyłu
                if(dll_is_empty(lista))
                    printf("List is empty\n");
                else{
                    dll_display_reverse(lista);
                    printf("\n");
                }
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
}
