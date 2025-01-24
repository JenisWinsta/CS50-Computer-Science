// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to get the index
    unsigned int index = hash(word);

    // Get the head of the linked list at that index
    node *cursor = table[index];

    // Traverse the linked list
    while (cursor != NULL)
    {
        // Compare the current word in the list with the input word (case-insensitively)
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // Word found
        }

        cursor = cursor->next; // Move to the next node
    }

    return false; // Word not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Convert the first character to lowercase to make the hash case-insensitive
    char first_letter = tolower(word[0]);

    // Ensure the character is a valid alphabet letter
    if (first_letter >= 'a' && first_letter <= 'z')
    {
        return first_letter - 'a'; // Return a number between 0 and 25
    }

    // Fallback for non-alphabetic characters
    return 0;
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1]; // Buffer to hold each word from the file

    // Read each word in the file
    while (fscanf(source, "%45s", word) != EOF) // Read words one at a time
    {
        // Create a new node for the word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false; // Return false if memory allocation fails
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the word to obtain its hash value
        unsigned int index = hash(word);

        // Insert the new node into the hash table
        new_node->next = table[index]; // Point the new node to the current head
        table[index] = new_node;       // Update the head to the new node
    }

    // Close the dictionary file
    fclose(source);
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Iterate through each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i]; // Start at the head of the linked list

        // Traverse the linked list and count nodes
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next; // Move to the next node
        }
    }

    return count; // Return the total word count
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Start at the head of the linked list
        node *cursor = table[i];

        // Traverse the linked list, freeing each node
        while (cursor != NULL)
        {
            node *temp = cursor;   // Save the current node
            cursor = cursor->next; // Move to the next node
            free(temp);            // Free the current node
        }

        // After freeing the list, set the bucket to NULL for safety
        table[i] = NULL;
    }

    return true; // Return true if all memory was successfully freed
}
