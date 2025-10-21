#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Coordinate;

void add_coordinate(Coordinate **coordinates, int *size, int x, int y) {
    Coordinate *tmp = realloc(*coordinates, (*size + 1) * sizeof(Coordinate));
    
    if (tmp == NULL) {
        free(*coordinates);
        perror("Re-allocation error");
        exit(1);
    }
    *coordinates = tmp;
    (*coordinates)[*size].x = x; 
    (*coordinates)[*size].y = y;
    (*size)++;
}

int search_coordinate(Coordinate **coordinates, int size, int x, int y) {
    for (int index = 0; index < size; index++) {
        if ((*coordinates)[index].x == x && (*coordinates)[index].y == y) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return 1;

    Coordinate *coordinates;
    int size = 0;

    int x = 0;
    int y = 0;
    add_coordinate(&coordinates, &size, x, y);

    // Very crude, I know. I felt lazy.
    // x and y shall always represent the latest Santa position
    char ch;
    while (fscanf(fptr, "%c", &ch) != EOF) {
        if (ch == '^') {
            // [0, 0+1]
            y++;

            if (search_coordinate(&coordinates, size, x, y) == 0) {
                add_coordinate(&coordinates, &size, x, y);
            }
        } else if (ch == '>') {
            // [0+1, 0]
            x++;

            if (search_coordinate(&coordinates, size, x, y) == 0) {
                add_coordinate(&coordinates, &size, x, y);
            }
        } else if (ch == 'v') {
            // [0, 0-1]
            y--;

            if (search_coordinate(&coordinates, size, x, y) == 0) {
                add_coordinate(&coordinates, &size, x, y);
            }
        } else if (ch == '<'){
            // [0-1, 0]
            x--;

            if (search_coordinate(&coordinates, size, x, y) == 0) {
                add_coordinate(&coordinates, &size, x, y);
            }
        }
    }

    // The size of the non-duplicate coordiante array is the result
    printf("Result: %d\n", size);

    free(coordinates);
    fclose(fptr);
    return 0;
}