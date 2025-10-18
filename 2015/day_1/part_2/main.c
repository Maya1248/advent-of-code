#include <stdio.h>

int main() {
    FILE* fptr = fopen("input", "r");
    if (fptr == NULL) return 1;

    int ch, counter = 0;
    int index_counter = 0;
    while ((ch = fgetc(fptr)) != EOF) {
        index_counter++;

        if (ch == '(') {
            counter++;
        } else if (ch == ')') {
            counter--;
        }

        if (counter == -1) {
            break;
        }
    }

    printf("Result: %d\n", index_counter);

    fclose(fptr);
    return 0;
}
