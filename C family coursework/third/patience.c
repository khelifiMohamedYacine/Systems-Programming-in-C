#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include "patience.h"


#define DECK_SIZE 52
#define MAX_PILES 9

FILE *log_file; // Global file pointer for logging

// Function to shuffle the deck using Fisher-Yates algorithm
void shuffle_deck(int deck[], int size) {
    int i, j, temp; 
    for (i = size - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Function to check if any two visible cards sum to 11
int *addto11(int visible[], int *visible_count) {
    int i, j; 
    for (i = 0; i < *visible_count - 1; i++) {
        for (j = i + 1; j < *visible_count; j++) {
            if (visible[i] + visible[j] == 11) {
                
                visible[i] = visible[*visible_count - 1];
                visible[j] = visible[*visible_count - 2];
                *visible_count -= 2;
                int *ret = malloc(2 * sizeof(int));
                ret[0] = visible[i];
                ret[1] = visible[j];
                return ret; // Return the pair of cards that sum to 11
            }
        }
    }
    return NULL; // No pair found
}

// Function to check if Jack, Queen, and King are all visible
int jqk(int visible[], int *visible_count) {
    int hasJack = 0, hasQueen = 0, hasKing = 0;
    int i; 
    for (i = 0; i < *visible_count; i++) {
        if (visible[i] == 11) hasJack = 1;
        if (visible[i] == 12) hasQueen = 1;
        if (visible[i] == 13) hasKing = 1;
    }
    if (hasJack && hasQueen && hasKing) {
        int new_count = 0;
        for (i = 0; i < *visible_count; i++) {
            if (visible[i] != 11 && visible[i] != 12 && visible[i] != 13) {
                visible[new_count++] = visible[i];
            }
        }
        *visible_count = new_count;
        return 1; // Jack, Queen, and King removed
    }
    return 0; // Not all three are visible
}


// Function to print visible cards to the console
void print_visible(int visible[], int count) {
    int i; 
    for (i = 0; i < count; i++) {
        printf("%d ", visible[i]);
    }
}

// Function to print visible cards to a file
void print_visible_to_file(FILE *file, int visible[], int count) {
    int i; 
    for (i = 0; i < count; i++) {
        fprintf(file, "%d ", visible[i]);
    }
}

// Function to log game events to both console and log file
void print_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);            // Print to console
    vfprintf(log_file, fmt, args); // Print to log file
    va_end(args);
}

// Function contain game logic
int play(int deck[], int verbose) {
    int visible[DECK_SIZE] = {0};  
    int visible_count = 0;         
    int deck_index = 0;            

    // Draw the first two cards
    visible[visible_count++] = deck[deck_index++];
    visible[visible_count++] = deck[deck_index++];

    // Print the initial state
    if (verbose == 1) {
        print_visible_to_file(log_file, visible, visible_count);
        print_visible(visible, visible_count);
        print_log("Cards don't add to 11; start a new pile\n");
    }

    // Game loop
    while (deck_index < DECK_SIZE) {
        // Check if the number of visible piles exceeds the limit
        if (visible_count > MAX_PILES) {
            if (verbose == 1) {
                print_log("you lose!\n");
            }
            return DECK_SIZE - deck_index; // Lose the game
        }

        // Try to remove pairs that sum to 11
        if (addto11(visible, &visible_count)) {
            if (verbose == 1) {
                print_visible_to_file(log_file, visible, visible_count);
                print_visible(visible, visible_count);
                print_log("Cards add to 11; cover with new cards\n");
            }
            continue;
        }

        // Try to remove Jack, Queen, and King
        if (jqk(visible, &visible_count)) {
            if (verbose == 1) {
                print_visible_to_file(log_file, visible, visible_count);
                print_visible(visible, visible_count);
                print_log("J, Q, K (11, 12, 13) visible; cover with new cards\n");
            }
            continue;
        }

        // If no rules apply, draw a new card
        visible[visible_count++] = deck[deck_index++];

        if (verbose == 1) {
            print_visible_to_file(log_file, visible, visible_count);
            print_visible(visible, visible_count);
            print_log("Cards don't add to 11; start a new pile\n");
        }
    }
    // If all cards are removed, the player wins
    if (verbose == 1) {
        print_log("you win!\n");
    }

    return 0; // Win the game 
}

void init_patience() {
    log_file = fopen("tmp.txt", "w");
    if (log_file == NULL) {
        perror("Error opening tmp.txt for writing");
        exit(1);
    }

}

#ifdef PATIENCE_MAIN
int main() {
    init_patience();
    srand(time(NULL));  

    int deck[] = {10, 4, 9, 8, 5, 1, 2, 12, 9, 11, 2, 12, 1, 3, 12, 10, 6, 13, 7, 6, 10,
                  4, 7, 5, 8, 2, 4, 1, 3, 9, 5, 4, 6, 9, 11, 10, 13, 11, 11, 1, 12, 3, 13,
                  2, 5, 13, 7, 3, 7, 6, 8, 8};
    shuffle_deck(deck, DECK_SIZE);

    int win = play(deck, 1);
    const char *newFilename = win == 0 ? "win.txt" : "lose.txt";
    fclose(log_file);
    remove(newFilename); 
    if (rename("tmp.txt", newFilename) != 0) {
        perror("Error renaming file");
        printf("Error code: %d\n", errno);
    }else {
        // Remove tmp.txt after it has been renamed
        remove("tmp.txt"); // Clean up by deleting tmp.txt
    }
    
    return 0;

}
#endif