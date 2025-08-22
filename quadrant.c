#include <stdio.h>

int main (void){
    int x; //initialise int for x coord
    int y; //initialise int for y coord 
    //printf("Enter x and y coordinates (separated by a space):\n");
    do {
        scanf("%d %d", &x, &y);
    
        if (x == 0 && y == 0){
            printf("(x%d, y%d) is at the origin\n", x, y);
        } else if (x < 0 && y > 0){
            printf("(x%d, y%d) is in Quadrant II\n", x, y);
        } else if (x < 0 && y < 0){
            printf("(x%d, y%d) is in Quadrant III\n", x, y);
        } else if (x > 0 && y < 0){
            printf("(x%d, y%d) is in Quadrant IV\n", x, y);
        } else if (x > 0 && y > 0) {
            printf("(x%d, y%d) is in Quadrant I\n", x, y);
        } else if (y == 0) {
            printf("(x%d, y%d) is on the X-axis\n", x, y);
        } else if (x == 0) {
            printf("(x%d, y%d) is on the Y-axis\n", x, y);
        }
    } while (!(x == 0 && y == 0));

    return 0;
}
