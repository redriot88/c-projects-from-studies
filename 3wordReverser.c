#include <stdio.h>
#include <string.h>

#define WORD_SIZE 4

int main (void){

    char word[WORD_SIZE]; //need to include '\0'
    char reverse[WORD_SIZE]; //int string

    printf("Enter a word with 3 letters ");
    scanf("%3s", word);

    printf("Word entered: %s\n", word);

    int length = strlen(word);


    for (int i = 0; i < length; i++){
        reverse[i] = word[length -1 - i];
        }
    reverse[length] = '\0';

    printf("Reverse word: %s\n", reverse);

    //
    return 0;
}
