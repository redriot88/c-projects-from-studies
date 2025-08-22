#include <stdio.h>

int main (void){
    int height = 4; //trap height on y-axis
    
    /** Trapezoid 
    We can build 2 triangles and 1 square
    **/

    //top triangle where it is shifted due to the space character
    for (int i = 1; i < height; i++){
        for (int j = 0; j < i; j++){
            printf("+ ");
        }
        printf("\n");
    }

        //printing the middle square
    for (int i = 0; i < height; i++){
        for (int j = 0; j < height; j++){
            printf("+ ");
        }
        printf("\n");
    }

    //bottom triangle shifted due to space
    for (int i = height - 1; i > 0; i--){
        for (int j = 0; j < i; j ++){
            printf("+ ");
        }
        printf("\n");
    }
    

    return 0;
}
