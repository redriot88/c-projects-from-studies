#include <stdio.h>

int main (void){
    int width = 5;
    int height = 10;

    for (int row = 0; row < height; row++){
        for (int column = 0; column < width; column++){
            printf("+");
        }
        printf("\n");
    }
}
