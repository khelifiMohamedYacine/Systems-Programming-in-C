#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void histogram(int *x, double *y, int n, int width) {
    // Find the maximum value in the array y
    double max_value = y[0];
    int i;  
    for (i = 1; i < n; i++) {
        if (y[i] > max_value) {
            max_value = y[i];
        }
    }

    // Draw the histogram
    for (i = 0; i < n; i++) {
        // Calculate the number of stars for the current value
        int num_stars = (int)((y[i] / max_value) * width);
        printf("%d ", i);  
        int j;
        for (j = 0; j < num_stars; j++) {
            printf("*");
        }
        printf(" %.1f\n", y[i]);  
    }
}


int* histogram_lengths(char **strings, int n) {  // Change return type to int* here
    // Find the maximum string length
    int max_len = 0;
    int i;  
    for (i = 0; i < n; i++) {
        int len = strlen(strings[i]);
        if (len > max_len) {
            max_len = len;
        }
    }

    // Allocate memory for the histogram (frequency of lengths)
    int *lengths_histogram = (int *)calloc(max_len + 1, sizeof(int)); 

    // Count the frequency of each string length
    for (i = 0; i < n; i++) {
        int len = strlen(strings[i]);
        lengths_histogram[len]++;  
    }

    return lengths_histogram;  
}

