#include <stdio.h>

#define ERROR -1

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    // Adaptable bank_size calculation
    int BANK_SIZE = 0;
    char buffer;
    while (fscanf(fptr, "%c", &buffer) != EOF) {
        if (buffer == '\n') {
            break;
        }
        BANK_SIZE++;
    }
    rewind(fptr);

    int bank_array[BANK_SIZE];
    int counter = 0;

    int result = 0;

    // Store values into an integer array
    while (fscanf(fptr, "%c", &buffer) != EOF) {
        if (buffer == '\n') {
            // Reset
            counter = 0;

            // Find 2 largest numbers
            int biggest = 0;
            int biggest_index = 0;
            
            for (int i = 0; i < BANK_SIZE - 1; i++) {
                if (bank_array[i] > biggest) {
                    biggest = bank_array[i];
                    biggest_index = i;
                }
            }
            
            int second_biggest = 0;
            for (int i = biggest_index + 1; i < BANK_SIZE; i++) {
                if (bank_array[i] > second_biggest) {
                    second_biggest = bank_array[i];
                }
            }
            printf("%d %d\n", biggest, second_biggest);
            //printf("AA\n");
            result += (biggest * 10 + second_biggest);

        } else {
            //printf("AA\n");
            bank_array[counter] = buffer - '0';
            counter++;
        }
    }

    printf("Result: %d\n", result);

    fclose(fptr);
    return 0;
}