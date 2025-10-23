#include <stdio.h>

#define STR_LEN 16
#define GOOD 1
#define NOT_GOOD 0
#define ERROR -1

int is_string_good(char *str_input) {
    int toggle_rule_2 = 0;

    for (int i = 0; i < STR_LEN - 2; i++) {
        if (str_input[i] == str_input[i + 2]) {
            toggle_rule_2 = 1;
            break;
        }
    }

    if (toggle_rule_2 == 0) return NOT_GOOD;

    // Rule 1
    // Ok so since the rule claims "at least 2", this simplifies it
    // as we are essentially looking for the first occurence of a duplicate pair
    // p1 and p2 are "original" pair and we are searching for their duplicate p3 and p4
    // if none are found, attempt the next pair, and so on.
    // if none are found entirely, continue onward toward "not good" return

    char p1, p2, p3, p4;
    for (int i = 0; i < STR_LEN - 3; i++) {
        p1 = str_input[i];
        p2 = str_input[i + 1];

        for (int j = i + 2; j < STR_LEN - 1; j++) {
            p3 = str_input[j];
            p4 = str_input[j + 1];

            if (p1 == p3 && p2 == p4) return GOOD;
        }
    }

    return NOT_GOOD;
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