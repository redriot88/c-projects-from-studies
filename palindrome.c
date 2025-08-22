#include <stdio.h>
#include <string.h>

#define WORD_SIZE 15

// void palindromeChecker(){
//     //
// }

int main (void){

    char word[WORD_SIZE]; //need to include '\0'
    char reverse[WORD_SIZE]; //int string

    printf("Enter a word: ");
    scanf("%14s", word);

    printf("Word entered: %s\n", word);

    int length = strlen(word);


    for (int i = 0; i < length; i++){
        reverse[i] = word[length -1 - i];
        }
    reverse[length] = '\0';

    printf("Reverse word: %s\n", reverse);

    //to check if palindrome
    int result = strcmp(word, reverse);

    if (result == 0){
        //printf("Is a palindrome.\n");
    } else {
        //printf("Is not a palindrome.\n");
        return 0;
    }
    //return 0;
}
