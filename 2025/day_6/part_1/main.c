#include <stdio.h>

#define ERROR -1
#define SUCCESS 0

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    // Prepare for map construction
    int ROW_LIMIT = 0;
    int COL_LIMIT = 0;
    {
        char ch;
        int test;
        int toggle = 0;
        while ((ch = fgetc(fptr)) != EOF) {
            
            // Ignore everything that is Not a digit in the ascii table
            // Move file pointer back by 1 once you detect it, otherwise you interpret "23" instead of the full "123"
            if (ch - '0' >= 0 && ch - '0' <= 9) {
                fseek(fptr, -1, SEEK_CUR);

                fscanf(fptr, "%d", &test);
                if (toggle == 0) {
                    COL_LIMIT++;
                }
                
            } else if (ch == '\n') {
                ROW_LIMIT++;
                toggle = 1;
            }
        }
    }
    rewind(fptr);

    // Construct the map
    ROW_LIMIT--;
    int MAP[ROW_LIMIT][COL_LIMIT];
    char OPERATIONS[COL_LIMIT];
    {
        char ch;
        int test;
        int row = 0;
        int col = 0;
        int counter = 0;
        while ((ch = fgetc(fptr)) != EOF) {
            
            // Ignore everything that is Not a digit in the ascii table
            // Move file pointer back by 1 once you detect it, otherwise you interpret "23" instead of the full "123"
            if (ch - '0' >= 0 && ch - '0' <= 9) {
                fseek(fptr, -1, SEEK_CUR);

                fscanf(fptr, "%d", &test);
                MAP[row][col] = test;
                col++;
                
            } else if (ch == '\n') {
                row++;
                col = 0;
            } else if (ch == '*' || ch == '+') {
                OPERATIONS[counter] = ch;
                counter++;   
            }
        }
    }
    fclose(fptr);
    
    // Do the math :3
    long long RESULT_PARTS[COL_LIMIT];
    {
        for (int col = 0; col < COL_LIMIT; col++) {
            char ch = OPERATIONS[col];
            for (int row = 0; row < ROW_LIMIT; row++) {
                if (ch == '+') {
                    if (row == 0) RESULT_PARTS[col] = 0;
                    RESULT_PARTS[col] += MAP[row][col];
                } else {
                    if (row == 0) RESULT_PARTS[col] = 1;
                    RESULT_PARTS[col] *= MAP[row][col];
                }
            }
        }
    }

    // Calculate result
    long long result = 0;
    {
        for (int i = 0; i < COL_LIMIT; i++) {
            result += RESULT_PARTS[i];
        }
    }
    printf("Result: %lli\n", result);

    return SUCCESS;
}