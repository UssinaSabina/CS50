// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// number of buckets in hash table
const unsigned int N = 26;

// size of a dictionary (number of words)
int words_count = 0;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 algorithm by dan bernstein
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get the hush of the word
    int index = hash(word);

    // cursor that will traverse the linked list in the hush table
    node *cursor = table[index];

    // search for word
    while (cursor != NULL)
    {
        // If strcasecmp returns true, then word has been found
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // check whether the file opened correctly
    if (source == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Add each word to the hash table
        int index = hash(word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory to load dictionary\n");
            return false;
        }
        strcpy(n->word, word);
        n->next = table[index];
        table[index] = n;
        words_count++;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}

