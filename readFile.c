#include <stdio.h>
#include <string.h>

typedef struct {
    char letter;
} player_t;

int main(){
    FILE* fp = fopen("player.txt", "r");
    char buffer[255];

    if (fp == NULL){
        printf("Error: can't open %s\n", "player.txt");
        return 1;
    }
    fgets(buffer, 255, fp);
    printf("%s", buffer);

    fclose(fp);
    return 0;
}
