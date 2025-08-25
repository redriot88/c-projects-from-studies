#include <stdio.h>

typedef struct {
    char letter;
    int age;
    double avg;
} player_t;

//scan player variables in struct
player_t scanPlayer (void){
    player_t p; //create variable from struct
    printf("Enter the first letter of the player name> ");
    scanf(" %c", &p.letter);

    printf("Enter the age> ");
    scanf(" %d", &p.age);
    
    printf("Enter the batting average> ");
    scanf(" %lf", &p.avg);
    return p;

}

// function to print player structure
void printPlayer (player_t p){
    printf("%c, %d, %.2f\n", p.letter, p.age, p.avg);
}

int main (void){
    player_t player = scanPlayer();
    //call printPlayer(player)
    printPlayer(player);
    return 0;
}
