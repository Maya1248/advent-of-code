#include <stdio.h>
#include <string.h>

#define ERROR -1
#define INVALID -10
#define VALID -20

long long check_num_validity(long long num) {
    int size = 0;
    long long temp = num;

    while (temp != 0) {
        temp /= 10;
        size++;
    }

    //printf("SIZE/2: %d\n", size/2);
    char str_num[32];
    
    int pass;
    sprintf(str_num, "%lli", num);

    
    for (int substr_size = 1; substr_size <= (size / 2); substr_size++) {
        if (size % substr_size != 0) {
            continue;
        }

        pass = INVALID;

        char buffer[32];
        
        strncpy(buffer, str_num, substr_size);
        
        //printf("strncpy(%s, %s, %d)\n", buffer, str_num, substr_size);

        for (int i = 0; i < (size - substr_size + 1); i += substr_size) {
            char temp_buffer[32];
            memcpy(temp_buffer, &str_num[i], substr_size);

            //printf("%s %s\n", buffer, temp_buffer);

            if (strcmp(buffer, temp_buffer) != 0) {
                memset(temp_buffer, 0, 32);
                pass = VALID;
                break;
            }
            memset(temp_buffer, 0, 32);
        }
        memset(buffer, 0, 32);

        if (pass == INVALID) {
            break;
        }
    }

    return pass;
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