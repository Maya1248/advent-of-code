#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOOD 0
#define ERROR -1

#define CHUNK 64

int fetch_number(int book_size, char book[book_size][CHUNK], char *wire) {
    // Find where the wire is positioned as a destination
    // Then we back track to get the number
    // Of course it wont be just a number, but a whole circuit board of logic that we must follow
    // We will do exactly that here, go backwards through the logic gates until we finally reach actual hard numbers down the line
    // and work our way up. All of this done automatically via recursion.

    int white_space_count = 0;
    int pos, len, toggle;
    char buff[16];
    //memset(buff, 0, 16);

    for (int index = 0; index < book_size; index++) {
        //printf("index: %d ; current: %s ; against wire: %s \n", index, book[index], wire);
        // Count spaces
        // space before and after the "->" do not count for simplicity.
        // 0 spaces means its a direct variable feed
        // 1 spaces means its "NOT variable"
        // 2 space means its "variable operator variable"

        white_space_count = -2; // 2 spaces we talked about
        len = strlen(book[index]);
        toggle = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (book[index][i] == ' ' && toggle == 0) {
                pos = i + 1;
                toggle = 1;
            }

            if (book[index][i] == ' ') white_space_count++;
        }

        memset(buff, 0, 16);
        int j = 0;
        for (int i = pos; i < len; i++) {
            buff[j] = book[index][i];
            j++;
        }

        // We found the desired variable and now we shall (based on white space count)
        // process the entire string
        if (strcmp(buff, wire) == 0) {
            //printf("%s\n", buff);
            //printf("whitespace: %d\n", white_space_count);
            //printf("full: %s\n", book[index]);
            
            int temp;
            char temp_buff[4];
            memset(temp_buff, 0, 4);
            switch (white_space_count) {
                case 0: // variable -> destination ; Forward variable if variable, return number if its actual number
                    if (sscanf(book[index], "%d ", &temp) != 0) { // IS a number
                        return temp;
                    }
                    
                    if (sscanf(book[index], "%s ", temp_buff) != 1) exit(ERROR);
                    fetch_number(book_size, book, temp_buff); // isnt a number, instead follow piped variable by the book

                    break;
                case 1: // NOT variable -> destination ; Similar to before but now we have to perform a lot of OPERATOR handling...
                
                    break;
                case 2: // variable OP variable -> destination

                    break;
            }

            break;
        }
    }

    return ERROR;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;

    char buffer[CHUNK];
    memset(buffer, 0, CHUNK);

    int book_size = 0;
    while (fgets(buffer, CHUNK, fptr) != NULL) {
        book_size++;
    }
    fclose(fptr);
    memset(buffer, 0, CHUNK);

    // I was too lazy to go over fseek/ftell...
    fptr = fopen("input", "r");
    if (fptr == NULL) return ERROR;
    
    char book[book_size][CHUNK];
    int index = 0;

    // Essentially transfer all of the input data into RAM memory
    // Because we will be accessing it all over the place via recursion
    while (fgets(buffer, CHUNK, fptr) != NULL) {
        buffer[strlen(buffer) - 1] = (char)0;  // Remove the newline.
        strcpy(book[index], buffer);
        memset(buffer, 0, CHUNK);
        index++;
    } 
    fclose(fptr);
    
    // Now we are actually beginning the solution
    printf("Result: %d\n", fetch_number(book_size, book, "a"));

    return GOOD;
}