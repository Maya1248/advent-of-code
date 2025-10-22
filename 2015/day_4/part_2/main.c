#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

int check_result(unsigned char *result) {
    // Its hex, soo for 6 chars of 0, its actually 3 hex values
    if (result[0] != 0 || result[1] != 0 || result[2] != 0) return -1;

    return 0;
}

void print_result(unsigned char *result) {
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", result[i]);
    }  
    printf("\n");
}

int main() {
    unsigned char *input = "iwrupvqb";
    unsigned char copy[16];
    unsigned char result[MD5_DIGEST_LENGTH];

    memset(copy, 0, sizeof(copy));
    strcat(copy, input);

    int attempt = 1;
    char attempt_string[16];
    memset(attempt_string, 0, sizeof(attempt_string));
    
    while (1 == 1) {
        sprintf(attempt_string, "%d", attempt);
        strcat(copy, attempt_string);

        MD5((unsigned char*)copy, strlen(copy), result);
        if (check_result(result) == 0) {
            printf("Result: %d\n", attempt);
            break;
        }

        memset(attempt_string, 0, sizeof(attempt_string));
        memset(copy, 0, sizeof(copy));
        strcat(copy, input);
        attempt++;
    }

    return 0;
}
