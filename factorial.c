#include <stdio.h>

int main(void) {
    int value;
    int factorial = 1;
    scanf("%d", &value);

    for (int i = value; i > 0; i--){
        factorial =  factorial * i;
        //printf("%d x ", i);
    }
    printf("%d\n", factorial);

    return 0;
    }
