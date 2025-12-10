#include <stdio.h>

#define SUCCESS 0
#define ERROR -1

// Practicing a new coding habbit of adding scopes within the main method
// Because i found myself having a headache due to variable name conflicts dancing all over each other...
// I am NOT creative when it comes to naming.

int scan_paper_rolls(int ROW_LIMIT, int COL_LIMIT, char map[ROW_LIMIT][COL_LIMIT], int row, int col) {
    // Box to be searched.
    int begin_row = row - 1;
    int begin_col = col - 1;
    int end_row = row + 1;
    int end_col = col + 1;

    // Filter out edge cases.
    if (begin_row < 0) begin_row = 0;
    if (begin_col < 0) begin_col = 0;
    if (end_row >= ROW_LIMIT) end_row = ROW_LIMIT - 1;
    if (end_col >= COL_LIMIT) end_col = COL_LIMIT - 1;
    
    // Perform search
    // Note: exclude SELF from said search
    int counter = -1;
    for (int i = begin_row; i <= end_row; i++) {
        for (int j = begin_col; j <= end_col; j++) {
            if (map[i][j] == '@' || map[i][j] == 'x') {
                counter++;
            }

//            printf(" %c ", map[i][j]);
        }
        //printf("\n");
    }
  //  printf("\n");

    // Perform check
    if (counter < 4) {
        return SUCCESS;
    }

    return ERROR;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    // Get 2D array size
    int ROW_LIMIT = 0, COL_LIMIT = 0;
    {
        char chr;
        int q_toggle = 0;
        while ((chr = fgetc(fptr)) != EOF) {
            if (chr == '\n') {
                q_toggle = 1;
                COL_LIMIT++;
            }

            if (q_toggle == 0) {
                ROW_LIMIT++;
            }
        }
        //printf("SIZE: %d : %d\n", ROW_LIMIT, COL_LIMIT);
    }
    rewind(fptr);

    // Construct map
    char map[ROW_LIMIT][COL_LIMIT];
    {
        int row = 0;
        int col = 0;
        char chr;
        while (row < ROW_LIMIT) {
            chr = fgetc(fptr);

            if (chr == '\n') {
                col = 0;
                row++;
            } else {
                map[row][col] = chr;
                col++;
            }
        }
    }
    fclose(fptr);
    
    // A clean plate, only remaining existing variables are map[][], ROW_LIMIT, COL_LIMIT, result.
    int result = 0;
    {
        //int max_paper_rolls_excl = 4;
        //char paper_symbol = '@';

        while (1 == 1) { // Feel free to crucify me for this.
            int temp_buffer = 0;

            for (int row = 0; row < ROW_LIMIT; row++) {
                for (int col = 0; col < COL_LIMIT; col++) {
                    if (map[row][col] != '@') continue;

                    if (scan_paper_rolls(ROW_LIMIT, COL_LIMIT, map, row, col) == SUCCESS) {
                        map[row][col] = 'x';
                        temp_buffer++;
                    }
                }
            }
            result += temp_buffer;

            // Now that we have logged every to-be-removed site. we actually remove them
            for (int row = 0; row < ROW_LIMIT; row++) {
                for (int col = 0; col < COL_LIMIT; col++) {
                    if (map[row][col] == 'x') map[row][col] = '.';
                }
            }

            if (temp_buffer == 0) break;
        }
    }

    // Debug map dump
    /*for (int i = 0; i < ROW_LIMIT; i++) {
        for (int j = 0; j < COL_LIMIT; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }*/

    printf("Result: %d\n", result);

    return SUCCESS;
}