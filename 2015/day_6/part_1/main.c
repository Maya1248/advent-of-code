#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

void command(int grid[1000][1000], int x1, int y1, int x2, int y2, char *action) {
    if (strcmp(action, "on") == 0) {
        for (int y = y1; y < y2 + 1; y++) {
            for (int x = x1; x < x2 + 1; x++) {
                grid[x][y] = 1;
            }
        }
    } else if (strcmp(action, "off") == 0) {
        for (int y = y1; y < y2 + 1; y++) {
            for (int x = x1; x < x2 + 1; x++) {
                grid[x][y] = 0;
            }
        }
    } else if (strcmp(action, "toggle") == 0) {
        for (int y = y1; y < y2 + 1; y++) {
            for (int x = x1; x < x2 + 1; x++) {
                if (grid[x][y] == 1) grid[x][y] = 0;
                else grid[x][y] = 1;
            }
        }
    }
}

// Feel free to crap on this code, i am beyond exhausted as im writing this, but too stubbron to not have all green dots on github...

int main() {
    char buffer[64];
    char action[10];
    int grid[1000][1000];
    int x1, x2, y1, y2;

    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;
    
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            grid[i][j] = 0;
        }
    }

    memset(buffer, 0, 64);
    memset(action, 0, 10);
    while (fgets(buffer, 64, fptr) != NULL) {
        // Due to inconsistent word count
        // Process input
        // turn and toggle
        if (buffer[1] == 'u') { // action is either on or off
            sscanf(buffer, "%*s %s %d,%d %*s %d,%d", action, &x1, &y1, &x2, &y2);
        } else if (buffer[1] == 'o') { // action is toggle
            sscanf(buffer, "%s %d,%d %*s %d,%d", action, &x1, &y1, &x2, &y2);
        }

        command(grid, x1, y1, x2, y2, action);

        memset(buffer, 0, 64);
        memset(action, 0, 10);
    }

    // Count 1s
    int result = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (grid[i][j] == 1) result++;
        }   
    }

    printf("Result: %d\n", result);

    fclose(fptr);
    return 0;
}