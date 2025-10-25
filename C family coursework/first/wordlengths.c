#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "histogram.c" 

extern void histogram(int *x, double *y, int n, int width);
extern int* histogram_lengths(char **strings, int n);

void read_file_and_process(char *filename) {
    FILE *file = fopen(filename, "r"); // open the file
    if (!file) {
        perror("Unable to open file");
        exit(1);
    }

    // Allocate memory for an array of strings (words)
    char **words = (char **)malloc(55564 * sizeof(char *));  // Initial capacity for 55564 words knowin that the file have 55562 eword in it 
    if (words == NULL){
        fprintf(stderr,"Couldn't allocate memory");
        exit(1);
    }

    int count = 0;
    char buffer[100];

    // Read the file word by word
    while (fscanf(file, "%s", buffer) != EOF) {
        char *word = (char *)malloc(strlen(buffer) + 1);  // Allocate memory for words including the nulls 
        if (word == NULL){
            fprintf(stderr,"Couldn't allocate memory");
            exit(1);
        }
        strcpy(word, buffer);
        words[count] = word;  // Copying the word into the array
        count++;
    }
    fclose(file);

    // Call histogram_lengths to get word length 
    int *lengths = histogram_lengths(words, count);

    // Find the maximum word length
    int max_length = 0;
    int i;  
    for (i = 0; i < count; i++) {
        int len = strlen(words[i]);
        if (len > max_length) {
            max_length = len;
        }
    }

    // Allocate memory for the percentages array
    double *percentages = (double *)malloc((max_length + 1) * sizeof(double));
    if (percentages == NULL){
        fprintf(stderr,"Couldn't allocate memory");
        exit(1);
    }

    for (i = 0; i <= max_length; i++) {
        percentages[i] = (double)lengths[i] / count * 100.0;  
    }

    // Prepare the x values (word lengths)
    int *x_values = (int *)malloc((max_length + 1) * sizeof(int));
    for (i = 0; i <= max_length; i++) {
        x_values[i] = i;  // The x-axis is for the word lengths
    }

    // Call the histogram function to print the histogram
    histogram(x_values, percentages, max_length + 1, 30);

    // Cleanup memory
    free(lengths);
    free(percentages);
    free(x_values);
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }


    read_file_and_process(argv[1]);
    return 0;
}

