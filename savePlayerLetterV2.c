#include <stdio.h>

//define struct player_t as first char letter.
typedef struct {
    char letter;
} player_t;


//savePlayerName function
int savePlayerName (player_t p, char filename[]){
    FILE* fp = fopen(filename, "w");
    if (fp == NULL){
        printf("error\n");
        return 1; 
    }
    fprintf(fp, "%c\n", p.letter); //to write player's letter
    printf("Player name saved.\n");
    fclose(fp);
    return 0; //return 0 for success
}

int main(void){
    player_t player; //declare player

    printf("Enter a letter for a player: ");
    scanf("%c", &player.letter);

    //call savePlayerName with filename
    if (savePlayerName(player, "player.txt") == 0){
        printf("Player name saved in file: player.txt");
    } else {
        printf("Failed to save player name.\n");
    }
    return 0;
}
