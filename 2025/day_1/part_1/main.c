#include <stdio.h>

#define ERROR -1

// Infinite dial handling.
int handle_dial_math(int dial_position, char movement_orientation, int movement_amount) {
    switch (movement_orientation) {
        case 'L':
            while (dial_position < movement_amount) {
                movement_amount -= dial_position;
                dial_position = 100;
            }
            
            return dial_position - movement_amount;

        case 'R':
            return (dial_position + movement_amount) % 100;
    }
    
    // This should never be reached if everything is correct.
    return ERROR;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    int dial_position = 50;
    int result_counter = 0;

    char movement_orientation;
    int movement_amount;

    while (fscanf(fptr, "%c%d\n", &movement_orientation, &movement_amount) != EOF) {
        dial_position = handle_dial_math(dial_position, movement_orientation, movement_amount);

        if (dial_position == 0) result_counter++;
    }

    printf("Result: %d\n", result_counter);

    fclose(fptr);
    return 0;
}