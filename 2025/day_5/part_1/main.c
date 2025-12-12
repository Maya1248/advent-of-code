#include <stdio.h>

#define SUCCESS 0
#define ERROR -1

int is_num_between_IDs(long long num, int MAP_SIZE, long long MAP[MAP_SIZE][2]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        if (num >= MAP[i][0] && num <= MAP[i][1]) {
            return SUCCESS;
        }
    }
    return ERROR;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    // Interpret input and prepare for the map construction
    int MAP_SIZE = 0;
    {
        long long num_1, num_2;
        while (fscanf(fptr, "%lli-%lli", &num_1, &num_2) == 2) {
            //printf("%lli-%lli\n", num_1, num_2);
            MAP_SIZE++;
        }
        rewind(fptr);
    }
    
    // Construct the map
    long long MAP[MAP_SIZE][2];
    {
        long long num_1, num_2;
        int counter = 0;
        while (fscanf(fptr, "%lli-%lli", &num_1, &num_2) == 2) {
            MAP[counter][0] = num_1;
            MAP[counter][1] = num_2;
            counter++;
        }
    }

    // Find amount of fresh IDs
    int result = 0;
    {
        long long num;
        while (fscanf(fptr, "%lli", &num) != EOF) {
            //printf("%lli\n", num);

            if (is_num_between_IDs(num, MAP_SIZE, MAP) == SUCCESS) {
                result++;
            }
        }
    }
    printf("Result: %d\n", result);

    fclose(fptr);
    return SUCCESS;
}