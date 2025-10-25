#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "patience.h"
#include "histogram.c"

#define DECK_SIZE 52
#define NUM_TRIALS 10000


int* many_plays(int N) {
    int* remaining = calloc(DECK_SIZE + 1, sizeof(int));
    if (remaining == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int deck[DECK_SIZE];
    int j;
    for (j = 0; j < DECK_SIZE; j++) {
        deck[j] = (j % 13) + 1;  // Initialize deck with values 1-13 
    }
    int i;
    for (i = 0; i < N; i++) {
        shuffle_deck(deck, DECK_SIZE);
        int result = play(deck, 0);

        // debug line to check the result
        if (result < 0 || result > DECK_SIZE) {
            fprintf(stderr, "Invalid result from play(): %d\n", result);
        }

        remaining[result]++;
    }

    return remaining;
}




void plot_histogram(int remaining[], int N) {
    FILE* file = fopen("phistogram.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return;
    }

    printf("Plotting histogram...\n");

    double percentages[DECK_SIZE + 1];
    double total_percentage = 0.0;
    double highest_percentage = 0.0;
    int count = 0;
    int i;

    // Calculate percentages and find highest percentage
    for (i = 0; i <= DECK_SIZE; i++) {
        percentages[i] = (double)remaining[i] / N * 100;
        total_percentage += percentages[i];
        count++;

        if (percentages[i] > highest_percentage) {
            highest_percentage = percentages[i];
        }
    }
    double average_percentage = total_percentage / count;

    for (i = 0; i <= DECK_SIZE; i++) {
        int num_stars = (int)((percentages[i] / highest_percentage) * 50);

        fprintf(file, "%d ", i);
        int j;
        for (j = 0; j < num_stars; j++) {
            fprintf(file, "*");
        }
        fprintf(file, " %.2f%%\n", percentages[i]);
    }
    histogram(remaining, percentages, DECK_SIZE + 1, 50);

    // Print the results to both console & file
    printf("\nHighest percentage: %.2f%%\n", highest_percentage);
    printf("Probability of winning a game: %.2f%%\n", average_percentage);
    
    fprintf(file, "\nHighest percentage: %.2f%%\n", highest_percentage);
    fprintf(file, "Probability of winning a game: %.2f%%\n", average_percentage);

    fclose(file);
}




int main() {
    init_patience();
    srand(time(NULL));
    int N = NUM_TRIALS;

    printf("Starting many plays...\n");
    int* remaining = many_plays(N);

    // Plot histogram
    plot_histogram(remaining, N);

    // Free the allocated memory
    free(remaining);
    remove("tmp.txt");
    return 0;
}