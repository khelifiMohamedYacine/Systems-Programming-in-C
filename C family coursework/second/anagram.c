#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "histogram.c"


#define MAX_WORD_LENGTH 50
#define MAX_WORDS 250000

// Define structure to represent a node for each word in a linked list
typedef struct WordNode {
    char word[MAX_WORD_LENGTH];  
    struct WordNode *next;  
} WordNode;

// Define structure to represent a node for each anagram group
typedef struct AnagramNode {
    char key[MAX_WORD_LENGTH];  
    WordNode *words;  
    struct AnagramNode *next;  
} AnagramNode;

// comparing two characters 
int compare_chars(const void *a, const void *b) {
    return *(char *)a - *(char *)b;
}

// Function to sort the characters of a word 
void sorted_key(char *word, char *key) {
    strcpy(key, word);  
    qsort(key, strlen(key), sizeof(char), compare_chars);  
}


// Function to insert a word into an anagram list
AnagramNode* insert_anagram(AnagramNode *head, char *word) {
    char key[MAX_WORD_LENGTH];
    sorted_key(word, key);  
    
    
    AnagramNode *prev = NULL, *current = head;
    while (current && strcmp(current->key, key) < 0) {
        prev = current;
        current = current->next;
    }
    
    // If the anagram group already exists, add the word to the existing group
    if (current && strcmp(current->key, key) == 0) {
        WordNode *newWord = (WordNode *)malloc(sizeof(WordNode));
        if (!newWord) {
            fprintf(stderr, "memory allocation error\n");
            exit(1);
        }
        strcpy(newWord->word, word);  
        newWord->next = current->words;  
        current->words = newWord;  
        return head;
    }

    // Create a new AnagramNode and insert it into the list
    AnagramNode *newNode = (AnagramNode *)malloc(sizeof(AnagramNode));
    if (!newNode) {
        fprintf(stderr, "memory allocation error\n");
        exit(1);
    }
    strcpy(newNode->key, key);  

    WordNode *newWord = (WordNode *)malloc(sizeof(WordNode));  
    if (!newWord) {
        fprintf(stderr, "memory allocation error\n");
        exit(1);
    }
    strcpy(newWord->word, word);  
    newWord->next = NULL;  

    newNode->words = newWord;  
    newNode->next = current;  

    if (prev) {
        prev->next = newNode;
        return head;
    } else {
        return newNode;
    }
}

// Function to build the anagram list from an array of words
AnagramNode* make_anagram_list(char **words, int n) {
    AnagramNode *head = NULL;
    int i; 
    for (i = 0; i < n; i++) {
        head = insert_anagram(head, words[i]);  
    }
    return head;
}

// Function to print all anagram groups that contain more than one word
void print_anagrams(AnagramNode *head) {
    while (head) {
        WordNode *wordList = head->words;
        int count = 0;
        WordNode *temp = wordList;
        // Count the number of words in the current anagram group
        while (temp) {
            count++;
            temp = temp->next;
        }

        // If there are more than one word in this anagram group, print it
        if (count > 1) {
            printf("Sorted key : %s -> ", head->key);
            while (wordList) {
                printf("%s ", wordList->word);
                wordList = wordList->next;
            }
            printf("\n");
        }
        head = head->next;  
    }
}


// Function to read words from a file into an array of strings
int read_words(const char *filename, char **words) {
    FILE *file = fopen(filename, "r");  
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int count = 0;
    // Read words from the file until the maximum word count is reached
    while (count < MAX_WORDS && fscanf(file, "%49s", words[count]) == 1) {
        count++;
    }

    fclose(file);  
    return count;  
}


// Function to free all memory allocated for the anagram list
void free_anagram_list(AnagramNode *head) {
    while (head) {
        WordNode *wordList = head->words;
        while (wordList) {
            WordNode *temp = wordList;
            wordList = wordList->next;
            free(temp);  // Free each word node
        }
        AnagramNode *temp = head;
        head = head->next;
        free(temp);  // Free the anagram node
    }
}

// Function to plot the histogram of anagram group sizes
void plot_histogram(AnagramNode *head) {
    int histograms[13] = {0};  
    double logs[13] = {0};  
    while (head) {
        int count = 0;
        WordNode *wordList = head->words;
        // Count the number of words in the current anagram group
        while (wordList) {
            count++;
            wordList = wordList->next;
        }
        // If the group size is between 2 and 12, increment the corresponding histogram 
        if (count >= 2 && count <= 12) {
            histograms[count]++;
        }

        head = head->next;  
    }

    // Print the histogram of log10 
    printf("\nHistogram (log10 of the number of anagram groups) :\n");
    int i; 
    for (i = 2; i <= 12; i++) {
        if (histograms[i] > 0) {
            logs[i] = log10(histograms[i]); 
            printf("V = %d : log10(%d) = %.2f\n", i, histograms[i], log10(histograms[i]));
        } else {
            logs[i] = 0;
            printf("V = %d : log10(0) = - (no-group)\n", i);
        }
    }
    // Print the histogram chart
    int size = sizeof(histograms) / sizeof(histograms[0]);
    int width = 12;
    printf("-----------histogram------------\n");
    histogram(histograms, logs, size, width);  
}


int main() {

    // memory allocation
    char **words = malloc(MAX_WORDS * sizeof(char *));  // for the array of words
    if (!words) {
        fprintf(stderr, "Memory allocation error for words\n");
        return 1;
    }

    int i; 
    for (i = 0; i < MAX_WORDS; i++) {
        words[i] = malloc(MAX_WORD_LENGTH * sizeof(char));  // for each word
        if (!words[i]) {
            fprintf(stderr, "Memory allocation error for words[%d]\n", i);
            return 1;
        }
    }

    
    int n = read_words("words.txt", words);
    printf("Number of words read : %d\n", n);
    if (n == -1) return 1;

    // Creating the anagram list from the words
    AnagramNode *anagram_list = make_anagram_list(words, n);
    print_anagrams(anagram_list);  

    printf("\n set of anagrams with the most variants :\n");
    AnagramNode *max_group = NULL;
    int max_count = 0;
    
    // Find the anagram group with the most variants (words)
    AnagramNode *current; 
    for (current = anagram_list; current; current = current->next) {
        int count = 0;
        WordNode *w; 
        for (w = current->words; w; w = w->next) count++;  // Count the number of words in this group
        if (count > max_count) {
            max_count = count; 
            max_group = current;  
        }
    }
    if (max_group) {
        printf("Sorted key : %s -> ", max_group->key);
        WordNode *w; 
        for (w = max_group->words; w; w = w->next) {
            printf("%s ", w->word);  // Print the words in the group with the most variants
        }
        printf("\n");
    }

    printf("\n the set of the longest anagrams : ");
    char *longest1 = "", *longest2 = "";
    // Find the two longest words in the anagram list
    for (current = anagram_list; current; current = current->next) {
        if (current->words && current->words->next) {
            WordNode *w1, *w2; 
            for (w1 = current->words; w1; w1 = w1->next) {
                for (w2 = w1->next; w2; w2 = w2->next) {
                    if (strlen(w1->word) > strlen(longest1)) {
                        longest1 = w1->word;
                        longest2 = w2->word;
                    }
                }
            }
        }
    }
    printf("%s, %s\n", longest1, longest2);  // Print the two longest anagram words


    plot_histogram(anagram_list);  

    // Cleanup memory
    free_anagram_list(anagram_list);  // for the anagram list
    for (i = 0; i < MAX_WORDS; i++) free(words[i]);  // for each word
    free(words);  // for the words array
    return 0;
}
