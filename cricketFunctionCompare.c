#include <stdio.h>

typedef struct {
    double avg; //batting average
} player_t;

//scan player batting averages
player_t scanPlayer (void){
    player_t p;//declaring p

    //user input for player
    printf("Enter the batting average: ");
    scanf("%lf", &p.avg);
    return p;
}


void printPlayer (player_t p1, player_t p2){
    printf("Batting average for Player1: %.2f, Player2: %.2f", p1.avg, p2.avg);
}

int compAB (player_t player1, player_t player2){
    if (player1.avg > player2.avg +10){
        return 1;
    } else if (player2.avg > player1.avg + 10){
        return -1;
    } else {
        //else would have all other combinations i.e. +- 10 range
        return 0;
    }
}


int main (void){
    player_t player1 = scanPlayer();
    player_t player2 = scanPlayer();

    printPlayer(player1, player2);
    printf("\n");

    int result = compAB(player1, player2);
    printf("Comparison results: %d\n", result);

    return 0;
}
