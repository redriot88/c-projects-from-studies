#include <stdio.h>

int main (void){
    int numerator;
    int denominator;
    int wholeNumber;
    int remainder;

    printf("Enter the numerator and denominator separated by a space> ");
    scanf("%d %d", &numerator, &denominator);

    wholeNumber = numerator / denominator;
    remainder = numerator % denominator;
    //printf("%d\n", wholeNumber); //to check whole number
    //printf("%d\n", remainder); //to check remainder

    printf("%d %d / %d\n", wholeNumber, remainder, denominator);
    return 0;
}
