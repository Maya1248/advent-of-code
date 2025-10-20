#include <stdio.h>

int get_smallest_ribbon(int l, int w, int h) {
    int o1 = 2 * l + 2 * w;
    int o2 = 2 * l + 2 * h;
    int o3 = 2 * w + 2 * h;

    int smallest = o1;
    if (o2 < smallest) smallest = o2;
    if (o3 < smallest) smallest = o3;
    return smallest;
}

int get_volume(int l, int w, int h) {
    return l * w * h;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return 1;

    int l, w, h, result = 0;
    while (fscanf(fptr, "%dx%dx%d", &l, &w, &h) != EOF) {
        result += get_smallest_ribbon(l, w, h) + get_volume(l, w, h);
    }
    printf("Result: %d\n", result);
 
    fclose(fptr);
    return 0;
}