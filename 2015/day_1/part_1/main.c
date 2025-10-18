#include <stdio.h>

int main() {
    FILE* fptr = fopen("input", "r");
    if (fptr == NULL) return 1;

    int ch, counter = 0;
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch == '(') {
            counter++;
        } else if (ch == ')') {
            counter--;
        }
    }

    printf("Result: %d\n", counter);

    fclose(fptr);
    return 0;
}
