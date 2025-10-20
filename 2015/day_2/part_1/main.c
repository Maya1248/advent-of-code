#include <stdio.h>

int get_smallest_area(int l, int w, int h) {
    int a1 = l*w;
    int a2 = w*h;
    int a3 = h*l;

    int smallest = a1;
    if (a2 < smallest) smallest = a2;
    if (a3 < smallest) smallest = a3;
    return smallest;
}

int calculate_surface_area(int l, int w, int h) {
    return 2*l*w + 2*w*h + 2*h*l;
}

int main() {
    FILE *fptr = fopen("input", "r");
    if (fptr == NULL) return 1;

    int l, w, h, result = 0;
    while (fscanf(fptr, "%dx%dx%d", &l, &w, &h) != EOF) {
        result += calculate_surface_area(l, w, h) + get_smallest_area(l, w, h);
    }
    printf("Result: %d\n", result);
 
    fclose(fptr);
    return 0;
}