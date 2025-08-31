#include <stdio.h>
#include <string.h>

#define WORD_SIZE 16

int main (void){
    char word[WORD_SIZE];
    char checkedLetters[WORD_SIZE];

    int i, j, k; /*int variables to use*/
    int duplicateCount = 0; /*counts total duplicate ACSII letters*/
    int checkedCount = 0;


    printf("Enter a word>\n");
    scanf("%15s", word);
    
    int length = strlen(word); /*store word length*/

    /*count each character*/
    for (i = 0; i < length; i++){
        char currentLetter = word[i];

        /*count if alreadyChecked*/
        int alreadyChecked = 0;
        for (k = 0; k < checkedCount; k++){
            if (checkedLetters[k] == currentLetter) {
                alreadyChecked = 1;
                break;
            }
        }

        if (alreadyChecked) continue;

        /*count current letter*/
        int countLetter = 0;
        for (j = 0; j < length; j++){
            if (word[j] == currentLetter){
                countLetter++;
            }
        }
        /*print if duplicated*/
        if (countLetter > 1){
            printf("Duplicate letter: %c, Occurrences: %d\n", currentLetter, countLetter);
            duplicateCount = 1;
        }

        /*marked letter as checked*/
        checkedLetters[checkedCount++] = currentLetter;
    }
    if (!duplicateCount){
        printf("No duplicates found\n");
    }

    return 0;
}
