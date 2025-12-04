#include <stdio.h>

#define ERROR -1
#define INVALID -10
#define VALID -20

int ten_pow(int num) {
    int result = 10;

    for (int i = 0; i < num - 1; i++) {
        result *= 10;
    }
    
    return result;
}

int check_num_validity(long long num) {
    int size = 0;
    long long temp = num;

    while (temp != 0) {
        temp /= 10;
        size++;
    }

    // Numbers NOT divisible by two Inherently can not fall under INVALID category. 
    if (size % 2 != 0) {
        return VALID;
    }

    long long temp_calc = (long long)ten_pow(size / 2);
    long long first_half = num / temp_calc;
    long long second_half = num % temp_calc;
    
    // If both halves are identical, the number falls under the INVALID category.
    if (first_half == second_half) {
        return INVALID;
    }

    return VALID;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    long long num_1;
    long long num_2;
    char place_holder;
    long long result = 0;

    while (fscanf(fptr, "%lli-%lli", &num_1, &num_2) != EOF) {
        //printf("interpreted: %lli - %lli\n", num_1, num_2);
        for (long long i = num_1; i <= num_2; i++) {
            if (check_num_validity(i) == INVALID) {
                result += i;
            }
        }

        // Either stores the comma and moves the internal file pointer OR at the end which has no comma it returns EOF
        // We ignore the EOF because there 2 places in this "while" code section where we can perform EOF checking, i picked one at the top.
        fscanf(fptr, ",", &place_holder); 
    }

    printf("Result: %lli\n", result);

    fclose(fptr);
    return 0;
}