#include <stdio.h>

#define STR_LEN 16
#define GOOD 1
#define NOT_GOOD 0
#define ERROR -1

int is_string_good(char *str_input) {
    // Does NOT contain "ab", "cd", "pq", "xy"
    // Contains at least one double character
    int double_toggle = 0;

    for (int i = 0; i < STR_LEN - 1; i++) {
        // I may forgo "else if" for "if" purely due to the existence of immediate return statements
        // Result being, code read-ability.

        if (str_input[i] == 'a' && str_input[i + 1] == 'b') return NOT_GOOD;
        if (str_input[i] == 'c' && str_input[i + 1] == 'd') return NOT_GOOD;
        if (str_input[i] == 'p' && str_input[i + 1] == 'q') return NOT_GOOD;
        if (str_input[i] == 'x' && str_input[i + 1] == 'y') return NOT_GOOD;

        if (double_toggle == 0 && str_input[i] == str_input[i + 1]) double_toggle = 1;
    }

    // No double characters present.
    if (double_toggle == 0) return NOT_GOOD;

    int vowel_counter = 0;

    for (int i = 0; i < STR_LEN; i++) {
        if (str_input[i] == 'a') vowel_counter++;
        else if (str_input[i] == 'e') vowel_counter++;
        else if (str_input[i] == 'i') vowel_counter++;
        else if (str_input[i] == 'o') vowel_counter++;
        else if (str_input[i] == 'u') vowel_counter++;
    }

    // Does contain at least 3 vowels ("aeiou")
    if (vowel_counter < 3) return NOT_GOOD;

    return GOOD;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    // newline is the 17th invisible char, and it must be accounted for
    // since we do not need to process it, we are allocating space for it 
    // and Forever ignoring it.
    char str_input[STR_LEN + 1];
    int nice_counter = 0;

    while (fread(str_input, sizeof(char), STR_LEN + 1, fptr) != 0) {
        if (is_string_good(str_input) == GOOD) nice_counter++;
    }
    
    printf("Result: %d\n", nice_counter);

    fclose(fptr);
    return 0;
}