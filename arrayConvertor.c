#include <stdio.h>
#include <math.h>

#define ARRAY_SIZE 5 //defined constant for array ARRAY_SIZE

int main(void){
    int inputArray[ARRAY_SIZE];
    int outputArray[ARRAY_SIZE];

    printf("Enter 5 values separated by spaces ");
    for (int i = 0; i < ARRAY_SIZE; i++){
        scanf("%d", &inputArray[i]);
    }
    int n;

    printf("Enter the value of n ");
    scanf("%d", &n);

    printf("Input array is: ");
    for (int j = 0; j < ARRAY_SIZE; j++){
        printf("%d ", inputArray[j]);
    }
    printf("\n");

    printf("Output array is: ");
    for (int j = 0; j < ARRAY_SIZE; j++){
        outputArray[j] = pow(inputArray[j], n);
        printf("%d ", outputArray[j]);
    }
    printf("\n");    
    //assume max is first element
    int maximum = outputArray[0];

    for (int j = 0; j <ARRAY_SIZE; j++){
        if (outputArray[j] > maximum){
            maximum = outputArray[j]; //to update if bigger
        }
    }
    printf("Maximum value in output array: %d", maximum);

    return 0;
}

    return 0;
}
