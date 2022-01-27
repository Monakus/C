#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 60

//CONWAY'S GAME OF LIFE
//CLion's terminal settings:
//Font:12
//Line spacing: 0.6

void draw(int *tab, int size){
    char line[SIZE+1] = {0};
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j, tab++) {
            if(*tab == 1){
                line[j] = '#';
            }else if(*tab == 0){
                line[j] = '.';
            }
        }
        printf("%s\n", line);
    }
}

void newgen(int *tab, int *tab2, int size){
    int sum = 0;
    int newTab[size][size];
    int *pocz = tab, *pocz2 = tab2;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j, tab++) {
            newTab[i][j] = *tab;
        }
    }
    tab = pocz;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j, tab++, tab2++) {
            for (int k = -1; k < 2; ++k) {
                for (int l = -1; l < 2; ++l) {
                    int x = (i+k+size)%size;
                    int y = (j+l+size)%size;
                    sum += newTab[x][y];
                }
            }
            sum -= newTab[i][j];
            if(*tab == 1 && (sum == 2 || sum == 3)){ //Any live cell with two or three live neighbours survives.
                *tab2 = 1;
            }else if(*tab == 0 && sum == 3){ //Any dead cell with three live neighbours becomes a live cell.
                *tab2 = 1;
            }else{ //All other live cells die in the next generation. Similarly, all other dead cells stay dead.
                *tab2 = 0;
            }
            sum = 0;
        }
    }
    tab = pocz;
    tab2 = pocz2;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j, tab++, tab2++){
            *tab = *tab2;
        }
    }
    draw(pocz, size);
}

int main() {
    int tab[SIZE][SIZE], tab2[SIZE][SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            tab[i][j] = rand() % 2;
        }
    }

    int cycles = 0;
    while(cycles < 1000){
        newgen(&tab[0][0], &tab2[0][0], SIZE);
        cycles++;
        //usleep(800);
        sleep(1);
        system("cls");
    }
    return 0;
}
