#include <stdio.h>
#include "histogram.c"

//main of demo_histogram
int main() {
    int x[] = {0, 1, 2, 3, 4, 5};
    double H[] = {12.5, 6.4, 10, 7.6, 8, 13};
    int size = 6;
    int scale = 30;

    histogram(x, H, size, scale);

    return 0;
}
