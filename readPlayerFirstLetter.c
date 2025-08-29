#include <stdio.h>

/**define player_t structure with first char letter**/
typedef struct {
    char letter;
} player_t;

/**readPlayerName function**/
char readPlayerName(char filename[]){
    /**FILE is definedin stdio.h, and make it point to the FILE struct**/
    FILE* fp = fopen(filename, "r");

    /**call to open the file but return and error if unable**/
    if (fp == NULL){
        printf("Error: can't open %s\n", filename);
        return 1;
    }
    /**need a way to scan in?**/
    char letter = getc(fp);

    printf("Player letter is: %c.\n", letter);
    fclose(fp);
    return letter; 
}

int main(void){

    if (readPlayerName("player.txt") != 1){
        printf("Player name read.\n");
    } else {
        printf("Failed to read player name.\n");
    }
    return 0;
}
