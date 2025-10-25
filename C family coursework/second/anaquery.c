#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 25000 

// Function to compare characters (used for sorting)
int compare_chars(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

// Function to generate the sorted key of a word
void sorted_key(char *word, char *key) {
    strcpy(key, word);
    qsort(key, strlen(key), sizeof(char), compare_chars);  
}

// Function to read words from a file
int read_words(const char *filename, char words[MAX_WORDS][MAX_WORD_LENGTH]) {
    FILE *file;
    int count = 0;

    file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    while (count < MAX_WORDS && fscanf(file, "%49s", words[count]) == 1) {
        count++;
    }

    fclose(file);
    return count;
}

// Function to display the anagrams of a word
void find_anagrams(const char *word, char words[MAX_WORDS][MAX_WORD_LENGTH], int word_count) {
    char key[MAX_WORD_LENGTH];
    char temp_key[MAX_WORD_LENGTH];
    int i;
    int found = 0;  

    sorted_key((char *)word, key);  // Generate sorted key of word

    printf("Anagrams of '%s' (key: %s):\n", word, key);  

    for (i = 0; i < word_count; i++) {
        sorted_key(words[i], temp_key);  
        if (strcmp(key, temp_key) == 0) {  // If the keys are identical, it is an anagram
            printf("%s ", words[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No anagrams found.");
    }
    printf("\n");
}

int main() {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    char user_word[MAX_WORD_LENGTH];
    int n;

    setlocale(LC_ALL, "");  // To avoid problems with accented characters

    // Read words from a file
    n = read_words("words.txt", words);
    if (n == -1) {
        return 1;
    }

    printf("Total number of words read: %d\n", n);

    // Ask the user for a word and display its anagrams
    while (1) {
        printf("Enter a word (or 'exit' to quit) : ");
        scanf("%s", user_word);

        // Exit if the user enters "exit"
        if (strcmp(user_word, "exit") == 0) {
            break;
        }

        // find and show anagrams
        find_anagrams(user_word, words, n);
    }

    return 0;
}
