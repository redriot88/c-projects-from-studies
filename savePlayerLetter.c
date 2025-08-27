#include <stdio.h>

//define struct player_t as first char letter.
typedef struct {
    char letter;
} player_t;


//savePlayerName function
int savePlayerName (player_t p, char filename []){
    FILE* fp = fopen("player.txt", "w");
    if (fp == NULL){
        printf("error\n");
        return 1; 
    }
    fprintf(fp, "%c\n", p.letter); //to write player's letter
    fclose(fp);
    return 0; //return 0 for success
}

int main(void){
    player_t player; //declare player
    
    FILE* fp = NULL; //file stream
    fp = fopen("player.txt", "w");
    // FILE* fopen(const char* filename, const char* mode); 


    if (fp == NULL){
        printf("file error\n");
        return 1;
    } else {
        scanf("%c", &player.letter);

        savePlayerName(player, "player.txt");
        
        fclose(fp);
        printf("Player name saved.\n");

        return 0;
    }
}
