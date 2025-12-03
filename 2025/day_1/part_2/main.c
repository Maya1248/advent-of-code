#include <stdio.h>

#define ERROR -1

int absolute(int number) {
    if (number < 0) return number * -1;
    return number;
}

// Infinite dial handling.
int handle_dial_math(int dial_position, char movement_orientation, int movement_amount, int *result_counter) {
    switch (movement_orientation) {
        case 'L':
            // Translate negative into positive because its easier to work with
            // Here we pretend we are actually going up so we can exploit the privilege of the mod (%) operator
            // Also (% 100) for the edge case of ending and then starting on a 0.
            int dial_position_negated = (100 - dial_position) % 100;

            int cross_overs = (int)((dial_position_negated + movement_amount) / 100);
            (*result_counter) += cross_overs;

            int temp = (dial_position_negated + movement_amount) % 100;
            
            // And translate back into negative territory and return dial position
            temp = 100 - temp;
            return temp % 100;

        case 'R':
            int cross_overs_2 = (int)((dial_position + movement_amount) / 100);
            (*result_counter) += cross_overs_2;
            return (dial_position + movement_amount) % 100;
    }
    
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
        // This time, we have to count ANY TIME 0 is touched/crossed over.
        dial_position = handle_dial_math(dial_position, movement_orientation, movement_amount, &result_counter);

        printf("dial position: %d\n", dial_position);
    }

    printf("Result: %d\n", result_counter);

    fclose(fptr);
    return 0;
}