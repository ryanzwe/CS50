// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Represents a hash table
node *hashtable[N];
int wordsAddedToDictionary = 0;
FILE *dictionaryFile = NULL;
// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;//malloc(sizeof(node));//NULL;//
    }

    // Open dictionary
    dictionaryFile = fopen(dictionary, "r");
    if (dictionaryFile == NULL)
    {
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table TODO
    while (fscanf(dictionaryFile, "%s", word) != EOF)
    {
        //Create the node and copy the word into it if there's enough memory
        node *curWord = malloc(sizeof(node));
        curWord->next = NULL;
        if (curWord == NULL || word[0] == '\0')
        {
            unload();
            printf("%s", "unloaded");
            return false;
        }
        else
        {
            strcpy(curWord->word, word);
            wordsAddedToDictionary++;
        }
        // hash the new node into the hash table and set the root node to point to it by putting the new node at the start and taking the previous pointer
        int wordHash = hash(word);
        curWord->next = hashtable[wordHash];
        hashtable[wordHash] = curWord;
    }
    // Close dictionary
    fclose(dictionaryFile);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordsAddedToDictionary; // could also make a loaded ? 0 : num ternary
}
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the word then loop through that bucket and compare the word to the dictionary
    int letterHash = hash(&word[0]);
    for (node *n = hashtable[letterHash]; n != NULL; n = n->next)
    {
        if(!word)
        {
            return false;
        }
        if (strcasecmp (word, n->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
void testUnload(void)
{
    for (int i = 0; i < N; i++)
    {
        int ind = 0;
        for (node *nod = hashtable[i]; nod != NULL; nod = nod->next)
        {
            printf("Index: %i nodInd: %i, word %s \n", i, ind, nod->word);
            ind++;
        }
    }
}
bool unload(void)
{
    int rawr = 0;
    for (int i = 0; i < N; i++)
    {
        node *temp = NULL;
        node *loop = hashtable[i];
        while(loop != NULL)
        {
            temp = loop->next;
            free(loop);
            loop = temp;
        }
        free(loop);
    }
    //printf("Rawr %i",rawr);
    //testUnload();
    return true;
}
